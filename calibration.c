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
#include <asf.h>
#include <LMX2592.h>
#include <calibration.h>
extern LMX2592_t LMX2592;




int8_t read_cal_EEPROM(cal_pow_t *cal_pow)
{
	uint8_t read_page[EEPROM_PAGE_SIZE];
	uint8_t i,j,k,l;
	k = 0;
	uint8_t tmp = 0;
	uint8_t tmp2;
	//nvm_eeprom_read_buffer(CAL_POW_EEPROM_ADDR+k,read_page, EEPROM_PAGE_SIZE);
	for(tmp = 0 ; tmp < EEPROM_PAGE_SIZE ; tmp++)
		read_page[tmp] = k;

	for(i=0;i<CAL_POW_FREQ;i++)
	{
		for(j=0;j<CAL_POW_STEPS; j++)
		{
			tmp2= ((i+1)*(j+1) )/EEPROM_PAGE_SIZE ;
			if(  ( ( (i+1)*(j+1) )/EEPROM_PAGE_SIZE ) == 1 )
				{
					//nvm_eeprom_read_buffer(CAL_POW_EEPROM_ADDR+k,read_page, EEPROM_PAGE_SIZE);
					for(tmp = 0 ; tmp < EEPROM_PAGE_SIZE ; tmp++)
						read_page[tmp] = k;
					k++;
					l=0;
				}
			cal_pow->cal_pow[i][j] = read_page[l];
			l++;
		}

	}

}