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
 * lcd_parser.c
 *
 *  Created on: Jun 23, 2026
 *      Author: MARFIX
 */


#include "main.h"
#include "A_os_includes.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "hydra_020226_00.h"


uint16_t	vp;
uint16_t	data0_val;
uint16_t	data1_val;

__weak uint32_t after_parser_function(UART_DriverStruct_t *uart_drv,uint16_t	lvp,uint16_t	ldata1_val)
{
	return 0;
}

uint8_t lcd_error = 0;
void lcdparse_error(void)
{
	lcd_error++;
}
uint8_t parser_buf[UART3_RX_BUF_SIZE];
uint32_t lcd_parser(UART_DriverStruct_t *uart_drv)
{
uint32_t	i,idx_found;
uint8_t 	*rx_buf = uart_drv->data;

	for(i=0;i<uart_drv->rx_num_chars;i++)
		parser_buf[i] = rx_buf[i];
	for(i=0;i<uart_drv->rx_num_chars;i++)
	{
		if (( parser_buf[i] == 0x5a )  && ( parser_buf[i+1] == 0xa5 ))
			break;
		if ( i > 16 )
		{
			lcdparse_error();
			return 1;
		}
	}
	idx_found = i;

	LCDdata_Struct_t	*rx_struct = (LCDdata_Struct_t *)&parser_buf[idx_found];

	if (( rx_struct->flags[0] == 0x5a) && ( rx_struct->flags[1] == 0xa5))
	{
		vp = rx_struct->vph<<8 | rx_struct->vpl;
		data0_val = rx_struct->data0h <<8 | rx_struct->data0l;
		data1_val = rx_struct->data1l;
	}
	else
		return 1;
	after_parser_function(uart_drv,vp,data1_val);
	for(i=0;i<MAX_VPCOUNT;i++)
	{
		if ( (vp == VPLCD_Struct[i].vp) && (VPLCD_Struct[i].vp_callback != NULL ))
			return VPLCD_Struct[i].vp_callback(data0_val,data1_val);
	}
	return 1;
}

#endif //#ifndef	SAMPLE_PROCESSES_ENABLED
