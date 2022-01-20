#ifndef _ui_H
#define _ui_H

#include "public.h"
#include "lcd1602.h"
#include "diode.h"

void startUI();
void mainUI(u16 now_T, u16 set_T, u8 mode);
void prepareAnneal(u16 temp);
void annealUI(u16 now_T, u16 set_T, u8 mode);
void config_welcome();
void config_setpoint(int setpoint, u8 mode);
void config_mode(int, u8);
void config_diode(int, u8);
void config_channel(int, u8);
void config_calibration(int, u8);
void config_info(int, u8);

static void (*config_func_list[6])(int, u8) = {
    config_setpoint, config_mode, config_diode, config_channel,
    config_calibration, config_info
    };


// temperature u16 refers to 1233 => 123.3K, 1222 => 1222mV
// mode 0 == temp, mode 1 == volt
void disp_int(u8 x, u8 y, u16 temp4digit, u8 mode); 



#endif