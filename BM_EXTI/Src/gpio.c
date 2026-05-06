#include "gpio.h"

void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode mode)
{
    if (pin > 15)
        return;

    if (pin < 8) {
        GPIOx->CRL &= ~(0xF << (pin * 4));
        GPIOx->CRL |=  ((uint32_t)mode << (pin * 4));
    } else {
        uint8_t __pin = pin - 8;
        GPIOx->CRH &= ~(0xF << (__pin * 4));
        GPIOx->CRH |=  ((uint32_t)mode << (__pin * 4));
    }
}

void GPIO_EnableClock(uint32_t bit_mask)
{
    RCC->APB2ENR |= bit_mask;
}

void GPIO_EnableInterrupt(GPIO_TypeDef* port, uint8_t pin, InterruptMode mode)
{
    if (pin > 15)
        return;

    if (mode == DISABLED) {
        EXTI_SetLineState(pin, false);
        return;
    }

    RCC->APB2ENR |= AFIOEN;

    uint8_t index = pin / 4;
    uint32_t pos = (pin % 4) * 4;

    uint32_t port_code = ((uint32_t)port - (uint32_t)GPIOA_BASE) / GPIO_OFFSET;

    AFIO->EXTICR[index] &= ~(0xF << pos);
    AFIO->EXTICR[index] |=  (port_code << pos);

    EXTI->PR = (1 << pin);

    switch (mode)
    {
    case RISING_EDGE:
        EXTI->RTSR |=  (1 << pin);
        EXTI->FTSR &= ~(1 << pin);
        break;

    case FALLING_EDGE:
        EXTI->FTSR |=  (1 << pin);
        EXTI->RTSR &= ~(1 << pin);
        break;

    case BOTH_EDGES:
        EXTI->RTSR |= (1 << pin);
        EXTI->FTSR |= (1 << pin);
        break;

    default:
        break;
    }

    EXTI_SetLineState(pin, true);
}
