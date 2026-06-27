#include "stm32h750xx.h"
#include "sys.h"

void delay_ms(uint32_t ms)
{

    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    
    DWT->LAR = 0xC5ACCE55; 
    
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;


    uint32_t end = ms * (SystemCoreClock / 1000U);
    uint32_t start = DWT->CYCCNT;

    while((DWT->CYCCNT - start) < end){}
}


void delay_us(uint32_t us)
{

    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    
    DWT->LAR = 0xC5ACCE55; 
    
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;


    uint32_t end = us * (SystemCoreClock / 1000000U);
    uint32_t start = DWT->CYCCNT;

    while((DWT->CYCCNT - start) < end){}
}


inline uint32_t getCurrentTime()
{
    return DWT->CYCCNT;
}