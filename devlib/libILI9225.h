#ifndef LIBILI9225_H_
#define LIBILI9225_H_

#include <stdint.h>

typedef enum LIB_ILI9225_SCAN_DIR { 
	LIB_ILI9225_SCAN_DIR_single_down = 0b00,
	LIB_ILI9225_SCAN_DIR_single_up   = 0b01,
	LIB_ILI9225_SCAN_DIR_split_down	 = 0b10,
	LIB_ILI9225_SCAN_DIR_split_up	 = 0b11
} LIB_ILI9225_SCAN_DIR;	

typedef enum LIB_ILI9225_LCD_SCANNING_MODE { 
	LIB_ILI9225_LCD_SCANNING_MODE_frame_inversion_1field 	= 0b000,
	LIB_ILI9225_LCD_SCANNING_MODE_frame_inversion_3field 	= 0b001,
	LIB_ILI9225_LCD_SCANNING_MODE_line_inversion_1field 	= 0b010,
	LIB_ILI9225_LCD_SCANNING_MODE_2line_inversion_1field 	= 0b100,
	LIB_ILI9225_LCD_SCANNING_MODE_no_inversion_positive 	= 0b110,
	LIB_ILI9225_LCD_SCANNING_MODE_no_inversion_negative 	= 0b111
} LIB_ILI9225_LCD_SCANNING_MODE;

typedef enum LIB_ILI9225_LCD_DISPLAY_MODE { 
	LIB_ILI9225_LCD_DISPLAY_MODE_0degrees_nflip 	= 0b110,
	LIB_ILI9225_LCD_DISPLAY_MODE_0degrees_flip 		= 0b010,
	LIB_ILI9225_LCD_DISPLAY_MODE_90degrees_nflip 	= 0b101,
	LIB_ILI9225_LCD_DISPLAY_MODE_90degrees_flip 	= 0b001,
	LIB_ILI9225_LCD_DISPLAY_MODE_180degrees_nflip 	= 0b000,
	LIB_ILI9225_LCD_DISPLAY_MODE_180degrees_flip 	= 0b100,
	LIB_ILI9225_LCD_DISPLAY_MODE_270degrees_nflip	= 0b011,
	LIB_ILI9225_LCD_DISPLAY_MODE_270degrees_flip	= 0b111
} LIB_ILI9225_LCD_DISPLAY_MODE;

typedef enum LIB_ILI9225_LCD_DISPLAY_POWER { 
	LIB_ILI9225_LCD_DISPLAY_POWER_Stop 		= 0b0000,
	LIB_ILI9225_LCD_DISPLAY_POWER_Slow1 	= 0b0001,
	LIB_ILI9225_LCD_DISPLAY_POWER_Slow2 	= 0b0010,
	LIB_ILI9225_LCD_DISPLAY_POWER_Slow3 	= 0b0011,
	LIB_ILI9225_LCD_DISPLAY_POWER_MSlow1 	= 0b0100,
	LIB_ILI9225_LCD_DISPLAY_POWER_MSlow2 	= 0b0101,
	LIB_ILI9225_LCD_DISPLAY_POWER_MSlow3 	= 0b0110,
	LIB_ILI9225_LCD_DISPLAY_POWER_MSlow4 	= 0b0111,
	LIB_ILI9225_LCD_DISPLAY_POWER_MFast1 	= 0b1000,
	LIB_ILI9225_LCD_DISPLAY_POWER_MFast2 	= 0b1001,
	LIB_ILI9225_LCD_DISPLAY_POWER_MFast3 	= 0b1010,
	LIB_ILI9225_LCD_DISPLAY_POWER_MFast4 	= 0b1011,
	LIB_ILI9225_LCD_DISPLAY_POWER_Fast1 	= 0b1100,
	LIB_ILI9225_LCD_DISPLAY_POWER_Fast2 	= 0b1101,
	LIB_ILI9225_LCD_DISPLAY_POWER_Fast3 	= 0b1110,
	LIB_ILI9225_LCD_DISPLAY_POWER_Fast4 	= 0b1111
} LIB_ILI9225_LCD_DISPLAY_POWER;
	
/**Initialize the screen.*/
void LIB_ILI9225_init(uint32_t clock, int GPIO_RS, int GPIO_CS);

