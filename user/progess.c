#include "process.h"

// anneal series
void anneal();
void check(u16 volt, u16 setpt, u8 mode);

// config series
void config();
void ctrl_setpoint();
void ctrl_work_mode();
void ctrl_channel();
void ctrl_diode();
void ctrl_calibration();

void workflow()
{
    u16 adc;
    u16 volt = 0;
    u16 temp = 0;
    lcd1602_init();
    startUI();
    ad7705_init();
    ad7705_calib(1);
    ad7705_calib(2);
    adc = ad7705_ReadAdc(channel);

    lcd1602_clear();
    while (1)
    {
        u8 i = 0;
        u8 key;
        delay1us();
        adc = ad7705_ReadAdc(channel);
        volt = ((u32)adc * 50000) / (65535);
        if (mode)
        {
            mainUI(volt, setpoint * 10, mode);
        }
        else
        {
            temp = trans_table(volt, diode);
            mainUI(temp, setpoint, mode);
        }
        for (i = 0; i < oversample; i++)
        {
            key = key_scan(0);

            if (key == KEY_ENTER_PRESS)
            {
                anneal();
            }

            if (key == KEY_RIGHT_PRESS)
            {
                config();
            }
        }
    }
}

void anneal()
{
    u16 adc;
    u16 volt = 0;
    u16 temp = 0;
    u8 key;
    delay1us();
    lcd1602_clear();
    // if (!mode)
    // {
    //     prepareAnneal(setpoint);
    //     calc_indices(setpoint);
    // }
    // lcd1602_clear();
    while (1)
    {
        delay1us();
        adc = ad7705_ReadAdc(channel);
        volt = ((u32)adc * 50000) / (65535);
        key = key_scan(0);
        if (!mode) // temp
        {
            temp = trans_table(volt, diode);
            annealUI(temp, setpoint, mode);
            check(temp, setpoint, mode);
        }
        else
        {
            annealUI(volt, setpoint * 10, mode);
            check(volt, setpoint * 10, mode);
        }
        if (key == KEY_SHIFT_PRESS)
        {
            lcd1602_clear();
            break;
        }
    }
}

void check(u16 volt, u16 setpt, u8 mode)
{
    if (!mode) // 温度
    {
        if (volt >= setpt)
            attach(); // 打开开关
        else
            detach(); //关闭
    }
    else
    {
        if (volt >= setpt)
            detach();
        else
            attach();
    }
}

void config()
{
    u8 key = 0;
    u8 index = 0;
    config_welcome();
    config_func_list[0](setpoint, mode);
    while (1)
    {
        key = key_scan(0);
        if (key == KEY_RIGHT_PRESS)
        {
            if (index == 5)
                index = 0;
            else
                index++;
            config_func_list[index](setpoint, mode);
        }
        if (key == KEY_LEFT_PRESS)
        {
            if (index == 0)
                index = 5;
            else
                index--;
            config_func_list[index](setpoint, mode);
        }
        if (key == KEY_SHIFT_PRESS)
        {
            lcd1602_clear();
            break;
        }
        if (key == KEY_ENTER_PRESS)
        {
            config_set(index);
        }
    }
}

void config_set(u8 index)
{
    switch (index)
    {
    case 0:
        ctrl_setpoint();
        break;
    case 1:
        ctrl_work_mode();
        break;
    case 2:
        ctrl_diode();
        break;
    case 3:
        ctrl_channel();
        break;
    case 4:
        ctrl_calibration();
        break;
    }
}

void ctrl_diode()
{
    u8 key_cal = 0;
    lcd1602_write_cmd(0xc0 + 9);
    lcd1602_write_data(0x7e);
    lcd1602_write_cmd(0xc0 + 6);
    lcd1602_write_data(0x7f);
    while (1)
    {
        key_cal = key_scan(0);
        if (key_cal == KEY_RIGHT_PRESS)
        {
            lcd1602_clear();
            diode = 1;
            lcd1602_show_string(0, 0, "DT-400");
            lcd1602_show_string(0, 1, "SET");
            delay_ms(1000);
            config_diode(0);
            break;
        }
        if (key_cal == KEY_LEFT_PRESS)
        {
            lcd1602_clear();
            diode = 0;
            lcd1602_show_string(0, 0, "DT-670");
            lcd1602_show_string(0, 1, "SET");
            delay_ms(1000);
            config_diode(0);
            break;
        }
        if (key_cal == KEY_SHIFT_PRESS)
        {
            config_diode(0);
            break;
        }
    }
}

