#include "stm32h750xx.h"
#include "gpio.h"
#include "usart.h"
#include "sai.h"
#include <stdint.h>
#include <string.h>



#define AUDIO_BUF_SAMPLES 256U
#define AUDIO_HALF        (AUDIO_BUF_SAMPLES / 2U)
#define DCACHE_LINE_SIZE  32U



__attribute__((aligned(32), section(".RAM_D2"))) static uint32_t audio_rx_buf[AUDIO_BUF_SAMPLES];

__attribute__((aligned(32), section(".RAM_D2"))) static uint32_t audio_tx_buf[AUDIO_BUF_SAMPLES];



static volatile uint8_t g_copy_first_half = 0U;
static volatile uint8_t g_copy_second_half = 0U;



// GPIO Configuration for SAI1

// Based on the Daisy Seed datasheet, SAI1 pins are PE2, PE3, PE4, PE5, PE6

static void sai_gpio_init(void) {
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN; // Enable Port E clock


    for (int i = 2; i <= 6; i++) 
    {
        GPIOE->MODER &= ~(3U << (i * 2));
        GPIOE->MODER |= (2U << (i * 2));      // Alternate Function Mode
        GPIOE->OSPEEDR |= (3U << (i * 2));    // Very High Speed

        // Configure AF6 for SAI1 
        if (i < 8) 
        {
            GPIOE->AFR[0] |= (6U << (i * 4));

        }
    }
}



static uint32_t is_dcache_enabled(void)
{
    return ((SCB->CCR & SCB_CCR_DC_Msk) != 0U) ? 1U : 0U;
}



static void dcache_invalidate_buffer(void *addr, uint32_t size)
{

#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    if (is_dcache_enabled() != 0U)
    {
        uintptr_t start = (uintptr_t)addr;
        uintptr_t aligned_start = start & ~((uintptr_t)DCACHE_LINE_SIZE - 1U);
        uintptr_t end = start + (uintptr_t)size;
        uintptr_t aligned_end = (end + DCACHE_LINE_SIZE - 1U) & ~((uintptr_t)DCACHE_LINE_SIZE - 1U);
        int32_t aligned_size = (int32_t)(aligned_end - aligned_start);
        SCB_InvalidateDCache_by_Addr((uint32_t*)aligned_start, aligned_size);
    }
#else
    (void)addr;
    (void)size;
#endif
}



static void dcache_clean_buffer(void *addr, uint32_t size)
{
#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)

    if (is_dcache_enabled() != 0U)
    {
        uintptr_t start = (uintptr_t)addr;
        uintptr_t aligned_start = start & ~((uintptr_t)DCACHE_LINE_SIZE - 1U);
        uintptr_t end = start + (uintptr_t)size;
        uintptr_t aligned_end = (end + DCACHE_LINE_SIZE - 1U) & ~((uintptr_t)DCACHE_LINE_SIZE - 1U);
        int32_t aligned_size = (int32_t)(aligned_end - aligned_start);
        SCB_CleanDCache_by_Addr((uint32_t*)aligned_start, aligned_size);
    }

#else
    (void)addr;
    (void)size;
#endif

}



static void copy_half(uint32_t dst_offset, uint32_t src_offset)
{
    memcpy(&audio_tx_buf[dst_offset], &audio_rx_buf[src_offset], AUDIO_HALF * sizeof(uint32_t));
    dcache_clean_buffer(&audio_tx_buf[dst_offset], AUDIO_HALF * sizeof(uint32_t));
}



static void rx_half_cplt(void) { g_copy_first_half = 1U; }

static void rx_cplt(void)      { g_copy_second_half = 1U; }



static sai_dma_handle_t sai1_rx_dma = {
    .stream       = DMA1_Stream0,
    .dmamux_req   = 88U,
    .mode         = SAI_DMA_CIRCULAR,
    .half_cplt_cb = rx_half_cplt,
    .cplt_cb      = rx_cplt
};



static sai_dma_handle_t sai1_tx_dma = {

    .stream       = DMA1_Stream1,
    .dmamux_req   = 87U,
    .mode         = SAI_DMA_CIRCULAR,
    .half_cplt_cb = 0,
    .cplt_cb      = 0

};



void DMA1_Stream0_IRQHandler(void)
{
    if (DMA1->LISR & DMA_LISR_HTIF0) 
    {
        DMA1->LIFCR |= DMA_LIFCR_CHTIF0;
        rx_half_cplt();
    }
    if (DMA1->LISR & DMA_LISR_TCIF0) 
    {
        DMA1->LIFCR |= DMA_LIFCR_CTCIF0;
        rx_cplt();
    }
}



