#ifndef _key_H
#define _key_H

#include "public.h"

sbit KEY_LEFT=P2^0;
sbit KEY_SHIFT=P2^1;
sbit KEY_ENTER=P2^2;
sbit KEY_RIGHT=P2^3;

#define KEY_LEFT_PRESS	1
#define KEY_SHIFT_PRESS	2
#define KEY_ENTER_PRESS	3
#define KEY_RIGHT_PRESS	4
#define KEY_UNPRESS	0

u8 key_scan(u8 mode);

#endif