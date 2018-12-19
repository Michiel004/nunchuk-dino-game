#ifndef RASP3BASE_H_
#define RASP3BASE_H_


#define BASE_ADDRESS 		0x3f000000

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

/*GPIO*/
#define GPFSEL0 			0x80000
#define GPFSEL1 			0x80001
#define GPFSEL2 			0x80002
#define GPFSEL3 			0x80003
#define GPFSEL4 			0x80004
#define GPFSEL5 			0x80005
#define GPSET0 				0x80007
#define GPSET1 				0x80008
#define GPCLR0 				0x8000A
#define GPCLR1 				0x8000B
#define GPLEV0 				0x8000D
#define GPLEV1 				0x8000E
#define GPEDS0 				0x80010
#define GPEDS1 				0x80011
#define GPREN0 				0x80013
#define GPREN1 				0x80014
#define GPFEN0 				0x80016
#define GPFEN1 				0x80017 
#define GPHEN0 				0x80019
#define GPHEN1 				0x8001A
#define GPLEN0 				0x8001C
#define GPLEN1 				0x8001D
#define GPAREN0 			0x8001F
#define GPAREN1 			0x80020
#define GPAFEN0 			0x80022
#define GPAFEN1 			0x80023
#define GPPUD 				0x80025
#define GPPUDCLK0 			0x80026
#define GPPUDCLK1 			0x80027
/******/

/*UART*/
#define USRTDR				0x80400
#define USRTRSRECR			0x80401
#define USRTFR				0x80406
#define USRTILPR			0x80408
#define USRTIBRD			0x80409
#define USRTFBRD			0x8040A
#define USRTLCRH			0x8040B
#define USRTCR				0x8040C
#define USRTIFLS			0x8040D
#define USRTIMSC			0x8040E
#define USRTRIS 			0x8040F
#define USRTMIS 			0x80410
#define USRTICR				0x80411
#define USRTDMACR			0x80412
#define USRTITCR 			0x80420
#define USRTITIP			0x80421
#define USRTITOP			0x80422
#define USRTTDR				0x80423

#define USRTDR_OE			11
#define USRTDR_BE			10
#define USRTDR_PE			 9
#define USRTDR_FE			 8
#define USRTDR_DATA			 0

#define USRTRSRECR_OE		 3
#define USRTRSRECR_BE		 2
#define USRTRSRECR_PE		 1
#define USRTRSRECR_FE		 0

#define USRTFR_RI			 8
#define USRTFR_TXFE			 7
#define USRTFR_RXFF			 6
#define USRTFR_TXFF			 5
#define USRTFR_RXFE			 4
#define USRTFR_BUSY			 3
#define USRTFR_DCD			 2
#define USRTFR_DSR			 1
#define USRTFR_CTS			 0

#define USRTLCRH_SPS		 7
#define USRTLCRH_WLEN		 5
#define USRTLCRH_FEN		 4
#define USRTLCRH_STP2		 3
#define USRTLCRH_EPS		 2
#define USRTLCRH_PEN		 1
#define USRTLCRH_BRK		 0

#define USRTCR_CTSEN		15
#define USRTCR_RTSEN		14
#define USRTCR_OUT2			13
#define USRTCR_OUT1			12
#define USRTCR_RTS			11
#define USRTCR_DTR			10
#define USRTCR_RXE			 9
#define USRTCR_TXE			 8
#define USRTCR_LBE			 7
#define USRTCR_SIRLP		 2
#define USRTCR_SIREN		 1
#define USRTCR_UARTEN		 0

#define USRTIFLS_RXIFPSEL	 9
#define USRTIFLS_TXIFPSEL	 6
#define USRTIFLS_RXIFLSEL	 3
#define USRTIFLS_TXIFLSEL	 0

#define USRTIMSC_OEIM		10
#define USRTIMSC_BEIM		 9
#define USRTIMSC_PEIM		 8
#define USRTIMSC_FEIM		 7
#define USRTIMSC_RTIM		 6
#define USRTIMSC_TXIM		 5
#define USRTIMSC_RXIM		 4
#define USRTIMSC_DSRMIM		 3
#define USRTIMSC_DCDMIM		 2
#define USRTIMSC_CTSMIM		 1
#define USRTIMSC_RIMIM		 0

