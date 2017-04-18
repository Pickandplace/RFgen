/**
*Epsilon r Labs RF Generator 30MHz 9.8GHz
*Copyright (C) 2017 Jean Wlodarski
* KaZjjW at gmailcom
*
*This program is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/
/*
 * RFgenBoardInit.c
 *
 * Created: 11/3/2016 7:15:43 PM
 *  Author: Jean
 */
#include <asf.h>
#include <string.h>
#include "RFgen.h"
void RfgenBoardInit(void)
{
	//RF Attenuator Port
	PORTA_DIRSET = PIN0_bm;
	PORTA_DIRSET = PIN1_bm;
	PORTA_DIRSET = PIN2_bm;
	PORTA_DIRSET = PIN3_bm;
	PORTA_DIRSET = PIN4_bm;
	PORTA_DIRSET = PIN5_bm;

	PORTA_OUTSET = PIN0_bm;
	PORTA_OUTSET = PIN1_bm;
	PORTA_OUTSET = PIN2_bm;
	PORTA_OUTSET = PIN3_bm;
	PORTA_OUTSET = PIN4_bm;
	PORTA_OUTSET = PIN5_bm;


	//Encoder A and B
	PORTA_DIRCLR = PIN6_bm;
	PORTA_DIRCLR = PIN7_bm;

	//PLL Chip Enable CE
	PORTB_DIRSET = PIN0_bm;
	PORTB_OUTCLR = PIN0_bm;

	//Encoder E
	PORTB_DIRCLR = PIN1_bm;

	//PLL SPI
	PORTC_DIRSET = PIN4_bm; //SS
	PORTC_OUTSET = PIN4_bm; //SS
	PORTC_DIRSET = PIN5_bm; //MOSI
	PORTC_DIRCLR = PIN6_bm; //MISO
	PORTC_DIRSET = PIN7_bm; //SCK

	//RF Relay
	PORTD_DIRSET = PIN3_bm;
	PORTD_OUTCLR = PIN3_bm;

	//-5V DCDC Converter SHUTDOWN
	PORTD_DIRSET = PIN0_bm;
	PORTD_OUTSET = PIN0_bm;

	//Jack Power Present
	PORTC_DIRCLR = PIN1_bm;
	//USB Power Present
	PORTD_DIRCLR = PIN2_bm;

	//Front Panel Detection
	PORTB_DIRSET = PIN2_bm;
	PORTD_OUTCLR = PIN3_bm;

	//+4.5 V Enable
	PORTC_DIRSET = PIN0_bm;
	PORTC_OUTCLR = PIN0_bm;
}



void string_digits_commas(char *str1, char *str2)
{
	uint8_t i;
	i = strlen(str1);
	//we are using a /10 frequency
	switch(i)
	{
		case 7:
		str2[0] = ' ';
		str2[1] = ' ';
		str2[2] = ' ';
		str2[3] = ' ';
		str2[4] = str1[0];	//x0 MHz
		str2[5] = str1[1];
		str2[6] = ',';
		str2[7] = str1[2];
		str2[8] = str1[3];
		str2[9] = str1[4];
		str2[10] = ',';
		str2[11] = str1[5];
		str2[12] = str1[6];
		str2[13] = 0;
		break;
		case 8:
		str2[0] = ' ';
		str2[1] = ' ';
		str2[2] = ' ';
		str2[3] = str1[0];	//x00 MHz
		str2[4] = str1[1];
		str2[5] = str1[2];
		str2[6] = ',';
		str2[7] = str1[3];
		str2[8] = str1[4];
		str2[9] = str1[5];
		str2[10] = ',';
		str2[11] = str1[6];
		str2[12] = str1[7];
		str2[13] = 0;
		break;
		case 9:
		str2[0] = ' ';
		str2[1] = str1[0];	//x GHz
		str2[2] = ',';
		str2[3] = str1[1];
		str2[4] = str1[2];
		str2[5] = str1[3];
		str2[6] = ',';
		str2[7] = str1[4];
		str2[8] = str1[5];
		str2[9] = str1[6];
		str2[10] = ',';
		str2[11] = str1[7];
		str2[12] = str1[8];
		str2[13] = 0;
		break;
		case 10:
		str2[0] = str1[0];	//x0 GHz
		str2[1] = str1[1];
		str2[2] = ',';
		str2[3] = str1[2];
		str2[4] = str1[3];
		str2[5] = str1[4];
		str2[6] = ',';
		str2[7] = str1[5];
		str2[8] = str1[6];
		str2[9] = str1[7];
		str2[10] = ',';
		str2[11] = str1[8];
		str2[12] = str1[9];
		str2[13] = 0;
		break;
	}

}

void string_digits_commas_dbm(char *str1, char *str2)
{
	uint8_t i;
	i = strlen(str1);
	if(str1[0] == '-')
	{
		switch(i)
		{
			case 2:
			str2[0] = str1[0];
			str2[1] = ' ';
			str2[2] = '0';
			str2[3] = '.';
			str2[4] = str1[1];
			str2[5]= 0;
			break;
			case 3:
			str2[0] =  str1[0];
			str2[1] = ' ';
			str2[2] = str1[1];
			str2[3] = '.';
			str2[4] = str1[2];
			str2[5]= 0;
			break;
			case 4:
			str2[0] = str1[0];
			str2[1] = str1[1];
			str2[2] = str1[2];
			str2[3] = '.';
			str2[4] = str1[3];
			str2[5]= 0;
			break;
		}
	}
	else
	{
		switch(i)
		{
			case 1:
			str2[0] =  ' ';
			str2[1] =  ' ';
			str2[2] = '0';
			str2[3] = '.';
			str2[4] = str1[0];
			str2[5]= 0;
			break;
			case 2:
			str2[0] =  ' ';
			str2[1] =  ' ';
			str2[2] = str1[0];
			str2[3] = '.';
			str2[4] = str1[1];
			str2[5]= 0;
			break;
			case 3:
			str2[0] =  ' ';
			str2[1] = str1[0];
			str2[2] = str1[1];
			str2[3] = '.';
			str2[4] = str1[2];
			str2[5]= 0;
			break;
		}
	}

}