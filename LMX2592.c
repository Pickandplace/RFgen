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
 * LMX2592.c
 *
 * Created: 10/30/2016 9:00:58 PM
 *  Author: Jean
 */
#include "asf.h"
#include "LMX2592.h"
#include "RFgen.h"
const uint16_t LMX2592_def_reg[] = {0x00AF,0x0000,0x0000,0x0000,0x03FC,0x00CF,0x0F23,0x0000,0x0000,0x0000,0x0000,0x03E8,0x0000,0x8204,0x0036,0x4000,0x0011,0x021D,0xC3D0,0x4210,0x4210,0x0001,0x0034,0x0084,0x2924,0x0000,0x0509,0x8842,0x2300,0x012C,0x0965,0x018C,0x4000,0x7001,0x0018,0x10D8,0x0102,0x1084,0x28B2,0x1943,0x0500,0x0808,0x2204 };
const uint8_t LMX2592_def_reg_number[] =      {64,62,61,59,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,25,24,23,22,20,19,14,13,12,11,10,9,8,7,4,2,1,0};//43
const uint8_t LMX2592_def_reg_number_conf[] = {0,1,2,4,7,8,9,10,11,12,13,14,19,20,22,23,24,25,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,59,61,62,64};//43

extern ui_t ui;
void LMX2592_write_24_reg(uint32_t reg)
{
		uint8_t buffer[3];

		spi_select_device();
		buffer[0] = (reg >>16) & 0xFF;
		buffer[1] = (reg >> 8 )& 0xFF;
		buffer[2] = (reg & 0xFF);
		spi_write_packet(&SPIC,buffer,3);
		spi_deselect_device();
}
uint8_t LMX2592_init_config(LMX2592_t *LMX2592)
{
	LMX2592->OSC_freq		=	100000000;
	LMX2592->Out_freq		=	50000;
	LMX2592->osc_dbl		=	1;
	LMX2592->PLL_R_pre_div	=	1;
	LMX2592->osc_mult		=	1;
	LMX2592->Post_R_div		=	1;
	LMX2592->PFD_freq		=	200000000;
	LMX2592->Low_PFD		=	0;
	LMX2592->High_PFD		=	0;
	LMX2592->PFD_delay		=	0;
	LMX2592->RF_out_div_seg1=	0;
	LMX2592->RF_out_div_seg2=	0;
	LMX2592->RF_out_div_seg3=	0;
	LMX2592->VCO_doubler	=	0;
	LMX2592->PLL_pre_N		=	0;
	LMX2592->PLL_den		=	1000;
	LMX2592->PLL_num		=	0;
	LMX2592->PLL_n_div		=	27;

	LMX2592->PFD_control	=	0;
	LMX2592->Charge_pump_I	=	0x0f;
	LMX2592->Charge_pump_x	=	1;
	LMX2592->Channel_div_EN	=	0;
//	LMX2592->Ch_div_seg_EN	=	0;
	LMX2592->Mash_seed		=	1;
	LMX2592->Mash_Order		=	0;
	LMX2592->Out_B_mux		=	0;
	LMX2592->PowerB			=	0;
	LMX2592->AcalFast		=	0;
	LMX2592->FcalFast		=	0;
	LMX2592->Fcal			=	0;
	LMX2592->VCO_dist_B_PD	=	1;
	LMX2592->CH_div_PD		=	1;
	LMX2592->MASH_dith_EN	=	0;
	LMX2592->CH_div_SEL		=	0;
	LMX2592->OUT_B_PD		=	1;
	LMX2592->CH_div_dist_PD	=	1;
	LMX2592->CH_div_seg1_EN	=	0;
	LMX2592->CH_div_seg2_EN	=	0;
	LMX2592->CH_div_seg3_EN	=	0;
	LMX2592->CH_div_distB_EN =	0;

	LMX2592->regs.RF_out_div_seg1=	0;
	LMX2592->regs.RF_out_div_seg2=	0;
	LMX2592->regs.RF_out_div_seg3=	0;
	return(1);

}
uint8_t LMX2592_configure(LMX2592_t *LMX2592)
{
	uint16_t registers[43];
	uint8_t buffer[3];
	int8_t i;

	registers[0]  = LD_EN(1) | (1<<9) | FCAL_HPFD_ADJ(LMX2592->High_PFD) | FCAL_LPFD_ADJ(LMX2592->Low_PFD) | (1<<4) | FCAL_EN(1) | MUXOUT_SEL(1) | RESET(0) | POWERDOWN(0);
	registers[1]  = (1<<11) | (1<<3) | CAL_CLK_DIV(0);
	registers[2]  = (1<<10) | (1<<8) ;
	registers[3]  = ACAL_CMP_DLY(25) | (1<<6) | 3;//Reg4
	registers[4]  = 0x28B2 ;//Reg7
	registers[5]  = 0x1084;//Reg8
	registers[6]  = OSC_2X(LMX2592->osc_dbl) | REF_EN(1) | (1<<8) | (1<<1)  ;//Reg9
	registers[7]  = (1<<12) | MULT(LMX2592->osc_mult) | (1<<6) | (3<<3)  ;//Reg10
	registers[8]  = PLL_R(LMX2592->Post_R_div) | (1<<3) ;//Reg11
	registers[9]  = (7<<12) | PLL_R_PRE(LMX2592->PLL_R_pre_div) ;//Reg12
	registers[10] = CP_EN(1) | PFD_CTL(LMX2592->PFD_control);//Reg13
	registers[11] = CP_IDN(LMX2592->Charge_pump_I) | CP_IUP(LMX2592->Charge_pump_I) | CP_ICOARSE(LMX2592->Charge_pump_x);//Reg14
	registers[12] = (1<<11) | (1<<8) | (3<<5) | (1<<2) | 1;//Reg19
	registers[13] = 0x012C;//Reg20
	registers[14] = 0x2300;//Reg22
	registers[15] = (1<<15) | (1<<11) | (1<<6) | 2;//Reg23
	registers[16] = (1<<10) | (1<<8) | (1<<3) | 1;//Reg24
	registers[17] = 0x0000;//Reg25
	registers[18] = (1<<13) | (1<<11) | (1<<8) | (1<<5)  | (1<<2);//Reg28
	registers[19] = (1<<7) | (1<<2) ;//Reg29
	registers[20] = MASH_DITHER(0) | (3<<4) | VCO_2X_EN(LMX2592->VCO_doubler) | (1<<2);//Reg30
	registers[21] = VCO_DISTB_PD(LMX2592->VCO_dist_B_PD) | VCO_DISTA_PD(1) | CHDIV_DIST_PD(LMX2592->CH_div_dist_PD) | 1;//Reg31
	registers[22] = (1<<14) | (1<<9) | (1<<4) ; //Reg32
	registers[23] = (1<<14) | (1<<9) | (1<<4) ; //Reg33
	registers[24] = (3<<14) | (0xF<<6) | CHDIV_EN(LMX2592->Channel_div_EN) | (1<<4); //Reg34
	registers[25] = CHDIV_SEG2(LMX2592->regs.RF_out_div_seg2) | CHDIV_SEG3_EN(LMX2592->CH_div_seg3_EN) | CHDIV_SEG2_EN(LMX2592->CH_div_seg2_EN) | (3<<3) | CHDIV_SEG1(LMX2592->regs.RF_out_div_seg1) | CHDIV_SEG1_EN(LMX2592->CH_div_seg1_EN) | 1; //Reg35
	registers[26] = CHDIV_DISTB_EN(LMX2592->CH_div_distB_EN) | CHDIV_DISTA_EN(0) | CHDIV_SEG_SEL(LMX2592->CH_div_SEL) | CHDIV_SEG3(LMX2592->regs.RF_out_div_seg3) ; //Reg36
	registers[27] = (1<<14) | PLL_N_PRE(LMX2592->PLL_pre_N) ; //Reg37
	registers[28] = PLL_N(LMX2592->PLL_n_div) ; //Reg38
	registers[29] = (1<<15) | PFD_DLY(LMX2592->PFD_delay) | (1<<2) ; //Reg39
	registers[30] = PLL_DEN_MSB(LMX2592->PLL_den) ;;//Reg40
	registers[31] = PLL_DEN_LSB(LMX2592->PLL_den) ; //Reg41
	registers[32] = MASH_SEED_MSB(LMX2592->Mash_seed) ; //Reg42
	registers[33] = MASH_SEED_LSB(LMX2592->Mash_seed) ; //Reg43
	registers[34] = PLL_NUM_MSB(LMX2592->PLL_num) ; //Reg44
	registers[35] = PLL_NUM_LSB(LMX2592->PLL_num) ; //Reg45
	registers[36] = (0<<8) | OUTB_PD(LMX2592->OUT_B_PD) | OUTA_PD(1) | MASH_EN(LMX2592->MASH_dith_EN)| MASH_ORDER(LMX2592->Mash_Order) ; //Reg46// LMX2592->MASH_dith_EN
	registers[37] = OUTA_MUX(0) | (3<<6) | OUTB_POW(LMX2592->PowerB) ; //Reg47
	registers[38] =  (0xFF<<2) | OUTB_MUX(LMX2592->Out_B_mux) ; //Reg48
	registers[39] =  0x20;//Reg59
	registers[40] =  1; //Reg61
	registers[41] =  0 ; //Reg62
	registers[42] =  ACAL_FAST(LMX2592->AcalFast) | FCAL_FAST(LMX2592->FcalFast)  | (1<<7) | (1<<5) | 0x0F; //Reg62


		for (i=42;i>=0;i--)
		{
			buffer[0] = LMX2592_def_reg_number_conf[i];
			buffer[1] = (uint8_t)((registers[i]>>8) & 0xFF);
			buffer[2] = (uint8_t)(registers[i] & 0x00FF);
			spi_select_device();
			spi_write_packet(&SPIC,buffer,3);
			spi_deselect_device();
		}


		return(1);
}