#define USRTRIS_OERIS 		10
#define USRTRIS_BERIS 		 9
#define USRTRIS_PERIS 		 8
#define USRTRIS_FERIS 		 7
#define USRTRIS_RTRIS 		 6
#define USRTRIS_TXRIS 		 5
#define USRTRIS_RXRIS 		 4
#define USRTRIS_DSRRMIS		 3
#define USRTRIS_DCDRMIS		 2
#define USRTRIS_CTSRMIS		 1
#define USRTRIS_RIRMIS 		 0

#define USRTMIS_OEMIS		10
#define USRTMIS_BEMIS		 9
#define USRTMIS_PEMIS		 8
#define USRTMIS_FEMIS		 7
#define USRTMIS_RTMIS		 6
#define USRTMIS_TXMIS		 5
#define USRTMIS_RXMIS		 4
#define USRTMIS_DSRMMIS		 3
#define USRTMIS_DCDMMIS		 2
#define USRTMIS_CTSMMIS		 1
#define USRTMIS_RIMMIS		 0

#define USRTICR_OEIC		10
#define USRTICR_BEIC		 9
#define USRTICR_PEIC		 8
#define USRTICR_FEIC		 7
#define USRTICR_RTIC		 6
#define USRTICR_TXIC		 5
#define USRTICR_RXIC		 4
#define USRTICR_DSRMIC		 3
#define USRTICR_DCDMIC		 2
#define USRTICR_CTSMIC		 1
#define USRTICR_RIMIC		 0

#define USRTDMACR_DMAONERR	 2
#define USRTDMACR_TXDMAE	 1
#define USRTDMACR_RXDMAE	 0

#define USRTITCR_ITCR1		 1
#define USRTITCR_ITCR0		 0

#define USRTITIP_ITIP3		 3
#define USRTITIP_ITIP0		 0

#define USRTITOP_ITOP11		11
#define USRTITOP_ITOP10		10
#define USRTITOP_ITOP9		 9
#define USRTITOP_ITOP8		 8
#define USRTITOP_ITOP7		 7
#define USRTITOP_ITOP6		 6
#define USRTITOP_ITOP3		 3
#define USRTITOP_ITOP0		 0
/******/

/*INTTERRUPT*/
#define IRQBASIC			0x2C80
#define IRQPEND1			0x2C81
#define IRQPEND2			0x2C82
#define IRQFIQCONTR			0x2C83
#define IRQENA1				0x2C84
#define IRQENA2				0x2C85
#define IRQENABASIC			0x2C86
#define IRQDIS1				0x2C87
#define IRQDIS2				0x2C88
#define IRQDISBASIC			0x2C89

#define IRQRQST_TIMERMATCH1	 1
#define IRQRQST_TIMERMATCH3	 3
#define IRQRQST_USBCONTROL	 9
#define IRQRQST_AUX			29
#define IRQRQST_I2C_SPI_SLV	43
#define IRQRQST_PWA0		45
#define IRQRQST_PWA1		46
#define IRQRQST_SMI			48
#define IRQRQST_GPIO0		49
#define IRQRQST_GPIO1		50
#define IRQRQST_GPIO2		51
#define IRQRQST_GPIO3		52
#define IRQRQST_I2C			53
#define IRQRQST_SPI			54
#define IRQRQST_PCM			55
#define IRQRQST_UART		57

#define IRQFIQSRC_GPU		 0
#define IRQFIQSRC_TIMER		64
#define IRQFIQSRC_MAILBOX	65
#define IRQFIQSRC_DBEL0		66
#define IRQFIQSRC_DBEL1		67
#define IRQFIQSRC_HALTGPU0	68
#define IRQFIQSRC_HALTGPU1	69
#define IRQFIQSRC_ILACC1	70
#define IRQFIQSRC_ILACC0	71

#define IRQBASIC_GPU_IRQ_62	20
#define IRQBASIC_GPU_IRQ_57	19
#define IRQBASIC_GPU_IRQ_56	18
#define IRQBASIC_GPU_IRQ_55	17
#define IRQBASIC_GPU_IRQ_54	16
#define IRQBASIC_GPU_IRQ_53	15
#define IRQBASIC_GPU_IRQ_19	14
#define IRQBASIC_GPU_IRQ_18	13
#define IRQBASIC_GPU_IRQ_10	12
#define IRQBASIC_GPU_IRQ_9	11
#define IRQBASIC_GPU_IRQ_7	10
#define IRQBASIC_PEND2		 9
#define IRQBASIC_PEND1		 8
#define IRQBASIC_ILACC0		 7
#define IRQBASIC_ILACC1		 6
#define IRQBASIC_HALTGPU1	 5
#define IRQBASIC_HRLTGPU0	 4
#define IRQBASIC_DBEL1		 3
#define IRQBASIC_DBEL0		 2
#define IRQBASIC_MAILBOX	 1
#define IRQBASIC_TIMER		 0

