#include "sai.h"
#include <stddef.h>

#define SAI_FLVL_EMPTY      (0x0UL << SAI_xSR_FLVL_Pos)
#define SAI_FLVL_FULL       (0x5UL << SAI_xSR_FLVL_Pos)
#define SAI_FLVL_GET(sr)    ((sr) & SAI_xSR_FLVL)
#define SAI_DISABLE_TIMEOUT 10000UL
#define SAI_DMA_MAX_HANDLES 6U

typedef struct {
    SAI_Block_TypeDef* block;
    sai_dma_handle_t*  handle;
} sai_dma_entry_t;

static sai_dma_entry_t s_dma_table[SAI_DMA_MAX_HANDLES];
static uint8_t s_dma_count = 0U;

static sai_dma_handle_t* find_handle(const SAI_Block_TypeDef* block)
{
    uint8_t i;
    for (i = 0U; i < s_dma_count; i++)
    {
        if (s_dma_table[i].block == block)
            return s_dma_table[i].handle;
    }
    return NULL;
}

static uint8_t datasize_to_bits(sai_datasize ds)
{
    switch (ds)
    {
        case SAI_DATASIZE_8B:  return 8U;
        case SAI_DATASIZE_10B: return 10U;
        case SAI_DATASIZE_16B: return 16U;
        case SAI_DATASIZE_20B: return 20U;
        case SAI_DATASIZE_24B: return 24U;
        case SAI_DATASIZE_32B: return 32U;
        default:               return 0U;
    }
}

static sai_status enable_sai_clock(const SAI_Block_TypeDef* instance)
{
    if ((instance == SAI1_Block_A) || (instance == SAI1_Block_B))
        RCC->APB2ENR |= RCC_APB2ENR_SAI1EN;
    else if ((instance == SAI2_Block_A) || (instance == SAI2_Block_B))
        RCC->APB2ENR |= RCC_APB2ENR_SAI2EN;
    else if ((instance == SAI3_Block_A) || (instance == SAI3_Block_B))
        RCC->APB2ENR |= RCC_APB2ENR_SAI3EN;
    else
        return SAI_ERROR;

    __DSB();
    return SAI_SUCCESS;
}

static void enable_dma_clock(const DMA_Stream_TypeDef* stream)
{
    if (((uint32_t)stream >= DMA1_BASE) && ((uint32_t)stream < DMA2_BASE))
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    else
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    __DSB();
}

static DMAMUX_Channel_TypeDef* get_dmamux_channel(const DMA_Stream_TypeDef* stream)
{
    uint32_t stream_index;

    if (((uint32_t)stream >= DMA1_BASE) && ((uint32_t)stream < DMA2_BASE))
        stream_index = ((uint32_t)stream - (uint32_t)DMA1_Stream0) / sizeof(DMA_Stream_TypeDef);
    else
        stream_index = 8U + (((uint32_t)stream - (uint32_t)DMA2_Stream0) / sizeof(DMA_Stream_TypeDef));

    return (DMAMUX_Channel_TypeDef*)(DMAMUX1_BASE + stream_index * sizeof(DMAMUX_Channel_TypeDef));
}

