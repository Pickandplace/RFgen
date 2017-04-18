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
/*
 * LMX2592.h
 *
 * Created: 10/30/2016 9:00:42 PM
 *  Author: Jean
 */


#ifndef LMX2592_H_
#define LMX2592_H_

#define LMX2592_DISABLE_CHIP PORTB_OUTCLR = PIN0_bm;
#define LMX2592_ENABLE_CHIP PORTB_OUTSET = PIN0_bm;
//Register R0
#define LD_EN(x) ((x)<<13)
#define FCAL_HPFD_ADJ(x) ((x)<<7)
#define FCAL_LPFD_ADJ(x) ((x)<<5)
#define FCAL_EN(x) ((x)<<3)
#define MUXOUT_SEL(x) ((x)<<2)
#define RESET(x) ((x)<<1)
#define POWERDOWN(x) ((x)<<0)

//Register R1
#define CAL_CLK_DIV(x) ((x)<<0)

//Register R4
#define ACAL_CMP_DLY(x) ((x)<<8)

//Register R9
#define OSC_2X(x) ((x)<<11)
#define REF_EN(x) ((x)<<9)
//Register R10
#define MULT(x) ((x)<<7)
//Register R11
#define PLL_R(x) ((x)<<4)
//Register R12
#define PLL_R_PRE(x) ((x)<<0)
//Register R13
#define CP_EN(x) ((x)<<14)
#define PFD_CTL(x) ((x)<<8)
//Register R14
#define CP_IDN(x) ((x)<<7)
#define CP_IUP(x) ((x)<<2)
#define CP_ICOARSE(x) ((x)<<0)
//Register R30
#define MASH_DITHER(x) ((x)<<10)
#define VCO_2X_EN(x) ((x)<<0)
//Register R31
#define VCO_DISTB_PD(x) ((x)<<10)
#define VCO_DISTA_PD(x) ((x)<<9)
#define CHDIV_DIST_PD(x) ((x)<<7)
//Register R34
#define CHDIV_EN(x) ((x)<<5)
//Register R35
#define CHDIV_SEG2(x) ((x)<<9)
#define CHDIV_SEG3_EN(x) ((x)<<8)
#define CHDIV_SEG2_EN(x) ((x) << 7)
#define CHDIV_SEG1(x) ((x) << 2)
#define CHDIV_SEG1_EN(x) ((x) << 1)
//Register R36
#define CHDIV_DISTB_EN(x) ((x)<<11)
#define CHDIV_DISTA_EN(x) ((x)<<10)
#define CHDIV_SEG_SEL(x) ((x)<<4)
#define CHDIV_SEG3(x) ((x)<<0)
//Register R37
#define PLL_N_PRE(x) (x<<12)
//Register R38
#define PLL_N(x) ((x)<<1)
//Register R39
#define PFD_DLY(x) ((x)<<8)
//Register R40
#define PLL_DEN_MSB(x) (((x) >> 16) & 0xFFFF)
//Register R41
#define PLL_DEN_LSB(x) ((x) & 0xFFFF)
//Register R42
#define MASH_SEED_MSB(x) (((x) >> 16) & 0xFFFF)
//Register R43
#define MASH_SEED_LSB(x) ((x) & 0xFFFF)
//Register R44
#define PLL_NUM_MSB(x) (((x) >> 16) & 0xFFFF)
//Register R45
#define PLL_NUM_LSB(x) ((x) & 0xFFFF)
//Register R46
#define OUTA_POW(x) ((x)<<8)
#define OUTB_PD(x) ((x)<<7)
#define OUTA_PD(x) ((x)<<6)
#define MASH_EN(x) ((x)<<5)
#define MASH_ORDER(x) ((x)<<0)
//Register R47
#define OUTA_MUX(x) ((x)<<11)
#define OUTB_POW(x) ((x)<<0)
//Register R48
#define OUTB_MUX(x) ((x)<<0)
//Register R64
#define ACAL_FAST(x) ((x)<<9)
#define FCAL_FAST(x) ((x)<<8)


