#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>
#define RCC_base 0x40021000


#define IOPEEN 1 << 6 // IO-E enable
#define IOPDEN 1 << 5 // IO-D enable
#define IOPCEN 1 << 4 // IO-D enable
#define IOPBEN 1 << 3 // IO-D enable
#define IOPAEN 1 << 2 // IO-D enable
//reservado
#define AFIOEN 1 << 0 // AFIO enable



typedef struct {
    volatile uint32_t RCC_CR;           // Offset 0x00
    volatile uint32_t RCC_CFGR;         // Offset 0x04
    volatile uint32_t RCC_CIR;          // Offset 0x08
    volatile uint32_t RCC_APB2RSTR;     // Offset 0x0C
    volatile uint32_t RCC_APB1RSTR;     // Offset 0x10 
    volatile uint32_t RCC_AHBENR;       // Offset 0x14
    volatile uint32_t RCC_APB2ENR;      //offeset 0x18
    volatile uint32_t RCC_APB1ENR;      //offeset 0x1c
} CLOCK_TypeDef;


#define RCC ((CLOCK_TypeDef *) RCC_base)





#endif