int8_t LMX2592_set_out_freq(LMX2592_t *LMX2592, uint32_t freq_10, uint8_t RFpower)
{
	uint32_t spacing = 100;//1KHz channel spacing
	uint64_t tmp=0;
	uint32_t gcd;


	if( (freq_10 < OUT_FREQ_MIN_10HZ) || (freq_10 > OUT_FREQ_MAX_10HZ) )
		return -1;
	LMX2592->Out_freq = freq_10;
	LMX2592_set_PFD(LMX2592, LMX2592->OSC_freq);

	freq_10 = LMX2592_search_divider(LMX2592, freq_10);

	if(LMX2592->Out_freq > VCO_MAX_FREQ_10HZ)
		{
			LMX2592->VCO_doubler = 1;
			LMX2592->PLL_pre_N = 4;
			freq_10 = (freq_10) >>1;
		}
	else
	{
		freq_10 = (freq_10)>>1;
		LMX2592->PLL_pre_N = 2;
		LMX2592->VCO_doubler = 0;
	}


	LMX2592->PLL_R_pre_div = 1;
	uint64_t den_tmp;
	do{
		do{
			den_tmp = 	(LMX2592->PFD_freq) / (spacing);
			spacing <<= 1;
		}while( den_tmp > 0xfffffff );

		LMX2592->PLL_den = (uint32_t)den_tmp;
		tmp = freq_10 * (uint64_t)LMX2592->PLL_den ;//+ (LMX2592->PFD_freq );
		tmp *= 10ul;
		do_div(tmp, LMX2592->PFD_freq); // Div round closest (n + d/2)/d
		LMX2592->PLL_num = do_div(tmp, LMX2592->PLL_den);
		LMX2592->PLL_n_div = tmp;

		if(LMX2592->PLL_num != 0)
		{
			gcd = gcd_iter((uint32_t)LMX2592->PLL_den, (uint32_t)LMX2592->PLL_num);
			LMX2592->PLL_den = LMX2592->PLL_den / gcd;
			LMX2592->PLL_num = LMX2592->PLL_num / gcd;
		}

		LMX2592->VCO_freq_10HZ = (LMX2592->PFD_freq/10) * 2 * (LMX2592->PLL_n_div + (LMX2592->PLL_num/LMX2592->PLL_den));
		if((LMX2592->PLL_n_div < 8) || (LMX2592->VCO_freq_10HZ > VCO_MAX_FREQ_10HZ))
		{
			LMX2592_search_pre_R(LMX2592,	LMX2592->PFD_freq);

			//spacing = 10;
		}

	}while( (LMX2592->PLL_n_div < 8) );



	if(LMX2592->RF_out_div_seg2 == 1)
		LMX2592->RF_out_div_seg2 = 0;
	if(LMX2592->RF_out_div_seg3 == 1)
		LMX2592->RF_out_div_seg3 = 0;

	if(LMX2592->PFD_freq > 200000000ul)
		LMX2592->PFD_control = 3;

	LMX2592->OUT_B_PD = 1;
	if(RFpower != 0xFF)
	{
		//LMX2592->PowerB = RFpower;
		LMX2592->OUT_B_PD = 0;
	}
	LMX2592->Fcal = 1;

	LMX2592->High_PFD = 0;
	if(LMX2592->PFD_freq > 100000000)
		LMX2592->High_PFD = 1;
	if(LMX2592->PFD_freq > 150000000)
		LMX2592->High_PFD = 2;
	if(LMX2592->PFD_freq > 200000000)
		LMX2592->High_PFD = 3;

	LMX2592->Low_PFD = 0;
	if(LMX2592->PFD_freq < 20000000)
		LMX2592->Low_PFD = 1;
	if(LMX2592->PFD_freq < 10000000)
		LMX2592->Low_PFD = 2;
	if(LMX2592->PFD_freq < 5000000)
		LMX2592->Low_PFD = 3;

	LMX2592_configure_dither(LMX2592);
	LMX2592_translate_regs(LMX2592);
	return(1);
}