sai_status sai_init(const sai_init_s* sai)
{
    uint8_t data_bits;
    uint32_t dis_timeout;
    uint32_t cr1_val;
    uint32_t frame_len;
    uint32_t fs_active;
    uint32_t frcr_val;
    uint32_t slotr_val;
    uint32_t slotsz_enc;
    uint32_t slot_mask;
    uint32_t fboff;

    if ((sai == NULL) || (sai->instance == NULL))
        return SAI_ERROR;

    data_bits = datasize_to_bits(sai->data_size);
    if (data_bits == 0U)
        return SAI_ERROR;
    if ((sai->slot_count == 0U) || (sai->slot_count > 16U))
        return SAI_ERROR;
    if ((sai->slot_size != SAI_SLOT_SIZE_16B) && (sai->slot_size != SAI_SLOT_SIZE_32B))
        return SAI_ERROR;
    if ((uint32_t)sai->slot_size < (uint32_t)data_bits)
        return SAI_ERROR;

    if (enable_sai_clock(sai->instance) != SAI_SUCCESS)
        return SAI_ERROR;

    sai->instance->CR1 &= ~SAI_xCR1_SAIEN;
    dis_timeout = SAI_DISABLE_TIMEOUT;
    while ((sai->instance->CR1 & SAI_xCR1_SAIEN) != 0U)
    {
        if (dis_timeout-- == 0U)
            return SAI_ERROR;
    }

    sai->instance->CR2 = 0U;
    sai->instance->FRCR = 0U;
    sai->instance->SLOTR = 0U;
    sai->instance->IMR = 0U;
    sai->instance->CLRFR = 0xFFFFFFFFUL;

    cr1_val = sai->instance->CR1;
    cr1_val &= ~(SAI_xCR1_MODE | SAI_xCR1_PRTCFG | SAI_xCR1_DS | SAI_xCR1_LSBFIRST |
                 SAI_xCR1_CKSTR | SAI_xCR1_SYNCEN | SAI_xCR1_MONO | SAI_xCR1_OUTDRIV |
                 SAI_xCR1_DMAEN | SAI_xCR1_NODIV | SAI_xCR1_MCKDIV | SAI_xCR1_MCKEN);

    cr1_val |= ((uint32_t)sai->mode << SAI_xCR1_MODE_Pos);
    cr1_val |= ((uint32_t)sai->sync_en << SAI_xCR1_SYNCEN_Pos);
    cr1_val |= ((uint32_t)sai->data_size << SAI_xCR1_DS_Pos);

    if (sai->channel == SAI_CH_MONO)
        cr1_val |= SAI_xCR1_MONO;

    if ((sai->mode == SAI_MODE_MASTER_TX) || (sai->mode == SAI_MODE_MASTER_RX))
        cr1_val |= SAI_xCR1_OUTDRIV;

    if (sai->mclk_enable == SAI_MCLK_ENABLE)
    {
        cr1_val |= SAI_xCR1_MCKEN;
        cr1_val |= ((uint32_t)(sai->mclk_div & 0x0FU) << SAI_xCR1_MCKDIV_Pos);
    }
    else
    {
        cr1_val |= SAI_xCR1_NODIV;
    }

    frame_len = (uint32_t)sai->slot_size * (uint32_t)sai->slot_count;
    fs_active = frame_len / 2U;

    frcr_val = 0U;
    frcr_val |= ((frame_len - 1U) << SAI_xFRCR_FRL_Pos);
    frcr_val |= ((fs_active - 1U) << SAI_xFRCR_FSALL_Pos);

    slotr_val = 0U;
    slotr_val |= ((uint32_t)(sai->slot_count - 1U) << SAI_xSLOTR_NBSLOT_Pos);
    slotsz_enc = (sai->slot_size == SAI_SLOT_SIZE_16B) ? 1U : 2U;
    slotr_val |= (slotsz_enc << SAI_xSLOTR_SLOTSZ_Pos);
    slot_mask = (1UL << sai->slot_count) - 1UL;
    slotr_val |= (slot_mask << SAI_xSLOTR_SLOTEN_Pos);

    switch (sai->protocol)
    {
        case SAI_PROTOCOL_I2S_PHILIPS:
            cr1_val &= ~SAI_xCR1_CKSTR;
            frcr_val |= SAI_xFRCR_FSDEF;
            frcr_val |= SAI_xFRCR_FSPOL;
            frcr_val |= SAI_xFRCR_FSOFF;
            fboff = 0U;
            slotr_val |= (fboff << SAI_xSLOTR_FBOFF_Pos);
            break;

        case SAI_PROTOCOL_LEFT_JUSTIFIED:
            cr1_val &= ~SAI_xCR1_CKSTR;
            frcr_val |= SAI_xFRCR_FSDEF;
            frcr_val |= SAI_xFRCR_FSPOL;
            frcr_val &= ~SAI_xFRCR_FSOFF;
            fboff = 0U;
            slotr_val |= (fboff << SAI_xSLOTR_FBOFF_Pos);
            break;

        case SAI_PROTOCOL_LSB_JUSTIFIED:
            cr1_val &= ~SAI_xCR1_CKSTR;
            frcr_val |= SAI_xFRCR_FSDEF;
            frcr_val |= SAI_xFRCR_FSPOL;
            frcr_val &= ~SAI_xFRCR_FSOFF;
            fboff = (uint32_t)sai->slot_size - (uint32_t)data_bits;
            slotr_val |= (fboff << SAI_xSLOTR_FBOFF_Pos);
            break;

        default:
            return SAI_ERROR;
    }

    sai->instance->CR1 = cr1_val;
    sai->instance->FRCR = frcr_val;
    sai->instance->SLOTR = slotr_val;
    sai->instance->CR1 |= SAI_xCR1_SAIEN;

    return SAI_SUCCESS;
}

