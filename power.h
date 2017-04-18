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