/**Write a register of the screen.*/
void LIB_ILI9225_write_reg(uint16_t reg, uint16_t data, uint16_t mask);

/**Write a command to the screen.*/
void LIB_ILI9225_wcom(uint16_t com);

/**Write a register of the screen.*/
void LIB_ILI9225_wreg(uint16_t reg, uint16_t data);

/**Write data to the screen.*/
void LIB_ILI9225_wdata(uint16_t data);

/**Set the draw mode of the screen.*/
void LIB_ILI9225_set_scan_direction(LIB_ILI9225_SCAN_DIR sd, int sim);

/**Set the driver height of the screen in pixels.*/
void LIB_ILI9225_set_display_driver_height(uint16_t height, int sim);

/**Set the scan mode of the screen.*/
void LIB_ILI9225_set_scanning_mode(LIB_ILI9225_LCD_SCANNING_MODE sm, int sim);

/**Set the rotation and inversion of the screen.*/
void LIB_ILI9225_set_display_mode(LIB_ILI9225_LCD_DISPLAY_MODE dm, int sim);

/**Set the power usage of the display.*/
void LIB_ILI9225_set_display_power(LIB_ILI9225_LCD_DISPLAY_POWER dp, int sim);

/**Set the screen to standby or not.*/
void LIB_ILI9225_set_standby_mode(int standby, int sim);

/**Set the screen to sleep mode or not.*/
void LIB_ILI9225_set_sleep_mode(int sleep, int sim);

/**Software reset.*/
void LIB_ILI9225_software_reset();

/**Set the scroll start and stop positions.*/
void LIB_ILI9225_set_vertical_scroll_start_stop(uint8_t start, uint8_t stop, int sim);

/**Set the scroll speed.*/
void LIB_ILI9225_set_vertical_scroll_speed(uint8_t speed, int sim);

/**Set the draw window.*/
void LIB_ILI9225_set_window(uint8_t xStart, uint8_t yStart, uint8_t xStop, uint8_t yStop, int sim);

/*REGISTERS*/
#define LIB_ILI9225_DCR 			0x00
#define LIB_ILI9225_DOC				0x01
#define LIB_ILI9225_LCDACDC			0x02
#define LIB_ILI9225_EM				0x03
#define LIB_ILI9225_DC1				0x07
#define LIB_ILI9225_BPC1			0x08
#define LIB_ILI9225_FCC				0x0B
#define LIB_ILI9225_IC				0x0C
#define LIB_ILI9225_OC				0x0F
#define LIB_ILI9225_PC1				0x10
#define LIB_ILI9225_PC2				0x11
#define LIB_ILI9225_PC3				0x12
#define LIB_ILI9225_PC4				0x13
#define LIB_ILI9225_PC5				0x14
#define LIB_ILI9225_VCIR			0x15
#define LIB_ILI9225_RAMAS1			0x20
#define LIB_ILI9225_RAMAS2			0x21
#define LIB_ILI9225_WDGRAM			0x22
#define LIB_ILI9225_SR				0x28
#define LIB_ILI9225_GSC				0x30
#define LIB_ILI9225_VSC1			0x31
#define LIB_ILI9225_VSC2			0x32
#define LIB_ILI9225_VSC3			0x33
#define LIB_ILI9225_PDP1			0x34
#define LIB_ILI9225_PDP2			0x35
#define LIB_ILI9225_HWA1			0x36
#define LIB_ILI9225_HWA2			0x37
#define LIB_ILI9225_VWA1			0x38
#define LIB_ILI9225_VWA2			0x39
#define LIB_ILI9225_GC1				0x50
#define LIB_ILI9225_GC2				0x51
#define LIB_ILI9225_GC3				0x52
#define LIB_ILI9225_GC4				0x53
#define LIB_ILI9225_GC5				0x54
#define LIB_ILI9225_GC6				0x55
#define LIB_ILI9225_GC7				0x56
#define LIB_ILI9225_GC8				0x57
#define LIB_ILI9225_GC9				0x58
#define LIB_ILI9225_GC10			0x59

