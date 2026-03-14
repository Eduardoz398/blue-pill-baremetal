#include "../Inc/gpio.h"


void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode mode) {
    if(pin > 15 )
        return;
    if (pin < 8) {
        GPIOx->CRL &= ~(0xF << (pin*4));
        GPIOx->CRL |= (mode << (pin*4));
        return;
    }
    uint8_t __pin = pin - 8; 
    GPIOx->CRH &= ~(0xF << (__pin*4));
    GPIOx->CRH |= (mode << (__pin*4));
}


void GPIO_EnableClock(uint32_t bit_mask) {
    RCC->RCC_APB2ENR |= bit_mask;
}

#define AFIO_base 0x40010000


typedef struct {
    volatile uint32_t EVCR;     // offest 0x0
    volatile uint32_t MAPR;     //offeset 0x4
    volatile uint32_t EXTICR1;  //offest 0x8
    volatile uint32_t EXTICR2;  //offest 0x0c
    volatile uint32_t EXTICR3;  //offest 0x10
    volatile uint32_t EXTICR4;  //offset 0x14
} AFIO_typedef;

#define AFIO ((AFIO_typedef * ) AFIO_base)


void AFIO_EnableClock() {
    RCC->RCC_APB2ENR |= AFIOEN;
}
void GPIO_EnableInterrupt(GPIO_TypeDef* port, uint8_t pin, InterruptMode mode) {
    //pegar no memory map a diferença dos endereços de GPIOA para o GPIOB, ... 
    //habilitar o clock do AFIO

    //configurar o AFIO->EXTICR[i]
    //configurr se é borda de subida ou descida ou ambos
    // configurar prioridade
    //chamar NVIC_enableIRQ
    // chamar a função IMR
}