#ifndef UTILS_H
#define UTILS_H

#define PA11 11
#define PA12 12
#define PA15 15

#define   GPIO_INPUT_FLOATING   0x4
#define   GPIO_INPUT_PULL       0x8
#define   GPIO_OUTPUT_50MHZ_PP  0x3
#define   GPIO_OUTPUT_2MHZ_PP   0x2

typedef enum {
	//off =  0,
	red = 1<< 11,
	green = 1 << 12,
	blue = 1 << 15,
	yellow = 1<< 11 | 1 << 12,
	cyan = 1<<12 | 1 << 15,
	purple = 1<< 11 | 1 << 15,
	white = 1<<11 | 1 << 12 | 1 << 15,

} Color;




#endif