#define LIB_ILI9225_DOC_VSPL		15
#define LIB_ILI9225_DOC_HSPL		14
#define LIB_ILI9225_DOC_DPL			13
#define LIB_ILI9225_DOC_EPL			12
#define LIB_ILI9225_DOC_SM			10
#define LIB_ILI9225_DOC_GS			 9
#define LIB_ILI9225_DOC_SS			 8
#define LIB_ILI9225_DOC_NL4			 4
#define LIB_ILI9225_DOC_NL3			 3
#define LIB_ILI9225_DOC_NL2			 2
#define LIB_ILI9225_DOC_NL1			 1
#define LIB_ILI9225_DOC_NL0			 0

#define LIB_ILI9225_LCDACDC_INV1	 9
#define LIB_ILI9225_LCDACDC_INV0	 8
#define LIB_ILI9225_LCDACDC_FLD		 0

#define LIB_ILI9225_EM_BGR			12
#define LIB_ILI9225_EM_MDT1			 9
#define LIB_ILI9225_EM_MDT0			 8
#define LIB_ILI9225_EM_ID1			 5
#define LIB_ILI9225_EM_ID0			 4
#define LIB_ILI9225_EM_AM			 3

#define LIB_ILI9225_DC1_TEMON		12
#define LIB_ILI9225_DC1_GON			 4
#define LIB_ILI9225_DC1_CL			 3
#define LIB_ILI9225_DC1_REV			 2
#define LIB_ILI9225_DC1_D1			 1
#define LIB_ILI9225_DC1_D0			 0

#define LIB_ILI9225_BPC1_FP3		11
#define LIB_ILI9225_BPC1_FP2		10
#define LIB_ILI9225_BPC1_FP1		 9
#define LIB_ILI9225_BPC1_FP0		 8
#define LIB_ILI9225_BPC1_BP3		 3
#define LIB_ILI9225_BPC1_BP2		 2
#define LIB_ILI9225_BPC1_BP1		 1
#define LIB_ILI9225_BPC1_BP0		 0

#define LIB_ILI9225_FCC_NO3			15
#define LIB_ILI9225_FCC_NO2			14
#define LIB_ILI9225_FCC_NO1			13
#define LIB_ILI9225_FCC_NO0			12
#define LIB_ILI9225_FCC_SDT3		11
#define LIB_ILI9225_FCC_SDT2		10
#define LIB_ILI9225_FCC_SDT1		 9
#define LIB_ILI9225_FCC_SDT0		 8
#define LIB_ILI9225_FCC_RTN3		 3
#define LIB_ILI9225_FCC_RTN2		 2
#define LIB_ILI9225_FCC_RTN1		 1
#define LIB_ILI9225_FCC_RTN0		 0

#define LIB_ILI9225_IC_RM			 8
#define LIB_ILI9225_IC_DM			 4
#define LIB_ILI9225_IC_RIM1			 1
#define LIB_ILI9225_IC_RIM0			 0

#define LIB_ILI9225_OC_FOSC4		12
#define LIB_ILI9225_OC_FOSC3		11
#define LIB_ILI9225_OC_FOSC2		10
#define LIB_ILI9225_OC_FOSC1		 9
#define LIB_ILI9225_OC_FOSC0		 8
#define LIB_ILI9225_OC_OSC_ON		 0

#define LIB_ILI9225_PC1_SAP3		11
#define LIB_ILI9225_PC1_SAP2		10
#define LIB_ILI9225_PC1_SAP1		 9
#define LIB_ILI9225_PC1_SAP0		 8
#define LIB_ILI9225_PC1_AB2A		 4
#define LIB_ILI9225_PC1_DSTB		 1
#define LIB_ILI9225_PC1_STB			 0

#define LIB_ILI9225_PC2_APON		12
#define LIB_ILI9225_PC2_PON3		11
#define LIB_ILI9225_PC2_PON2		10
#define LIB_ILI9225_PC2_PON1		 9
#define LIB_ILI9225_PC2_PON0		 8
#define LIB_ILI9225_PC2_AON			 5
#define LIB_ILI9225_PC2_VCI1_EN		 4
#define LIB_ILI9225_PC2_VC3			 3
#define LIB_ILI9225_PC2_VC2			 2
#define LIB_ILI9225_PC2_VC1			 1
#define LIB_ILI9225_PC2_VC0			 0