#define IRQFIQCONTR_ENA		 7
#define IRQFIQCONTR_SRC		 0

#define IRQENABASIC_ACCER0	 7
#define IRQENABASIC_ACCER1	 6
#define IRQENABASIC_HALTGPU1 5
#define IRQENABASIC_HALTGPU0 4
#define IRQENABASIC_DBEL1	 3
#define IRQENABASIC_DBEL2	 2
#define IRQENABASIC_MAILBOX	 1
#define IRQENABASIC_TIMER	 0

#define IRQDISBASIC_ACCER0	 7
#define IRQDISBASIC_ACCER1	 6
#define IRQDISBASIC_HALTGPU1 5
#define IRQDISBASIC_HALTGPU0 4
#define IRQDISBASIC_DBEL1	 3
#define IRQDISBASIC_DBEL2	 2
#define IRQDISBASIC_MAILBOX	 1
#define IRQDISBASIC_TIMER	 0
/************/

/*SPI*/
#define SPICS				0x81000
#define SPIFIFO				0x81001
#define SPICLK				0x81002
#define SPIDLEN				0x81003
#define SPILTOH				0x81004
#define SPIDC				0x81005

#define SPICS_LEN_LONG		25
#define SPICS_DMA_LEN		24
#define SPICS_CSPOL2		23
#define SPICS_CSPOL1		22
#define SPICS_CSPOL0		21
#define SPICS_RXF			20
#define SPICS_RXR			19
#define SPICS_TXD			18
#define SPICS_RXD			17
#define SPICS_DONE			16
#define SPICS_TE_EN			15
#define SPICS_LMONO			14
#define SPICS_LEN			13
#define SPICS_REN			12
#define SPICS_ADCS			11
#define SPICS_INTR			10
#define SPICS_INTD			 9
#define SPICS_DMAEN			 8
#define SPICS_TA			 7
#define SPICS_CSPOL			 6
#define SPICS_CLEAR			 4
#define SPICS_CPOL			 3
#define SPICS_CPHA			 2
#define SPICS_CS			 0

#define SPIDC_RPANIC		24
#define SPIDC_RDREQ			16
#define SPIDC_TPANIC		 8
#define SPIDC_TDREQ			 0
/*****/


// Peripheral base address
#define PERIPHERAL_BASE 0x20000000UL

/*I2C*/
#define BSC1_BASE 		(0x201000) 

#define BSC1_C        	(BSC1_BASE + 0x00)
#define BSC1_S        	(BSC1_BASE + 0x01)
#define BSC1_DLEN    	(BSC1_BASE + 0x02)
#define BSC1_A        	(BSC1_BASE + 0x03)
#define BSC1_FIFO    	(BSC1_BASE + 0x04)
#define BSC1_DIV    	(BSC1_BASE + 0x05)

#define BSC_C_I2CEN    	(1 << 15)
#define BSC_C_INTR    	(1 << 10)
#define BSC_C_INTT    	(1 << 9)
#define BSC_C_INTD    	(1 << 8)
#define BSC_C_ST    	(1 << 7)
#define BSC_C_CLEAR    	(1 << 4)
#define BSC_C_READ    	1

#define START_READ    	BSC_C_I2CEN|BSC_C_ST|BSC_C_CLEAR|BSC_C_READ
#define START_WRITE   	BSC_C_I2CEN|BSC_C_ST

#define BSC_S_CLKT	(1 << 9)
#define BSC_S_ERR    	(1 << 8)
#define BSC_S_RXF    	(1 << 7)
#define BSC_S_TXE    	(1 << 6)
#define BSC_S_RXD    	(1 << 5)
#define BSC_S_TXD    	(1 << 4)
#define BSC_S_RXR    	(1 << 3)
#define BSC_S_TXW    	(1 << 2)
#define BSC_S_DONE   	(1 << 1)
#define BSC_S_TA    	1

#define CLEAR_STATUS    BSC_S_CLKT|BSC_S_ERR|BSC_S_DONE
/*****/
#endif