sai_status sai_transmit(SAI_Block_TypeDef* sai_block, const uint32_t* data, uint16_t size, uint32_t timeout)
{
    uint16_t i;
    if ((sai_block == NULL) || (data == NULL) || (size == 0U))
        return SAI_ERROR;

    for (i = 0U; i < size; i++)
    {
        uint32_t tickstart = timeout;
        while (SAI_FLVL_GET(sai_block->SR) >= SAI_FLVL_FULL)
        {
            if (tickstart-- == 0U)
                return SAI_ERROR;
        }
        sai_block->DR = data[i];
    }
    return SAI_SUCCESS;
}

sai_status sai_receive(SAI_Block_TypeDef* sai_block, uint32_t* data, uint16_t size, uint32_t timeout)
{
    uint16_t i;
    if ((sai_block == NULL) || (data == NULL) || (size == 0U))
        return SAI_ERROR;

    for (i = 0U; i < size; i++)
    {
        uint32_t tickstart = timeout;
        while (SAI_FLVL_GET(sai_block->SR) == SAI_FLVL_EMPTY)
        {
            if (tickstart-- == 0U)
            {
                return SAI_ERROR;
            }
        }
        data[i] = sai_block->DR;
    }
    return SAI_SUCCESS;
}

sai_status sai_start_dma(SAI_Block_TypeDef* sai_block, sai_dma_handle_t* handle)
{
    uint32_t timeout;
    DMAMUX_Channel_TypeDef* mux;
    uint32_t cr;
    uint32_t stream_num;
    volatile uint32_t* clr_reg;
    uint32_t shift;

    if ((sai_block == NULL) || (handle == NULL) || (handle->stream == NULL))
        return SAI_ERROR;
    if (s_dma_count >= SAI_DMA_MAX_HANDLES)
        return SAI_ERROR;

    enable_dma_clock(handle->stream);

    handle->stream->CR &= ~DMA_SxCR_EN;
    timeout = 10000U;
    while ((handle->stream->CR & DMA_SxCR_EN) != 0U)
    {
        if (timeout-- == 0U)
            return SAI_ERROR;
    }

    if (((uint32_t)handle->stream >= (uint32_t)DMA1_Stream0) && ((uint32_t)handle->stream <= (uint32_t)DMA1_Stream7))
    {
        stream_num = ((uint32_t)handle->stream - (uint32_t)DMA1_Stream0) / sizeof(DMA_Stream_TypeDef);
        clr_reg = (stream_num < 4U) ? &DMA1->LIFCR : &DMA1->HIFCR;
    }
    else
    {
        stream_num = ((uint32_t)handle->stream - (uint32_t)DMA2_Stream0) / sizeof(DMA_Stream_TypeDef);
        clr_reg = (stream_num < 4U) ? &DMA2->LIFCR : &DMA2->HIFCR;
    }
    shift = (stream_num % 4U == 0U) ? 0U : (stream_num % 4U == 1U) ? 6U : (stream_num % 4U == 2U) ? 16U : 22U;
    *clr_reg = (0x3DUL << shift);

    mux = get_dmamux_channel(handle->stream);
    mux->CCR = (handle->dmamux_req & DMAMUX_CxCR_DMAREQ_ID);

    cr = 0U;
    cr |= DMA_SxCR_PL_1;
    cr |= DMA_SxCR_MSIZE_1;
    cr |= DMA_SxCR_PSIZE_1;
    cr |= DMA_SxCR_MINC;
    if (handle->mode == SAI_DMA_CIRCULAR)
        cr |= DMA_SxCR_CIRC;
    cr |= DMA_SxCR_TCIE | DMA_SxCR_HTIE | DMA_SxCR_TEIE;

    handle->stream->CR = cr;
    handle->stream->FCR = 0U;
    handle->stream->PAR = (uint32_t)&sai_block->DR;

    sai_block->CR1 |= SAI_xCR1_DMAEN;

    s_dma_table[s_dma_count].block = sai_block;
    s_dma_table[s_dma_count].handle = handle;
    s_dma_count++;

    return SAI_SUCCESS;
}

