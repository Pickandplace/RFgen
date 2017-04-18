/**
*Epsilon r Labs RF Generator 30MHz 9.8GHz
*Copyright (C) 2017 Jean Wlodarski
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

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */
/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <stdint.h>
//#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <asf.h>
#include <string.h>
#include "main.h"
#include <twi_master_driver.h>
#include "qdec_driver.h"

#include <conf_usb.h>
#include "ui.h"
#include "uart.h"
#include "u8g.h"
#include "LMX2592.h"
#include <power.h>
#include "scpi.h"
#include "scpi-def.h"

size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
	(void) context;
	//return fwrite(data, 1, len, stdout);
	return udi_cdc_multi_write_buf(0, data, len);
}

scpi_result_t SCPI_Flush(scpi_t * context) {
	(void) context;

	return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err) {
	char rx_buffer[10];
	(void) context;

	//fprintf(stderr, "**ERROR: %d, \"%s\"\r\n", (int16_t) err, SCPI_ErrorTranslate(err));
	udi_cdc_multi_write_buf(0, "**ERROR: ", 9);
	itoa((int16_t)err, rx_buffer, 10);
	udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
	udi_cdc_putc(' ');
	udi_cdc_write_buf(SCPI_ErrorTranslate(err),strlen(SCPI_ErrorTranslate(err)));
	udi_cdc_multi_write_buf(0, "\r\n", 2);
	return 0;
}

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
	char rx_buffer[10];
	(void) context;

	if (SCPI_CTRL_SRQ == ctrl) {
		//fprintf(stderr, "**SRQ: 0x%X (%d)\r\n", val, val);
		udi_cdc_multi_write_buf(0, "**SRQ: ", 7);
		utoa(val, rx_buffer, 10);
		udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
		udi_cdc_multi_write_buf(0, "\r\n", 2);
		} else {
				udi_cdc_multi_write_buf(0, "**CTRL ", 7);
				utoa(ctrl, rx_buffer, 10);
				udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
				udi_cdc_putc(' ');
				utoa(val, rx_buffer, 10);
				udi_cdc_write_buf(rx_buffer,strlen(rx_buffer));
				udi_cdc_multi_write_buf(0, "\r\n", 2);
		//fprintf(stderr, "**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);
	}
	return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * context) {
	(void) context;

	//fprintf(stderr, "**Reset\r\n");
	udi_cdc_multi_write_buf(0, "**Reset\r\n", 9);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context) {
	(void) context;

	return SCPI_RES_ERR;
}

#define TWI_MASTER       TWIE
#define TWI_MASTER_PORT  PORTE
#define TWI_MASTER_ADDR  0x50


void OLEDcommand(uint8_t command);
void RfgenBoardInit(void);
void string_digits_commas(char *str1, char *str2);
void string_digits_commas_dbm(char *str1, char *str2);

TWI_Master_t twiMaster;
uint8_t twiBuffer[10];
uint8_t i;
#define F_SYS   32000000
#define BAUDRATE        400000
#define TWI_BAUDSETTING TWI_BAUD(F_SYS, BAUDRATE)

u8g_t u8g;
uint32_t Frequency_10 = 10000000; //100MHz
char string[10];
char string2[10];
char Freq_string[11];
char Freq_string_print[14];
char Power_string_print[6];
char PowerB_string_print[6];
uint32_t freq_MHz = 50;
uint32_t freq_MHz_tmp, Freq_MHz_old ;
uint16_t cnt_old;
int16_t power_tmp;

extern ui_t ui;

int16_t power_dbm;
char Power_string[5];

char smbuffer[20];
uint8_t smbuffer_ptr;
#define	CUR_POS_MAIN_MAX	12
#define	CUR_POS_MAIN_RFONOFF	3
#define	CUR_POS_MAIN_10HZ	12
#define	CUR_POS_MAIN_100HZ	11
#define	CUR_POS_MAIN_1kHZ	10
#define	CUR_POS_MAIN_10kHZ	9
#define	CUR_POS_MAIN_100kHZ	8
#define	CUR_POS_MAIN_1MHZ	7
#define	CUR_POS_MAIN_10MHZ	6
#define	CUR_POS_MAIN_100MHZ	5
#define	CUR_POS_MAIN_1GHZ	4
#define	CUR_POS_MAIN_01dBm	2
#define	CUR_POS_MAIN_1dBm	1
#define	CUR_POS_MAIN_10dBm	0

