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
 * weak_ks_functions.c
 *
 *  Created on: Jun 10, 2026
 *      Author: fil
 */
#include "main.h"
#include "A_os_includes.h"
#include "hydra_020226_00.h"

__weak	uint32_t	usb_parser(USB_DriverStruct_t	*USB_Driver)
{
	return 0;
}

__weak	uint32_t	lcd_parser(UART_DriverStruct_t	*UART_Driver)
{
	return 0;
}

