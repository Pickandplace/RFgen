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
 * power.c
 *
 * Created: 11/16/2016 9:05:23 PM
 *  Author: Jean
 */
#include <asf.h>
#include <power.h>
#include <LMX2592.h>
#include <calibration.h>
extern LMX2592_t LMX2592;

//int16_t max_pow_out[] = {240, 240, 240, 240, 240, 240, 240, 220, 220, 210, 200, 190, 180, 160, 150, 140, 135, 130, 100, 90, 80};

//uint8_t LMX2592_pow_out[49] = {0,0,2,5,10,20,25	,30	,35	,40	,45	,52	,55	,62	,65	,68	,72	,76	,80	,82	,85	,89	,90	,92	,95	,99	,101,102,105,108,109,110,112,114,115,115,116,118,119,120,121,121,122,123,123,124,125,125,126};


int16_t PowerSend(LMX2592_t *LMX2592, uint32_t frequency, int16_t power )
{
	uint8_t LMX2592_pow;
	uint8_t HMC424;
	uint8_t port_tmp = 0;

	//power = cal_power_att(frequency, power, &LMX2592_pow, &HMC424);
	/*if(LMX2592_pow > 31 )//Theres a gap on the LMX2592 output power register
		LMX2592->PowerB = LMX2592_pow + 16;
	else
		LMX2592->PowerB = LMX2592_pow;
*/
	//port_tmp = ((HMC424 & 0x20) >> 5) | ((HMC424 & 0x10) >> 3) | ((HMC424 & 0x08) >> 1) | ((HMC424 & 0x04) << 1) | ((HMC424 & 0x02) << 3) | ((HMC424 & 0x01) << 5);
	//HMC424 = port_tmp;

	HMC424 = (uint8_t)((abs(power)) / 5);
	port_tmp = PORTA_DIR;
	PORTA_DIR = (port_tmp & 0xC0) | HMC424 ;
	return (power);

}
