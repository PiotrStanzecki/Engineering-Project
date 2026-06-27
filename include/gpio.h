#ifndef GPIO_H
#define GPIO_H

#include "stm32h750xx.h"

typedef enum
{
    port_A,
    port_B,
    port_C,
    port_D,
    port_E,
    port_F,
    port_G,
    port_H,
    port_I,
    port_J,
    port_K
}gpio_port;


typedef enum
{
    GPIO_ERROR = 0,
    GPIO_SUCCESS
}gpio_status;

typedef enum
{
    GPIO_RESET = 0,
    GPIO_SET
}gpio_state;

typedef enum
{
    INPUT = 0,
    OUTPUT,
    ALTERNATE,
    ANALOG
}gpio_mode;

typedef enum
{
    PUSH_PULL = 0,
    OPEN_DRAIN
}gpio_type;

typedef enum
{
    SPEED_LOW = 0,
    SPEED_MEDIUM,
    SPEED_HIGH,
    SPEED_VERY_HIGH
}gpio_speed;

typedef enum
{
    PULL_NONE = 0,
    PULL_UP,
    PULL_DOWN,
    reserved
}gpio_pull;

typedef enum
{
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
}gpio_alt;


typedef uint8_t gpio_pin;

typedef struct 
{
   gpio_mode mode;
   gpio_type type;
   gpio_speed speed;
   gpio_pull pull;
   gpio_alt  alt;
   gpio_pin pin;
   gpio_port port;
}gpio;


gpio_status gpio_init(gpio* init);

/**
 * 
 * @brief Function to write a value to a gpio pin
 * @param port Port of the gpio (GPIOA, GPIOB etc.)
 * @param pin Pin number
 * @param state State of a pin (GPIO_SET, GPIO_RESET)
 * 
 */
gpio_status gpio_write(GPIO_TypeDef* port, gpio_pin pin, gpio_state state);

/**
 * 
 * @brief Function to toggle the state of a gpio pin
 * @param port Port of the gpio (GPIOA, GPIOB etc.)
 * @param pin Pin number
 * 
 */
gpio_status gpio_toggle(GPIO_TypeDef* port, gpio_pin pin);

/**
 * 
 * @brief Function to read the state of a gpio pin
 * @param port Port of the gpio (GPIOA, GPIOB etc.)
 * @param pin Pin number
 * 
 */
gpio_state  gpio_read(GPIO_TypeDef* port, gpio_pin pin);
gpio_status gpio_set_af(GPIO_TypeDef* port, gpio_pin pin, gpio_alt af);




#endif /* GPIO_H */