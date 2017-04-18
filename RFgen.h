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

typedef struct rfgen_struct  {
	bool		rfOnOff;
	bool		lock_lost;
	uint32_t	Frequency_10;
	int16_t		power_dbm;
	char		Freq_string[11];
}rfgen_t;

typedef struct ui_struct  {
	bool	cur_selected;
	bool	menu;
	uint8_t cur_pos;	//Cursor position (logical)
	uint8_t cur_x;
	uint8_t cur_y;
	bool	refresh;
	char	Freq_string_print[14];
}ui_t;

void string_digits_commas(char *str1, char *str2);
void string_digits_commas_dbm(char *str1, char *str2);
void RfgenBoardInit(void);
#endif /* RFGEN_H_ */