int8_t LMX2592_set_out_pow_level(LMX2592_t *LMX2592, uint8_t RFlevel)
{
	LMX2592->PowerB = RFlevel;

}
// greatest common denominator - euclid algo w/o recursion
uint32_t gcd_iter(uint32_t u, uint32_t v)
{
	uint32_t t;
	while (v) {
		t = u;
		u = v;
		v = t % v;
	}
	return u ;
}
void LMX2592_search_pre_R(LMX2592_t *LMX2592, uint32_t	PFD_freq_tmp)
{
	if(LMX2592->osc_dbl == 1)
	{
		while(LMX2592->VCO_freq_10HZ > VCO_MAX_FREQ_10HZ)
		{
			LMX2592->PLL_R_pre_div++;
			LMX2592->PFD_freq = (PFD_freq_tmp  / LMX2592->PLL_R_pre_div);
			LMX2592->VCO_freq_10HZ = (LMX2592->PFD_freq/10) * 2 * ((float)LMX2592->PLL_n_div + (float)(LMX2592->PLL_num/LMX2592->PLL_den));
		};
	}
	else
	{
		while(LMX2592->VCO_freq_10HZ > VCO_MAX_FREQ_10HZ)
		{
			LMX2592->PLL_R_pre_div++;
			LMX2592->PFD_freq = (PFD_freq_tmp  / LMX2592->PLL_R_pre_div);
			LMX2592->VCO_freq_10HZ = (LMX2592->PFD_freq/10) * 2 * ((float)LMX2592->PLL_n_div + (float)(LMX2592->PLL_num/LMX2592->PLL_den));
		};
	}
}

