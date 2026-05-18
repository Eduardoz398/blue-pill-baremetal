#ifndef COLOR_H
#define COLOR_H


typedef enum {
	off =  0,
	red = 1<< 11,
	green = 1 << 12,
	blue = 1 << 15,
	yellow = 1<< 11 | 1 << 12,
	cyan = 1<<12 | 1 << 15,
	purple = 1<< 11 | 1 << 15,
	white = 1<<11 | 1 << 12 | 1 << 15,

} Color;


#endif
