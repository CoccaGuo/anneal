#include "ui.h"

// start UI
void startUI()
{
    lcd1602_clear();
    lcd1602_show_string(2, 0, "ANNEAL  PROG");
    lcd1602_show_string(6, 1, "INIT");
}

// main UI
void mainUI(u16 now_T, u16 set_T, u8 mode)
{
    lcd1602_show_string(0, 0, "NOW: ");
    disp_int(5, 0, now_T, mode);
    lcd1602_show_string(12, 0, "# go");
    lcd1602_show_string(0, 1, "SET: ");
    disp_int(5, 1, set_T, mode);
    lcd1602_write_cmd(0xc0 + 12); //箭头
    lcd1602_write_data(0x7e);
    lcd1602_show_string(13, 1, "cfg");
}

void prepareAnneal(u16 temp)
{
    lcd1602_clear();
    lcd1602_show_string(0, 0, "Calc Index At");
    disp_int(0, 1, setpoint, mode);
    delay_ms(100);
}

void annealUI(u16 now_T, u16 set_T, u8 mode)
{
    lcd1602_show_string(0, 0, "NOW: ");
    disp_int(5, 0, now_T, mode);
    lcd1602_show_string(0, 1, "SET: ");
    disp_int(5, 1, set_T, mode);
    lcd1602_show_string(12, 1, "^esc");
}

//config welcome UI
void config_welcome()
{
    lcd1602_clear();
    lcd1602_show_string(3, 0, "--CONFIG--");
    delay_ms(500);
}

void config_setpoint(int setpoint, u8 mode)
{
    lcd1602_clear();
    lcd1602_show_string(0, 0, "SET TEMP:");
    lcd1602_show_string(10, 1, "#Enter");
    lcd1602_show_string(10, 0, "^ Back");
    if (mode)
    {
        setpoint *= 10;
    }

    disp_int(0, 1, setpoint, mode);
}

void config_mode(int x, u8 mode)
{
    lcd1602_clear();
    lcd1602_show_string(0, 0, "WORK MODE:");
    lcd1602_show_string(0, 1, "TEMP");
    lcd1602_show_string(12, 1, "VOLT");
}

void config_diode(int x, u8 mode)
{
    lcd1602_clear();
    lcd1602_show_string(0, 0, "DIODE:");
    lcd1602_show_string(10, 1, "DT-400");
    lcd1602_show_string(0, 1, "DT-670");
}

void config_channel(int x, u8 mode)
{
    lcd1602_clear();
    lcd1602_show_string(0, 0, "CHANNEL:");
    lcd1602_show_string(0, 1, "CH1");
    lcd1602_show_string(13, 1, "CH2");
}

void config_calibration(int x, u8 mode)
{
    lcd1602_clear();
    lcd1602_show_string(0, 0, "SELF-CALIB:");
    lcd1602_show_string(0, 1, "CH1");
    lcd1602_show_string(13, 1, "CH2");
}

void config_info(int x, u8 mode)
{
    lcd1602_clear();
    lcd1602_show_string(0, 0, "Author: CoccaGuo");
    lcd1602_show_string(0, 1, "Ver: 1.0 2022.01");
}

// temperature u16 refers to 1233 => 123.3K
// mode 0 == temp, mode 1 == volt
void disp_int(u8 x, u8 y, u16 temp4digit, u8 mode)
{
    u8 addry1 = 0;
    u8 aff = 0x30;
    if (mode) // volt, show four digits
    {
        temp4digit /= 10;
    }

    if (y == 1)
        addry1 = 0x40;
    lcd1602_write_cmd(0x80 + addry1 + x);
    if (temp4digit / 1000 != 0)
    {
        lcd1602_write_data(aff + temp4digit / 1000);
    }
    else
    {
        lcd1602_write_data(0x20);
    }
    lcd1602_write_cmd(0x80 + addry1 + x + 1);
    lcd1602_write_data(aff + temp4digit / 100 - temp4digit / 1000 * 10);
    lcd1602_write_cmd(0x80 + addry1 + x + 2);
    lcd1602_write_data(aff + (temp4digit % 100 - temp4digit % 10) / 10);
    if (!mode)
    {
        lcd1602_write_cmd(0x80 + addry1 + x + 3);
        lcd1602_write_data('.');
        lcd1602_write_cmd(0x80 + addry1 + x + 4);
        lcd1602_write_data(aff + temp4digit % 10);
        lcd1602_write_cmd(0x80 + addry1 + x + 5);
        lcd1602_write_data('K');
    }
    else
    {
        lcd1602_write_cmd(0x80 + addry1 + x + 3);
        lcd1602_write_data(aff + temp4digit % 10);
        lcd1602_write_cmd(0x80 + addry1 + x + 4);
        lcd1602_write_data('m');
        lcd1602_write_cmd(0x80 + addry1 + x + 5);
        lcd1602_write_data('V');
    }
}
