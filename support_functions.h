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
 * support_functions.h
 *
 *  Created on: Jun 10, 2026
 *      Author: fil
 */

#ifndef SUPPORT_FUNCTIONS_H_
#define SUPPORT_FUNCTIONS_H_

extern	void process_led(void);
extern	void ac_cmd0_on(void);
extern	void ac_cmd0_off(void);
extern	void ac_cmd1_on(void);
extern	void ac_cmd1_off(void);
extern	void ac_cmd2_on(void);
extern	void ac_cmd2_off(void);
extern	void buzzer_on(void);
extern	void buzzer_off(void);
extern	void hydrogen_on(void);
extern	void hydrogen_off(void);
extern	void aux1_on(void);
extern	void aux1_off(void);
extern	void aux2_on(void);
extern	void aux2_off(void);
extern	void peri_fwd(void);
extern	void peri_rev(void);
extern	void get_adc_values(void);
extern	uint32_t set_default_BOARD_Config(void);
extern	uint32_t read_BOARD_Config(void);
extern	uint32_t config_pins_from_BOARD_Config(void);
extern	void tim_pin_on(uint16_t BOARD_Config_tim_number);
extern	void tim_pin_off(uint16_t BOARD_Config_tim_number);
extern	uint32_t test_blink_ports(uint8_t index , uint8_t level);


#endif /* SUPPORT_FUNCTIONS_H_ */
