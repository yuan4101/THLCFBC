/*	Simple Delay Routines
	Copyright (C) 2014 Jesus Ruben Santa Anna Zamudio.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DELAY_H
#define DELAY_H
/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/
#include "DelayPort.h"
/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			*/
/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
/*		Function prototypes				*/
/*-------------------------------------------------------------*/
#ifndef delay_ms
/**
 * @brief Generates a delay of N miliseconds
 *
 * Blocks the program operation for a given interval of time expressed in
 * miliseconds.
 * 
 * @param time The ammount of time to block program execution.
 */
void delay_ms( uint32_t time);
#endif

#ifndef delay_us
/**
 * @brief Generates a delay of N microseconds
 * 
 * Blocks the program operation for a given interval of time expressed in
 * microseconds.
 * 
 * @param time The ammount of time to block program execution.
 */
void delay_us(uint32_t time);
#endif

#ifndef delay_cycles
/**
 * @brief Generates a delay of N CPU Cycles
 *
 * Blocks the program operation for a given interval of time expressed in
 * instruction cycles.
 * 
 * @param cycles The number of CPU cycles to block program execution
 */
void delay_cycles(uint32_t cycles);
#endif

#endif
// End of Header file