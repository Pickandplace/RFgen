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
 * ui.c
 *
 * Created: 1/2/2015 3:15:54 PM
 * Under the CC BY-NC-SA license
 * Jean Wlodarski
 * Pickandplace.wordpress.com
 */
#include <asf.h>
#include "ui.h"

#include <string.h>
#include "LMX2592.h"
void Display_ui(LMX2592_t *LMX2592)
{
	uint8_t i;
	char rx_char;
/*
	const char WELCOME_STRING[] PROGMEM = "\r\n\r\nEpsilon R Labs RF Generator\r\n";
	const char MENU1_STRING[] PROGMEM = "Intensity (0..255) :";
	const  char FREQUENCY_SET_STRING[] PROGMEM = "\r\nFset: ";
	const char PLL_pre_N_STRING[] PROGMEM = "\r\nPRE N: ";
	const char PLL_n_div_STRING[] PROGMEM = "\r\nN DIV: ";
	const char PLL_num_STRING[] PROGMEM = "\r\nNUM: ";
	const char PLL_den_STRING[] PROGMEM = "\r\nDEN: ";
	const char VCO_dbl_STRING[] PROGMEM = "\r\nVCO Doubler: ";
	const char VCO_freq_STRING[] PROGMEM = "\r\nVCO Freq: ";
	const char PFD_freq_STRING[] PROGMEM = "\r\nPFD Freq: ";
	const char RF_out_div_seg1_STRING[] PROGMEM = "\r\nOUT DIV1: ";
	const char RF_out_div_seg2_STRING[] PROGMEM = "\r\nOUT DIV2: ";
	const char RF_out_div_seg3_STRING[] PROGMEM = "\r\nOUT DIV3: ";
	const char Mash_Order_STRING[] PROGMEM = "\r\nMash_Order: ";
	const char MASH_dith_EN_STRING[] PROGMEM = "\r\nMash Dither: ";
	const char PFD_delay_STRING[] PROGMEM = "\r\nPFD Delay: ";

*/

	//char _STRING[] = "\r\n: ";
	//char MENU4_STRING[] = "Display date and time";
	char rx_buffer[20];


		udi_cdc_putc('\r');
		udi_cdc_putc('\n');
		udi_cdc_putc('\r');
		udi_cdc_putc('\n');
		udi_cdc_putc('\r');
		udi_cdc_putc('\n');

		udi_cdc_write_buf("\r\nFset: ",sizeof("\r\nFset: "));
		uint64toa(LMX2592->Out_freq,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nPRE N: ",sizeof("\r\nPRE N: "));
		utoa(LMX2592->PLL_pre_N,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nN DIV: ",sizeof("\r\nN DIV: "));
		utoa(LMX2592->PLL_n_div,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nNUM: ",sizeof("\r\nNUM: "));
		ultoa(LMX2592->PLL_num,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nDEN: ",sizeof("\r\nDEN: "));
		ultoa(LMX2592->PLL_den,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nVCO Doubler: ",sizeof("\r\nVCO Doubler: "));
		utoa(LMX2592->VCO_doubler,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nVCO Freq: ",sizeof("\r\nVCO Freq: "));
		ultoa(LMX2592->VCO_freq_10HZ * 10,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nPFD Freq: ",sizeof("\r\nPFD Freq: "));
		ultoa(LMX2592->PFD_freq,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nOUT DIV1: ",sizeof("\r\nOUT DIV1: "));
		utoa(LMX2592->RF_out_div_seg1,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nOUT DIV2: ",sizeof("\r\nOUT DIV2: "));
		utoa(LMX2592->RF_out_div_seg2,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nOUT DIV3: ",sizeof("\r\nOUT DIV3: "));
		utoa(LMX2592->RF_out_div_seg3,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nMash_Order: ",sizeof("\r\nMash_Order: "));
		utoa(LMX2592->MASH_dith_EN,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nMash Dither: ",sizeof("\r\nMash Dither: "));
		utoa(LMX2592->Mash_Order,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf("\r\nPFD Delay: ",sizeof("\r\nPFD Delay: "));
		utoa(LMX2592->PFD_delay,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		//udi_cdc_write_buf(WELCOME_STRING,sizeof(WELCOME_STRING));

	if(udi_cdc_is_rx_ready()==1)
	{
		rx_char = udi_cdc_getc();

		switch (rx_char)
		{
			case 13:
			//if(MenuPos == 0)
			//udi_cdc_putc(12);
			udi_cdc_putc('\r');
			udi_cdc_putc('\n');
			udi_cdc_write_buf("\r\n\r\nEpsilon R Labs RF Generator\r\n",sizeof("\r\n\r\nEpsilon R Labs RF Generator\r\n"));
			//MenuPos = 1;

			break;
			case '1':
			udi_cdc_write_buf("Intensity (0..255) :",sizeof("Intensity (0..255) :"));
			i = 0;
			rx_buffer[0] = 48;
			while(rx_char != 13)
			{
				if(udi_cdc_is_rx_ready()==1)
				{
					rx_char = udi_cdc_getc();
					udi_cdc_putc(rx_char);
					rx_buffer[i] = rx_char;
					i++;
					if (i>5)
					break;
				}
			}
			udi_cdc_putc(10);
			udi_cdc_putc(13);
			//assignAllToValue((uint8_t)numberFromAscii(rx_buffer), leds);
			udi_cdc_putc(10);
			udi_cdc_putc(13);
			break;

			default:
			udi_cdc_putc(rx_char);
			break;
		}
	}


}



void Val8bitToASCII(uint8_t value, char*ascii)
{
	if (value < 10)
	{
		ascii[0] = 48;
		ascii[1] = 48;
		ascii[2] = 48+value;
		return;
	}

	if (value < 100)
	{
		ascii[0] = 48;
		ascii[1] = 48 + (value / 10);
		ascii[2] = 48+ (value % 10);
		return;
	}
	if (value < 200)
	{
		ascii[0] = 48 + (value / 100);
		ascii[1] = 48 + ( (value - 100) / 10);
		ascii[2] = 48+ ((value - 100) % 10);
		return;
	}
	else
	{
		ascii[0] = 48 + (value / 100);
		ascii[1] = 48 + ( (value - 200) / 10);
		ascii[2] = 48+ ((value - 200) % 10);
		return;
	}
}

volatile uint16_t numberFromAscii(char buffer[])
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		if(buffer[i] == 13)
			break;
	}
	if(i==3)
		return ((buffer[0] - 48)*100 + (buffer[1] - 48)*10 + (buffer[2] - 48)) ;
	if(i==2)
		return ((buffer[0] - 48)*10 + (buffer[1] - 48));
	if(i==1)
		return (buffer[0] - 48);
	return(0);
}



char *uint64toa( uint64_t value, char *buffer, int base )
{
	static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *buffer_stop = buffer;
	char *buffer_start = buffer;

	//value = value * measure.div_freq_lf * measure.div_freq_rf * REF_RATIO*8;
	//value += measure.cntd1 * measure.div_freq_rf * (measure.div_freq_lf / 2);
	// generate string in reverse order:
	do
	{
		*buffer_stop++ = digits[value%base];
		value /= base;
	}
	while( value );
	*buffer_stop-- = '\0'; // terminate

	// reverse order:
	while( buffer_start < buffer_stop )
	{
		char  tmp = *buffer_start;
		*buffer_start++ = *buffer_stop;
		*buffer_stop-- = tmp;
	}

	return buffer;
}