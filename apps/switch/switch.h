#ifndef _switch_H
#define _switch_H

#include "public.h"


sbit _SWITCH = P1^6;

void attach();
void detach();


#endif