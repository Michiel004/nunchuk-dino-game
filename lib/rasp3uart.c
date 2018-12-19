#include "rasp3base.h"
#include "rasp3gpio.h"
#include "rasp3uart.h"
#include "rasp3int.h"
#include <stdint.h>

extern volatile unsigned int* REG;

volatile unsigned int tim;

volatile char txbuf[UART_BUFFER_SIZE];
volatile char rxbuf[UART_BUFFER_SIZE];

volatile int rxbuf_use = 0;
volatile int txbuf_use = 0;
volatile int rxbuf_off = 0;
volatile int txbuf_off = 0;

volatile int repeatData = 0;

void UART_intterrupt();
void UART_TX_buffer_sent();

void RP3_UART_init(int baudrate){
	REG[USRTCR] = 0x00;
	
	RP3_GPIO_set_function(14, RP3_GPIO_function_af0);
	RP3_GPIO_set_function(15, RP3_GPIO_function_af0);
	
	RP3_GPIO_set_pull(14, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull(15, RP3_GPIO_pull_non);
	
	REG[USRTICR] = (1<<USRTICR_OEIC) | (1<<USRTICR_BEIC) | (1<<USRTICR_PEIC) | (1<<USRTICR_FEIC) | 
				   (1<<USRTICR_RTIC) | (1<<USRTICR_TXIC) | (1<<USRTICR_RXIC) | (1<<USRTICR_CTSMIC);
	
	REG[USRTIBRD] = 48000000 / (16 * baudrate);
	REG[USRTFBRD] = ((4 * 48000000 + baudrate / 2) / baudrate) & 0x3f;
	REG[USRTLCRH] = (0b11<<USRTLCRH_WLEN);// | (1<<USRTLCRH_FEN);
//	REG[USRTIFLS] = (0b100 << USRTIFLS_RXIFLSEL) | (0b000 << USRTIFLS_TXIFLSEL);Not working yet
	REG[USRTIMSC] = (1 << USRTIMSC_TXIM) | (1 << USRTIMSC_RXIM);
	REG[USRTCR] = (1<<USRTCR_RXE) | (1<<USRTCR_TXE) | (1<<USRTCR_UARTEN);
	
	RP3_INT_enable_irq();
	
	RP3_INT_enableIRQFunction(IRQRQST_UART, UART_intterrupt);
	
	rxbuf_use = 0;
	txbuf_use = 0;
	rxbuf_off = 0;
	txbuf_off = 0;
	repeatData = 0;
}

void RP3_UART_set_repeat_data(int d){
	repeatData = d;
}

void RP3_UART_send_char(char c){
	if(txbuf_use < UART_BUFFER_SIZE){
		txbuf[(txbuf_off + (txbuf_use++)) % UART_BUFFER_SIZE] = c;
	}
	if(!(REG[USRTFR] & (1<<USRTFR_TXFF)) & txbuf_use == 1){
		UART_TX_buffer_sent();
	}
}

void RP3_UART_send_chars(char *c) // output a string of chars
{
	while (*c) txbuf[(txbuf_off + (txbuf_use++)) % UART_BUFFER_SIZE] = *c++;
	if(!(REG[USRTFR] & (1<<USRTFR_TXFF))){
		UART_TX_buffer_sent();
	}
}

char RP3_UART_receive_and_wait_char(){
	while(rxbuf_use <= 0);
	char c = rxbuf[rxbuf_off++];
	rxbuf_use--;
	rxbuf_off = rxbuf_off % UART_BUFFER_SIZE;
	return c;
	
}

char RP3_UART_receive_char(){
	if(rxbuf_use > 0){
		char c = rxbuf[rxbuf_off++];
		rxbuf_use--;
		rxbuf_off = rxbuf_off % UART_BUFFER_SIZE;
		return c;
	}
	return 0;
}

void RP3_UART_receive_chars(char *c, int amount){
	int i = 0;
	for(; i < amount; i++){
		c[i] = RP3_UART_receive_and_wait_char();
	}
}

int RP3_UART_receive_until_char(char *c, int amount, char chr){
	int i = 0;
	for(; i < amount; i++){
		c[i] = RP3_UART_receive_and_wait_char();
		if( c[i] == chr)
			return i;
	}
	return -1;
}

int RP3_UART_urpx(int x)
{
  char c;
  if (x){
     c = tab[x % 16];
     RP3_UART_urpx(x / 16);
  }
  RP3_UART_send_char(c);
}

int RP3_UART_uprintx(int x)
{
  RP3_UART_send_chars("0x");
  if (x==0)
    RP3_UART_send_char('0');
  else
    RP3_UART_urpx(x);
  RP3_UART_send_char(' ');
}

int RP3_UART_urpu(int x)
{
  char c;
  if (x){
     c = tab[x % 10];
     RP3_UART_urpu(x / 10);
  }
  RP3_UART_send_char(c);
}

int RP3_UART_uprintu(int x)
{
  if (x==0)
    RP3_UART_send_char('0');
  else
    RP3_UART_urpu(x);
  RP3_UART_send_char(' ');
}

int RP3_UART_uprinti(int x)
{
  if (x<0){
    RP3_UART_send_char('-');
    x = -x;
  }
  RP3_UART_uprintu(x);
}

int RP3_UART_ufprintf(char *fmt,...)
{
  int *ip;
  char *cp;
  cp = fmt;
  ip = (int *)&fmt + 1;

  while(*cp){
    if (*cp != '%'){
      RP3_UART_send_char(*cp);
      if (*cp=='\n')
	RP3_UART_send_char('\r');
      cp++;
      continue;
    }
    cp++;
    switch(*cp){
    case 'c': RP3_UART_send_char((char)*ip);      break;
    case 's': RP3_UART_send_chars((char *)*ip);  break;
    case 'd': RP3_UART_uprinti(*ip);           break;
    case 'u': RP3_UART_uprintu(*ip);           break;
    case 'x': RP3_UART_uprintx(*ip);  break;
    }
    cp++; ip++;
  }
}

int RP3_UART_uprintf(char *fmt, ...)
{
  int *ip;
  char *cp;
  cp = fmt;
  ip = (int *)&fmt + 1;

  while(*cp){
    if (*cp != '%'){
      RP3_UART_send_char(*cp);
      if (*cp=='\n')
	RP3_UART_send_char('\r');
      cp++;
      continue;
    }
    cp++;
    switch(*cp){
    case 'c': RP3_UART_send_char((char)*ip);      break;
    case 's': RP3_UART_send_chars((char *)*ip);   break;
    case 'd': RP3_UART_uprinti(*ip);           break;
    case 'u': RP3_UART_uprintu(*ip);           break;
    case 'x': RP3_UART_uprintx(*ip);  break;
    }
    cp++; ip++;
  }
}

void UART_TX_buffer_sent(){
	REG[USRTIMSC] &= ~(1 << USRTIMSC_TXIM);
	REG[USRTDR] = txbuf[txbuf_off++];
	txbuf_use--;
	txbuf_off = txbuf_off % UART_BUFFER_SIZE;
	REG[USRTIMSC] |= (1 << USRTIMSC_TXIM);
}

void UART_intterrupt(){
	uint32_t intterrupts = REG[USRTMIS];
		
	if(intterrupts & (1 << USRTMIS_RXMIS)){
		RP3_GPIO_pin_set(21);
		if(!(REG[USRTFR] & (1<<USRTFR_RXFE))){
			if(rxbuf_use < UART_BUFFER_SIZE){
				RP3_GPIO_pin_set(20);
				char c = (char)(REG[USRTDR]);
				rxbuf[(rxbuf_off + rxbuf_use++) % UART_BUFFER_SIZE] = c;
				if(repeatData)RP3_UART_send_char(c);
			}
		}
	}
	if(intterrupts & (1 << USRTMIS_TXMIS)){
		if(txbuf_use > 0){
			UART_TX_buffer_sent();
		}
	}
	REG[USRTICR] = (1<<USRTICR_OEIC) | (1<<USRTICR_BEIC) | (1<<USRTICR_PEIC) | (1<<USRTICR_FEIC) | 
				   (1<<USRTICR_RTIC) | (1<<USRTICR_TXIC) | (1<<USRTICR_RXIC) | (1<<USRTICR_CTSMIC);
}