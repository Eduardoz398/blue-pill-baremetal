#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>
#include <stdbool.h>
#define EXTI_base 0x40010400

typedef struct {             // function                           | offest
    volatile uint32_t IMR;   // Interrupt mask register            | 0x0
    volatile uint32_t EMR;   // Event mask register                | 0x4
    volatile uint32_t RTSR;  // Rising trigger selection register  | Ox8
    volatile uint32_t FTSR;  // Falling trigger selection register | 0x0c
    volatile uint32_t SWIER; // Software interrupt event register  | 0x10
    volatile uint32_t PR;    // Pending register                   | 0x14
} EXTI_TypeDef;


#define EXTI ((EXTI_TypeDef*) EXTI_base)


void EXTI_SetLineState(uint8_t line, bool enabled);



#endif 