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
#include "LMX2592.h"
#include "scpi-def.h"

extern ui_t ui;
extern rfgen_t rfgen;
extern LMX2592_t LMX2592;
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

void string_digits_commas_dbm_scpi(char *str1, char *str2)
{
	uint8_t i;
	i = strlen(str1);
	if(str1[0] == '-')
	{
		switch(i)
		{
			case 2:
			str2[0] = str1[0];
			str2[1] = '0';
			str2[2] = '.';
			str2[3] = str1[1];
			str2[4]= 0;
			break;
			case 3:
			str2[0] = str1[0];
			str2[1] = str1[1];
			str2[2] = '.';
			str2[3] = str1[2];
			str2[4]= 0;
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
			str2[0] = '0';
			str2[1] = '.';
			str2[2] = str1[0];
			str2[3]= 0;
			break;
			case 2:
			str2[0] = str1[0];
			str2[1] = '.';
			str2[2] = str1[1];
			str2[3]= 0;
			break;
			case 3:
			str2[0] = str1[0];
			str2[1] = str1[1];
			str2[2] = '.';
			str2[3] = str1[2];
			str2[4]= 0;
			break;
		}
	}

}

size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
	(void) context;
	//return fwrite(data, 1, len, stdout);
	return udi_cdc_write_buf(data, len);
}

scpi_result_t SCPI_Flush(scpi_t * context) {
	(void) context;

	return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err) {
	char rx_buffer[50];
	(void) context;

	//fprintf(stderr, "**ERROR: %d, \"%s\"\r\n", (int16_t) err, SCPI_ErrorTranslate(err));
	udi_cdc_write_buf("**ERROR: ", 9);
	itoa((int16_t)err, rx_buffer, 10);
	udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
	udi_cdc_putc(' ');
	udi_cdc_write_buf(SCPI_ErrorTranslate(err),strlen(SCPI_ErrorTranslate(err)));
	udi_cdc_write_buf("\r\n", 2);
	return 0;
}

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
	char rx_buffer[50];
	(void) context;

	if (SCPI_CTRL_SRQ == ctrl) {
		//fprintf(stderr, "**SRQ: 0x%X (%d)\r\n", val, val);
		udi_cdc_write_buf("**SRQ: ", 7);
		utoa(val, rx_buffer, 10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
		udi_cdc_write_buf("\r\n", 2);
		} else {
		udi_cdc_write_buf("**CTRL ", 7);
		utoa(ctrl, rx_buffer, 10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
		udi_cdc_putc(' ');
		utoa(val, rx_buffer, 10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
		udi_cdc_write_buf("\r\n", 2);
		//fprintf(stderr, "**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);
	}
	return SCPI_RES_OK;
}


scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context) {
	(void) context;

	return SCPI_RES_ERR;
}




void RFgenReset(LMX2592_t *LMX2592, ui_t *ui, rfgen_t *rfgen)
{
	rfgen->Frequency_10 = 810000000; //100MHz
	rfgen->power_dbm = -100; //-10.0 dBm
	ltoa(rfgen->Frequency_10,rfgen->Freq_string,10);
	string_digits_commas(rfgen->Freq_string,ui->Freq_string_print);

	itoa(rfgen->power_dbm,rfgen->Power_string,10);
	string_digits_commas_dbm(rfgen->Power_string, ui->Power_string_print);

	ui->refresh = 1;
	ui->cur_pos = CUR_POS_MAIN_10MHZ;
	ui->cur_x = CUR_POS_MAIN_10MHZ_X;
	ui->cur_y = CUR_POS_MAIN_FREQ_Y;
	LMX2592_init_config(LMX2592);
	LMX2592_reset();
	delay_ms(100);
	LMX2592_defaults();

	LMX2592_set_PFD(LMX2592, 100000000);
	LMX2592_set_out_freq(LMX2592,rfgen->Frequency_10, 0xFF);
	LMX2592_RFonOff(LMX2592, 0);
	LMX2592_configure(LMX2592);
	//LMX2592_write_24_reg(0x002304  );
}

scpi_result_t SCPI_Reset(scpi_t * context)
{
	(void) context;
	udi_cdc_write_buf( "**Reset\r\n", 9);
	RFgenReset(&LMX2592, &ui, &rfgen);
	return SCPI_RES_OK;
}
