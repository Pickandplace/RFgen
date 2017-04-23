/*-
 * Copyright (c) 2012-2013 Lutz Hoerl, Thorlabs GmbH
 *
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file   scpi_user_config.h
 * @date   Wed Aug 05 10:00:00 UTC 2015
 *
 * @brief  User resp. device dependent SCPI Configuration
 *
 *
 */

#ifndef __SCPI_USER_CONFIG_H_
#define __SCPI_USER_CONFIG_H_

#ifdef   __cplusplus
extern "C" {
#endif

#define SCPI_LINE_ENDING    "\r\n"    /*   use <CR><LF> carriage return + line feed as termination charcters */

#define USE_FULL_ERROR_LIST 0
#define USE_USER_ERROR_LIST 1

#define LIST_OF_USER_ERRORS \
	X(SCPI_ERROR_CALIBRATION_STATE_IS_OFF,                   100, "Calibration state is off")                     \
	X(SCPI_ERROR_PLL_UNLOCKED,                   101, "PLL lost lock")                     \
    X(SCPI_ERROR_DATA_OUT_OF_RANGE,            -222, "Data out of range")                            \
    X(SCPI_ERROR_INCOMPATIBLE_TYPE,            -294, "Incompatible type")                            \

#ifdef   __cplusplus
}
#endif

#endif   /* #define __SCPI_USER_CONFIG_H_ */
