
#ifndef _AD7705_H
#define _AD7705_H

#include "public.h"

void ad7705_init(void);
void ad7705_calib(u8 _ch);
void ad7705_SytemCalibZero(u8 _ch);
void ad7705_SytemCalibFull(u8 _ch);
u16 ad7705_ReadAdc(u8 _ch);

void ad7705_WriteReg(u8 _RegID, u32 _RegValue);
u32 ad7705_ReadReg(u8 _RegID);

#endif

