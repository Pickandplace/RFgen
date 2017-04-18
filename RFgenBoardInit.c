/*
 * RFgenBoardInit.c
 *
 * Created: 11/3/2016 7:15:43 PM
 *  Author: Jean
 */ 
#include <asf.h>

void RfgenBoardInit(void)
{


	
	//RF Attenuator Port
	PORTA_DIRSET = PIN0_bm;
	PORTA_DIRSET = PIN1_bm;
	PORTA_DIRSET = PIN2_bm;
	PORTA_DIRSET = PIN3_bm;
	PORTA_DIRSET = PIN4_bm;
	PORTA_DIRSET = PIN5_bm;
	
	PORTA_OUTSET = PIN0_bm;
	PORTA_OUTSET = PIN1_bm;
	PORTA_OUTSET = PIN2_bm;
	PORTA_OUTSET = PIN3_bm;
	PORTA_OUTSET = PIN4_bm;
	PORTA_OUTSET = PIN5_bm;
	
	
	//Encoder A and B
	PORTA_DIRCLR = PIN6_bm;
	PORTA_DIRCLR = PIN7_bm;
	
	//PLL Chip Enable CE
	PORTB_DIRSET = PIN0_bm;
	PORTB_OUTCLR = PIN0_bm;
	
	//Encoder E
	PORTB_DIRCLR = PIN1_bm;
	
	//PLL SPI
	PORTC_DIRSET = PIN4_bm; //SS
	PORTC_OUTSET = PIN4_bm; //SS
	PORTC_DIRSET = PIN5_bm; //MOSI
	PORTC_DIRCLR = PIN6_bm; //MISO
	PORTC_DIRSET = PIN7_bm; //SCK
	
	//RF Relay
	PORTD_DIRSET = PIN3_bm;
	PORTD_OUTCLR = PIN3_bm;
	
	//-5V DCDC Converter SHUTDOWN
	PORTD_DIRSET = PIN0_bm;
	PORTD_OUTSET = PIN0_bm;
	
	//Jack Power Present
	PORTC_DIRCLR = PIN1_bm;
	//USB Power Present
	PORTD_DIRCLR = PIN2_bm;	
	
	//Front Panel Detection
	PORTB_DIRSET = PIN2_bm;
	PORTD_OUTCLR = PIN3_bm;
	
	//+4.5 V Enable
	PORTC_DIRSET = PIN0_bm;
	PORTC_OUTCLR = PIN0_bm;
	
	
}