#include "usart.h"
#include <stddef.h>

// Lookup tables for clock dividers
static const uint8_t ahb_presc_table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
static const uint8_t apb_presc_table[8]  = {0, 0, 0, 0, 1, 2, 3, 4};

/**
 * @brief Calculates the exact frequency of the APB1 bus
 */
static uint32_t get_apb1_freq(void) {
    uint32_t hpre  = (RCC->D1CFGR & RCC_D1CFGR_HPRE) >> RCC_D1CFGR_HPRE_Pos;
    uint32_t ppre1 = (RCC->D2CFGR & RCC_D2CFGR_D2PPRE1) >> RCC_D2CFGR_D2PPRE1_Pos;
    
    uint32_t hclk  = SystemCoreClock >> ahb_presc_table[hpre];
    return hclk >> apb_presc_table[ppre1];
}

/**
 * @brief Calculates the exact frequency of the APB2 bus 
 */
static uint32_t get_apb2_freq(void) {
    uint32_t hpre  = (RCC->D1CFGR & RCC_D1CFGR_HPRE) >> RCC_D1CFGR_HPRE_Pos;
    uint32_t ppre2 = (RCC->D2CFGR & RCC_D2CFGR_D2PPRE2) >> RCC_D2CFGR_D2PPRE2_Pos;
    
    uint32_t hclk  = SystemCoreClock >> ahb_presc_table[hpre];
    return hclk >> apb_presc_table[ppre2];
}

