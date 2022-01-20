#ifndef _process_H
#define _process_H

#include "public.h"
#include "lcd1602.h"
#include "ad7705.h"
#include "ui.h"
#include "key.h"
#include "switch.h"
#include "diode.h"

void workflow();
void config();
void config_set(u8 index);

#endif