static void audio_clock_init(void)
{
    RCC->CR |= RCC_CR_HSEON;

    while ((RCC->CR & RCC_CR_HSERDY) == 0U) {}


    RCC->CR &= ~RCC_CR_PLL2ON;

    while ((RCC->CR & RCC_CR_PLL2RDY) != 0U) {}

    RCC->PLLCKSELR &= ~(RCC_PLLCKSELR_DIVM2_Msk | RCC_PLLCKSELR_PLLSRC_Msk);
    RCC->PLLCKSELR |= (2U << RCC_PLLCKSELR_PLLSRC_Pos);
    RCC->PLLCKSELR |= (5U << RCC_PLLCKSELR_DIVM2_Pos);

    RCC->PLL2DIVR = 0U;
    RCC->PLL2DIVR |= ((49U - 1U) << RCC_PLL2DIVR_N2_Pos);
    RCC->PLL2DIVR |= ((2U - 1U) << RCC_PLL2DIVR_P2_Pos);
    RCC->PLL2DIVR |= ((2U - 1U) << RCC_PLL2DIVR_Q2_Pos);
    RCC->PLL2DIVR |= ((2U - 1U) << RCC_PLL2DIVR_R2_Pos);



    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLL2RGE_Msk | RCC_PLLCFGR_PLL2VCOSEL | RCC_PLLCFGR_DIVP2EN | RCC_PLLCFGR_DIVQ2EN | RCC_PLLCFGR_DIVR2EN);
    RCC->PLLCFGR |= (2U << RCC_PLLCFGR_PLL2RGE_Pos);
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLL2VCOSEL;
    RCC->PLLCFGR |= RCC_PLLCFGR_DIVP2EN | RCC_PLLCFGR_DIVQ2EN | RCC_PLLCFGR_DIVR2EN;


    RCC->CR |= RCC_CR_PLL2ON;

    while ((RCC->CR & RCC_CR_PLL2RDY) == 0U) {}

    RCC->D2CCIP1R &= ~RCC_D2CCIP1R_SAI1SEL_Msk;
    RCC->D2CCIP1R |= (1U << RCC_D2CCIP1R_SAI1SEL_Pos);

}



int main(void)
{

    sai_init_s sai_tx;
    sai_init_s sai_rx;

    // Initialize Clocks
    audio_clock_init();

   

    // Initialize GPIOs for SAI
    sai_gpio_init();



    sai_tx.instance    = SAI1_Block_A;
    sai_tx.mode        = SAI_MODE_MASTER_TX;
    sai_tx.sync_en     = SAI_SYNC_ASYNC;
    sai_tx.protocol    = SAI_PROTOCOL_LEFT_JUSTIFIED;
    sai_tx.data_size   = SAI_DATASIZE_24B;
    sai_tx.channel     = SAI_CH_STEREO;
    sai_tx.slot_count  = 2U;
    sai_tx.slot_size   = SAI_SLOT_SIZE_32B;
    sai_tx.mclk_enable = SAI_MCLK_ENABLE;
    sai_tx.mclk_div    = 24U;
    sai_tx.dma_enabled = 1U; 



    sai_rx.instance    = SAI1_Block_B;
    sai_rx.mode        = SAI_MODE_SLAVE_RX;
    sai_rx.sync_en     = SAI_SYNC_INTERNAL;
    sai_rx.protocol    = SAI_PROTOCOL_LEFT_JUSTIFIED;
    sai_rx.data_size   = SAI_DATASIZE_24B;
    sai_rx.channel     = SAI_CH_STEREO;
    sai_rx.slot_count  = 2U;
    sai_rx.slot_size   = SAI_SLOT_SIZE_32B;
    sai_rx.mclk_enable = SAI_MCLK_DISABLE;
    sai_rx.mclk_div    = 0U;
    sai_rx.dma_enabled = 1U; 



    memset(audio_rx_buf, 0, sizeof(audio_rx_buf));
    memset(audio_tx_buf, 0, sizeof(audio_tx_buf));



    if (sai_init(&sai_tx) != SAI_SUCCESS) while (1) {}
    if (sai_init(&sai_rx) != SAI_SUCCESS) while (1) {}



    dcache_clean_buffer(audio_tx_buf, sizeof(audio_tx_buf));
    dcache_invalidate_buffer(audio_rx_buf, sizeof(audio_rx_buf));

    if (sai_start_dma(SAI1_Block_A, &sai1_tx_dma) != SAI_SUCCESS) while (1) {}
    if (sai_start_dma(SAI1_Block_B, &sai1_rx_dma) != SAI_SUCCESS) while (1) {}

    NVIC_SetPriority(DMA1_Stream0_IRQn, 1U);
    NVIC_EnableIRQ(DMA1_Stream0_IRQn);



    if (sai_transmit_dma(SAI1_Block_A, audio_tx_buf, AUDIO_BUF_SAMPLES) != SAI_SUCCESS) while (1) {}
    if (sai_receive_dma(SAI1_Block_B, audio_rx_buf, AUDIO_BUF_SAMPLES) != SAI_SUCCESS) while (1) {}



    gpio gp;
    gp.pin = 11;
    gp.port = port_C;
    gp.mode = OUTPUT;
    gp.pull = PULL_NONE;
    gp.speed = SPEED_MEDIUM;

    gpio_init(&gp);
    gpio_write(GPIOC, 11, GPIO_SET);

    while (1)
    {

        if (g_copy_first_half != 0U)
        {
            g_copy_first_half = 0U;
            dcache_invalidate_buffer(&audio_rx_buf[0], AUDIO_HALF * sizeof(uint32_t));
            copy_half(0U, 0U);
        }



        if (g_copy_second_half != 0U)
        {
            g_copy_second_half = 0U;
            dcache_invalidate_buffer(&audio_rx_buf[AUDIO_HALF], AUDIO_HALF * sizeof(uint32_t));
            copy_half(AUDIO_HALF, AUDIO_HALF);
        }
    }
} 

