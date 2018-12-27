#include "libILI9225.h"
#include "../lib/rasp3spi.h"
#include "../lib/rasp3gpio.h"
#include <stdint.h>

char buffer[32];
uint16_t regs[38];

int pin_rs, pin_cs;
volatile unsigned int tim;

void LIB_ILI9225_write_reg_sim(uint16_t reg, uint16_t data, uint16_t mask, int sim);
void LIB_ILI9225_write_regT(uint16_t reg, uint16_t data, uint16_t mask);
void LIB_ILI9225_regT_to_chip();
void LIB_ILI9225_regT_clear();
void LIB_ILI9225_regT_default();

uint16_t LIB_ILI9225_get_reg_local_addr(uint16_t reg);
uint16_t LIB_ILI9225_get_local_addr_reg(uint16_t addr);

void LIB_ILI9225_init(uint32_t clock, int GPIO_RS, int GPIO_CS){
	pin_rs = GPIO_RS;
	pin_cs = GPIO_CS;
	
	RP3_SPI_init(clock);
	
	RP3_GPIO_set_pull(pin_rs, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull(pin_cs, RP3_GPIO_pull_non);
	
	RP3_GPIO_set_as_output(pin_rs);
	RP3_GPIO_set_as_output(pin_cs);
	
	RP3_GPIO_pin_clear(pin_rs);
	RP3_GPIO_pin_set(pin_cs);
	
	for(tim = 0; tim < 100000; tim++);
	
	LIB_ILI9225_write_reg(LIB_ILI9225_PC1, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC2, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC3, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC4, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC5, 0x0000, 0xFFFF);
	
	for(tim = 0; tim < 100000; tim++);
	
	LIB_ILI9225_write_reg(LIB_ILI9225_PC2, 0x0018, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC3, 0x6121, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC4, 0x006F, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC5, 0x495F, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PC1, 0x0A00, 0xFFFF);
	
	for(tim = 0; tim < 100000; tim++);
	
	LIB_ILI9225_write_reg(LIB_ILI9225_PC2, 0x103B, 0xFFFF);
	
	for(tim = 0; tim < 100000; tim++);
	
	LIB_ILI9225_write_reg(LIB_ILI9225_DOC		, 0x011C, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_LCDACDC	, 0x0100, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_EM		, 0x1030, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_DC1		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_BPC1		, 0x0808, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_FCC		, 0x1100, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_IC		, 0x0001, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_OC		, 0x0801, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_VCIR		, 0x0020, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_RAMAS1	, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_RAMAS2	, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GSC		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_VSC1		, 0x00DB, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_VSC2		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_VSC3		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PDP1		, 0x00DB, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_PDP2		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_HWA1		, 0x00AF, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_HWA2		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_VWA1		, 0x00DB, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_VWA2		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC1		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC2		, 0x0808, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC3		, 0x080A, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC4		, 0x000A, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC5		, 0x0A08, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC6		, 0x0808, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC7		, 0x0000, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC8		, 0x0A00, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC9		, 0x1007, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_GC10		, 0x0710, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_DC1		, 0x1017, 0xFFFF);
	
	for(tim = 0; tim < 100000; tim++);
}

void LIB_ILI9225_set_scan_direction(LIB_ILI9225_SCAN_DIR sd, int sim){
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_DOC,
				((sd & 1) << LIB_ILI9225_DOC_GS) | (((sd >> 1) & 1) << LIB_ILI9225_DOC_SM),
				(1 << LIB_ILI9225_DOC_GS) | (1 << LIB_ILI9225_DOC_SM),
				sim);
}

void LIB_ILI9225_set_display_driver_height(uint16_t height, int sim){
	uint8_t nl = 0b11100;
	if(height <= 216)
		nl = height / 8;
	
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_DOC,
				((nl & 0x1F) << LIB_ILI9225_DOC_NL0),
				(0x1F << LIB_ILI9225_DOC_NL0),
				sim);
}

void LIB_ILI9225_set_scanning_mode(LIB_ILI9225_LCD_SCANNING_MODE sm, int sim){
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_LCDACDC,
				((sm & 1) << LIB_ILI9225_LCDACDC_FLD) | (((sm >> 1) & 3) << LIB_ILI9225_LCDACDC_INV0),
				(1 << LIB_ILI9225_LCDACDC_FLD) | (3 << LIB_ILI9225_LCDACDC_INV0),
				sim);
}

void LIB_ILI9225_set_display_mode(LIB_ILI9225_LCD_DISPLAY_MODE dm, int sim){
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_EM,
				((dm & 1) << LIB_ILI9225_EM_AM) | (((dm >> 1) & 3) << LIB_ILI9225_EM_ID0),
				(1 << LIB_ILI9225_EM_AM) | (3 << LIB_ILI9225_EM_ID0),
				sim);
}

void LIB_ILI9225_set_display_power(LIB_ILI9225_LCD_DISPLAY_POWER dp, int sim){
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_PC1,
				((dp & 16) << LIB_ILI9225_PC1_SAP0),
				(16 << LIB_ILI9225_PC1_SAP0),
				sim);
}

