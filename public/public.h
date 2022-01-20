#ifndef _public_H
#define _public_H

#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;
typedef unsigned long u32;

////////====user profile====//////

#define MAX_TEMP 3500 // 350K
#define MIN_TEMP 4 // 4K

static u16 setpoint = 1300; // == 130.0K
static u8 oversample = 1;
static u8 channel = 1;
static u8 diode = 0; //0 for dt-670, 1 for dt-400
static u8 mode = 0; // 0 for temperature, 1 for volt


///////====end of profile====//////
void delay_10us(u16 ten_us);
void delay1us();
void delay_ms(u16 ms);

#endif