#define	CUR_SELECTED		1
#define	CUR_FREE			0

#define CUR_WIDTH				6
#define	CUR_POS_MAIN_1HZ_X		91
#define	CUR_POS_MAIN_10HZ_X		84
#define	CUR_POS_MAIN_100HZ_X	77
#define	CUR_POS_MAIN_1kHZ_X		63
#define	CUR_POS_MAIN_10kHZ_X	56
#define	CUR_POS_MAIN_100kHZ_X	49
#define	CUR_POS_MAIN_1MHZ_X		35
#define	CUR_POS_MAIN_10MHZ_X	28
#define	CUR_POS_MAIN_100MHZ_X	21
#define	CUR_POS_MAIN_1GHZ_X		7
#define	CUR_POS_MAIN_01dBm_X	28
#define	CUR_POS_MAIN_1dBm_X		14
#define	CUR_POS_MAIN_10dBm_X	7

#define	CUR_POS_MAIN_FREQ_Y	13
#define	CUR_POS_MAIN_POW_Y	30
#define UI_FREQ_POS_Y		12
#define UI_POW_POS_Y		29

#define UI_RFONOFF_POS_X		100
#define UI_LOCK_POS_X		80

#define POWER_UPPPER_LIMIT	100
#define POWER_LOWER_LIMIT -300
#define FREQ_UPPPER_LIMIT	1000000000//10GHz
#define FREQ_LOWER_LIMIT 2000000//20MHz
#define ENC_INIT		100
LMX2592_t LMX2592;
int_fast16_t encoder_value;
uint32_t freq_tmp;
bool new_enc_val;
bool enc_inc;
//bool rfOnOff;
bool freq_changed, pow_changed;
bool lock_lost;
static volatile bool main_b_cdc_enable = true;
volatile uint8_t USB_port;
ISR(TWIE_TWIM_vect)
    {
      TWI_MasterInterruptHandler(&twiMaster);
    }

ISR(PORTB_INT0_vect)
{
	ui.refresh = 1;
	if(ui.cur_pos != CUR_POS_MAIN_RFONOFF)
	{
		ui.cur_selected ^= 1;

		if(ui.cur_selected == 1)
		{
			encoder_value = 0;
		}
		else
			encoder_value = ui.cur_pos;
	}
	else
	{
		ui.rfOnOff ^= 1;
		pow_changed = 1;
	}

}

