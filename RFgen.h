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
 * RFgen.h
 *
 * Created: 4/18/2017 6:44:21 PM
 *  Author: Jean
 */


#ifndef RFGEN_H_
#define RFGEN_H_
#include "scpi.h"
#include "LMX2592.h"

#define OLED_ADD 0x3c
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
typedef struct rfgen_struct  {
	bool		rfOnOff;
	bool		lock_lost;
	uint32_t	Frequency_10;
	int16_t		power_dbm;
	char		Freq_string[11];
	char		Power_string[5];
}rfgen_t;

typedef struct ui_struct  {
	bool	cur_selected;
	bool	menu;
	uint8_t cur_pos;	//Cursor position (logical)
	uint8_t cur_x;
	uint8_t cur_y;
	bool	refresh;
	char	Freq_string_print[14];
	char	Power_string_print[6];
}ui_t;


void RfgenBoardInit(void);
void string_digits_commas(char *str1, char *str2);
void string_digits_commas_dbm(char *str1, char *str2);
void string_digits_commas_dbm_scpi(char *str1, char *str2);

void RFgenReset(LMX2592_t *LMX2592, ui_t *ui, rfgen_t *rfgen);
#endif /* RFGEN_H_ */