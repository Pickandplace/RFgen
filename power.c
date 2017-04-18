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

int16_t max_power(uint32_t frequency)
{
	if(frequency < 50000000) //0.5GHz
		return(max_pow_out[0]);
	if(frequency < 100000000) //1GHz
		return(max_pow_out[1]);
	if(frequency < 150000000) //
		return(max_pow_out[2]);
	if(frequency < 200000000) //
		return(max_pow_out[3]);
	if(frequency < 250000000) //
		return(max_pow_out[4]);
	if(frequency < 300000000) //
		return(max_pow_out[5]);
	if(frequency < 350000000) //3GHz
		return(max_pow_out[6]);
	if(frequency < 450000000) //4,5GHz
		return(max_pow_out[7]);
	if(frequency < 500000000) //
		return(max_pow_out[8]);
	if(frequency < 450000000)
		return(max_pow_out[9]);
	if(frequency < 500000000)
		return(max_pow_out[10]);
	if(frequency < 550000000)
		return(max_pow_out[11]);
	if(frequency < 600000000)
		return(max_pow_out[12]);
	if(frequency < 650000000)
		return(max_pow_out[13]);
	if(frequency < 700000000)
		return(max_pow_out[14]);
	if(frequency < 750000000)
		return(max_pow_out[15]);
	if(frequency < 800000000)
		return(max_pow_out[16]);
	if(frequency < 850000000)
		return(max_pow_out[17]);
	if(frequency < 900000000)
		return(max_pow_out[18]);
	if(frequency < 950000000)
		return(max_pow_out[19]);
	if(frequency < 1000000000)
		return(max_pow_out[20]);

	return 0;
}
/*
int8_t cal_power_att(uint32_t frequency, int16_t power, uint8_t *LMX2592_pow, uint8_t *HMC424)
{

	int16_t max_pow;
	int16_t pow_tmp;
	uint8_t i =47;

	max_pow = max_power(frequency);
	if(power > max_pow)
		power = max_pow;
	*LMX2592_pow = 0;
	*HMC424 = 0;
	pow_tmp = max_pow;
	for(i=0; i < 47; i++)
	{
		pow_tmp = max_pow - LMX2592_pow_out[47] + LMX2592_pow_out[i]; // see if we reach the desired power by reducing the LMX2592 output level
		if((power < pow_tmp))
			break;
	}

	*LMX2592_pow = i;

	if( i == 0)//we are below the minimum LMX2592 output level --> use the attenuator
	{
		i = pow_tmp;
		while(power < pow_tmp)
		{
			pow_tmp =  i - ((*HMC424) * 5);
			(*HMC424)++;
			if((*HMC424) >= 63)
				break;
		}
	}
	return(*HMC424);
}*/

int16_t cal_power_att(uint32_t frequency, int16_t power, uint8_t *LMX2592_pow, uint8_t *HMC424)
{
	int16_t min_pow;
	uint16_t *cal_array;
	uint8_t i =47;

/*	min_max_pow = max_power(frequency);
	if(power > min_max_pow)
		power = min_max_pow;

	min_max_pow = min_power(frequency);
	if(power < min_max_pow)
		power = min_max_pow;
	*/
	min_pow = min_power(frequency);
	*LMX2592_pow = 0;
	*HMC424 = 0;
	cal_array = cal_picker(frequency);
	for(i=0; i < 87; i++)
	{
		if( power <= (min_pow + (i*5)))
		break;
	}
	*LMX2592_pow = (cal_array[i] & 0xFF00) >> 8;
	*HMC424 = (cal_array[i] & 0xFF) ;
	return(power);
}


uint16_t *cal_picker(uint32_t frequency)
{
	if(frequency < 50000000) //0.5GHz
	return(cal_0_0);
	if(frequency < 100000000) //1GHz
	return(cal_0_5);
	if(frequency < 150000000) //
	return(cal_1_0);
	if(frequency < 200000000) //
	return(cal_1_5);
	if(frequency < 250000000) //
	return(cal_2_0);
	if(frequency < 300000000) //
	return(cal_2_5);
	if(frequency < 350000000) //3GHz
	return(cal_3_0);
	if(frequency < 450000000) //4,5GHz
	return(cal_3_5);
	if(frequency < 500000000) //
	return(cal_4_0);
	if(frequency < 450000000)
	return(cal_4_5);
	if(frequency < 500000000)
	return(cal_5_0);
	if(frequency < 550000000)
	return(cal_5_5);
	if(frequency < 600000000)
	return(cal_6_0);
	if(frequency < 650000000)
	return(cal_6_5);
	if(frequency < 700000000)
	return(cal_7_0);
	if(frequency < 750000000)
	return(cal_7_5);
	if(frequency < 800000000)
	return(cal_8_0);
	if(frequency < 850000000)
	return(cal_8_5);
	if(frequency < 900000000)
	return(cal_9_0);
	if(frequency < 950000000)
	return(cal_9_5);
	if(frequency < 1000000000)
	return(cal_10_0);

	return 0;
}

int16_t min_power(uint32_t frequency)
{
	if(frequency < 50000000) //0.5GHz
	return(min_pow_out[0]);
	if(frequency < 100000000) //1GHz
	return(min_pow_out[1]);
	if(frequency < 150000000) //
	return(min_pow_out[2]);
	if(frequency < 200000000) //
	return(min_pow_out[3]);
	if(frequency < 250000000) //
	return(min_pow_out[4]);
	if(frequency < 300000000) //
	return(min_pow_out[5]);
	if(frequency < 350000000) //3GHz
	return(min_pow_out[6]);
	if(frequency < 450000000) //4,5GHz
	return(min_pow_out[7]);
	if(frequency < 500000000) //
	return(min_pow_out[8]);
	if(frequency < 450000000)
	return(min_pow_out[9]);
	if(frequency < 500000000)
	return(min_pow_out[10]);
	if(frequency < 550000000)
	return(min_pow_out[11]);
	if(frequency < 600000000)
	return(min_pow_out[12]);
	if(frequency < 650000000)
	return(min_pow_out[13]);
	if(frequency < 700000000)
	return(min_pow_out[14]);
	if(frequency < 750000000)
	return(min_pow_out[15]);
	if(frequency < 800000000)
	return(min_pow_out[16]);
	if(frequency < 850000000)
	return(min_pow_out[17]);
	if(frequency < 900000000)
	return(min_pow_out[18]);
	if(frequency < 950000000)
	return(min_pow_out[19]);
	if(frequency < 1000000000)
	return(min_pow_out[20]);

	return 0;
}