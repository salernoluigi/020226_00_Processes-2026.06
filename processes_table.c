/*
 * processes_table.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */
#include "main.h"
#include "A_os_includes.h"

#ifndef	SAMPLE_PROCESSES_ENABLED

extern	void process_1(uint32_t process_id);	//This is process1
extern	void process_1_init(uint32_t process_id);

extern	void process_2(uint32_t process_id);	//This is process2
extern	void process_2_init(uint32_t process_id);

extern	void process_3(uint32_t process_id);	//This is process3
extern	void process_4(uint32_t process_id);	//This is process4 of the application

USRprcs_t	UserProcesses[USR_PROCESS_NUMBER] =
{
		{
				.user_init = process_1_init,
				.user_process = process_1,
				.stack_size = 1024,
		},
		{
				.user_init = process_2_init,
				.user_process = process_2,
				.stack_size = 1024,
		},
		{
				.user_process = process_3,
				.stack_size = 1024,
		},
		{
				.user_process = process_4,
				.stack_size = 1024,
		}
};
#endif // #ifndef	SAMPLE_PROCESSES_ENABLED

