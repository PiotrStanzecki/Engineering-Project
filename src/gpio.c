#include "gpio.h"



gpio_status gpio_init(gpio* init)
{
    
    if (init->port < 0 || init->port > 10 ) return GPIO_ERROR;
    if (init->pin < 0 || init->pin > 15 ) return GPIO_ERROR;

    RCC->AHB4ENR |= (1U << init->port);

    __DSB();
    
    GPIO_TypeDef* portSym;
    
    switch (init->port)
    {
        case port_A:
            portSym = GPIOA;
            break;
        case port_B:
            portSym = GPIOB;
            break;
        case port_C:
            portSym = GPIOC;
            break;
        case port_D:
            portSym = GPIOD;
            break;
        case port_E:
            portSym = GPIOE;
            break;
        case port_F:
            portSym = GPIOF;
            break;
        case port_G:
            portSym = GPIOG;
            break;
        case port_H:
            portSym = GPIOH;
            break;
        case port_I:
            portSym = GPIOI;
            break;
        case port_J:
            portSym = GPIOJ;
            break;
        case port_K:
            portSym = GPIOK;
            break;
        default:
            return GPIO_ERROR;
            break;
    }


    switch(init->mode)
    {
        case INPUT:
            portSym->MODER &= ~(3U << (init->pin * 2));
            break;
        case OUTPUT:
            portSym->MODER &= ~(3U << (init->pin * 2));
            portSym->MODER |=  (1U << (init->pin * 2));
            break;
        case ALTERNATE:
            portSym->MODER &= ~(3U << (init->pin * 2));
            portSym->MODER |=  (2U << (init->pin * 2));
            break;
        case ANALOG:
            //portSym->MODER &= ~(3U << (init->pin * 2));
            portSym->MODER |=  (3U << (init->pin * 2));
            break;
        default:
            return GPIO_ERROR;
    }


    switch(init->type)
    {
        case PUSH_PULL:
            portSym->OTYPER &= ~(1U << init->pin);
            break;
        case OPEN_DRAIN:
            portSym->OTYPER |=  (1U << init->pin);
            break;
        default:
            return GPIO_ERROR;
    }


    switch(init->speed)
    {
        case SPEED_LOW:
            portSym->OSPEEDR &= ~(3U << (init->pin * 2));
            break;
        case SPEED_MEDIUM:
            portSym->OSPEEDR &= ~(3U << (init->pin * 2));
            portSym->OSPEEDR |=  (1U << (init->pin * 2));
            break;
        case SPEED_HIGH:
            portSym->OSPEEDR &= ~(3U << (init->pin * 2));
            portSym->OSPEEDR |=  (2U << (init->pin * 2));
            break;
        case SPEED_VERY_HIGH:
            //portSym->OSPEEDR &= ~(3U << (init->pin * 2));
            portSym->OSPEEDR |=  (3U << (init->pin * 2));
            break;
        default:
            return GPIO_ERROR;
    }


    switch(init->pull)
    {
        case PULL_NONE:
            portSym->PUPDR &= ~(3U << (init->pin * 2));
            break;
        case PULL_UP:
            portSym->PUPDR &= ~(3U << (init->pin * 2));
            portSym->PUPDR |=  (1U << (init->pin * 2));
            break;
        case PULL_DOWN:
            portSym->PUPDR &= ~(3U << (init->pin * 2));
            portSym->PUPDR |=  (2U << (init->pin * 2));
            break;
        default:
            return GPIO_ERROR;
    }
    return GPIO_SUCCESS;
}


gpio_status gpio_write(GPIO_TypeDef* port, gpio_pin pin, gpio_state state)
{
    if(state == GPIO_SET)
    {
        port->BSRR |= (1U << pin);
    }
    else if(state == GPIO_RESET)
    {
        port->BSRR &= ~(1U << pin);
        port->BSRR |= (1U << (pin + 16));
    }
    else
    {
        return GPIO_ERROR;
    }
    
    return GPIO_SUCCESS;
}




gpio_status gpio_toggle(GPIO_TypeDef* port, gpio_pin pin)
{
    port->ODR ^= (1U << pin);

    return GPIO_SUCCESS;
}


gpio_state  gpio_read(GPIO_TypeDef* port, gpio_pin pin)
{
    if((port->IDR & (1U << pin)) != 0)
    {
        return GPIO_SET;
    }
    else
    {
        return GPIO_RESET;
    }

    return GPIO_RESET;
}


gpio_status gpio_set_af(GPIO_TypeDef* port, gpio_pin pin, gpio_alt af)
{
    if(pin > 15 || pin < 15 || af > 15 || af < 15)
    {
        return GPIO_ERROR;
    }

    uint8_t af_idx = (uint8_t) (pin >> 3);       // Which AF register is the pin in
    uint8_t pos = (pin % 8) * 4;                 // Position of bits in AF registers

    port->AFR[af_idx] &= ~(0xFU << pos);         // Clearing 4 bits (0xF = 0b1111)
    port->AFR[af_idx] |= ((uint32_t) af << pos); // Setting new value

    return GPIO_SUCCESS;

}