usart_status usart_init(usart_init_s* usart)
{
    uint32_t bus_freq = 0;

    if(usart == NULL || usart->instance == NULL)
    {
        return USART_ERROR;
    }

    // Clock configuration
    if (usart->instance == USART1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        bus_freq = get_apb2_freq();
    }
    else if(usart->instance == USART2)
    {
        RCC->APB1LENR |= RCC_APB1LENR_USART2EN;
        bus_freq = get_apb1_freq();
    }
    else if(usart->instance == USART3)
    {
        RCC->APB1LENR |= RCC_APB1LENR_USART3EN;
        bus_freq = get_apb1_freq();
    }
    else if(usart->instance == UART4)
    {
        RCC->APB1LENR |= RCC_APB1LENR_UART4EN;
        bus_freq = get_apb1_freq();
    }
    else if(usart->instance == UART5)
    {
        RCC->APB1LENR |= RCC_APB1LENR_UART5EN;
        bus_freq = get_apb1_freq();
    }
    else if(usart->instance == USART6)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
        bus_freq = get_apb2_freq();
    }
    else if(usart->instance == UART7)
    {
        RCC->APB1LENR |= RCC_APB1LENR_UART7EN;
        bus_freq = get_apb1_freq();
    }
    else if(usart->instance == UART8)
    {
        RCC->APB1LENR |= RCC_APB1LENR_UART8EN;
        bus_freq = get_apb1_freq();
    }
    else 
    {
        return USART_ERROR;
    }

    
    __DSB();

    // Disabling uart
    usart->instance->CR1 &= ~USART_CR1_UE;

    // Word length
    usart->instance->CR1 &= ~(USART_CR1_M0 | USART_CR1_M1);
    if (usart->word_length == USART_WORDLEN_9B) 
    {
        usart->instance->CR1 |= USART_CR1_M0;
    } 
    else if (usart->word_length == USART_WORDLEN_7B) 
    {
        usart->instance->CR1 |= USART_CR1_M1;
    }
    else if (usart->word_length == USART_WORDLEN_8B)
    {
        // 8B is 00, already cleared by mask
    }
    else
    {
        return USART_ERROR;
    }

    // Parity
    usart->instance->CR1 &= ~(USART_CR1_PCE | USART_CR1_PS);
    if (usart->parity == USART_PARITY_EVEN) 
    {
        usart->instance->CR1 |= USART_CR1_PCE; 
    } 
    else if (usart->parity == USART_PARITY_ODD) 
    {
        usart->instance->CR1 |= (USART_CR1_PCE | USART_CR1_PS);
    }
    else if (usart->parity == USART_PARITY_NONE)
    {
        // NONE is 00, already cleared by mask
    }
    else
    {
        return USART_ERROR;
    }

    // Stop bits
    usart->instance->CR2 &= ~USART_CR2_STOP;
    if (usart->stop_bits == USART_STOPBITS_1)
    {
        usart->instance->CR2 |= (USART_STOPBITS_1 << USART_CR2_STOP_Pos);
    }
    else if (usart->stop_bits == USART_STOPBITS_0_5)
    {
        usart->instance->CR2 |= (USART_STOPBITS_0_5 << USART_CR2_STOP_Pos);
    }
    else if (usart->stop_bits == USART_STOPBITS_2)
    {
        usart->instance->CR2 |= (USART_STOPBITS_2 << USART_CR2_STOP_Pos);
    }
    else if (usart->stop_bits == USART_STOPBITS_1_5)
    {
        usart->instance->CR2 |= (USART_STOPBITS_1_5 << USART_CR2_STOP_Pos);
    }
    else
    {
        return USART_ERROR;
    }

    // Hardware flow control
    usart->instance->CR3 &= ~(USART_CR3_RTSE | USART_CR3_CTSE);
    if (usart->hw_flow_ctrl == USART_HWCONTROL_RTS) 
    {
        usart->instance->CR3 |= USART_CR3_RTSE;
    } 
    else if (usart->hw_flow_ctrl == USART_HWCONTROL_CTS) 
    {
        usart->instance->CR3 |= USART_CR3_CTSE;
    } 
    else if (usart->hw_flow_ctrl == USART_HWCONTROL_RTS_CTS) 
    {
        usart->instance->CR3 |= (USART_CR3_RTSE | USART_CR3_CTSE);
    }
    else if (usart->hw_flow_ctrl == USART_HWCONTROL_NONE)
    {
        // NONE is 00, already cleared by mask
    }
    else
    {
        return USART_ERROR;
    }
    
    // Oversampling
    usart->instance->CR1 &= ~USART_CR1_OVER8;
    if (usart->oversampling == USART_OVERSAMPLING_8) 
    {
        usart->instance->CR1 |= USART_CR1_OVER8;
    }
    else if (usart->oversampling == USART_OVERSAMPLING_16)
    {
        // 16 is 0, already cleared by mask
    }
    else
    {
        return USART_ERROR;
    }


    // Mode (TX, RX)
    usart->instance->CR1 &= ~(USART_CR1_TE | USART_CR1_RE);
    if (usart->mode == USART_MODE_TX) 
    {
        usart->instance->CR1 |= USART_CR1_TE;
    } 
    else if (usart->mode == USART_MODE_RX) 
    {
        usart->instance->CR1 |= USART_CR1_RE;
    } 
    else if (usart->mode == USART_MODE_TX_RX) 
    {
        usart->instance->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    }
    else
    {
        return USART_ERROR;
    }
 
    // Baudrate
    if (usart->baud_rate == 0)
    {
        return USART_ERROR;
    }

    if (usart->oversampling == USART_OVERSAMPLING_16) 
    {
        usart->instance->BRR = bus_freq / usart->baud_rate;
    } 
    else 
    {
        uint32_t usartdiv = (2 * bus_freq) / usart->baud_rate;
        usart->instance->BRR = ((usartdiv & 0xFFF0) | ((usartdiv & 0x000F) >> 1));
    }

    
    // Enable uart
    usart->instance->CR1 |= USART_CR1_UE;

    if (usart->mode == USART_MODE_TX || usart->mode == USART_MODE_TX_RX)
    {
        while (!(usart->instance->ISR & USART_ISR_TEACK)) {}
    }

    if (usart->mode == USART_MODE_RX || usart->mode == USART_MODE_TX_RX)
    {
        while (!(usart->instance->ISR & USART_ISR_REACK)) {}
    }


    
    return USART_SUCCESS;
}


usart_status usart_send_char(const char c, USART_TypeDef* usart, uint32_t timeout)
{
    if(usart == NULL)
    {
        return USART_ERROR;
    }

    while(!(usart->ISR & USART_ISR_TXE_TXFNF))
    {
        if(--timeout == 0)
        {
            return USART_ERROR;
        }
    }

    usart->TDR = c;

    return USART_SUCCESS;
}


usart_status usart_print(const char* c, USART_TypeDef* usart, uint32_t timeout)
{
    if (c == NULL || usart == NULL)
    {
        return USART_ERROR;
    }

    while (*c != '\0')
    {
        if (usart_send_char(*c++, usart, timeout) != USART_SUCCESS)
        {
            return USART_ERROR;
        }
    }

    while (!(usart->ISR & USART_ISR_TC))
    {
        if (--timeout == 0)
        {
            return USART_ERROR;
        }
    }

    return USART_SUCCESS;
}