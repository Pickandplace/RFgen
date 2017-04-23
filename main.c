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
#include "RFgen.h"
#include "scpi_user_config.h"


#define TWI_MASTER       TWIE
#define TWI_MASTER_PORT  PORTE
#define TWI_MASTER_ADDR  0x50




TWI_Master_t twiMaster;
uint8_t twiBuffer[10];
uint8_t i;
#define F_SYS   32000000
#define BAUDRATE        400000
#define TWI_BAUDSETTING TWI_BAUD(F_SYS, BAUDRATE)

u8g_t u8g;
//uint32_t Frequency_10 = 10000000; //100MHz
char string[10];
char string2[10];
//char Freq_string[11];
//char Freq_string_print[14];

char PowerB_string_print[6];
uint32_t freq_MHz = 50;
uint32_t freq_MHz_tmp, Freq_MHz_old ;
uint16_t cnt_old;
int16_t power_tmp;



//int16_t power_dbm;

#define SCPI_UART_BUFFER 40
char smbuffer[SCPI_UART_BUFFER];
uint8_t smbuffer_ptr;


ui_t ui;
rfgen_t rfgen;
LMX2592_t LMX2592;
int_fast16_t encoder_value;
uint32_t freq_tmp;
bool new_enc_val;
bool enc_inc;
bool freq_changed, pow_changed;
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
		rfgen.rfOnOff ^= 1;
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


	u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x32_hw_spi,U8G_I2C_OPT_DEV_1 );

	//qdec_position = 0;

	LMX2592_ENABLE_CHIP
	delay_ms(100);


	//PORTD_OUTCLR = PIN0_bm;

	RFgenReset(&LMX2592, &ui, &rfgen);
	freq_changed = 0;
	pow_changed = 0;
	delay_ms(100);



	sysclk_enable_peripheral_clock(&EVSYS);
	sysclk_enable_peripheral_clock(&TCC0);

	QDEC_Total_Setup(&PORTA, 6, false, 0, EVSYS_CHMUX_PORTA_PIN6_gc, 0, EVSYS_QDIRM_00_gc, &TCC0, TC_EVSEL_CH0_gc, 16382);


	freq_tmp = rfgen.Frequency_10;

	uint8_t tmp;

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
					for(i=0;i<SCPI_UART_BUFFER;i++)
						smbuffer[i] = 0;
					smbuffer_ptr = 0;
				}
				else
				{
					if(smbuffer_ptr < SCPI_UART_BUFFER - 1)
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
						string[0] = ui.Freq_string_print[12];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10HZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_100HZ	:
						string[0] = ui.Freq_string_print[11];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_100HZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1kHZ	:
						string[0] = ui.Freq_string_print[9];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_1kHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_10kHZ	:
						string[0] = ui.Freq_string_print[8];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10kHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_100kHZ	:
						string[0] = ui.Freq_string_print[7];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_100kHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1MHZ	:
						string[0] = ui.Freq_string_print[5];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_1MHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_10MHZ	:
						string[0] = ui.Freq_string_print[4];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10MHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_100MHZ	:
						if(ui.Freq_string_print[3] == ' ')
							string[0] = '0';
						else
							string[0] = ui.Freq_string_print[3];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_100MHZ_X,UI_FREQ_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1GHZ	:
						if(ui.Freq_string_print[1] == ' ')
							string[1] = '0';
						else
							string[1] = ui.Freq_string_print[1];
						string[0] = ui.Freq_string_print[0];
						string[2] = 0;
						u8g_DrawStr(&u8g,1,12,string);
					break;
					case	CUR_POS_MAIN_01dBm	:
						string[0] = ui.Power_string_print[4];
						string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_01dBm_X,UI_POW_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_1dBm	:
					string[0] = ui.Power_string_print[2];
					string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_1dBm_X,UI_POW_POS_Y-1,string);
					break;
					case	CUR_POS_MAIN_10dBm	:
					string[0] = ui.Power_string_print[1];
					string[1] = 0;
						u8g_DrawStr(&u8g,CUR_POS_MAIN_10dBm_X,UI_POW_POS_Y-1,string);
					break;
				}
		}

		u8g_DrawStr(&u8g,0,UI_FREQ_POS_Y,ui.Freq_string_print);
		tmp = u8g_GetStrPixelWidth(&u8g,"10,000,000,00");
		u8g_DrawStr(&u8g,tmp+1,UI_FREQ_POS_Y,"0");
		u8g_DrawStr(&u8g,tmp+10,UI_FREQ_POS_Y,"Hz");

		u8g_DrawStr(&u8g,0, UI_POW_POS_Y,ui.Power_string_print);
		tmp = u8g_GetStrPixelWidth(&u8g,"-10.0");
		u8g_DrawStr(&u8g,tmp+4,UI_POW_POS_Y,"dBm");
		u8g_DrawStr(&u8g, tmp+4+40,UI_POW_POS_Y,PowerB_string_print);

		u8g_SetFont(&u8g, u8g_font_profont10r);



		if(rfgen.rfOnOff == 0)
		{
			u8g_DrawStr(&u8g,UI_RFONOFF_POS_X,UI_POW_POS_Y-1,"RF:OFF");
		}
		else
		{
			u8g_DrawStr(&u8g,UI_RFONOFF_POS_X,UI_POW_POS_Y-1,"RF:ON");
			u8g_DrawStr(&u8g,UI_RFONOFF_POS_X,UI_POW_POS_Y,"   ON");
		}
		if(rfgen.lock_lost == 1 )
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
			if(rfgen.lock_lost == 0)
				ui.refresh = 1;
			rfgen.lock_lost	= 1;
			SCPI_ErrorPush(&scpi_context,SCPI_ERROR_PLL_UNLOCKED);
		}
		else{
			if(rfgen.lock_lost == 1)
				ui.refresh = 1;
			rfgen.lock_lost = 0;
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
							rfgen.power_dbm +=  5;
						break;
						case	CUR_POS_MAIN_1dBm	:
							pow_changed = 1;
							rfgen.power_dbm +=  10ul;
						break;
						case	CUR_POS_MAIN_10dBm	:
							pow_changed = 1;
							rfgen.power_dbm +=  100ul;
						break;
						case	CUR_POS_MAIN_RFONOFF	:
							rfgen.rfOnOff =  1;
							LMX2592_RFonOff(&LMX2592, rfgen.rfOnOff);
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
							rfgen.power_dbm -=  5;
						break;
						case	CUR_POS_MAIN_1dBm	:
							pow_changed = 1;
							rfgen.power_dbm -=  10ul;
						break;
						case	CUR_POS_MAIN_10dBm	:
							pow_changed = 1;
							rfgen.power_dbm -=  100ul;
						break;
						case	CUR_POS_MAIN_RFONOFF	:
							rfgen.rfOnOff ^=  1;
							pow_changed = 1;
						break;
					}
				}
				if(freq_changed == 1)
				{
					rfgen.Frequency_10 = (uint32_t)freq_tmp;
					ultoa(rfgen.Frequency_10,rfgen.Freq_string,10);
					string_digits_commas(rfgen.Freq_string,ui.Freq_string_print);
					/*power_tmp = max_power(Frequency_10);
					if(power_dbm > power_tmp)
					power_dbm = power_tmp;

					power_tmp = min_power(Frequency_10);
					if(power_dbm <  power_tmp)
					power_dbm = power_tmp;*/

					itoa(rfgen.power_dbm,rfgen.Power_string,10);

					string_digits_commas_dbm(rfgen.Power_string, ui.Power_string_print);
				}

				if(pow_changed == 1)
				{
				/*	power_tmp = max_power(Frequency_10);
					if(power_dbm > power_tmp)
						power_dbm = power_tmp;

					power_tmp = min_power(Frequency_10);
					if(power_dbm <  power_tmp)
						power_dbm = power_tmp;*/
					if(rfgen.power_dbm > 0)
					{
						rfgen.power_dbm = 0;
						LMX2592.PowerB++;
					}
					if(rfgen.power_dbm < -315)
					{
						rfgen.power_dbm = -315;
						if(LMX2592.PowerB > 0)
							LMX2592.PowerB--;
					}

					if(rfgen.power_dbm == -5)
					{
						if(LMX2592.PowerB > 0)
						{
							LMX2592.PowerB--;
							rfgen.power_dbm = 0;
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
					itoa(rfgen.power_dbm,rfgen.Power_string,10);
					string_digits_commas_dbm(rfgen.Power_string, ui.Power_string_print);
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
		if(rfgen.rfOnOff == 1)
		{

			LMX2592_set_out_freq(&LMX2592, rfgen.Frequency_10, 0);
			//power_dbm = PowerSend(&LMX2592, Frequency_10, power_dbm);
			PowerSend(&LMX2592, rfgen.Frequency_10, rfgen.power_dbm);
			LMX2592_RFonOff(&LMX2592, 1);
			LMX2592_configure(&LMX2592);
			/*if (USB_port == 1)
			{
				Display_ui(&LMX2592);
			}*/
		}
		else
		{
			LMX2592_set_out_freq(&LMX2592, rfgen.Frequency_10, 0);
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


void OLEDcommand(uint8_t command)
{
	uint8_t tmp[2];
	tmp[0] = 0x80;
	tmp[1] = command;
	TWI_MasterWrite(&twiMaster, OLED_ADD, tmp,2,0);
	while (twiMaster.status != TWIM_STATUS_READY);
}