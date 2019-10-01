#include "main.h"

static void CAN_GPIO_Config(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;   	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1); 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12,GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13,GPIO_AF_CAN1); 
		 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void CAN_NVIC_Config(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure;
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = CAN1_RX0_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;			   
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = CAN2_RX0_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;			   
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void CAN_Mode_Config(void)
{
	CAN_InitTypeDef        CAN_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

	CAN_DeInit(CAN1); 
	CAN_DeInit(CAN2); 
	CAN_StructInit(&CAN_InitStructure);
	
	CAN_InitStructure.CAN_TTCM	    =   DISABLE;			   //MCR-TTCM  关闭时间触发通信模式使能
	CAN_InitStructure.CAN_ABOM		=   ENABLE;			       //MCR-ABOM  使能自动离线管理 
	CAN_InitStructure.CAN_AWUM		=   DISABLE;			   //MCR-AWUM  使用自动唤醒模式
	CAN_InitStructure.CAN_NART		=   DISABLE;			   //MCR-NART  禁止报文自动重传	  
	CAN_InitStructure.CAN_RFLM		=   DISABLE;			   //MCR-RFLM  接收FIFO 不锁定 溢出时新报文会覆盖原有报文  
	CAN_InitStructure.CAN_TXFP  	=   DISABLE;			   //MCR-TXFP  发送FIFO优先级 取决于报文标示符 
	CAN_InitStructure.CAN_Mode	    =   CAN_Mode_Normal;       //正常工作模式
	
	CAN_InitStructure.CAN_SJW		=	CAN_SJW_1tq;		   
	CAN_InitStructure.CAN_BS1		=	CAN_BS1_7tq;		  
	CAN_InitStructure.CAN_BS2		=	CAN_BS2_7tq;		   
	
	CAN_InitStructure.CAN_Prescaler = 3;		 
	CAN_Init(CAN1, &CAN_InitStructure);
	CAN_Init(CAN2, &CAN_InitStructure);
}

static void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	CAN_FilterInitStructure.CAN_FilterNumber=0;						
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	

	CAN_FilterInitStructure.CAN_FilterIdHigh= 0x0000;		
	CAN_FilterInitStructure.CAN_FilterIdLow= 0x0000; 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0x0000;			
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0x0000;			
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;				
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;			
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=14;						
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	

	CAN_FilterInitStructure.CAN_FilterIdHigh= 0x0000;		
	CAN_FilterInitStructure.CAN_FilterIdLow= 0x0000; 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0x0000;			
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0x0000;			
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;				
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE );
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE );
}



void CAN_Config(void)
{
	CAN_GPIO_Config();
	CAN_NVIC_Config();
	CAN_Mode_Config();
	CAN_Filter_Config(); 
}


void CAN1_TX_IRQHandler( void )
{
	if ( CAN_GetITStatus( CAN1, CAN_IT_TME ) != RESET )
	{
		CAN_ClearITPendingBit( CAN1, CAN_IT_TME );
	}
}


uint16_t i,j;
void CAN1_RX0_IRQHandler( void )
{
	
	CanRxMsg rx_message;
	if ( CAN_GetITStatus( CAN1, CAN_IT_FMP0 ) != RESET )
	{
		CAN_ClearITPendingBit( CAN1, CAN_IT_FMP0 );
		CAN_Receive( CAN1, CAN_FIFO0, &rx_message );

		if ( (rx_message.IDE == CAN_Id_Standard) && (rx_message.IDE == CAN_RTR_Data) && (rx_message.DLC == 8) ) /* 标准帧、数据帧、数据长度为8 */
		{
			if ( rx_message.StdId == 0x201 )                                                                /* 关于2006电机 */
			{
				i++;
				if(i>=500){
				LED_GREEN_TOGGLE();
				i=0;}
			}
		}
	}
}

