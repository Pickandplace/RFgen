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
 * calibration.h
 *
 * Created: 12/3/2016 5:18:47 PM
 *  Author: Jean
 */


#ifndef CALIBRATION_H_
#define CALIBRATION_H_

uint16_t cal_pow[10][100]; //frequency: 0G..9.8G in 1G steps ; -35dBm..+15dBm in 0.5dB steps. (5..0)(5..0): (LMX2592 power)(ATT value)

int16_t min_power[10]; //Contains values for min. power for each F range -35dBm..+15dBm
int16_t max_power[10]; //Contains values for max. power for each F range -35dBm..+15dBm
#endif /* CALIBRATION_H_ */