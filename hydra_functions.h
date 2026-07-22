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
 * hydra_functions.h
 *
 *  Created on: Jul 18, 2026
 *      Author: MARFIX
 */
// source from hydra_method_q8 V4.6 .h

#ifndef HYDRA_FUNCTIONS_H_
#define HYDRA_FUNCTIONS_H_

#define PAGE_HOME         1
#define PAGE_HYDRA        2
#define PAGE_AIRPEN       3
#define PAGE_WATERPEEL    4
#define PAGE_IONOPEEL     5
#define PAGE_COOLPEN      6
#define PAGE_CUP          7
#define PAGE_VORTEX       8
#define PAGE_MOUSSE       9
#define PAGE_DIAGNOSTIC   10

#define HYDRAPEN_VP       0x1200	//
#define TREATMENT_SEL_VP  0x1300	// ozono trattamenti
/*
 * data0_val = data1_val = l = prodotto
 * data0_val = data1_val = 2 = ozono
 * data0_val = data1_val = 3 = acqua idrogenata , 9v on hydra
 *
 */
#define HOTWATER_VP       	0x1400
#define HYDROGEN_VP       	0x1500
#define JETPEEL_VP        	0x1700
#define JETPEEL_PRG_VP    	0x6100
#define OZONE_VP          	0x1900
#define PELTIER_1_VP      	0x2000	// manipolo crio 1
#define PELTIER_2_VP      	0x2200	// manipolo crio 2
#define AIRPEN_VP         	0x2400	//
#define BIOLED_VP         	0x2500
#define PRICKING_VP       	0x2600
#define CUPPING_VP        	0x2700	//
#define MOUSSE_VP         	0x2800	//
#define IONOPEN_VP        	0x2900	//
#define IONOPEN_CLEAN_VP  	0x3000
#define TIMEFIELD_VP  	  	0x3100
#define TIMESET_VP  	  	0x3200
#define VORTEX_VP		  	0x3500
#define VORTEX_DOSE_VP	  	0x5100
#define VORTEX_VACUUM_VP  	0x5000	// proporzionale vacuum vortex
#define VORTEX_SPEED_VP	  	0x5102	// pwm motore 12V

#define CUPPING_INTENSITY	0x5002
#define CUPPING_SU  		0x5003
#define CUPPING_RELEASE  	0x5004

#define PAGE_SWITCH_VP    	0x8000


#define	DWIN_STRING_LEN		32
#define	DWIN_NUMERIC_LEN	10

extern	uint32_t send_numeric_dwin_packet(UART_DriverStruct_t *uart_drv,uint16_t command,uint16_t vp,uint8_t value);
extern	uint32_t send_string_dwin_pkt(UART_DriverStruct_t *uart_drv,uint16_t command,uint16_t vp,uint8_t *string_value );
extern	uint32_t set_tim_buf(uint32_t timer,uint8_t *string_value);

#endif /* HYDRA_FUNCTIONS_H_ */
