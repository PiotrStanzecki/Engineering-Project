#ifndef SYS_H
#define SYS_H

#include "stm32h750xx.h"

/**
 * 
 * @brief Blocking delay function
 * @param ms Time in milliseconds
 * 
 */
void delay_ms(uint32_t ms);

/**
 * 
 * @brief Blocking delay function
 * @param us Time in microseconds
 * 
 */
void delay_us(uint32_t us);

/**
 * 
 * @brief Function to get current time
 * @return Current time stamp
 * 
 */
inline uint32_t getCurrentTime();

#endif  /* SYS_H */