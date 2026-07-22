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
 * hydra_functions.c
 *
 *  Created on: Jul 18, 2026
 *      Author: MARFIX
 */

#include "main.h"
#include "A_os_includes.h"
#ifndef	SAMPLE_PROCESSES_ENABLED

#include "hydra_020226_00.h"

LCDdata_Struct_t	IRED_LCD_Struct;

extern	uint32_t	callback_vp_hydrapen(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_treatment_sel(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_hotwater(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_hydrogen(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_jetpeel(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_jetpeel_program(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_ozone(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_peltier1(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_peltier2(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_airpen(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_bioled(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_pricking(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_au_cupping(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_au_ionopen(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_au_timeset(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_au_mousse(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_au_ionopen_clean(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_vortex(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_vortex_dose(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_vortex_vacuum(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_vortex_speed(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_linfocup_set_intensity(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_linfocup_set_release(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_linfocup_set_su(uint16_t	data0_val,uint16_t	data1_val);
extern	uint32_t	callback_vp_au_page_switch(uint16_t	data0_val,uint16_t	data1_val);

VPLCD_Struct_t		VPLCD_Struct[MAX_VPCOUNT] =
{
		{
				.vp = HYDRAPEN_VP,
				.vp_callback = callback_vp_hydrapen,
		},
		{
				.vp = TREATMENT_SEL_VP,
				.vp_callback = callback_vp_treatment_sel,
		},
		{
				.vp = HOTWATER_VP,
				.vp_callback = callback_vp_hotwater,
		},
		{
				.vp = HYDROGEN_VP,
				.vp_callback = callback_vp_hydrogen,
		},
		{
				.vp = JETPEEL_VP,
				.vp_callback = callback_vp_jetpeel,
		},
		{
				.vp = JETPEEL_PRG_VP,
				.vp_callback = callback_vp_jetpeel_program,
		},
		{
				.vp = OZONE_VP,
				.vp_callback = callback_vp_ozone,
		},
		{
				.vp = PELTIER_1_VP,
				.vp_callback = callback_vp_peltier1,
		},
		{
				.vp = PELTIER_2_VP,
				.vp_callback = callback_vp_peltier2,
		},
		{
				.vp = AIRPEN_VP,
				.vp_callback = callback_vp_airpen,
		},
		{
				.vp = BIOLED_VP,
				.vp_callback = callback_vp_bioled,
		},
		{
				.vp = PRICKING_VP,
				.vp_callback = callback_vp_pricking,
		},
		{
				.vp = CUPPING_VP,
				.vp_callback = callback_vp_au_cupping,
		},

		{
				.vp = CUPPING_INTENSITY,
				.vp_callback = callback_vp_linfocup_set_intensity,
		},
		{
				.vp = CUPPING_SU,
				.vp_callback = callback_vp_linfocup_set_release,
		},
		{
				.vp = CUPPING_RELEASE,
				.vp_callback = callback_vp_linfocup_set_su,
		},
		{
				.vp = MOUSSE_VP,
				.vp_callback = callback_vp_au_mousse,
		},
		{
				.vp = IONOPEN_VP,
				.vp_callback = callback_vp_au_ionopen,
		},
		{
				.vp = TIMESET_VP,
				.vp_callback = callback_vp_au_timeset,
		},

		{
				.vp = IONOPEN_CLEAN_VP,
				.vp_callback = callback_vp_au_ionopen_clean,
		},
		{
				.vp = VORTEX_VP,
				.vp_callback = callback_vp_vortex,
		},
		{
				.vp = VORTEX_DOSE_VP,
				.vp_callback = callback_vp_vortex_dose,
		},
		{
				.vp = VORTEX_VACUUM_VP,
				.vp_callback = callback_vp_vortex_vacuum,
		},
		{
				.vp = VORTEX_SPEED_VP,
				.vp_callback = callback_vp_vortex_speed,
		},
		{
				.vp = PAGE_SWITCH_VP,
				.vp_callback = callback_vp_au_page_switch,
		},
};

__weak	uint32_t	callback_vp_hydrapen(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}

__weak	uint32_t	callback_vp_treatment_sel(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_hotwater(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_hydrogen(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_jetpeel(uint16_t	data0_val,uint16_t	data1_val)
{
	return jetpeel_set_out(data1_val);
}
__weak	uint32_t	callback_vp_jetpeel_program(uint16_t	data0_val,uint16_t	data1_val)
{
	jetpeel_set_program(data1_val);
	return 0;
}
__weak	uint32_t	callback_vp_ozone(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_peltier1(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_peltier2(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_airpen(uint16_t	data0_val,uint16_t	data1_val)
{
	return airpen_set_out(data1_val);
}
__weak	uint32_t	callback_vp_bioled(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_pricking(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_au_cupping(uint16_t	data0_val,uint16_t	data1_val)
{
	return linfocup_set_out(data1_val);
}
__weak	uint32_t	callback_vp_linfocup_set_intensity(uint16_t	data0_val,uint16_t	data1_val)
{
	return linfocup_set_intensity(data1_val);
}
__weak	uint32_t	callback_vp_linfocup_set_release(uint16_t	data0_val,uint16_t	data1_val)
{
	return linfocup_set_release(data1_val);
}
__weak	uint32_t	callback_vp_linfocup_set_su(uint16_t	data0_val,uint16_t	data1_val)
{
	return linfocup_set_su(data1_val);
}
__weak	uint32_t	callback_vp_au_mousse(uint16_t	data0_val,uint16_t	data1_val)
{
	return mousse_set_out(data1_val);
}
__weak	uint32_t	callback_vp_au_timeset(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_au_ionopen(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_au_ionopen_clean(uint16_t	data0_val,uint16_t	data1_val)
{
	return 0;
}
__weak	uint32_t	callback_vp_vortex(uint16_t	data0_val,uint16_t	data1_val)
{
	return vortex_start(data1_val);
}
__weak	uint32_t	callback_vp_vortex_dose(uint16_t	data0_val,uint16_t	data1_val)
{
	return vortex_set_dose(data1_val);
}
__weak	uint32_t	callback_vp_vortex_vacuum(uint16_t	data0_val,uint16_t	data1_val)
{
	return vortex_set_vacuum(data1_val);
}
__weak	uint32_t	callback_vp_vortex_speed(uint16_t	data0_val,uint16_t	data1_val)
{
	return vortex_set_speed(data1_val);
}
__weak	uint32_t	callback_vp_au_page_switch(uint16_t	data0_val,uint16_t	data1_val)
{
	HYDRA_Struct.global_timer_value = HYDRA_Struct.global_timer = GLOBAL_TIMER_DEFAULT;
	HYDRA_Struct.global_timer_status = GLOBAL_TIMER_STOP;
	if ( HYDRA_Struct.cleanup_function != NULL )
		HYDRA_Struct.cleanup_function(0,0);
	HYDRA_Struct.current_page = data1_val;
	HYDRA_Struct.cleanup_function = NULL;
	global_timer_stop();
	return 0;
}



/*
* out vp
*/

uint8_t	uart_numeric_pkt[DWIN_NUMERIC_LEN];

uint32_t send_numeric_dwin_packet(UART_DriverStruct_t *uart_drv,uint16_t command,uint16_t vp,uint8_t value)
{
	uart_numeric_pkt[0] = 0x5a;
	uart_numeric_pkt[1] = 0xa5;
	uart_numeric_pkt[2] = command >> 8; //0x06;
	uart_numeric_pkt[3] = command & 0xff; //0x82;
	uart_numeric_pkt[4] = vp >> 8;
	uart_numeric_pkt[5] = vp & 0xff;
	uart_numeric_pkt[6] = value;
	uart_numeric_pkt[7] = 0;
	uart_numeric_pkt[8] = 0;
	uart_numeric_pkt[9] = 0;
	return uart_send(uart_drv,uart_numeric_pkt,DWIN_NUMERIC_LEN);
}

uint8_t	uart_string_pkt[DWIN_STRING_LEN];
uint32_t send_string_dwin_pkt(UART_DriverStruct_t *uart_drv,uint16_t command,uint16_t vp,uint8_t *string_value )
{
uint32_t i;
uint32_t	len = strlen((char *)string_value);
	for(i=0;i<32;i++)
		uart_string_pkt[i] = 0x20;
	uart_string_pkt[0] = 0x5a;
	uart_string_pkt[1] = 0xa5;
	uart_string_pkt[2] = command >> 8; //0x13;
	uart_string_pkt[3] = command & 0xff; //0x82;
	uart_string_pkt[4] = vp >> 8;
	uart_string_pkt[5] = vp & 0xff;
	for(i=0;i<len;i++)
		uart_string_pkt[i+6] = string_value[i];
	return uart_send(uart_drv,uart_string_pkt,DWIN_STRING_LEN);
}


uint32_t set_tim_buf(uint32_t timer,uint8_t *string_value)
{
int	m,s;
	m = timer / 60;
	s = (timer - 60*m);
	sprintf((char *)string_value,"%02d:%02d",m,s);
	return 0;
}

#endif // #ifndef	SAMPLE_PROCESSES_ENABLED