uint32_t LMX2592_search_divider(LMX2592_t *LMX2592, uint32_t freq_10)
{
	LMX2592->RF_out_div_seg1 = 1;
	LMX2592->RF_out_div_seg2 = 1;
	LMX2592->RF_out_div_seg3 = 1;

	if(freq_10 < 355000000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 1;
		LMX2592->RF_out_div_seg3 = 1;
	}
	if(freq_10 < 236667000ul)
	{
		LMX2592->RF_out_div_seg1 = 3;
		LMX2592->RF_out_div_seg2 = 1;
		LMX2592->RF_out_div_seg3 = 1;
	}
	if(freq_10 < 177500000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 2;
		LMX2592->RF_out_div_seg3 = 1;
	}
	if(freq_10 < 118300000ul)
	{
		LMX2592->RF_out_div_seg1 = 3;
		LMX2592->RF_out_div_seg2 = 2;
		LMX2592->RF_out_div_seg3 = 1;
	}
	if(freq_10 < 88750000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 4;
		LMX2592->RF_out_div_seg3 = 1;
	}
	if(freq_10 < 59167000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 6;
		LMX2592->RF_out_div_seg3 = 1;
	}
	if(freq_10 < 44375000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 1;
	}

	if(freq_10 < 25983000ul)
	{
		LMX2592->RF_out_div_seg1 = 3;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 1;
	}	/*
	if(freq_10 < 23000000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 2;
	}	*/
/*	if(freq_10 <= 15000000ul)
	{
		LMX2592->RF_out_div_seg1 = 3;
		LMX2592->RF_out_div_seg2 = 6;
		LMX2592->RF_out_div_seg3 = 2;
	}*/
	if(freq_10 < 22188000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 2;
	}
	if(freq_10 < 11094000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 4;
	}
	if(freq_10 < 7396000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 6;
	}
	if(freq_10 < 5547000ul)
	{
		LMX2592->RF_out_div_seg1 = 2;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 8;
	}
	if(freq_10 < 3698000ul)
	{
		LMX2592->RF_out_div_seg1 = 3;
		LMX2592->RF_out_div_seg2 = 8;
		LMX2592->RF_out_div_seg3 = 8;
	}
	LMX2592->PLL_out_div =  LMX2592->RF_out_div_seg1 * LMX2592->RF_out_div_seg2 * LMX2592->RF_out_div_seg3;
	return(LMX2592->Out_freq * LMX2592->RF_out_div_seg1 * LMX2592->RF_out_div_seg2 * LMX2592->RF_out_div_seg3);
}
uint8_t LMX2592_set_PFD(LMX2592_t *LMX2592, uint32_t user_osc_freq)
{
	if( (user_osc_freq < OSC_FREQ_MIN) || (user_osc_freq > OSC_FREQ_MAX) )
		return -1;
	LMX2592->OSC_freq = user_osc_freq;
	LMX2592->PLL_R_pre_div = 1;
	LMX2592->osc_mult = 1;
	if( (user_osc_freq >= (PFD_OPTIMAL-50000000)) && (user_osc_freq <= (PFD_OPTIMAL+50000000)) )
		{
			LMX2592->PFD_freq = user_osc_freq;
			return(1);
		}


	if(user_osc_freq < PFD_OPTIMAL)
	{
		if( ((user_osc_freq<<1) < PFD_OPTIMAL) && (user_osc_freq >= OSC_MULT_MIN) && (user_osc_freq <= OSC_MULT_MAX))
		{
			LMX2592->osc_dbl = 0;	//Use the multiplier instead of the low noise doubler
			while((user_osc_freq*LMX2592->osc_mult) < PFD_OPTIMAL)
			{
				LMX2592->osc_mult++;
				if(LMX2592->osc_mult > 0x1F)
					break;
			}
			LMX2592->PFD_freq = user_osc_freq * LMX2592->osc_mult;
			return(1);
		}
		else //we cannot use the multiplier, use the doubler
		{
			LMX2592->osc_dbl = 1;
			LMX2592->PFD_freq = user_osc_freq * 2;
			return(1);
		}
	}
	else//OSC frequency greater than PFD_OPTIMAL -> divide
	{
		LMX2592->PLL_R_pre_div = 1;
		while(user_osc_freq/LMX2592->PLL_R_pre_div > PFD_OPTIMAL)
		{
			LMX2592->PLL_R_pre_div++;
			if(LMX2592->PLL_R_pre_div > 0x1fff)
				break;
		}
		LMX2592->PFD_freq = user_osc_freq / LMX2592->PLL_R_pre_div;
		LMX2592->High_PFD = 1;
		return(1);
	}
}