void LIB_ILI9225_set_standby_mode(int standby, int sim){
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_PC1,
				((standby & 1) << LIB_ILI9225_PC1_DSTB),
				(1 << LIB_ILI9225_PC1_DSTB),
				sim);
}

void LIB_ILI9225_set_sleep_mode(int sleep, int sim){
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_PC1,
				((sleep & 1) << LIB_ILI9225_PC1_STB),
				(1 << LIB_ILI9225_PC1_STB),
				sim);
}

void LIB_ILI9225_software_reset(){
	LIB_ILI9225_write_reg(LIB_ILI9225_SR, 0x00CE, 0xFFFF);
}

void LIB_ILI9225_set_vertical_scroll_start_stop(uint8_t start, uint8_t stop, int sim){
	if(start > 219)
		start = 219;
	if(stop > 219)
		stop = 219;
	
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_VSC1, stop, 0x00ff, sim);
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_VSC2, start, 0x00ff, sim);
}

void LIB_ILI9225_set_vertical_scroll_speed(uint8_t speed, int sim){
	if(speed > 219)
		speed = 219;
	
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_VSC3, speed, 0x00ff, sim);
}

void LIB_ILI9225_set_window(uint8_t xStart, uint8_t yStart, uint8_t xStop, uint8_t yStop, int sim){	
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_HWA2, xStart, 0x00ff, sim);
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_VWA2, yStart, 0x00ff, sim);
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_HWA1, xStop, 0x00ff, sim);
	LIB_ILI9225_write_reg_sim(LIB_ILI9225_VWA1, yStop, 0x00ff, sim);
}

void LIB_ILI9225_regT_to_chip(){
	uint16_t i;
	for(i = 0; i < 38; i++){
		uint16_t reg = LIB_ILI9225_get_local_addr_reg(i);
		LIB_ILI9225_wreg(reg, regs[i]);
	}
}

void LIB_ILI9225_regT_clear(){
	uint16_t i;
	for(i = 0; i < 38; i++){
		regs[i] = 0x0000;
	}
}

void LIB_ILI9225_regT_default(){
	regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_DCR)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_DOC)] 		= 0x011C;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_LCDACDC)] 	= 0x0100;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_EM)] 		= 0x1038;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_DC1)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_BPC1)] 		= 0x0808;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_FCC)] 		= 0x1100;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_IC)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_OC)] 		= 0x0D01;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_PC1)] 		= 0x0800;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_PC2)] 		= 0x0018;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_PC3)] 		= 0x6121;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_PC4)] 		= 0x006F;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_PC5)] 		= 0x495F;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_VCIR)] 		= 0x0020;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_RAMAS1)] 	= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_RAMAS2)] 	= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_WDGRAM)] 	= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_SR)] 		= 0x00CE;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GSC)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_VSC1)] 		= 0x00DB;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_VSC2)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_VSC3)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_PDP1)] 		= 0x00DB;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_PDP2)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_HWA1)] 		= 0x00AF;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_HWA2)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_VWA1)] 		= 0x00DB;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_VWA2)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC1)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC2)] 		= 0x0808;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC3)] 		= 0x080A;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC4)] 		= 0x000A;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC5)] 		= 0x0A08;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC6)] 		= 0x0808;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC7)] 		= 0x0000;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC8)] 		= 0x0A00;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC9)] 		= 0x0710;
    regs[LIB_ILI9225_get_reg_local_addr(LIB_ILI9225_GC10)] 		= 0x0710;
}

void LIB_ILI9225_write_reg(uint16_t reg, uint16_t data, uint16_t mask){
	LIB_ILI9225_write_regT(reg, data, mask);
	LIB_ILI9225_wreg(reg, regs[LIB_ILI9225_get_reg_local_addr(reg)]);
}

void LIB_ILI9225_write_reg_sim(uint16_t reg, uint16_t data, uint16_t mask, int sim){
	if(sim)
		LIB_ILI9225_write_regT(reg, data, mask);
	else
		LIB_ILI9225_write_reg(reg, data, mask);
}

void LIB_ILI9225_write_regT(uint16_t reg, uint16_t data, uint16_t mask){
	regs[LIB_ILI9225_get_reg_local_addr(reg)] = (regs[LIB_ILI9225_get_reg_local_addr(reg)] & ~mask) | (data & mask);
}

void LIB_ILI9225_wreg(uint16_t reg, uint16_t data){
	LIB_ILI9225_wcom(reg);
	
	LIB_ILI9225_wdata(data);
}

void LIB_ILI9225_wcom(uint16_t com){
	RP3_GPIO_pin_clear(pin_rs);
	RP3_GPIO_pin_clear(pin_cs);
	buffer[0] = (char)(com >> 8);
	buffer[1] = (char)(com);
	RP3_SPI_transmit(buffer, 2);
	RP3_GPIO_pin_set(pin_cs);
}


