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
 * easy_functions.c
 *
 *  Created on: Aug 7, 2026
 *      Author: fil
 */


#include "main.h"
#include "../A_os_includes.h"
#include "../hydra_020226_00.h"
#ifndef	SAMPLE_PROCESSES_ENABLED
#include "easy_functions.h"


extern	uint8_t	uart7_Easy_rx_buffer[UART7_RX_BUF_SIZE];
extern	uint8_t	uart7_Easy_tx_buffer[UART7_TX_BUF_SIZE];

uint8_t	Easy_tx_payload[EASY_PAYLOAD_LEN];
EASY_Struct_t	ebuf;

uint32_t easy_send(uint8_t *payload, uint8_t address, uint8_t command)
{
	uint8_t	i;
	bzero(ebuf.payload,EASY_PAYLOAD_LEN);
	ebuf.address = address;
	ebuf.command = command;
	ebuf.header = EASY_HEADER;
	ebuf.footer = EASY_FOOTER;
	for(i=0;i<EASY_PAYLOAD_LEN;i++)
		ebuf.payload[i] = payload[i];
	return uart_send(&Uart7_Easy_Drv,(uint8_t *)&ebuf,UART7_RX_BUF_SIZE);
}

uint32_t easy_loop(void)
{
	sprintf((char *)Easy_tx_payload,"Ciao FIL!!!");
	return easy_send(Easy_tx_payload,EASY_ADDR_MASTER,EASY_CMD_DISCOVERY);
}



#endif	//#ifndef	SAMPLE_PROCESSES_ENABLED

