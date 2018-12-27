#include "rasp3base.h"
#include "rasp3gpio.h"
#include "rasp3uart.h"
#include "rasp3int.h"
#include <stdint.h>

//reference to the variable that holds all the registers
extern volatile unsigned int* REG;

//create the needed buffers
volatile char txbuf[UART_BUFFER_SIZE];
volatile char rxbuf[UART_BUFFER_SIZE];

//create the buffer pointers
volatile int rxbuf_use = 0;
volatile int txbuf_use = 0;
volatile int rxbuf_off = 0;
volatile int txbuf_off = 0;

//do we need to send the received data directly
volatile int repeatData = 0;

void UART_intterrupt();//uart interrupt
void UART_TX_buffer_sent();//sent the tx buffer
int RP3_UART_urpx(int x);
int RP3_UART_urpu(int x);

void RP3_UART_init(int baudrate){
	REG[USRTCR] = 0x00;//reset the uart control register
	
	//set the gpio pins as needed for the uart
	RP3_GPIO_set_function(14, RP3_GPIO_function_af0);
	RP3_GPIO_set_function(15, RP3_GPIO_function_af0);
	RP3_GPIO_set_pull(14, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull(15, RP3_GPIO_pull_non);
	
	//set the needed registers for the uart to work
	REG[USRTICR] = (1<<USRTICR_OEIC) | (1<<USRTICR_BEIC) | (1<<USRTICR_PEIC) | (1<<USRTICR_FEIC) | 
				   (1<<USRTICR_RTIC) | (1<<USRTICR_TXIC) | (1<<USRTICR_RXIC) | (1<<USRTICR_CTSMIC);
	REG[USRTIBRD] = 48000000 / (16 * baudrate);
	REG[USRTFBRD] = ((4 * 48000000 + baudrate / 2) / baudrate) & 0x3f;
	REG[USRTLCRH] = (0b11<<USRTLCRH_WLEN);
	REG[USRTIMSC] = (1 << USRTIMSC_TXIM) | (1 << USRTIMSC_RXIM);
	REG[USRTCR] = (1<<USRTCR_RXE) | (1<<USRTCR_TXE) | (1<<USRTCR_UARTEN);
	
	//enable the interrupt for the uart
	RP3_INT_enable_irq();
	RP3_INT_enableIRQFunction(IRQRQST_UART, UART_intterrupt);
	
	//reset the variables
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
	//if there is a spot add the char to the buffer
	if(txbuf_use < UART_BUFFER_SIZE){
		txbuf[(txbuf_off + (txbuf_use++)) % UART_BUFFER_SIZE] = c;
	}
	//try to start the transmission
	if(!(REG[USRTFR] & (1<<USRTFR_TXFF)) & txbuf_use == 1){
		UART_TX_buffer_sent();
	}
}

void RP3_UART_send_chars(char *c)
{
	//if there is a spot add the chars to the buffer
	while (*c) txbuf[(txbuf_off + (txbuf_use++)) % UART_BUFFER_SIZE] = *c++;
	//try to start the transmission
	if(!(REG[USRTFR] & (1<<USRTFR_TXFF))){
		UART_TX_buffer_sent();
	}
}

char RP3_UART_receive_and_wait_char(){
	//wait for a char in the receive buffer
	while(rxbuf_use <= 0);
	
	//get that char and return it
	char c = rxbuf[rxbuf_off++];
	rxbuf_use--;
	rxbuf_off = rxbuf_off % UART_BUFFER_SIZE;
	return c;
	
}

char RP3_UART_receive_char(){
	//if there is a char in the receive buffer
	if(rxbuf_use > 0){
		//retreive it and return it
		char c = rxbuf[rxbuf_off++];
		rxbuf_use--;
		rxbuf_off = rxbuf_off % UART_BUFFER_SIZE;
		return c;
	}
	//if not return 0
	return 0;
}

void RP3_UART_receive_chars(char *c, int amount){
	//receive the wanted amount of chars one by one
	int i = 0;
	for(; i < amount; i++){
		c[i] = RP3_UART_receive_and_wait_char();
	}
}

int RP3_UART_receive_until_char(char *c, int amount, char chr){
	//receive chars one by one until the max amount is reached or the specified char is read.
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
	//convert the variable to its hex value and sent it
	char c;
	if (x){
		c = tab[x % 16];
		RP3_UART_urpx(x / 16);
	}
	RP3_UART_send_char(c);
}

int RP3_UART_uprintx(int x)
{
	//convert the variable to its hex value and sent it whit the needed extras
	RP3_UART_send_chars("0x");
	if (x==0)
		RP3_UART_send_char('0');
	else
		RP3_UART_urpx(x);
	RP3_UART_send_char(' ');
}

int RP3_UART_urpu(int x)
{
	//sent the variable in decimal
	char c;
	if (x){
		c = tab[x % 10];
		RP3_UART_urpu(x / 10);
	}
	RP3_UART_send_char(c);
}

int RP3_UART_uprintu(int x)
{
	//sent the variable in decimal whit the needed extras
	if (x==0)
		RP3_UART_send_char('0');
	else
		RP3_UART_urpu(x);
	RP3_UART_send_char(' ');
}

int RP3_UART_uprinti(int x)
{
	//sent the variable in decimal including negative numbers
	if (x<0){
		RP3_UART_send_char('-');
		x = -x;
	}
	RP3_UART_uprintu(x);
}

int RP3_UART_ufprintf(char *fmt,...)
{
	//convert the given string and add numbers to the expected spots
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
			case 'c': RP3_UART_send_char((char)*ip);    break;
			case 's': RP3_UART_send_chars((char *)*ip); break;
			case 'd': RP3_UART_uprinti(*ip);           	break;
			case 'u': RP3_UART_uprintu(*ip);           	break;
			case 'x': RP3_UART_uprintx(*ip);  			break;
		}
		cp++; 
		ip++;
	}
}