#define LIB_ILI9225_PC3_BT2			14
#define LIB_ILI9225_PC3_BT1			13
#define LIB_ILI9225_PC3_BT0			12
#define LIB_ILI9225_PC3_DC11		 9
#define LIB_ILI9225_PC3_DC10		 8
#define LIB_ILI9225_PC3_DC21		 5
#define LIB_ILI9225_PC3_DC20		 4
#define LIB_ILI9225_PC3_DC31		 1
#define LIB_ILI9225_PC3_DC30		 0

#define LIB_ILI9225_PC4_DCR_EX		12
#define LIB_ILI9225_PC4_DCR2		10
#define LIB_ILI9225_PC4_DCR1		 9
#define LIB_ILI9225_PC4_DCR0		 8
#define LIB_ILI9225_PC4_GVD6		 6
#define LIB_ILI9225_PC4_GVD5		 5
#define LIB_ILI9225_PC4_GVD4		 4
#define LIB_ILI9225_PC4_GVD3		 3
#define LIB_ILI9225_PC4_GVD2		 2
#define LIB_ILI9225_PC4_GVD1		 1
#define LIB_ILI9225_PC4_GVD0		 0

#define LIB_ILI9225_PC5_VCOMG		15
#define LIB_ILI9225_PC5_VCM6		14
#define LIB_ILI9225_PC5_VCM5		13
#define LIB_ILI9225_PC5_VCM4		12
#define LIB_ILI9225_PC5_VCM3		11
#define LIB_ILI9225_PC5_VCM2		10
#define LIB_ILI9225_PC5_VCM1		 9
#define LIB_ILI9225_PC5_VCM0		 8
#define LIB_ILI9225_PC5_VCMR		 7
#define LIB_ILI9225_PC5_VML6		 6
#define LIB_ILI9225_PC5_VML5		 5
#define LIB_ILI9225_PC5_VML4		 4
#define LIB_ILI9225_PC5_VML3		 3
#define LIB_ILI9225_PC5_VML2		 2
#define LIB_ILI9225_PC5_VML1		 1
#define LIB_ILI9225_PC5_VML0		 0

#define LIB_ILI9225_VCIR_VCIR2		 6
#define LIB_ILI9225_VCIR_VCIR1		 5
#define LIB_ILI9225_VCIR_VCIR0		 4
#define LIB_ILI9225_VCIR_VCIR_VSS	 0

#define LIB_ILI9225_RAMAS1_AD7		 7
#define LIB_ILI9225_RAMAS1_AD6		 6
#define LIB_ILI9225_RAMAS1_AD5		 5
#define LIB_ILI9225_RAMAS1_AD4		 4
#define LIB_ILI9225_RAMAS1_AD3		 3
#define LIB_ILI9225_RAMAS1_AD2		 2
#define LIB_ILI9225_RAMAS1_AD1		 1
#define LIB_ILI9225_RAMAS1_AD0		 0

#define LIB_ILI9225_RAMAS2_AD15		 7
#define LIB_ILI9225_RAMAS2_AD14		 6
#define LIB_ILI9225_RAMAS2_AD13		 5
#define LIB_ILI9225_RAMAS2_AD12		 4
#define LIB_ILI9225_RAMAS2_AD11		 3
#define LIB_ILI9225_RAMAS2_AD10		 2
#define LIB_ILI9225_RAMAS2_AD9		 1
#define LIB_ILI9225_RAMAS2_AD8		 0

#define LIB_ILI9225_GSC_SCN4		 4
#define LIB_ILI9225_GSC_SCN3		 3
#define LIB_ILI9225_GSC_SCN2		 2
#define LIB_ILI9225_GSC_SCN1		 1
#define LIB_ILI9225_GSC_SCN0		 0

#define LIB_ILI9225_VSC1_SEA7		 7
#define LIB_ILI9225_VSC1_SEA6		 6
#define LIB_ILI9225_VSC1_SEA5		 5
#define LIB_ILI9225_VSC1_SEA4		 4
#define LIB_ILI9225_VSC1_SEA3		 3
#define LIB_ILI9225_VSC1_SEA2		 2
#define LIB_ILI9225_VSC1_SEA1		 1
#define LIB_ILI9225_VSC1_SEA0		 0

#define LIB_ILI9225_VSC2_SSA7		 7
#define LIB_ILI9225_VSC2_SSA6		 6
#define LIB_ILI9225_VSC2_SSA5		 5
#define LIB_ILI9225_VSC2_SSA4		 4
#define LIB_ILI9225_VSC2_SSA3		 3
#define LIB_ILI9225_VSC2_SSA2		 2
#define LIB_ILI9225_VSC2_SSA1		 1
#define LIB_ILI9225_VSC2_SSA0		 0

