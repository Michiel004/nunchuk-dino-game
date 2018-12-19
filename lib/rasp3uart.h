#ifndef RASP3UART_H_
#define RASP3UART_H_

#include "rasp3base.h"
#include <stdint.h>

#define UART_BUFFER_SIZE 100

static char *tab = "0123456789ABCDEF";

void RP3_UART_init(int baudrate);
void RP3_UART_set_repeat_data(int d);
void RP3_UART_send_char(char c);
void RP3_UART_send_chars(char *c);
char RP3_UART_receive_and_wait_char();
char RP3_UART_receive_char();
void RP3_UART_receive_chars(char *c, int amount);
int RP3_UART_receive_until_char(char *c, int amount, char chr);
int RP3_UART_urpx(int x);
int RP3_UART_uprintx(int x);
int RP3_UART_urpu(int x);
int RP3_UART_uprintu(int x);
int RP3_UART_uprinti(int x);
int RP3_UART_ufprintf(char *fmt,...);
int RP3_UART_uprintf(char *fmt, ...);

#endif