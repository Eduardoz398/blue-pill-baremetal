

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "gpio.h"

int main()
{


    GPIO_EnableClock(IOPAEN);
    GPIO_EnableClock(IOPBEN);
    GPIO_SetPinMode(GPIOA, 8, GPIO_INPUT_PUPD);
    GPIO_SetPinMode(GPIOA, 9, GPIO_INPUT_PUPD);
    GPIO_SetPinMode(GPIOA, 10, GPIO_INPUT_PUPD);

    GPIOA->ODR &= ~((1 << 8) | (1 << 9) | (1 << 10));

    GPIO_SetPinMode(GPIOA, 11, GPIO_OUTPUT);
    GPIO_SetPinMode(GPIOA, 12, GPIO_OUTPUT);
    GPIO_SetPinMode(GPIOB, 5, GPIO_OUTPUT);

    /*/debug
    //GPIO_EnableClock(IOPCEN);
    //GPIOC->ODR &= ~(1 << 13);
	*/


        uint32_t prev_state = 0;

        const uint32_t PINS_MASK = (1 << 8) | (1 << 9) | (1 << 10);

        while (1)
        {
            uint32_t cur_state = GPIOA->IDR & PINS_MASK;

            uint32_t rising_edges = cur_state & ~prev_state;

            if (rising_edges & (1 << 8))
            {
                busy_wait_delay(5000);
                if (GPIOA->IDR & (1 << 8))
                {
                    GPIOA->ODR ^= (1 << 11);
                }
            }

            if (rising_edges & (1 << 9))
            {
                busy_wait_delay(5000);
                if (GPIOA->IDR & (1 << 9))
                {
                    GPIOA->ODR ^= (1 << 12);
                }
            }

            if (rising_edges & (1 << 10))
            {
                busy_wait_delay(5000);
                if (GPIOA->IDR & (1 << 10))
                {
                    GPIOB->ODR ^= (1 << 5);
                }
            }

            prev_state = cur_state;
        }
}
