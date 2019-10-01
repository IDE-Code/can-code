#include"main.h"



int main( void )
{
	LED_Configuration();
	USART6_Configuration(115200);
	CAN_Config();
	TIMx_Configuration();
	while (1)
	{
	
	}
}

