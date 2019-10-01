#include "stm32f4xx_it.h"
#include "main.h"
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/



/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
  
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
void  TIM1_UP_TIM10_IRQHandler (void)
{
	rm_imu_data_t rm_imu_data;
	if ( TIM_GetITStatus( TIM1, TIM_IT_Update) != RESET ) 
	{	
		LED_GREEN_TOGGLE();
//		printf("���ٶ�ģʽ %d\r\n",rm_imu_data.accel_rangle);
//		printf("������ģʽ %d\r\n",rm_imu_data.accel_rangle);
//		printf("�¶� %d\r\n",rm_imu_data.sensor_control_temperature);
//		printf("������װ��ת˳�� %d\r\n",rm_imu_data.imu_sensor_rotation);
//		printf("��̬�Ƕ���ת˳�� %d\r\n",rm_imu_data.ahrs_rotation_sequence);
//		printf("��Ԫ��0,ŷ����1 =%d\r\n",rm_imu_data.quat_euler);

////		printf("yaw=%f\r\n",rm_imu_data.euler_angle_fp32[0]);
////		printf("pitch=%f\r\n",rm_imu_data.euler_angle_fp32[1]);
////		printf("roll=%f\r\n",rm_imu_data.euler_angle_fp32[2]);

//		printf("��Ԫ��q0=%f\r\n",rm_imu_data.quat_fp32[0]);
//		printf("��Ԫ��q1=%f\r\n",rm_imu_data.quat_fp32[1]);
//		printf("��Ԫ��q2=%f\r\n",rm_imu_data.quat_fp32[2]);
//		printf("��Ԫ��q3=%f\r\n",rm_imu_data.quat_fp32[3]);

//		printf("x����ٶ�=%f\r\n",rm_imu_data.gyro_fp32[0]);
//		printf("y����ٶ�=%f\r\n",rm_imu_data.gyro_fp32[1]);
//		printf("z����ٶ�=%f\r\n",rm_imu_data.gyro_fp32[2]);
//		printf("�¶�=%d\r\n",rm_imu_data.sensor_temperature);

//		printf("x����ٶ�=%f\r\n",rm_imu_data.accel_fp32[0]);
//		printf("y����ٶ�=%f\r\n",rm_imu_data.accel_fp32[1]);
//		printf("z����ٶ�=%f\r\n",rm_imu_data.accel_fp32[2]);

//		printf("X_axis=%d\r\n",rm_imu_data.X_axis);
//		printf("Y_axis=%d\r\n",rm_imu_data.Y_axis);
//		printf("Z_axis=%d\r\n",rm_imu_data.Z_axis);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  		 
	}		 	
}