int main (void)
{

	//uint8_t spi_buffer[10];
	uint32_t i;
	board_init();
	RfgenBoardInit();

	pmic_init();
	//OSC_XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_16KCLK_gc;
	//OSC_CTRL |= OSC_XOSCEN_bm;
	//while(!(OSC_STATUS & OSC_XOSCRDY_bm));
	sysclk_init();
	cpu_irq_enable();
	irq_initialize_vectors();


//	PR.PRGEN = 0xFB;
//	PR.PRPC = 0xF7;
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	PMIC.CTRL |= PMIC_MEDLVLEN_bm;
	PMIC.CTRL |= PMIC_HILVLEN_bm;

	PORTB.INT0MASK |= 0x02;
	PORTB.PIN1CTRL	= PORT_OPC_WIREDORPULL_gc | PORT_ISC_FALLING_gc;
	PORTB.INTCTRL	= PORT_INT0LVL_LO_gc;

	sei();
	TWI_MASTER_PORT.PIN0CTRL = PORT_OPC_WIREDANDPULL_gc;
	TWI_MASTER_PORT.PIN1CTRL = PORT_OPC_WIREDANDPULL_gc;
/*	i=30000000;//3000000;
	LMX2592_set_PFD(&LMX2592, 100000000);
	while(i<=980000000)
	{
		float freqdbg;
		int32_t freq_diff;
		LMX2592_set_out_freq(&LMX2592,i, 0xFF);
		uint32_t PFD_freq= LMX2592.PFD_freq;
		uint32_t PLL_pre_N;
		uint32_t PLL_n_div= LMX2592.PLL_n_div;
		uint32_t PLL_num= LMX2592.PLL_num;
		uint32_t PLL_den = LMX2592.PLL_den;
		uint32_t PLL_out_div;
		uint8_t VCO_dbl;
		if(LMX2592.PLL_out_div == 0)
			PLL_out_div = 1;
		else
			PLL_out_div = LMX2592.PLL_out_div;

		if(LMX2592.PLL_pre_N == 0)
			PLL_pre_N = 2;
		else
			PLL_pre_N = 4;

		if(LMX2592.VCO_doubler == 1)
			VCO_dbl = 2;
		else
			VCO_dbl = 1;

		freqdbg = (float)((float)PLL_num / (float)PLL_den);
		freqdbg += PLL_n_div;
		freqdbg *= PLL_pre_N;
		freqdbg *= PFD_freq;
		freqdbg /= PLL_out_div;
		freq_diff = (uint32_t)(freqdbg/10) - i;
		i += 10;
	}

	*/


	sysclk_enable_peripheral_clock(&TWI_MASTER);
	TWI_MasterInit(&twiMaster, &TWIE, TWI_MASTER_INTLVL_HI_gc, TWI_BAUDSETTING);

	spi_master_init(&SPIC);
	spi_master_setup_device(&SPIC, /*&spi_device_conf, */SPI_MODE_0, 4000000, 1);
	spi_enable(&SPIC);

	#define OLED_ADD 0x3c
	u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x32_hw_spi,U8G_I2C_OPT_DEV_1 );

	//qdec_position = 0;

	LMX2592_ENABLE_CHIP
	delay_ms(100);


	//PORTD_OUTCLR = PIN0_bm;


	LMX2592_init_config(&LMX2592);
	LMX2592_reset();
	delay_ms(100);
	LMX2592_defaults();

	LMX2592_set_PFD(&LMX2592, 100000000);
	LMX2592_set_out_freq(&LMX2592,10000000, 0xFF);
	LMX2592_RFonOff(&LMX2592, 0);
	LMX2592_configure(&LMX2592);
	freq_changed = 0;
	pow_changed = 0;
	delay_ms(100);

	LMX2592_write_24_reg(0x002304  );

	sysclk_enable_peripheral_clock(&EVSYS);
	sysclk_enable_peripheral_clock(&TCC0);

	QDEC_Total_Setup(&PORTA, 6, false, 0, EVSYS_CHMUX_PORTA_PIN6_gc, 0, EVSYS_QDIRM_00_gc, &TCC0, TC_EVSEL_CH0_gc, 16382);

	power_dbm = -100; //-10.0 dBm
	freq_tmp = (uint32_t)Frequency_10;
	ltoa(Frequency_10,Freq_string,10);
	string_digits_commas(Freq_string,Freq_string_print);

	itoa(power_dbm,Power_string,10);
	string_digits_commas_dbm(Power_string, Power_string_print);
	uint8_t tmp;
	ui.refresh = 1;
	ui.cur_pos = CUR_POS_MAIN_10MHZ;
	ui.cur_x = CUR_POS_MAIN_10MHZ_X;
	ui.cur_y = CUR_POS_MAIN_FREQ_Y;
	encoder_value = CUR_POS_MAIN_10MHZ;
	TCC0.CNT = 1000;
	cnt_old = TCC0.CNT;

		PORTA_DIRCLR = PIN0_bm;
		PORTA_DIRCLR = PIN1_bm;
		PORTA_DIRCLR = PIN2_bm;
		PORTA_DIRCLR = PIN3_bm;
		PORTA_DIRCLR = PIN4_bm;
		PORTA_DIRCLR = PIN5_bm;

	PORTD_OUTCLR = PIN3_bm;
	PORTD_OUTSET = PIN3_bm;
	PORTD_OUTCLR = PIN3_bm;
	SCPI_Init(&scpi_context,
	scpi_commands,
	&scpi_interface,
	scpi_units_def,
	SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
	scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
	scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);
	ui_init();
	udc_start();
	udc_attach();
	USB_port=0;
	smbuffer_ptr = 0;
	while(1)
	{
		if(udi_cdc_is_rx_ready()==1)
		{
			smbuffer[smbuffer_ptr] = udi_cdc_getc();

			if(smbuffer[smbuffer_ptr] == '\n')
				{
					smbuffer[smbuffer_ptr+1] = 0;
					SCPI_Input(&scpi_context, smbuffer, strlen(smbuffer));
					for(i=0;i<20;i++)
						smbuffer[i] = 0;
					smbuffer_ptr = 0;
				}
				else
				{
					if(smbuffer_ptr < 19)
					smbuffer_ptr++;
					else
					smbuffer_ptr = 0;
				}
		}


		sysclk_disable_peripheral_clock(&TWI_MASTER);
		if(ui.refresh == 1)
		{
			sysclk_enable_peripheral_clock(&TWI_MASTER);
		u8g_FirstPage(&u8g);
		do
		{
			u8g_SetFont(&u8g, u8g_font_profont15r);

		if(ui.cur_selected == 1)//highlighting of the selected digit
		{
				switch(ui.cur_pos)
				{
					case	CUR_POS_MAIN_10HZ	:
						string[0] = Freq_string_print[12];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10HZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_100HZ	:
						string[0] = Freq_string_print[11];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_100HZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1kHZ	:
						string[0] = Freq_string_print[9];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_1kHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_10kHZ	:
						string[0] = Freq_string_print[8];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10kHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_100kHZ	:
						string[0] = Freq_string_print[7];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_100kHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1MHZ	:
						string[0] = Freq_string_print[5];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_1MHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_10MHZ	:
						string[0] = Freq_string_print[4];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10MHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_100MHZ	:
						if(Freq_string_print[3] == ' ')
							string[0] = '0';
						else
							string[0] = Freq_string_print[3];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_100MHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1GHZ	:
						if(Freq_string_print[1] == ' ')
							string[1] = '0';
						else
							string[1] = Freq_string_print[1];
						string[0] = Freq_string_print[0];
						string[2] = 0;
						u8g_DrawStr(&u8g,1,12,string);
					break;
					case	CUR_POS_MAIN_01dBm	:
						string[0] = Power_string_print[4];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_01dBm_X,UI_POW_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1dBm	:
					string[0] = Power_string_print[2];
					string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_1dBm_X,UI_POW_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_10dBm	:
					string[0] = Power_string_print[1];
					string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10dBm_X,UI_POW_POS_Y-1,string);
					break;
				}
		}

		u8g_DrawStr(&u8g,0,UI_FREQ_POS_Y,Freq_string_print);
		tmp = u8g_GetStrPixelWidth(&u8g,"10,000,000,00");
		u8g_DrawStr(&u8g,tmp+1,UI_FREQ_POS_Y,"0");
		u8g_DrawStr(&u8g,tmp+10,UI_FREQ_POS_Y,"Hz");

		u8g_DrawStr(&u8g,0, UI_POW_POS_Y,Power_string_print);
		tmp = u8g_GetStrPixelWidth(&u8g,"-10.0");
		u8g_DrawStr(&u8g,tmp+4,UI_POW_POS_Y,"dBm");
		u8g_DrawStr(&u8g, tmp+4+40,UI_POW_POS_Y,PowerB_string_print);

		u8g_SetFont(&u8g, u8g_font_profont10r);



		if(ui.rfOnOff == 0)
		{
			u8g_DrawStr(&u8g,UI_RFONOFF_POS_X,UI_POW_POS_Y-1,"RF:OFF");
		}
		else
		{
			u8g_DrawStr(&u8g,UI_RFONOFF_POS_X,UI_POW_POS_Y-1,"RF:ON");
			u8g_DrawStr(&u8g,UI_RFONOFF_POS_X,UI_POW_POS_Y,"   ON");
		}
		if(lock_lost == 1 )
		{
			u8g_DrawStr(&u8g,UI_LOCK_POS_X,UI_POW_POS_Y-1,"LCK!");
		}

		u8g_SetFont(&u8g, u8g_font_profont15r);
		if(ui.cur_pos != CUR_POS_MAIN_RFONOFF)
		{
			u8g_DrawHLine(&u8g,ui.cur_x,ui.cur_y,CUR_WIDTH);
			u8g_DrawHLine(&u8g,ui.cur_x,ui.cur_y+1,CUR_WIDTH);
		}
		else
		{
			u8g_DrawHLine(&u8g,ui.cur_x,ui.cur_y,CUR_WIDTH*2);
			u8g_DrawHLine(&u8g,ui.cur_x,ui.cur_y+1,CUR_WIDTH*2);
		}

		} while ( u8g_NextPage(&u8g) );
			ui.refresh = 0;
		}//if refresh == 1

		if((PORTC_IN & 0x40) != 0x40)
		{
			if(lock_lost == 0)
				ui.refresh = 1;
			lock_lost	= 1;

		}
		else{
			if(lock_lost == 1)
				ui.refresh = 1;
			lock_lost = 0;
		}

		if(cnt_old < (TCC0.CNT&0xfffe))
		{
			encoder_value--;
			cnt_old = (TCC0.CNT&0xfffe);
			new_enc_val = 1;
			enc_inc = 0;
		}
		if(cnt_old > (TCC0.CNT&0xfffe))
		{
			encoder_value++;
			cnt_old = (TCC0.CNT&0xfffe);
			new_enc_val = 1;
			enc_inc = 1;
		}

		if(new_enc_val )
		{
			ui.refresh = 1;
			new_enc_val = 0;
			if(ui.cur_selected == 1)
			{
				freq_changed = 0;
				pow_changed = 0;
				if(enc_inc == 1)
				{
					switch(ui.cur_pos)
					{
						case	CUR_POS_MAIN_10HZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT))
								freq_tmp += 1ul;
						break;
						case	CUR_POS_MAIN_100HZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-10ul))
								freq_tmp += 10ul;
						break;
						case	CUR_POS_MAIN_1kHZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-100ul))
								freq_tmp += 100ul;
						break;
						case	CUR_POS_MAIN_10kHZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-1000ul))
								freq_tmp += 1000ul;
						break;
						case	CUR_POS_MAIN_100kHZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-10000ul))
								freq_tmp += 10000ul;
						break;
						case	CUR_POS_MAIN_1MHZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-100000ul))
								freq_tmp += 100000ul;
						break;
						case	CUR_POS_MAIN_10MHZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-1000000ul))
								freq_tmp += 1000000ul;
						break;
						case	CUR_POS_MAIN_100MHZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-10000000ul))
								freq_tmp += 10000000ul;
						break;
						case	CUR_POS_MAIN_1GHZ	:
							freq_changed = 1;
							if(freq_tmp < (FREQ_UPPPER_LIMIT-100000000ul))
								freq_tmp += 100000000ul;
							else
								freq_tmp = FREQ_UPPPER_LIMIT;
						break;
						case	CUR_POS_MAIN_01dBm	:
							pow_changed = 1;
							power_dbm +=  5;
						break;
						case	CUR_POS_MAIN_1dBm	:
							pow_changed = 1;
							power_dbm +=  10ul;
						break;
						case	CUR_POS_MAIN_10dBm	:
							pow_changed = 1;
							power_dbm +=  100ul;
						break;
						case	CUR_POS_MAIN_RFONOFF	:
							ui.rfOnOff =  1;
							LMX2592_RFonOff(&LMX2592, ui.rfOnOff);
							LMX2592_configure(&LMX2592);
						break;
					}
				}
				if(enc_inc == 0)
				{
					switch(ui.cur_pos)
					{
						case	CUR_POS_MAIN_10HZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+1ul))
								freq_tmp -= 1ul;
						break;
						case	CUR_POS_MAIN_100HZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+1ul))
								freq_tmp -= 10ul;
						break;
						case	CUR_POS_MAIN_1kHZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+100ul))
								freq_tmp -= 100ul;
						break;
						case	CUR_POS_MAIN_10kHZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+1000ul))
								freq_tmp -= 1000ul;
						break;
						case	CUR_POS_MAIN_100kHZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+10000ul))
								freq_tmp -= 10000ul;
						break;
						case	CUR_POS_MAIN_1MHZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+100000ul))
								freq_tmp -= 100000ul;
						break;
						case	CUR_POS_MAIN_10MHZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+1000000ul))
								freq_tmp -= 1000000ul;
						break;
						case	CUR_POS_MAIN_100MHZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+10000000ul))
							freq_tmp -= 10000000ul;
						break;
						case	CUR_POS_MAIN_1GHZ	:
							freq_changed = 1;
							if(freq_tmp >= (FREQ_LOWER_LIMIT+100000000ul))
								freq_tmp -= 100000000ul;
							else
								if(freq_tmp >= (FREQ_LOWER_LIMIT+10000000ul))
									freq_tmp -= 10000000ul;
								else
									if(freq_tmp >= (FREQ_LOWER_LIMIT+1000000ul))
										freq_tmp -= 1000000ul;
						break;
						case	CUR_POS_MAIN_01dBm	:
							pow_changed = 1;
							power_dbm -=  5;
						break;
						case	CUR_POS_MAIN_1dBm	:
							pow_changed = 1;
							power_dbm -=  10ul;
						break;
						case	CUR_POS_MAIN_10dBm	:
							pow_changed = 1;
							power_dbm -=  100ul;
						break;
						case	CUR_POS_MAIN_RFONOFF	:
							ui.rfOnOff ^=  1;
							pow_changed = 1;
						break;
					}
				}
				if(freq_changed == 1)
				{
					Frequency_10 = (uint32_t)freq_tmp;
					ultoa(Frequency_10,Freq_string,10);
					string_digits_commas(Freq_string,Freq_string_print);
					/*power_tmp = max_power(Frequency_10);
					if(power_dbm > power_tmp)
					power_dbm = power_tmp;

					power_tmp = min_power(Frequency_10);
					if(power_dbm <  power_tmp)
					power_dbm = power_tmp;*/

					itoa(power_dbm,Power_string,10);

					string_digits_commas_dbm(Power_string, Power_string_print);
				}

				if(pow_changed == 1)
				{
				/*	power_tmp = max_power(Frequency_10);
					if(power_dbm > power_tmp)
						power_dbm = power_tmp;

					power_tmp = min_power(Frequency_10);
					if(power_dbm <  power_tmp)
						power_dbm = power_tmp;*/
					if(power_dbm > 0)
					{
						power_dbm = 0;
						LMX2592.PowerB++;
					}
					if(power_dbm < -315)
					{
						power_dbm = -315;
						if(LMX2592.PowerB > 0)
							LMX2592.PowerB--;
					}

					if(power_dbm == -5)
					{
						if(LMX2592.PowerB > 0)
						{
							LMX2592.PowerB--;
							power_dbm = 0;
						}
					}

					if(LMX2592.PowerB > 63)
					LMX2592.PowerB = 63;

					if((LMX2592.PowerB > 31 ) && (power_tmp <= 31))//Theres a gap on the LMX2592 output power register
					{
						LMX2592.PowerB = LMX2592.PowerB + 16;

					}
					if((LMX2592.PowerB < 48 ) && (power_tmp >= 48))//Theres a gap on the LMX2592 output power register
					{
						LMX2592.PowerB = LMX2592.PowerB - 16;

					}

					power_tmp = LMX2592.PowerB;
					itoa(power_dbm,Power_string,10);
					string_digits_commas_dbm(Power_string, Power_string_print);
					itoa(LMX2592.PowerB,PowerB_string_print,10);
				}

			}
			if(ui.cur_selected == 0)
			{
				//cursor not selected
				if(encoder_value > CUR_POS_MAIN_MAX)
				{
					encoder_value = 0;
				}
				if(encoder_value < 0)
				{
					encoder_value = CUR_POS_MAIN_MAX;
				}
				ui.cur_pos = encoder_value;
				switch(ui.cur_pos)
				{
					case	CUR_POS_MAIN_10HZ	:
						ui.cur_x = CUR_POS_MAIN_10HZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_100HZ	:
						ui.cur_x = CUR_POS_MAIN_100HZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_1kHZ	:
						ui.cur_x = CUR_POS_MAIN_1kHZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_10kHZ	:
						ui.cur_x = CUR_POS_MAIN_10kHZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_100kHZ	:
						ui.cur_x = CUR_POS_MAIN_100kHZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_1MHZ	:
						ui.cur_x = CUR_POS_MAIN_1MHZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_10MHZ	:
						ui.cur_x = CUR_POS_MAIN_10MHZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_100MHZ	:
						ui.cur_x = CUR_POS_MAIN_100MHZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_1GHZ	:
						ui.cur_x = CUR_POS_MAIN_1GHZ_X;
						ui.cur_y = CUR_POS_MAIN_FREQ_Y;
					break;
					case	CUR_POS_MAIN_01dBm	:
						ui.cur_x = CUR_POS_MAIN_01dBm_X;
						ui.cur_y = CUR_POS_MAIN_POW_Y;
					break;
					case	CUR_POS_MAIN_1dBm	:
						ui.cur_x = CUR_POS_MAIN_1dBm_X;
						ui.cur_y = CUR_POS_MAIN_POW_Y;
					break;
					case	CUR_POS_MAIN_10dBm	:
						ui.cur_x = CUR_POS_MAIN_10dBm_X;
						ui.cur_y = CUR_POS_MAIN_POW_Y;
					break;
					case	CUR_POS_MAIN_RFONOFF	:
						ui.cur_x = UI_RFONOFF_POS_X;
						ui.cur_y= CUR_POS_MAIN_POW_Y;
					break;
				}
			}

		}
	if((freq_changed == 1) ||  (pow_changed == 1) )
	{
		freq_changed = 0;
		pow_changed = 0;
		if(ui.rfOnOff == 1)
		{

			LMX2592_set_out_freq(&LMX2592, Frequency_10, 0);
			//power_dbm = PowerSend(&LMX2592, Frequency_10, power_dbm);
			PowerSend(&LMX2592, Frequency_10, power_dbm);
			LMX2592_RFonOff(&LMX2592, 1);
			LMX2592_configure(&LMX2592);
			/*if (USB_port == 1)
			{
				Display_ui(&LMX2592);
			}*/
		}
		else
		{
			LMX2592_set_out_freq(&LMX2592, Frequency_10, 0);
			LMX2592_RFonOff(&LMX2592, 0);
			LMX2592_configure(&LMX2592);
			/*if (USB_port == 1)
			{
				Display_ui(&LMX2592);
			}*/
		}


	}

	}//Main loop

	return(0);
}

