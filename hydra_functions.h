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

#define PAGE_HOME         			1
#define PAGE_HYDRA        			2
#define PAGE_AIRPEN       			3
#define PAGE_WATERPEEL    			4
#define PAGE_IONOPEEL     			5
#define PAGE_COOLPEN      			6
#define PAGE_CUP          			7
#define PAGE_VORTEX       			8
#define PAGE_MOUSSE       			9
#define PAGE_DIAGNOSTIC   			10

#define HYDRAPEN_VP       			0x1000	// hydrapen
#define HYDRAPEN_VACUUM_VP 			0x1001	// proporzionale vacuum vortex
#define HYDRAPEN_PRODUCT_VP			0x1002	// proporzionale vacuum vortex
#define HYDRAPEN_TREATMENT_SEL_VP	0x1003	// ozono trattamenti
/*
 * data0_val = data1_val = l = prodotto
 * data0_val = data1_val = 2 = ozono
 * data0_val = data1_val = 3 = acqua idrogenata , 9v on hydra
 */
#define HYDRAPEN_ALARM_VP 			0x1004	// hydrapen alarm indicator
#define HYDRAPEN_HOTWATER_VP		0x1005
#define HYDRAPEN_HYDROGEN_VP       	0x1006
#define HYDRAPEN_OZONE_VP          	0x1007
#define HYDRAPEN_BIOLED_VP    		0x1008
#define HYDRAPEN_PRICKING_VP		0x1009

#define AIRPEN_VP         			0x1100	//

#define JETPEEL_VP        	0x1200
#define JETPEEL_PRG_VP    	0x1201
/*
 * data0_val = data1_val = l = prog1
 * data0_val = data1_val = 2 = prog2
 * data0_val = data1_val = 3 = prog3
 */

#define PELTIER_1_VP      	0x1300	// manipolo crio 1
#define PELTIER_1_INCR_VP  	0x1301	// manipolo crio 1
/*
 * data0_val = data1_val = l = value
 */
#define PELTIER_2_VP      	0x1400	// manipolo crio 2
#define PELTIER_2_INCR_VP  	0x1401	// manipolo crio 1
/*
 * data0_val = data1_val = l = value
 */

#define CUPPING_VP        	0x1500	//
#define CUPPING_INTENSITY	0x1501
/*
 * data0_val = data1_val = l = value
 */
#define CUPPING_RELEASE  	0x1502
/*
 * data0_val = data1_val = l = value
 */
#define CUPPING_SU  		0x1503
/*
 * data0_val = data1_val = l = value
 */

#define VORTEX_VP		  	0x1600
#define VORTEX_VACUUM_VP  	0x1601	// proporzionale vacuum vortex
#define VORTEX_DOSE_VP	  	0x1602	// stepper dose
#define VORTEX_SPEED_VP	  	0x1603	// pwm motore 12V

#define MOUSSE_VP         	0x1700	//

#define IONOPEN_VP        			0x1800
#define IONOPEN_RF_INTENSITY_VP		0x1801
#define IONOPEN_EMS_INTENSITY_VP	0x1802
#define IONOPEN_DOSE_VP				0x1803	// 12V pwm motor
#define IONOPEN_SPEED_VP			0x1804	// 12V pwm motor
#define IONOPEN_CLEAN_VP			0x1805



#define TIMEFIELD_VP  	  	0x2000
#define TIMESET_VP  	  	0x2001

#define PAGE_SWITCH_VP    	0x8000

#define	DWIN_STRING_LEN		32
#define	DWIN_NUMERIC_LEN	10

extern	uint32_t send_numeric_dwin_packet(UART_DriverStruct_t *uart_drv,uint16_t command,uint16_t vp,uint8_t value);
extern	uint32_t send_string_dwin_pkt(UART_DriverStruct_t *uart_drv,uint16_t command,uint16_t vp,uint8_t *string_value );
extern	uint32_t set_tim_buf(uint32_t timer,uint8_t *string_value);

#endif /* HYDRA_FUNCTIONS_H_ */
