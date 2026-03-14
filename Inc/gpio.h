#ifndef GPIO_H
#define GPIO_H


#include <stdint.h>
#include "clock.h"
#include "interrupt.h"


#define GPIOG_BASE 0x40012000 
#define GPIOF_BASE 0x40011C00
#define GPIOE_BASE 0x40011800
#define GPIOD_BASE 0x40011400
#define GPIOB_BASE 0x40010C00
#define GPIOA_BASE 0x40010800
#define GPIOC_BASE 0x40011000


// The offset is automatically determined by the position in the struct.
typedef struct {
    volatile uint32_t CRL;   // Offset 0x00
    volatile uint32_t CRH;   // Offset 0x04
    volatile uint32_t IDR;   // Offset 0x08
    volatile uint32_t ODR;   // Offset 0x0C
    volatile uint32_t BSRR;  // Offset 0x10
    volatile uint32_t BRR;   // Offset 0x14
} GPIO_TypeDef;


#define GPIOA    ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB    ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC    ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD    ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE    ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF    ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG    ((GPIO_TypeDef *) GPIOG_BASE)



/**
 * @brief GPIO pin configuration value (CNF followed by MODE).
 *
 *     [ CNF_bit1 CNF_bit0 MODE_bit1 MODE_bit0 ]
 *
 */
typedef enum {
     GPIO_INPUT  = 0x4,
	 GPIO_OUTPUT = 0x3
} GPIO_Mode;


/**
 * @brief Rising and Falling edge triggers can be set for the same interrupt line. In this configuration,
both generate a trigger condition
 * 
 * 
 */
typedef enum {
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGES,
    DISABLED
} InterruptMode;


/**
 * @brief Configure the mode of a GPIO pin.
 *
 * @param GPIOx Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB).
 * @param pin   GPIO pin number (0–15).
 * @param mode  Pin mode configuration value to be written in CRL/CRH.
 */

void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode mode);

/**
 * @brief Enable clock for a peripheral on the APB2 bus.
 *
 * @param rcc      Pointer to the RCC peripheral structure.
 * @param bit_mask Bit mask corresponding to the peripheral clock enable bit.
 */
void GPIO_EnableClock(uint32_t bit_mask);


//------------- alternative I/O and interrput

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


void AFIO_EnableClock();




void GPIO_EnableInterrupt(GPIO_TypeDef* port, uint8_t pin, InterruptMode mode);



#endif