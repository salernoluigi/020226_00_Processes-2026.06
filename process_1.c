/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : A_os
*/
/*
 * process_1.c
 *
 *  Created on: Mar 13, 2026
 *      Author: fil
 */
#include "main.h"
#include "A_os_includes.h"
#include "hydra_020226_00.h"

#ifndef	SAMPLE_PROCESSES_ENABLED
uint32_t prescaler = 960;
void stepper_callback(uint32_t value)
{
	stepper_set_prescaler(&Stepper_Control,prescaler);
}

void get_i2c_data(void)
{
	bzero(HYDRA_Struct.i2cBufr,I2C_24XX_PAGESIZE);
	if ( HAL_I2C_IsDeviceReady(i2c_24xx_Drv.bus,i2c_24xx_Drv.device_address,5,1000) == 0 )
	{
		HYDRA_Struct.flags |= HYDRA_I2CMEM_PRESENT;
		i2c_24xx_read(&i2c_24xx_Drv,EE_HEADER_ADDRESS,i2c_rx_buffer,I2C_24XX_PAGESIZE);
	}
}

void process_1_init(uint32_t process_id)
{
	hydra_register_devices();
	bzero((char *)uart7_Easy_tx_buffer,UART7_RX_BUF_SIZE);
	bzero((char *)uart7_Easy_rx_buffer,UART7_RX_BUF_SIZE);
}

uint8_t 	timbuf[32],easy_uart=0;
uint32_t	easy_result=0;


void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
uint32_t	count=0;
	create_timer(TIMER_ID_0,TIM_TICK,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	adc_start(&ADC_Drv);
	uart_start_receive(&Uart3_LCD_Drv);
	uart_start_receive(&Uart7_Easy_Drv);
	global_timer_init();
	global_timer_stop();
	HAL_GPIO_WritePin(SLEEP_3G_GPIO_Port, SLEEP_3G_Pin, GPIO_PIN_RESET);
	get_i2c_data();
	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_ADC1_IRQ | EVENT_UART3_IRQ | EVENT_I2C1_IRQ | EVENT_SW_MODULES);
		get_wakeup_flags(&wakeup,&flags);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			process_led();
			easy_result = easy_loop();
			jetpeel_timer_call();

			count++;
			if (( count == 5 ) || ( count == 10 ))
			{
				if ( HYDRA_Struct.pump_status == 1 )
				{
					if ( HAL_GPIO_ReadPin(YF_S401_IN_GPIO_Port, YF_S401_IN_Pin) )
					{
						HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(PIN_TIM1_CH2_GPIO_Port, PIN_TIM1_CH2_Pin, GPIO_PIN_RESET);
					}
					/*
					else
					{
						HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(PIN_TIM1_CH2_GPIO_Port, PIN_TIM1_CH2_Pin, GPIO_PIN_SET);
					}
					*/
					if ( HYDRA_Struct.hydrapen_running == 1 )
					{
						if ( HAL_GPIO_ReadPin(FLOATER_GPIO_Port, FLOATER_Pin) == 0 )
						{
							HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin, GPIO_PIN_RESET);
							HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
							task_delay(50);
							send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,HYDRAPEN_ALARM_VP,0);
						}
						else
						{
							HAL_GPIO_WritePin(AC_CMD0_GPIO_Port, AC_CMD0_Pin, GPIO_PIN_SET);
							if ( HYDRA_Struct.global_timer_status == GLOBAL_TIMER_STOP )
							{
								HYDRA_Struct.global_timer_status = GLOBAL_TIMER_RUNNING;
								task_delay(50);
								send_numeric_dwin_packet(&Uart3_LCD_Drv,0x0682,HYDRAPEN_ALARM_VP,1);
							}
						}
					}
				}
			}

			if ( count >= 10 )
			{
				global_timer_run();
				count=0;
			}
			if ((HYDRA_Struct.stepper_running == 1) && (HYDRA_Struct.pump_status == 0))
			{
				if ( HYDRA_Struct.stepper_running_timeout )
				{
					HYDRA_Struct.stepper_running_timeout--;
					if ( HYDRA_Struct.stepper_running_timeout == 0 )
					{
						stepper_stop(&Stepper_Control,TIM_CHANNEL_1);
						HYDRA_Struct.stepper_running = 0;
					}
				}
			}
		}
		if (( wakeup & WAKEUP_FROM_ADC1_IRQ) == WAKEUP_FROM_ADC1_IRQ)
		{
			get_adc_values();
		}
		if (( wakeup & WAKEUP_FROM_LCD_UART_IRQ) == WAKEUP_FROM_LCD_UART_IRQ)
		{
			if ( uart_get_rxlen(&Uart3_LCD_Drv) > 2)
				lcd_parser(&Uart3_LCD_Drv);
		}
		if (( wakeup & WAKEUP_FROM_EASY_UART_IRQ) == WAKEUP_FROM_EASY_UART_IRQ)
		{
			if (( flags & WAKEUP_FLAGS_UART_RX) == WAKEUP_FLAGS_UART_RX )
				easy_uart++;
		}

		if (( wakeup & WAKEUP_FROM_SW_MODULES_IRQ) == WAKEUP_FROM_SW_MODULES_IRQ)
		{
			if ( (Stepper_Control.status & STEPPER_CHANNEL_STARTED) == 0)
			{
				HYDRA_Struct.stepper_running = 0;
				HYDRA_Struct.stepper_running_timeout = 0;
			}
		}
		if (( wakeup & WAKEUP_FROM_I2C1_IRQ) == WAKEUP_FROM_I2C1_IRQ)
		{
			if (( HYDRA_Struct.flags |= HYDRA_I2CMEM_PRESENT ) == HYDRA_I2CMEM_PRESENT)
			{
				if (( flags & WAKEUP_FLAGS_I2C_RX) == WAKEUP_FLAGS_I2C_RX)
				{
					bzero((char *)i2c_tx_buffer,I2C_24XX_PAGESIZE);
					sprintf((char *)i2c_tx_buffer,"Hydra Board Name : %s\n\rMachine Name : %s\n\rMachine Version : %s\n\rAos version : %s\n\rAPP version : %s",BOARD_NAME,MACHINE_NAME,MACHINE_VERSION,A_OS_VERSION,APP_VERSION);
					if ( strcmp ((char *)i2c_rx_buffer,(char *)i2c_tx_buffer))
					{
						i2c_24xx_write(&i2c_24xx_Drv,EE_HEADER_ADDRESS,i2c_tx_buffer,I2C_24XX_PAGESIZE);
						HYDRA_Struct.flags |= HYDRA_I2CMEM_REINIT;
					}
					else
						HYDRA_Struct.flags |= HYDRA_I2CMEM_CHECKED;
				}
				if (( flags & WAKEUP_FLAGS_I2C_TX) == WAKEUP_FLAGS_I2C_TX)
				{
					if (( flags & HYDRA_I2CMEM_REINIT) == HYDRA_I2CMEM_REINIT)
					{
						bzero((char *)i2c_tx_buffer,I2C_24XX_PAGESIZE);
						i2c_24xx_write(&i2c_24xx_Drv,EE_COUNTERS_ADDRESS,i2c_tx_buffer,I2C_24XX_PAGESIZE);
						HYDRA_Struct.flags &=  ~HYDRA_I2CMEM_REINIT;
						HYDRA_Struct.flags |= HYDRA_I2CMEM_CHECKED;
					}
				}
			}
		}
	}
}
#endif //#ifdef SAMPLE_PROCESSES_ENABLED



