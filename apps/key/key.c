# include "key.h"

u8 key_scan(u8 mode)
{
	static u8 key=1;

	if(mode)key=1;
	if(key==1&&(KEY_LEFT==0||KEY_SHIFT==0||KEY_ENTER==0||KEY_RIGHT==0))
	{
		delay_10us(100);
		key=0;
		if(KEY_LEFT==0)
			return KEY_LEFT_PRESS;
		else if(KEY_SHIFT==0)
			return KEY_SHIFT_PRESS;
		else if(KEY_ENTER==0)
			return KEY_ENTER_PRESS;
		else if(KEY_RIGHT==0)
			return KEY_RIGHT_PRESS;	
	}
	else if(KEY_LEFT==1&&KEY_SHIFT==1&&KEY_ENTER==1&&KEY_RIGHT==1)
	{
		key=1;			
	}
	return KEY_UNPRESS;		
}