void LMX2592_defaults(void)
{
	uint8_t buffer[3];
	uint8_t i;

	for (i=0;i<43;i++)
	{
		spi_select_device();
		buffer[0] = LMX2592_def_reg_number[i];
		buffer[1] = (uint8_t)((LMX2592_def_reg[i] >>8) & 0xFF);
		buffer[2] = (uint8_t)(LMX2592_def_reg[i] & 0x00FF);
		spi_write_packet(&SPIC,buffer,3);
		spi_deselect_device();
	}


}

void LMX2592_reset(void)
{
	uint8_t buffer[3];

	spi_select_device();
		buffer[0] = 0;
		buffer[1] = 0x23;
		buffer[2] = 0x16;
		spi_write_packet(&SPIC,buffer,3);
	spi_deselect_device();
}
void LMX2592_RFonOff(LMX2592_t *LMX2592, bool rfOn)
{
	//uint16_t reg=0;
	if(rfOn == 0)
	{
		LMX2592->OUT_B_PD = 1;
		PORTD_OUTSET = PIN0_bm;
		PORTC_OUTCLR = PIN0_bm;
	}
	else
	{
		LMX2592->OUT_B_PD = 0;
		PORTD_OUTCLR = PIN0_bm;
		PORTC_OUTSET = PIN0_bm;
	}
	/*
	reg = (0<<8) | OUTB_PD(LMX2592->OUT_B_PD) | OUTA_PD(1) | MASH_EN(LMX2592->MASH_dith_EN) | (1<<5) | MASH_ORDER(LMX2592->Mash_Order) ; //Reg46
	LMX2592_write_reg(46,reg);
	*/
}
void LMX2592_write_reg(uint8_t reg, uint16_t regvalue)
{
	uint8_t buffer[3];

	spi_select_device();
		buffer[0] = reg;
		buffer[1] = (regvalue>>8) & 0xFF;
		buffer[2] = (regvalue & 0xFF);
		spi_write_packet(&SPIC,buffer,3);
	spi_deselect_device();
}

