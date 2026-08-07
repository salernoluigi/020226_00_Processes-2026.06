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
 * process_2.c
 *
 *  Created on: Feb 14, 2025
 *      Author: fil
 */


#include "main.h"
#include "A_os_includes.h"
#include "hydra_020226_00.h"

#ifndef	SAMPLE_PROCESSES_ENABLED

#define	XMODEM_AREA_LEN		32768
uint8_t	xmodem_area[XMODEM_AREA_LEN];

#define	USB_BUF_LEN	XMODEM_LINE_LEN
uint8_t	usb_rx_buffer[XMODEM_LINE_LEN];
uint8_t	usb_tx_buffer[XMODEM_LINE_LEN];



USB_DriverStruct_t	USB_Drv =
{
		.data = usb_rx_buffer,
		.data_index = 0,
		.requested_len = XMODEM_LINE_LEN,
		.usb_interface_class = USB_CDC_CLASS,
		.timeout = 250,
		.wakeup_id = WAKEUP_FROM_USB_DEVICE_IRQ,
};


void process_2_init(uint32_t process_id)
{
	usb_device_driver_register(&USB_Drv);
}

uint8_t		xmodem_rx_usb_enable;
uint8_t		xmodem_rx_usb_enable_poll;
uint8_t		tim_downscale=0;

void process_2(uint32_t process_id)
{
uint32_t	wakeup,flags;

	xmodem_rx_usb_enable = 0;
	xmodem_rx_usb_enable_poll = 1;

	xmodem_rx_init((uint8_t *)xmodem_area,XMODEM_AREA_LEN);
	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);

	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_USB_DEVICE_IRQ | EVENT_I2C1_IRQ);
		get_wakeup_flags(&wakeup,&flags);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( xmodem_rx_usb_enable == 1 )
			{
				if ( xmodem_rx_usb_enable_poll	 == 1 )
				{
					tim_downscale ++;
					if ( tim_downscale > 10 )
					{
						xmodem_data_process((uint32_t *)&USB_Drv,xmodem_rx_usb_enable_poll,XMODEM_IF_USB,usb_rx_buffer);
						tim_downscale = 0;
					}
				}
			}
		}
		if (( wakeup & WAKEUP_FROM_USB_DEVICE_IRQ) == WAKEUP_FROM_USB_DEVICE_IRQ)
		{
			if (( usb_rx_buffer[0] == '<') && ( usb_rx_buffer[1] == 'h'))
			{
				xmodem_rx_usb_enable = 1;
				xmodem_rx_usb_enable_poll = 1;
			}
			else
			{
				if (xmodem_data_process((uint32_t *)&USB_Drv,xmodem_rx_usb_enable_poll,XMODEM_IF_USB,usb_rx_buffer) == X_EOT)
				{
					xmodem_rx_usb_enable = 0;
					xmodem_rx_usb_enable_poll = 0;
					i2c_24xx_write(&i2c_24xx_Drv,EE_PROGRAM_ADDRESS,xmodem_area,xmodem_rx_get_rxed_amount());
				}
				else
				{
					xmodem_rx_usb_enable = 1;
					xmodem_rx_usb_enable_poll = 0;
				}
			}
		}
	}
}

#endif // #ifndef	SAMPLE_PROCESSES_ENABLED

