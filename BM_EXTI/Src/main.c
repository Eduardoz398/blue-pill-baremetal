#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f1xx.h"
#include "gpio.h"
#include "interrupt.h"


void EXTI0_IRQHandler(void)
{
        GPIOA->ODR ^= (1 << 11);
        EXTI->PR = (1 << 0);
}

void EXTI9_5_IRQHandler(void)
{
        GPIOA->ODR ^= (1 << 12);
        EXTI->PR = (1 << 8);
}

void EXTI15_10_IRQHandler(void)
{
        GPIOB->ODR ^= (1 << 5);
        EXTI->PR = (1 << 10);
}

int main(void)
{
	//habilitar clock de GPIOA e GPIOB
    GPIO_EnableClock(IOPAEN);
    GPIO_EnableClock(IOPBEN);


    // configura pinos PA8, PB0, PB10 como entradas pull down
    GPIO_SetPinMode(GPIOA, 8, GPIO_INPUT_PULL);
    GPIOA->ODR &= ~(1 << 8);

    GPIO_SetPinMode(GPIOB, 0, GPIO_INPUT_PULL);
    GPIOB->ODR &= ~(1 << 0);

    GPIO_SetPinMode(GPIOB, 10, GPIO_INPUT_PULL);
    GPIOB->ODR &= ~(1 << 10);

    // configura pinos PA8, PA11, PB5 como entradas pull down
    GPIO_SetPinMode(GPIOA, 12, GPIO_OUTPUT_2MHZ_PP);
    GPIOA->ODR &= ~(1 << 12);
    GPIO_SetPinMode(GPIOA, 11, GPIO_OUTPUT_2MHZ_PP);
    GPIOA->ODR &= ~(1 << 11);

    GPIO_SetPinMode(GPIOB, 5, GPIO_OUTPUT_2MHZ_PP);
    GPIOB->ODR &= ~(1 << 5);

    //habilita e configura interrupção.
    GPIO_EnableInterrupt(GPIOA, 8, RISING_EDGE);
    GPIO_EnableInterrupt(GPIOB, 0, RISING_EDGE);
    GPIO_EnableInterrupt(GPIOB, 10, RISING_EDGE);

    NVIC_SetPriority(EXTI0_IRQn, 0x10);
    NVIC_EnableIRQ(EXTI0_IRQn);

    NVIC_SetPriority(EXTI9_5_IRQn, 0x10);
    NVIC_EnableIRQ(EXTI9_5_IRQn);

    NVIC_SetPriority(EXTI15_10_IRQn, 0x10);
    NVIC_EnableIRQ(EXTI15_10_IRQn);


    __enable_irq();

    while (1) {
    }
}