int RP3_UART_uprintf(char *fmt, ...)
{
	//convert the given string and add numbers to the expected spots
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
			case 'c': RP3_UART_send_char((char)*ip);    break;
			case 's': RP3_UART_send_chars((char *)*ip); break;
			case 'd': RP3_UART_uprinti(*ip);           	break;
			case 'u': RP3_UART_uprintu(*ip);           	break;
			case 'x': RP3_UART_uprintx(*ip);  			break;
		}
		cp++; 
		ip++;
	}
}

void UART_TX_buffer_sent(){
	REG[USRTIMSC] &= ~(1 << USRTIMSC_TXIM);//stop the uart interrupt
	REG[USRTDR] = txbuf[txbuf_off++];//sent a char from the buffer
	txbuf_use--;//remove that char from the buffer
	txbuf_off = txbuf_off % UART_BUFFER_SIZE;//calc the offset
	REG[USRTIMSC] |= (1 << USRTIMSC_TXIM);//start the uart interrupt
}

void UART_intterrupt(){
	uint32_t intterrupts = REG[USRTMIS];//which iterrupt was it
		
	if(intterrupts & (1 << USRTMIS_RXMIS)){//receive interrupt
		//receive the char if a spot is left and resend if wanted
		if(!(REG[USRTFR] & (1<<USRTFR_RXFE))){
			if(rxbuf_use < UART_BUFFER_SIZE){
				char c = (char)(REG[USRTDR]);
				rxbuf[(rxbuf_off + rxbuf_use++) % UART_BUFFER_SIZE] = c;
				if(repeatData)RP3_UART_send_char(c);
			}
		}
	}
	if(intterrupts & (1 << USRTMIS_TXMIS)){//transmit interrupt
		if(txbuf_use > 0){
			UART_TX_buffer_sent();//transmet the next char if there is one left
		}
	}
	REG[USRTICR] = (1<<USRTICR_OEIC) | (1<<USRTICR_BEIC) | (1<<USRTICR_PEIC) | (1<<USRTICR_FEIC) | 
				   (1<<USRTICR_RTIC) | (1<<USRTICR_TXIC) | (1<<USRTICR_RXIC) | (1<<USRTICR_CTSMIC);
}