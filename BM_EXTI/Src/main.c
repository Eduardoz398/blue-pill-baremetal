#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f1xx.h"
#include "gpio.h"
#include "interrupt.h"

void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR & (1 << 8)) {
        GPIOA->ODR ^= (1 << 12);  // alterna LED em PA12
        EXTI->PR = (1 << 8);      // limpa pending da EXTI8
    }
}

int main(void)
{
    GPIO_EnableClock(IOPAEN);

    GPIO_SetPinMode(GPIOA, 8, GPIO_INPUT_PULL);
    GPIOA->ODR &= ~(1 << 8);      // ODR=0 em entrada pull => pull-down

    GPIO_SetPinMode(GPIOA, 12, GPIO_OUTPUT_2MHZ_PP);
    GPIOA->ODR &= ~(1 << 12);     // LED começa apagado

    // PA8 gera EXTI8 por borda de subida
    GPIO_EnableInterrupt(GPIOA, 8, RISING_EDGE);

    NVIC_SetPriority(EXTI9_5_IRQn, 0x10);
    NVIC_EnableIRQ(EXTI9_5_IRQn);

    __enable_irq();

    while (1) {
    }
}