#define LIB_ILI9225_VSC3_SST7		 7
#define LIB_ILI9225_VSC3_SST6		 6
#define LIB_ILI9225_VSC3_SST5		 5
#define LIB_ILI9225_VSC3_SST4		 4
#define LIB_ILI9225_VSC3_SST3		 3
#define LIB_ILI9225_VSC3_SST2		 2
#define LIB_ILI9225_VSC3_SST1		 1
#define LIB_ILI9225_VSC3_SST0		 0

#define LIB_ILI9225_PDP1_SE17		 7	
#define LIB_ILI9225_PDP1_SE16		 6
#define LIB_ILI9225_PDP1_SE15		 5
#define LIB_ILI9225_PDP1_SE14		 4
#define LIB_ILI9225_PDP1_SE13		 3
#define LIB_ILI9225_PDP1_SE12		 2
#define LIB_ILI9225_PDP1_SE11		 1
#define LIB_ILI9225_PDP1_SE10		 0

#define LIB_ILI9225_PDP2_SS17		 7
#define LIB_ILI9225_PDP2_SS16		 6
#define LIB_ILI9225_PDP2_SS15		 5
#define LIB_ILI9225_PDP2_SS14		 4
#define LIB_ILI9225_PDP2_SS13		 3
#define LIB_ILI9225_PDP2_SS12		 2
#define LIB_ILI9225_PDP2_SS11		 1
#define LIB_ILI9225_PDP2_SS10		 0

#define LIB_ILI9225_HWA1_HEA7		 7
#define LIB_ILI9225_HWA1_HEA6		 6
#define LIB_ILI9225_HWA1_HEA5		 5
#define LIB_ILI9225_HWA1_HEA4		 4
#define LIB_ILI9225_HWA1_HEA3		 3
#define LIB_ILI9225_HWA1_HEA2		 2
#define LIB_ILI9225_HWA1_HEA1		 1
#define LIB_ILI9225_HWA1_HEA0		 0

#define LIB_ILI9225_HWA2_HSA7		 7
#define LIB_ILI9225_HWA2_HSA6		 6
#define LIB_ILI9225_HWA2_HSA5		 5
#define LIB_ILI9225_HWA2_HSA4		 4
#define LIB_ILI9225_HWA2_HSA3		 3
#define LIB_ILI9225_HWA2_HSA2		 2
#define LIB_ILI9225_HWA2_HSA1		 1
#define LIB_ILI9225_HWA2_HSA0		 0

#define LIB_ILI9225_VWA1_VEA7		 7
#define LIB_ILI9225_VWA1_VEA6		 6
#define LIB_ILI9225_VWA1_VEA5		 5
#define LIB_ILI9225_VWA1_VEA4		 4
#define LIB_ILI9225_VWA1_VEA3		 3
#define LIB_ILI9225_VWA1_VEA2		 2
#define LIB_ILI9225_VWA1_VEA1		 1
#define LIB_ILI9225_VWA1_VEA0		 0

#define LIB_ILI9225_VWA2_VSA7		 7
#define LIB_ILI9225_VWA2_VSA6		 6
#define LIB_ILI9225_VWA2_VSA5		 5
#define LIB_ILI9225_VWA2_VSA4		 4
#define LIB_ILI9225_VWA2_VSA3		 3
#define LIB_ILI9225_VWA2_VSA2		 2
#define LIB_ILI9225_VWA2_VSA1		 1
#define LIB_ILI9225_VWA2_VSA0		 0

#define LIB_ILI9225_GC1_KP13		11
#define LIB_ILI9225_GC1_KP12		10
#define LIB_ILI9225_GC1_KP11		 9
#define LIB_ILI9225_GC1_KP10		 8
#define LIB_ILI9225_GC1_KP03		 3
#define LIB_ILI9225_GC1_KP02		 2
#define LIB_ILI9225_GC1_KP01		 1
#define LIB_ILI9225_GC1_KP00		 0