void CAN2_RX0_IRQHandler(void)
{
    CanRxMsg rx_message;
	rm_imu_data_t rm_imu_data;
	if ( CAN_GetITStatus( CAN2, CAN_IT_FMP0 ) != RESET )
	{
		CAN_ClearITPendingBit( CAN2, CAN_IT_FMP0 );
		CAN_Receive( CAN2, CAN_FIFO0, &rx_message );
		
		if ( (rx_message.IDE == CAN_Id_Standard) && (rx_message.IDE == CAN_RTR_Data)) 
		{
			
			switch(rx_message.StdId)
			{
				case RM_IMU_PARAM_ID:
				{
					rm_imu_data.accel_rangle = rx_message.Data[0] &0x0F;
					rm_imu_data.gyro_rangle = (rx_message.Data[0] &0xF0) >> 4;
					rm_imu_data.sensor_control_temperature = rx_message.Data[2];
					rm_imu_data.imu_sensor_rotation = rx_message.Data[3] & 0x1F;
					rm_imu_data.ahrs_rotation_sequence = (rx_message.Data[3] & 0xE0) >> 5;
					rm_imu_data.quat_euler = rx_message.Data[4] & 0x01;
					
					LED_RED_TOGGLE();
					switch(rm_imu_data.gyro_rangle)
					{
						case 0: rm_imu_data.gyro_sen = GYRO_2000_SEN; break;
						case 1: rm_imu_data.gyro_sen = GYRO_1000_SEN; break;
						case 2: rm_imu_data.gyro_sen = GYRO_500_SEN; break;
						case 3: rm_imu_data.gyro_sen = GYRO_250_SEN; break;
						case 4: rm_imu_data.gyro_sen = GYRO_125_SEN; break;
					}
					
					switch(rm_imu_data.accel_rangle)
					{
						case 0: rm_imu_data.accel_sen = ACCEL_3G_SEN; break;
						case 1: rm_imu_data.accel_sen = ACCEL_6G_SEN; break;
						case 2: rm_imu_data.accel_sen = ACCEL_12G_SEN; break;
						case 3: rm_imu_data.accel_sen = ACCEL_24G_SEN; break;
					}
					break;
				}
				
				case RM_IMU_QUAT_ID:
				{
					if(rm_imu_data.quat_euler && rx_message.DLC == 6)
					{
						memcpy(rm_imu_data.euler_angle, rx_message.Data, rx_message.DLC);
						rm_imu_data.euler_angle_fp32[0] = rm_imu_data.euler_angle[0] * 0.0001f;
						rm_imu_data.euler_angle_fp32[1] = rm_imu_data.euler_angle[1] * 0.0001f;
						rm_imu_data.euler_angle_fp32[2] = rm_imu_data.euler_angle[2] * 0.0001f;
					}
					
					else if(rm_imu_data.quat_euler == 0 && rx_message.DLC == 8)
					{
						memcpy(rm_imu_data.quat, rx_message.Data, rx_message.DLC);
						rm_imu_data.quat_fp32[0] = rm_imu_data.quat[0] * 0.0001f;
						rm_imu_data.quat_fp32[1] = rm_imu_data.quat[1] * 0.0001f;
						rm_imu_data.quat_fp32[2] = rm_imu_data.quat[2] * 0.0001f; 
						rm_imu_data.quat_fp32[3] = rm_imu_data.quat[3] * 0.0001f;
					}
					
					break;
				}
				
				case RM_IMU_GYRO_ID:
				{
					memcpy(rm_imu_data.gyro_int16, rx_message.Data,6);
					rm_imu_data.gyro_fp32[0] = rm_imu_data.gyro_int16[0] * rm_imu_data.gyro_sen;
					rm_imu_data.gyro_fp32[1] = rm_imu_data.gyro_int16[1] * rm_imu_data.gyro_sen; 
					rm_imu_data.gyro_fp32[2] = rm_imu_data.gyro_int16[2] * rm_imu_data.gyro_sen;
					rm_imu_data.sensor_temperature = (int16_t)((rx_message.Data[6] << 3) | (rx_message.Data[7] >>5));
					
					if (rm_imu_data.sensor_temperature > 1023)
					{
						rm_imu_data.sensor_temperature -= 2048;
					}
					break;
				}
				
				case RM_IMU_ACCEL_ID:
				{
					memcpy(rm_imu_data.accel_int16, rx_message.Data,6);
					rm_imu_data.accel_fp32[0] = rm_imu_data.accel_int16[0] * rm_imu_data.accel_sen;
					rm_imu_data.accel_fp32[1] = rm_imu_data.accel_int16[1] * rm_imu_data.accel_sen; 
					rm_imu_data.accel_fp32[2] = rm_imu_data.accel_int16[2] * rm_imu_data.accel_sen; 
					memcpy(&rm_imu_data.sensor_time, (rx_message.Data + 6), 2);
		
					
					break;
				}
				
				case RM_IMU_MAG_ID:
				{
					memcpy(rm_imu_data.mag_int16, rx_message.Data,6);
					
					rm_imu_data.X_axis=(((int16_t)rx_message.Data[1])<<8) + rx_message.Data[0];
					rm_imu_data.Y_axis=(((int16_t)rx_message.Data[3])<<8) + ((int16_t)rx_message.Data[2]);
					rm_imu_data.Z_axis=(((int16_t)rx_message.Data[5])<<8) + ((int16_t)rx_message.Data[4]);
				    break;
			    }
				default: break;
			}
		}
	}
}


int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART6, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
