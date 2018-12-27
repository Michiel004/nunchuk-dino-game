#ifndef RASP3UART_H_
#define RASP3UART_H_

#include "rasp3base.h"
#include <stdint.h>

#define UART_BUFFER_SIZE 100

static char *tab = "0123456789ABCDEF";

/**Initialize the uart.*/
void RP3_UART_init(int baudrate);

/**Set if the received chars will be directly transmitted again.*/
void RP3_UART_set_repeat_data(int d);

/**Send a char over the uart.*/
void RP3_UART_send_char(char c);

/**Send a series of chars over the uart.*/
void RP3_UART_send_chars(char *c);

/**Wait until a char is received.*/
char RP3_UART_receive_and_wait_char();

/**Get the char that was received if there is one.*/
char RP3_UART_receive_char();

/**Receive a series of chars and wait until they are all received.*/
void RP3_UART_receive_chars(char *c, int amount);

/**Receive chars until a specified char is received or the maximum amount is reached.*/
int RP3_UART_receive_until_char(char *c, int amount, char chr);

/**Send a unsigned integer as hex.*/
int RP3_UART_uprintx(int x);

/**Send a unsigned integer as decimal.*/
int RP3_UART_uprintu(int x);

/**Send a signed integer as decimal.*/
int RP3_UART_uprinti(int x);

/**Send a pattern string.*/
int RP3_UART_ufprintf(char *fmt,...);

/**Send a pattern string.*/
int RP3_UART_uprintf(char *fmt, ...);

#endif