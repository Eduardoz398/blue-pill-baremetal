#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "utils.h"
#include "stm32f1xx.h"



int SysTick_TASK = 0;
int TIM2_TASK = 0;

uint32_t count = 0;
const uint32_t color_table[] = { red, green, blue, yellow, cyan, purple, white };

void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF)
	{

		TIM2_TASK = 1;
		TIM2->SR &=~TIM_SR_UIF;
	}

}

void SysTick_Handler(void)
{
	// Do stuff
	SysTick_TASK = 1;
}


static inline void Init_Gpio(void) {
	RCC->APB2ENR |= (1 << 2);
    // PA11
    GPIOA->CRH &= ~((uint32_t)0xF << ((PA11 - 8) * 4));
    GPIOA->CRH |=  ((uint32_t)GPIO_OUTPUT_2MHZ_PP << ((PA11 - 8) * 4));
    GPIOA->ODR &= ~(1 << PA11);

    // PA12
    GPIOA->CRH &= ~((uint32_t)0xF << ((PA12 - 8) * 4));
    GPIOA->CRH |=  ((uint32_t)GPIO_OUTPUT_2MHZ_PP << ((PA12 - 8) * 4));
    GPIOA->ODR &= ~(1 << PA12);

    // PA15
	RCC->APB2ENR |= (1 << 0);
	AFIO->MAPR |= (2 << 24);
    GPIOA->CRH &= ~((uint32_t)0xF << ((PA15 - 8) * 4));
    GPIOA->CRH |=  ((uint32_t)GPIO_OUTPUT_2MHZ_PP << ((PA15 - 8) * 4));
    GPIOA->ODR &= ~(1 << PA15);


    //cor inicial
    GPIOA->ODR |= color_table[count];

}


void Init_SysTick(void) {

	const uint32_t ticks = 500000;
	if ((ticks - 1UL) <= 0xFFFFFFUL)
	{
		 /* set reload register */
		SysTick->LOAD  = (uint32_t)(ticks - 1UL);

		SysTick->VAL   = 0UL;			/* Load the SysTick Counter Value */

		SysTick->CTRL  = (0 << 2) |		/* 0 -> SysTick_Clock = AHB/8 */
						 (1 << 1) |	 	/* Enable SysTick IRQ and SysTick Timer */
						 (1 << 0);
	}

}
static inline void Switch_Color(void) {
    count = (count + 1) % 7;
    GPIOA->ODR &= ~((1 << 11) | (1 << 12) | (1 << 15));
    GPIOA->ODR |= color_table[count];
}

static inline void blink(void) {
    GPIOA->ODR ^= color_table[count];
}

void Init_Timer(void) {
	// Enable clock access to timer2
	    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;


	    // Configure timer2
		TIM2->PSC = 8000-1; 	//8000000/8000 =1000 i.e. 1ms
		TIM2->ARR = 2000-1; 	//count up to 2000 which is 1 second

		TIM2->EGR |= TIM_EGR_UG; //Reinitialize the counter and generates an update of the registers
		TIM2->SR &= ~TIM_SR_UIF;

		/* Set UIE(Update interrupt enable) bit
		 * in TIMx DMA/Interrupt enable register (TIMx_DIER)
		 * to enable timer interrupt*/
		TIM2->DIER |= TIM_DIER_UIE;

		// Enable timer2 interrupt in NVIC
		NVIC_EnableIRQ(TIM2_IRQn);

		// Enable the timer
		TIM2->CR1 |= TIM_CR1_CEN;
}
int main(void)
{
	Init_Gpio();
	Init_Timer();
 	Init_SysTick();



	while(1)
	{
		if(TIM2_TASK) {
			TIM2_TASK = 0;
			Switch_Color();
			SysTick->VAL = 0UL;
			SysTick_TASK = 0;
		}

		if(SysTick_TASK) {
			SysTick_TASK = 0;
			blink();
		}
	}
}