#define R64_DEFAULT	0x4000AF
#define R62_DEFAULT	0x3E0000
#define R61_DEFAULT	0x3D0000
#define R59_DEFAULT	0x3B0000
#define R48_DEFAULT	0x3003FC
#define R47_DEFAULT	0x2F00CF
#define R46_DEFAULT	0x2E0F23
#define R45_DEFAULT	0x2D0000
#define R44_DEFAULT	0x2C0000
#define R43_DEFAULT	0x2B0000
#define R42_DEFAULT	0x2A0000
#define R41_DEFAULT	0x2903E8
#define R40_DEFAULT	0x280000
#define R39_DEFAULT	0x278204
#define R38_DEFAULT	0x260036
#define R37_DEFAULT	0x254000
#define R36_DEFAULT	0x240011
#define R35_DEFAULT	0x23021D
#define R34_DEFAULT	0x22C3D0
#define R33_DEFAULT	0x214210
#define R32_DEFAULT	0x204210
#define R31_DEFAULT	0x1F0001
#define R30_DEFAULT	0x1E0034
#define R29_DEFAULT	0x1D0084
#define R28_DEFAULT	0x1C2924
#define R25_DEFAULT	0x190000
#define R24_DEFAULT	0x180509
#define R23_DEFAULT	0x178842
#define R22_DEFAULT	0x162300
#define R20_DEFAULT	0x14012C
#define R19_DEFAULT	0x130965
#define R14_DEFAULT	0x0E018C
#define R13_DEFAULT	0x0D4000
#define R12_DEFAULT	0x0C7001
#define R11_DEFAULT	0x0B0018
#define R10_DEFAULT	0x0A10D8
#define R9_DEFAULT	0x090102
#define R8_DEFAULT	0x081084
#define R7_DEFAULT	0x0728B2
#define R4_DEFAULT	0x041943
#define R2_DEFAULT	0x020500
#define R1_DEFAULT	0x010808
#define R0_DEFAULT	0x00220C

#define OSC_FREQ_MIN	5000000
#define OSC_FREQ_MAX	1400000000
#define PFD_OPTIMAL	200000000
#define OSC_MULT_MIN	40000000
#define OSC_MULT_MAX	70000000
#define OUT_FREQ_MAX_KHZ	1000000000
#define OUT_FREQ_MIN_KHZ	2000000
#define VCO_MIN_FREQ_KHZ	355000000
#define VCO_MAX_FREQ_KHZ	710000000
#define VCO_DOUBLED_MIN_FREQ_KHZ	355000000
#define VCO_DOUBLED_MAX_FREQ_KHZ	980000000
#define PLL_R_PRE_MAX				0x0fff
typedef struct LMX2592_struct{
	uint32_t	OSC_freq;		//Oscillator frequency (Hz)
	uint32_t	Out_freq;		//Output frequency, in KHz
	bool		osc_dbl;		//Oscillator low noise doubler
	uint16_t	PLL_R_pre_div;	//Oscillator pre-divider (12bits)
	uint8_t		osc_mult;		//Oscillator multiplier (5bits)
	uint16_t	Post_R_div;		//Oscillator post divider (8bits)
	uint32_t	PFD_freq;		//in Hz
	uint8_t		Low_PFD;		//
	uint8_t		High_PFD;		//PDF>200MHz
	uint8_t		PFD_delay;		//
	uint8_t		RF_out_div_seg1;//Output divider 1 (by 2 or 3)
	uint8_t		RF_out_div_seg2;//Output divider 1 (by 2, 4, 6 or 8)
	uint8_t		RF_out_div_seg3;//Output divider 1 (by 2, 4, 6 or 8)
	bool		VCO_doubler;	//
	uint8_t		PLL_pre_N;		//pre scalar divider (2 or 4)
	uint32_t	PLL_den;		//Denominator and channel spacing
	uint32_t	PLL_num;
	uint32_t	PLL_n_div;

	uint8_t		PFD_control;	//0:dual 3: single (if fPFD>200MHz)
	uint8_t		Charge_pump_I;	//Charge pump current (Up AND Down)
	uint8_t		Charge_pump_x;	//Charge pump current multiplier
	bool		Channel_div_EN;	//Enable the whole channel divider
//	uint8_t		Ch_div_seg_EN;	//EN for the three divider channels (b0:CH1 ; b1:CH2 ; b2:CH3) and distrib. b4-b6

	uint32_t	Mash_seed;
	uint8_t		Mash_Order;
	uint8_t		Out_B_mux;		//Selects signal to the output buffer 0:channel divider output ; 1:output from VCO
	uint8_t		PowerB;
	bool		AcalFast;		//Enables fast frequency calibration
	bool		FcalFast;		//Enables fast amplitude calibration
	uint8_t		Fcal;
	bool		VCO_dist_B_PD;	//Power down buffer between VCO and output B
	bool		CH_div_PD;		//
	bool		MASH_dith_EN;
	bool		CH_div_seg1_EN;	//Enable channel divider segment 1
	bool		CH_div_seg2_EN;	//Enable channel divider segment 2
	bool		CH_div_seg3_EN;	//Enable channel divider segment 3
	uint8_t		CH_div_SEL;		//Channel divider segment select
	bool		OUT_B_PD;
	bool		CH_div_dist_PD;//Power down buffer between VCO and channel divider
	bool		CH_div_distB_EN;//Enable buffer between channel divider and output B
	uint16_t	PLL_out_div;	//Total output divider (debug)

}LMX2592_t;