sai_status sai_transmit_dma(SAI_Block_TypeDef* sai_block, const uint32_t* data, uint16_t size)
{
    sai_dma_handle_t* h;
    uint32_t timeout;

    if ((sai_block == NULL) || (data == NULL) || (size == 0U))
        return SAI_ERROR;

    h = find_handle(sai_block);
    if (h == NULL)
        return SAI_ERROR;

    h->stream->CR &= ~DMA_SxCR_EN;
    timeout = 10000U;
    while ((h->stream->CR & DMA_SxCR_EN) != 0U)
    {
        if (timeout-- == 0U)
            return SAI_ERROR;
    }

    h->stream->M0AR = (uint32_t)data;
    h->stream->NDTR = size;
    h->stream->CR |= DMA_SxCR_DIR_0;
    h->stream->CR &= ~DMA_SxCR_DIR_1;
    h->stream->CR |= DMA_SxCR_EN;

    return SAI_SUCCESS;
}

sai_status sai_receive_dma(SAI_Block_TypeDef* sai_block, uint32_t* data, uint16_t size)
{
    sai_dma_handle_t* h;
    uint32_t timeout;

    if ((sai_block == NULL) || (data == NULL) || (size == 0U))
        return SAI_ERROR;

    h = find_handle(sai_block);
    if (h == NULL)
        return SAI_ERROR;

    h->stream->CR &= ~DMA_SxCR_EN;
    timeout = 10000U;
    while ((h->stream->CR & DMA_SxCR_EN) != 0U)
    {
        if (timeout-- == 0U)
            return SAI_ERROR;
    }

    h->stream->M0AR = (uint32_t)data;
    h->stream->NDTR = size;
    h->stream->CR &= ~(DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1);
    h->stream->CR |= DMA_SxCR_EN;

    return SAI_SUCCESS;
}

sai_status sai_stop_dma(SAI_Block_TypeDef* sai_block)
{
    sai_dma_handle_t* h;
    if (sai_block == NULL)
        return SAI_ERROR;

    h = find_handle(sai_block);
    if (h == NULL)
        return SAI_ERROR;

    h->stream->CR &= ~DMA_SxCR_EN;
    sai_block->CR1 &= ~SAI_xCR1_DMAEN;
    return SAI_SUCCESS;
}

void sai_dma_irq_handler(SAI_Block_TypeDef* sai_block)
{
    sai_dma_handle_t* h;
    DMA_Stream_TypeDef* stream;
    uint32_t stream_num;
    DMA_TypeDef* dma;
    uint32_t shift;
    volatile uint32_t* isr_reg;
    volatile uint32_t* clr_reg;
    uint32_t isr;

    h = find_handle(sai_block);
    if (h == NULL)
        return;

    stream = h->stream;

    if (((uint32_t)stream >= (uint32_t)DMA1_Stream0) && ((uint32_t)stream <= (uint32_t)DMA1_Stream7))
    {
        dma = DMA1;
        stream_num = ((uint32_t)stream - (uint32_t)DMA1_Stream0) / sizeof(DMA_Stream_TypeDef);
    }
    else
    {
        dma = DMA2;
        stream_num = ((uint32_t)stream - (uint32_t)DMA2_Stream0) / sizeof(DMA_Stream_TypeDef);
    }

    shift = (stream_num % 4U == 0U) ? 0U : (stream_num % 4U == 1U) ? 6U : (stream_num % 4U == 2U) ? 16U : 22U;
    isr_reg = (stream_num < 4U) ? (volatile uint32_t*)&dma->LISR : (volatile uint32_t*)&dma->HISR;
    clr_reg = (stream_num < 4U) ? (volatile uint32_t*)&dma->LIFCR : (volatile uint32_t*)&dma->HIFCR;
    isr = *isr_reg;

    if ((isr >> shift) & DMA_LISR_TEIF0)
    {
        *clr_reg = (DMA_LIFCR_CTEIF0 << shift);
        return;
    }

    if ((isr >> shift) & DMA_LISR_HTIF0)
    {
        *clr_reg = (DMA_LIFCR_CHTIF0 << shift);
        if (h->half_cplt_cb != NULL)
            h->half_cplt_cb();
    }

    if ((isr >> shift) & DMA_LISR_TCIF0)
    {
        *clr_reg = (DMA_LIFCR_CTCIF0 << shift);
        if (h->cplt_cb != NULL)
            h->cplt_cb();
    }
}
