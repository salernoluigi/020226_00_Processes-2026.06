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
 * global_timer.c
 *
 *  Created on: Jul 21, 2026
 *      Author: MARFIX
 */
#include "main.h"
#include "A_os_includes.h"
#include "hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "global_timer.h"
uint16_t 	timer=1800;

uint32_t global_timer_init(void)
{
	HYDRA_Struct.global_timer_value = HYDRA_Struct.global_timer = GLOBAL_TIMER_DEFAULT;
	return 0;
}

uint32_t global_timer_run(void)
{
	if ( HYDRA_Struct.global_timer_callback != NULL )
		HYDRA_Struct.global_timer_callback(0,0);
	if ( HYDRA_Struct.global_timer_status == GLOBAL_TIMER_RUNNING )
	{
		set_tim_buf(HYDRA_Struct.global_timer,HYDRA_Struct.timbuf);
		send_string_dwin_pkt(&Uart3_LCD_Drv,0x1382,TIMEFIELD_VP,HYDRA_Struct.timbuf);
		if ( HYDRA_Struct.global_timer )
			HYDRA_Struct.global_timer--;
		else
		{
			HYDRA_Struct.global_timer = HYDRA_Struct.global_timer_value;
			if ( HYDRA_Struct.global_timer_elapsed_callback != NULL )
				HYDRA_Struct.global_timer_elapsed_callback(0,0);
			return 1;
		}
	}
	return 0;
}

uint32_t global_timer_stop(void)
{
	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	HYDRA_Struct.global_timer = HYDRA_Struct.global_timer_value;
	set_tim_buf(HYDRA_Struct.global_timer,HYDRA_Struct.timbuf);
	send_string_dwin_pkt(&Uart3_LCD_Drv,0x1382,TIMEFIELD_VP,HYDRA_Struct.timbuf);
	return 0;
}

uint32_t callback_vp_au_timeset(uint16_t	data0_val,uint16_t	data1_val)
{
	if ( data1_val == 1 )
	{
		HYDRA_Struct.global_timer_value+=60;
	}
	if ( data1_val == 2 )
	{
		if ( HYDRA_Struct.global_timer_value > 60 )
		{
			HYDRA_Struct.global_timer_value-=60;
		}
		else
		{
			if ( HYDRA_Struct.global_timer_value > 10 )
				HYDRA_Struct.global_timer_value-=10;
			else if ( HYDRA_Struct.global_timer_value > 1 )
				HYDRA_Struct.global_timer_value-=1;
		}
	}
	HYDRA_Struct.global_timer = HYDRA_Struct.global_timer_value;
	set_tim_buf(HYDRA_Struct.global_timer,HYDRA_Struct.timbuf);
	send_string_dwin_pkt(&Uart3_LCD_Drv,0x1382,TIMEFIELD_VP,HYDRA_Struct.timbuf);

	return 0;
}
#endif //#ifndef	SAMPLE_PROCESSES_ENABLED

