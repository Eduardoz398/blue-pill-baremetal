#include "../Inc/interrupt.h"




void EXTI_SetLineState(uint32_t line, bool enabled) {
    if(line > 19)
        return;
    if(!enabled) {
        EXTI->IMR &= ~(1 << line);
        return;
    }
     EXTI->IMR |= (1 << line);    
}
