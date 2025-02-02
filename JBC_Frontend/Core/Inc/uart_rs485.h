#ifndef UART_RS485_H
#define UART_RS485_H

#include "stm32f7xx_hal.h"

#define INTERFACE_RS485	0

#define UART_RX_RS485_BUFFER_SIZE	255
#define UART_TX_RS485_BUFFER_SIZE	255

	 
#define UART_RS485_TIMEOUT 10UL
#define UART_RS485_MAX_TX_TIME	1000//ms Maximale Zeit die der Transmitter des RS485 Converter Chips aktiv sein darf

typedef struct
{		
		uint8_t ready_for_deinit_error;
		uint8_t tx_active;
		uint8_t rx_active;
		uint8_t rx_buffer[UART_RX_RS485_BUFFER_SIZE];
		uint8_t tx_buffer[UART_TX_RS485_BUFFER_SIZE];
		uint8_t	rx_wPos,rx_rPos;
		uint8_t	tx_wPos;
		uint8_t rcv_byte;
		uint32_t time_out;	
		uint64_t t_since_TX_Enable;
}UART_rs485_protocol_var;

extern volatile UART_rs485_protocol_var 		uart_rs485_flags;			// deklaration der uart debug Flags
extern DMA_HandleTypeDef 	hdma_usart_rs485_tx;


void UART_RS485_rx_callback(void);
void UART_RS485_tx_callback(void);
void UART_RS485_error_callback(void);

void UART_RS485_transmit_data(uint8_t *s, uint16_t len);
void UART_RS485_transmit_string(char *s);
void UART_RS485_transmit_ui32(uint32_t i);
void UART_RS485_transmit_char(char c);
void UART_RS485_transmit_crlf(void);

uint16_t UART_RS485_get_len(void);
char UART_RS485_get_c_nowait(void);
char UART_RS485_get_c_wait(void);
uint32_t UART_RS485_get_number(void);

void UART_RS485_rx_callback(void);
void UART_RS485_tx_callback(void);
void UART_RS485_error_callback(void);
void UART_RS485_receive_data(void);
void UART_RS485_stop_DMA(void);
void UART_RS485_clear_buffer(void);

#endif