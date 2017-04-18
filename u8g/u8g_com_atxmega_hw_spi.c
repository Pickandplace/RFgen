/*
  
  u8g_com_atxmega_hw_spi.c

  Universal 8bit Graphics Library
  
  Copyright (c) 2011, olikraus@gmail.com
  Copyright (c) 2015, florianmenne@t-online.de
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

  A special SPI interface for ST7920 controller with HW SPI Support

  Assumes, that 
    MOSI is at PORTB, Pin 3
  and
    SCK is at PORTB, Pin 5

  Update for ATOMIC operation done (01 Jun 2013)
    U8G_ATOMIC_OR(ptr, val)
    U8G_ATOMIC_AND(ptr, val)
    U8G_ATOMIC_START()
    U8G_ATOMIC_END()
 

*/

#include "u8g.h"
#include "twi_master_driver.h"
TWI_Master_t twiMaster;
#if defined(__AVR_XMEGA__)
#define U8G_ATXMEGA_HW_SPI
#endif


#if defined(U8G_ATXMEGA_HW_SPI)

#include <avr/interrupt.h>
#include <avr/io.h>


static uint8_t u8g_atxmega_spi_out(uint8_t data)
{
  /* send data */
  SPIC.DATA = data;
  
  /* wait for transmission */
  while(!(SPIC.STATUS & SPI_IF_bm));
  
  /* clear the SPIF flag by reading SPDR */
  return SPIC.DATA;
}


uint8_t u8g_com_atxmega_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
	uint8_t bytei2c;
	uint8_t tmp[2];
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
    break;
    
    case U8G_COM_MSG_INIT:

    break;
    
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
  
    break;

    case U8G_COM_MSG_CHIP_SELECT:
    
    break;
    
    case U8G_COM_MSG_RESET:

    break;
    
    case U8G_COM_MSG_WRITE_BYTE:
		tmp[0] = 0x80;
		tmp[1] =arg_val;
		TWI_MasterWrite(&twiMaster, 0x3c, tmp,2,0);
			while (twiMaster.status != TWIM_STATUS_READY);
    break;
    
    case U8G_COM_MSG_WRITE_SEQ:
    {
      register uint8_t *ptr = arg_ptr;      
	  TWI_MasterWrite(&twiMaster, 0x3c, &(*ptr++),arg_val,MEMORY_BYTE);
	  while (twiMaster.status != TWIM_STATUS_READY);
    }
    break;
	
    case U8G_COM_MSG_WRITE_SEQ_P:
    {
      register uint8_t *ptr = arg_ptr;
      //while( arg_val > 0 )
      //{
 
		 TWI_MasterWrite(&twiMaster, 0x3c, u8g_pgm_read(ptr),arg_val, COMMAND_BYTE);
		 while (twiMaster.status != TWIM_STATUS_READY);		  
        //ptr++;
        //arg_val--;
      //}
    }
    break;
  }
  return 1;
}

#else

uint8_t u8g_com_atxmega_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  return 1;
}

#endif