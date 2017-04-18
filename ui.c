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
	char WELCOME_STRING[] = "\r\n\r\nEpsilon R Labs RF Generator\r\n";
	char MENU1_STRING[] = "Intensity (0..255) :";
	char MENU2_STRING[] = "DD/MM/YY :";
	char MENU3_STRING[] = "hh:mm :";
	char MENU6_STRING[] = "Frequency (128..999) :";
	char MENU7_STRING[] = "Negative Threshold (7..12) :";
	char MENU8_STRING[] = "Burst Length (8..32) :";
	char MENU9_STRING[] = "Burst Repetition (1..63) :";
	char MENUa_STRING[] = "NDIL (1..31) :";

	char FREQUENCY_SET_STRING[] = "\r\nFset: ";
	char PLL_pre_N_STRING[] = "\r\nPRE N: ";
	char PLL_n_div_STRING[] = "\r\nN DIV: ";
	char PLL_num_STRING[] = "\r\nNUM: ";
	char PLL_den_STRING[] = "\r\nDEN: ";
	char VCO_dbl_STRING[] = "\r\nVCO Doubler: ";
	char PFD_freq_STRING[] = "\r\nPFD Freq: ";
	char RF_out_div_seg1_STRING[] = "\r\nOUT DIV1: ";
	char RF_out_div_seg2_STRING[] = "\r\nOUT DIV2: ";
	char RF_out_div_seg3_STRING[] = "\r\nOUT DIV3: ";
	char Mash_Order_STRING[] = "\r\nMash_Order: ";
	char MASH_dith_EN_STRING[] = "\r\nMash Dither: ";
	char PFD_delay_STRING[] = "\r\nPFD Delay: ";

	//char _STRING[] = "\r\n: ";
	//char MENU4_STRING[] = "Display date and time";
	char rx_buffer[20];


		udi_cdc_putc('\r');
		udi_cdc_putc('\n');
		udi_cdc_putc('\r');
		udi_cdc_putc('\n');
		udi_cdc_putc('\r');
		udi_cdc_putc('\n');

		udi_cdc_write_buf(FREQUENCY_SET_STRING,sizeof(FREQUENCY_SET_STRING));
		uint64toa(LMX2592->Out_freq,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(PLL_pre_N_STRING,sizeof(PLL_pre_N_STRING));
		utoa(LMX2592->PLL_pre_N,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(PLL_n_div_STRING,sizeof(PLL_n_div_STRING));
		utoa(LMX2592->PLL_n_div,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(PLL_num_STRING,sizeof(PLL_num_STRING));
		ultoa(LMX2592->PLL_num,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(PLL_den_STRING,sizeof(PLL_den_STRING));
		ultoa(LMX2592->PLL_den,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(VCO_dbl_STRING,sizeof(VCO_dbl_STRING));
		utoa(LMX2592->VCO_doubler,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(PFD_freq_STRING,sizeof(PFD_freq_STRING));
		ultoa(LMX2592->PFD_freq,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(RF_out_div_seg1_STRING,sizeof(RF_out_div_seg1_STRING));
		utoa(LMX2592->RF_out_div_seg1,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(RF_out_div_seg2_STRING,sizeof(RF_out_div_seg2_STRING));
		utoa(LMX2592->RF_out_div_seg2,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(RF_out_div_seg3_STRING,sizeof(RF_out_div_seg3_STRING));
		utoa(LMX2592->RF_out_div_seg3,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(MASH_dith_EN_STRING,sizeof(MASH_dith_EN_STRING));
		utoa(LMX2592->MASH_dith_EN,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(Mash_Order_STRING,sizeof(Mash_Order_STRING));
		utoa(LMX2592->Mash_Order,rx_buffer,10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));

		udi_cdc_write_buf(PFD_delay_STRING,sizeof(PFD_delay_STRING));
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
			udi_cdc_write_buf(WELCOME_STRING,sizeof(WELCOME_STRING));
			//MenuPos = 1;

			break;
			case '1':
			udi_cdc_write_buf(MENU1_STRING,sizeof(MENU1_STRING));
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