void OLEDcommand(uint8_t command)
{
	uint8_t tmp[2];
	tmp[0] = 0x80;
	tmp[1] = command;
	TWI_MasterWrite(&twiMaster, OLED_ADD, tmp,2,0);
	while (twiMaster.status != TWIM_STATUS_READY);
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

void main_suspend_action(void)
{
	ui_powerdown();
}

void main_resume_action(void)
{
	ui_wakeup();
}

void main_sof_action(void)
{
	if (!main_b_cdc_enable)
	return;
	ui_process(udd_get_frame_number());
}

#ifdef USB_DEVICE_LPM_SUPPORT
void main_suspend_lpm_action(void)
{
	ui_powerdown();
}

void main_remotewakeup_lpm_disable(void)
{
	ui_wakeup_disable();
}

void main_remotewakeup_lpm_enable(void)
{
	ui_wakeup_enable();
}
#endif

bool main_cdc_enable(uint8_t port)
{
	main_b_cdc_enable = true;
	// Open communication
	//uart_open(port);
	//Display_ui();
	return true;
}

void main_cdc_disable(uint8_t port)
{
	main_b_cdc_enable = false;
	// Close communication
	//uart_close(port);
}

void main_cdc_set_dtr(uint8_t port, bool b_enable)
{
	if (b_enable) {
		// Host terminal has open COM
		//HEATING_OFF
		//assignAllToValue(1, leds);
		ui_com_open(port);


		USB_port = 1;

		}else{
		// Host terminal has close COM
		ui_com_close(port);
		USB_port = 0;
	}
}