int8_t LMX2592_translate_regs(LMX2592_t *LMX2592)
{
		LMX2592->Out_B_mux = 1;
		LMX2592->CH_div_dist_PD = 1;
		LMX2592->CH_div_SEL = 0;
		LMX2592->Channel_div_EN = 0;
		LMX2592->VCO_dist_B_PD = 0;
		LMX2592->CH_div_seg1_EN = 0;
		LMX2592->CH_div_seg2_EN = 0;
		LMX2592->CH_div_seg3_EN = 0;

		if(LMX2592->RF_out_div_seg1 >1)
		{
			LMX2592->VCO_dist_B_PD = 1;
			LMX2592->CH_div_dist_PD = 0;
			LMX2592->CH_div_seg1_EN = 1;

			LMX2592->Out_B_mux = 0;
			if(LMX2592->RF_out_div_seg1 == 3)
				LMX2592->regs.RF_out_div_seg1 = 1;

			if(LMX2592->RF_out_div_seg1 == 2)
				LMX2592->regs.RF_out_div_seg1 = 0;

			LMX2592->CH_div_SEL = 1;
			LMX2592->CH_div_distB_EN = 1;
			LMX2592->Channel_div_EN = 1;
		}

		if(LMX2592->RF_out_div_seg2 >0)
		{
			LMX2592->CH_div_seg2_EN = 1;
			if(LMX2592->RF_out_div_seg2 == 2 )
				LMX2592->regs.RF_out_div_seg2 = 1;	//Translate to register code
			if(LMX2592->RF_out_div_seg2 == 4 )
				LMX2592->regs.RF_out_div_seg2 = 2;
			if(LMX2592->RF_out_div_seg2 == 6 )
				LMX2592->regs.RF_out_div_seg2 = 4;

			LMX2592->CH_div_SEL = 2;

		}
		if(LMX2592->RF_out_div_seg3 >0)
		{
			LMX2592->CH_div_seg3_EN = 1;
			if(LMX2592->RF_out_div_seg3 == 2 )
				LMX2592->regs.RF_out_div_seg3 = 1;	//Translate to register code
			if(LMX2592->RF_out_div_seg3 == 4 )
				LMX2592->regs.RF_out_div_seg3 = 2;
			if(LMX2592->RF_out_div_seg3 == 6 )
				LMX2592->regs.RF_out_div_seg3 = 4;

			LMX2592->CH_div_SEL = 4;
		}
	return(1);
}

int8_t LMX2592_configure_dither(LMX2592_t *LMX2592)
{

	if(LMX2592->PLL_n_div >= 8)
	LMX2592->PFD_delay = 1;
	if(LMX2592->PLL_num > 1)
	{
		LMX2592->MASH_dith_EN = 1;
		if(LMX2592->PLL_n_div >= 11){
			LMX2592->PFD_delay = 1;
			LMX2592->Mash_Order = 1;
		}
		if(LMX2592->PLL_n_div >= 16){
			LMX2592->PFD_delay = 2;
			LMX2592->Mash_Order = 2;
		}
		if(LMX2592->PLL_n_div >= 18){
			LMX2592->PFD_delay = 2;
			LMX2592->Mash_Order = 3;
		}
		if(LMX2592->PLL_n_div >= 30){
			LMX2592->PFD_delay = 8;
			LMX2592->Mash_Order = 4;
		}
		if(LMX2592->PLL_n_div <11){
			LMX2592->PFD_delay = 1;
			LMX2592->Mash_Order = 0; //No Mash if div==9

		}

	}
	else//Integer mode
	{
		LMX2592->PFD_delay = 1;
		LMX2592->Mash_Order = 0;
		LMX2592->MASH_dith_EN = 0;
	}
	if(LMX2592->Mash_Order == 0)
	LMX2592->MASH_dith_EN = 0;
	return(1);
}