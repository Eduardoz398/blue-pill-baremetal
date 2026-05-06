#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "clock.h"
#include "interrupt.h"
#include "stm32f1xx.h"

#define GPIO_OFFSET 0x400

typedef enum {
    GPIO_INPUT_FLOATING  = 0x4,
    GPIO_INPUT_PULL      = 0x8,
    GPIO_OUTPUT_50MHZ_PP = 0x3,
    GPIO_OUTPUT_2MHZ_PP  = 0x2
} GPIO_Mode;

typedef enum {
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGES,
    DISABLED
} InterruptMode;

void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode mode);
void GPIO_EnableClock(uint32_t bit_mask);
void GPIO_EnableInterrupt(GPIO_TypeDef* port, uint8_t pin, InterruptMode mode);

#endif
