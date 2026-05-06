

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f1xx.h"

void EXTI_SetLineState(uint32_t line, bool enabled);



#endif
