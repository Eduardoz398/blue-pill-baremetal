#include "gpio.h"


void inline GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode mode) {
    if(pin > 15 )
        return;
    if (pin < 8) {
        GPIOx->CRL &= ~(0xF << (pin*4));
        GPIOx->CRL |= (mode << (pin*4));
        return;
    }
    uint32_t __pin = pin - 8;
    GPIOx->CRH &= ~(0xF << (__pin*4));
    GPIOx->CRH |= (mode << (__pin*4));
}


void GPIO_EnableClock(uint32_t bit_mask) {
    RCC->RCC_APB2ENR |= bit_mask;
}


void busy_wait_delay(uint32_t time)
{
    for(int i = 0; i < time; i++);
}