#define LIB_ILI9225_GC2_KP33		11
#define LIB_ILI9225_GC2_KP32		10
#define LIB_ILI9225_GC2_KP31		 9
#define LIB_ILI9225_GC2_KP30		 8
#define LIB_ILI9225_GC2_KP23		 3
#define LIB_ILI9225_GC2_KP22		 2
#define LIB_ILI9225_GC2_KP21		 1
#define LIB_ILI9225_GC2_KP20		 0

#define LIB_ILI9225_GC3_KP53		11
#define LIB_ILI9225_GC3_KP52		10
#define LIB_ILI9225_GC3_KP51		 9
#define LIB_ILI9225_GC3_KP50		 8
#define LIB_ILI9225_GC3_KP43		 3
#define LIB_ILI9225_GC3_KP42		 2
#define LIB_ILI9225_GC3_KP41		 1
#define LIB_ILI9225_GC3_KP40		 0

#define LIB_ILI9225_GC4_RP13		11
#define LIB_ILI9225_GC4_RP12		10
#define LIB_ILI9225_GC4_RP11		 9
#define LIB_ILI9225_GC4_RP10		 8
#define LIB_ILI9225_GC4_RP03		 3
#define LIB_ILI9225_GC4_RP02		 2
#define LIB_ILI9225_GC4_RP01		 1
#define LIB_ILI9225_GC4_RP00		 0

#define LIB_ILI9225_GC5_KN13		11
#define LIB_ILI9225_GC5_KN12		10
#define LIB_ILI9225_GC5_KN11		 9
#define LIB_ILI9225_GC5_KN10		 8
#define LIB_ILI9225_GC5_KN03		 3
#define LIB_ILI9225_GC5_KN02		 2
#define LIB_ILI9225_GC5_KN01		 1
#define LIB_ILI9225_GC5_KN00		 0

#define LIB_ILI9225_GC6_KN33		11
#define LIB_ILI9225_GC6_KN32		10
#define LIB_ILI9225_GC6_KN31		 9
#define LIB_ILI9225_GC6_KN30		 8
#define LIB_ILI9225_GC6_KN23		 3
#define LIB_ILI9225_GC6_KN22		 2
#define LIB_ILI9225_GC6_KN21		 1
#define LIB_ILI9225_GC6_KN20		 0

#define LIB_ILI9225_GC7_KN53		11
#define LIB_ILI9225_GC7_KN52		10
#define LIB_ILI9225_GC7_KN51		 9
#define LIB_ILI9225_GC7_KN50		 8
#define LIB_ILI9225_GC7_KN43		 3
#define LIB_ILI9225_GC7_KN42		 2
#define LIB_ILI9225_GC7_KN41		 1
#define LIB_ILI9225_GC7_KN40		 0

#define LIB_ILI9225_GC8_RN13		11
#define LIB_ILI9225_GC8_RN12		10
#define LIB_ILI9225_GC8_RN11		 9
#define LIB_ILI9225_GC8_RN10		 8
#define LIB_ILI9225_GC8_RN03		 3
#define LIB_ILI9225_GC8_RN02		 2
#define LIB_ILI9225_GC8_RN01		 1
#define LIB_ILI9225_GC8_RN00		 0


#define LIB_ILI9225_GC9_VRP14		12
#define LIB_ILI9225_GC9_VRP13		11
#define LIB_ILI9225_GC9_VRP12		10
#define LIB_ILI9225_GC9_VRP11		 9
#define LIB_ILI9225_GC9_VRP10		 8
#define LIB_ILI9225_GC9_VRP04		 4
#define LIB_ILI9225_GC9_VRP03		 3
#define LIB_ILI9225_GC9_VRP02		 2
#define LIB_ILI9225_GC9_VRP01		 1
#define LIB_ILI9225_GC9_VRP00		 0

#define LIB_ILI9225_GC10_VRN14		12
#define LIB_ILI9225_GC10_VRN13		11
#define LIB_ILI9225_GC10_VRN12		10
#define LIB_ILI9225_GC10_VRN11		 9
#define LIB_ILI9225_GC10_VRN10		 8
#define LIB_ILI9225_GC10_VRN04		 4
#define LIB_ILI9225_GC10_VRN03		 3
#define LIB_ILI9225_GC10_VRN02		 2
#define LIB_ILI9225_GC10_VRN01		 1
#define LIB_ILI9225_GC10_VRN00		 0

#endif