typedef struct ui_struct  {
	bool	cur_selected;
	bool	menu;
	uint8_t cur_pos;	//Cursor position (logical)
	uint8_t cur_x;
	uint8_t cur_y;
	bool	refresh;
	bool	rfOnOff;
}ui_t;
//#define VCO_D_B_PD(x)	(((x) & 0x80) >> 7)
//#define VCO_D_A_PD(x)	(((x) & 0x40) >> 6)
//#define CH_DIV_PD(x)	(((x) & 0x20) >> 5)
//#define OUT_B_PD(x)		(((x) & 0x10) >> 4)
//#define MASH_ENab(x)	(((x) & 0x08) >> 3)
/*
#define CH_DIV_SEG1(x)	((x) & 0x1)
#define CH_DIV_SEG2(x)	(((x) & 0x2) >> 1)
#define CH_DIV_SEG3(x)	(((x) & 0x4) >> 2)
#define CH_DIV_D_B(x)	(((x) & 0x8) >> 3)
#define CH_DIV_SEL(x)	(((x) & 0xF0) >> 4)*/
//Send the default register values
void LMX2592_defaults(void);
//Soft reset the IC. No need to clear reset bit
void LMX2592_reset(void);

void LMX2592_write_reg(uint8_t reg, uint16_t regvalue);

uint8_t LMX2592_set_PFD(LMX2592_t *LMX2592, uint32_t user_osc_freq);

int8_t LMX2592_set_out_freq(LMX2592_t *LMX2592, uint32_t freq_KHz, uint8_t RFpower);
uint8_t LMX2592_configure(LMX2592_t *LMX2592);

uint8_t LMX2592_init_config(LMX2592_t *LMX2592);
int8_t LMX2592_set_out_pow_level(LMX2592_t *LMX2592, uint8_t RFlevel);
void LMX2592_RFonOff(LMX2592_t *LMX2592, bool rfOn);
uint32_t LMX2592_search_divider(LMX2592_t *LMX2592, uint32_t freq_10);
void LMX2592_search_pre_R(LMX2592_t *LMX2592);
uint32_t gcd_iter(uint32_t u, uint32_t v) ;
void LMX2592_write_24_reg(uint32_t reg);
# define do_div(n, base) ({                                             \
        uint32_t __base = (base);                                   \
        uint32_t __rem;                                             \
        __rem = ((uint64_t)(n)) % __base;                     \
        (n) = ((uint64_t)(n)) / __base;                       \
         __rem;                                                          \
  })


#endif /* LMX2592_H_ */