void LIB_ILI9225_wdata(uint16_t data){
	RP3_GPIO_pin_set(pin_rs);
	buffer[0] = (char)(data >> 8);
	buffer[1] = (char)(data);
	RP3_GPIO_pin_clear(pin_cs);
	RP3_SPI_transmit(buffer, 2);
	RP3_GPIO_pin_set(pin_cs);
}

uint16_t LIB_ILI9225_get_reg_local_addr(uint16_t reg){
	switch(reg){
		case LIB_ILI9225_DOC: 		return  0;
        case LIB_ILI9225_LCDACDC: 	return  1;
        case LIB_ILI9225_EM: 		return  2;
        case LIB_ILI9225_DC1: 		return  3;
        case LIB_ILI9225_BPC1: 		return  4;
        case LIB_ILI9225_FCC: 		return  5;
        case LIB_ILI9225_IC: 		return  6;
        case LIB_ILI9225_OC: 		return  7;
        case LIB_ILI9225_PC1: 		return  8;
        case LIB_ILI9225_PC2: 		return  9;
        case LIB_ILI9225_PC3: 		return 10;
        case LIB_ILI9225_PC4: 		return 11;
        case LIB_ILI9225_PC5: 		return 12;
        case LIB_ILI9225_VCIR: 		return 13;
        case LIB_ILI9225_RAMAS1: 	return 14;
        case LIB_ILI9225_RAMAS2: 	return 15;
        case LIB_ILI9225_WDGRAM: 	return 16;
        case LIB_ILI9225_SR: 		return 17;
        case LIB_ILI9225_GSC: 		return 18;
        case LIB_ILI9225_VSC1: 		return 19;
        case LIB_ILI9225_VSC2: 		return 20;
        case LIB_ILI9225_VSC3: 		return 21;
        case LIB_ILI9225_PDP1: 		return 22;
        case LIB_ILI9225_PDP2: 		return 23;
        case LIB_ILI9225_HWA1: 		return 24;
        case LIB_ILI9225_HWA2: 		return 25;
        case LIB_ILI9225_VWA1: 		return 26;
        case LIB_ILI9225_VWA2: 		return 27;
        case LIB_ILI9225_GC1: 		return 28;
        case LIB_ILI9225_GC2: 		return 29;
        case LIB_ILI9225_GC3: 		return 30;
        case LIB_ILI9225_GC4: 		return 31;
        case LIB_ILI9225_GC5: 		return 32;
        case LIB_ILI9225_GC6: 		return 33;
        case LIB_ILI9225_GC7: 		return 34;
        case LIB_ILI9225_GC8: 		return 35;
        case LIB_ILI9225_GC9: 		return 36;
        case LIB_ILI9225_GC10: 		return 37;
		default: return 0xffff;
	}
}

uint16_t LIB_ILI9225_get_local_addr_reg(uint16_t addr){
	switch(addr){
		case  0: 	return LIB_ILI9225_DOC;
        case  1: 	return LIB_ILI9225_LCDACDC;
        case  2: 	return LIB_ILI9225_EM;
        case  3: 	return LIB_ILI9225_DC1;
        case  4: 	return LIB_ILI9225_BPC1;
        case  5: 	return LIB_ILI9225_FCC;
        case  6: 	return LIB_ILI9225_IC;
        case  7: 	return LIB_ILI9225_OC;
        case  8: 	return LIB_ILI9225_PC1;
        case  9: 	return LIB_ILI9225_PC2;
        case 10: 	return LIB_ILI9225_PC3;
        case 11: 	return LIB_ILI9225_PC4;
        case 12: 	return LIB_ILI9225_PC5;
        case 13: 	return LIB_ILI9225_VCIR;
        case 14: 	return LIB_ILI9225_RAMAS1;
        case 15: 	return LIB_ILI9225_RAMAS2;
        case 16: 	return LIB_ILI9225_WDGRAM;
        case 17: 	return LIB_ILI9225_SR;
        case 18: 	return LIB_ILI9225_GSC;
        case 19: 	return LIB_ILI9225_VSC1;
        case 20: 	return LIB_ILI9225_VSC2;
        case 21: 	return LIB_ILI9225_VSC3;
        case 22: 	return LIB_ILI9225_PDP1;
        case 23: 	return LIB_ILI9225_PDP2;
        case 24: 	return LIB_ILI9225_HWA1;
        case 25: 	return LIB_ILI9225_HWA2;
        case 26: 	return LIB_ILI9225_VWA1;
        case 27: 	return LIB_ILI9225_VWA2;
        case 28: 	return LIB_ILI9225_GC1;
        case 29: 	return LIB_ILI9225_GC2;
        case 30: 	return LIB_ILI9225_GC3;
        case 31: 	return LIB_ILI9225_GC4;
        case 32: 	return LIB_ILI9225_GC5;
        case 33: 	return LIB_ILI9225_GC6;
        case 34: 	return LIB_ILI9225_GC7;
        case 35: 	return LIB_ILI9225_GC8;
        case 36: 	return LIB_ILI9225_GC9;
        case 37: 	return LIB_ILI9225_GC10;
		default: return 0xffff;
	}
}