void ctrl_channel()
{
    u8 key_cal = 0;
    lcd1602_write_cmd(0xc0 + 12);
    lcd1602_write_data(0x7e);
    lcd1602_write_cmd(0xc0 + 3);
    lcd1602_write_data(0x7f);
    while (1)
    {
        key_cal = key_scan(0);
        if (key_cal == KEY_RIGHT_PRESS)
        {
            lcd1602_clear();
            channel = 2;
            lcd1602_show_string(0, 0, "CH2 SET");
            delay_ms(1000);
            config_channel(0);
            break;
        }
        if (key_cal == KEY_LEFT_PRESS)
        {
            lcd1602_clear();
            channel = 1;
            lcd1602_show_string(0, 0, "CH1 SET");
            delay_ms(1000);
            config_channel(0);
            break;
        }
        if (key_cal == KEY_SHIFT_PRESS)
        {
            config_channel(0);
            break;
        }
    }
}
void ctrl_work_mode()
{
    u8 key_cal = 0;
    lcd1602_write_cmd(0xc0 + 11);
    lcd1602_write_data(0x7e);
    lcd1602_write_cmd(0xc0 + 4);
    lcd1602_write_data(0x7f);
    while (1)
    {
        key_cal = key_scan(0);
        if (key_cal == KEY_RIGHT_PRESS)
        {
            lcd1602_clear();
            mode = 1;
            lcd1602_show_string(0, 0, "MODE: VOLT");
            delay_ms(1000);
            config_mode(0);
            break;
        }
        if (key_cal == KEY_LEFT_PRESS)
        {
            lcd1602_clear();
            mode = 0;
            lcd1602_show_string(0, 0, "MODE: TEMP");
            delay_ms(1000);
            config_mode(0);
            break;
        }
        if (key_cal == KEY_SHIFT_PRESS)
        {
            config_mode(0);
            break;
        }
    }
}

void ctrl_calibration()
{
    u8 key_cal = 0;
    lcd1602_write_cmd(0xc0 + 12);
    lcd1602_write_data(0x7e);
    lcd1602_write_cmd(0xc0 + 3);
    lcd1602_write_data(0x7f);
    while (1)
    {
        key_cal = key_scan(0);
        if (key_cal == KEY_RIGHT_PRESS)
        {
            ad7705_calib(2);
            lcd1602_clear();
            lcd1602_show_string(0, 0, "CH2 self-calibed");
            delay_ms(1000);
            config_calibration(0);
            break;
        }
        if (key_cal == KEY_LEFT_PRESS)
        {
            ad7705_calib(1);
            lcd1602_clear();
            lcd1602_show_string(0, 0, "CH1 self-calibed");
            delay_ms(1000);
            config_calibration(0);
            break;
        }
        if (key_cal == KEY_SHIFT_PRESS)
        {
            config_calibration(0);
            break;
        }
    }
}

void ctrl_setpoint()
{
    u8 key_stp = 0;
    u8 cur_pos = 0;
    lcd1602_show_string(10, 1, "      ");
    lcd1602_show_string(8, 1, "<change>");
    lcd1602_write_cmd(0x0e);
    lcd1602_write_cmd(0xC0);
    while (1)
    {
        key_stp = key_scan(0);
        if (key_stp == KEY_RIGHT_PRESS)
        {
            if (cur_pos == 3)
                cur_pos = 0;
            else
                cur_pos++;
            lcd1602_write_cmd(0xC0 + cur_pos);
            if (cur_pos == 3)
                lcd1602_write_cmd(0xC0 + cur_pos + 1);
        }
        if (key_stp == KEY_LEFT_PRESS)
        {
            if (cur_pos == 0)
                cur_pos = 3;
            else
                cur_pos--;
            lcd1602_write_cmd(0xC0 + cur_pos);
            if (cur_pos == 3)
                lcd1602_write_cmd(0xC0 + cur_pos + 1);
        }
        if (key_stp == KEY_SHIFT_PRESS)
        {
            config_setpoint(setpoint);
            lcd1602_write_cmd(0x0c);
            break;
        }
        if (key_stp == KEY_ENTER_PRESS)
        {
            u8 ud_key = 0;
            lcd1602_write_cmd(0x0f);
            while (1)
            {
                ud_key = key_scan(0);
                if (ud_key == KEY_RIGHT_PRESS)
                {
                    u8 i;
                    u16 adder = 1;
                    for (i = 3 - cur_pos; i > 0; i--)
                        adder *= 10;
                    if (setpoint + adder < MAX_TEMP)
                    {
                        setpoint += adder;
                    }
                    disp_int(0, 1, setpoint, 0);
                    lcd1602_write_cmd(0xc0 + cur_pos);
                }
                if (ud_key == KEY_LEFT_PRESS)
                {
                    u8 i;
                    u16 adder = 1;
                    for (i = 3 - cur_pos; i > 0; i--)
                        adder *= 10;
                    if (setpoint - adder > MIN_TEMP)
                        setpoint -= adder;
                    disp_int(0, 1, setpoint, 0);
                    lcd1602_write_cmd(0xc0 + cur_pos);
                }
                if (ud_key == KEY_SHIFT_PRESS)
                {
                    // lcd1602_show_string(8, 0, "        ");
                    // lcd1602_show_string(8, 1, "        ");
                    lcd1602_write_cmd(0x0e);
                    lcd1602_write_cmd(0xC0 + cur_pos);
                    break;
                }
            }
        }
    }
}
