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
 * power.h
 *
 * Created: 11/16/2016 9:05:37 PM
 *  Author: Jean
 */


#ifndef POWER_H_
#define POWER_H_

#include <LMX2592.h>

#define POWER_DBM10_MAX 100
#define POWER_DBM10_MIN -200

int16_t PowerSend(LMX2592_t *LMX2592, uint32_t frequency, int16_t power );

int16_t max_power(uint32_t frequency);
int16_t min_power(uint32_t frequency);
uint16_t *cal_picker(uint32_t frequency);

int16_t cal_power_att(uint32_t frequency, int16_t power, uint8_t *LMX2592_pow, uint8_t *HMC424);

#endif /* POWER_H_ */