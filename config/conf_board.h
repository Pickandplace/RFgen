/**
 * \file
 *
 * \brief User board configuration template
 *
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H
#define  USART               USARTD0
#define  USART_RX_Vect       USARTD0_RXC_vect
#define  USART_DRE_Vect      USARTD0_DRE_vect
#define  USART_SYSCLK        SYSCLK_USART0
#define  USART_PORT          PORTD
#define  USART_PORT_PIN_TX   (1<<3)  // PC3 (TXC0)
#define  USART_PORT_PIN_RX   (1<<2)  // PC2 (RXC0)
#define  USART_PORT_SYSCLK   SYSCLK_PORT_F
#endif // CONF_BOARD_H
