#include "rf232.h"

struct RFCB rfcb;

const uint8_t FreqTab868[141][3]=
{
  //reg75      reg76	reg77	freq	
	{0x73,	0x64,	0x00},	// 868	0
	{0x73,	0x57,	0x80},	// 867
	{0x73,	0x66,	0x80},	// 868.2
	{0x73,	0x5A,	0x00},	// 867.2	3
	{0x73,	0x69,	0x00},	// 868.4
	{0x73,	0x5C,	0x80},	// 867.4
	{0x73,	0x6B,	0x80},	// 868.6	6
	{0x73,	0x5F,	0x00},	// 867.6
	{0x73,	0x6E,	0x00},	// 868.8
	{0x73,	0x61,	0x80},	// 867.8	9
	{0x73,	0x70,	0x80},	// 869
	{0x73,	0x55,	0x00},	// 866.8
	{0x73,	0x73,	0x00},	// 869.2	12
	{0x73,	0x52,	0x80},	// 866.6
	{0x73,	0x75,	0x80},	// 869.4
	{0x73,	0x50,	0x00},	// 866.4	15
	{0x73,	0x78,	0x00},	// 869.6
	{0x73,	0x4D,	0x80},	// 866.2
	{0x73,	0x7A,	0x80},	// 869.8	18
	{0x73,	0x4B,	0x00},	// 866
	{0x73,	0x7D,	0x00},	// 870
	{0x73,	0x48,	0x80},	// 865.8	21
	{0x73,	0x7F,	0x80},	// 870.2
	{0x73,	0x46,	0x00},  	// 865.6		
	{0x73,	0x82,	0x00},  	// 870.4	24	
	{0x73,	0x43,	0x80},  	// 865.4		
	{0x73,	0x84,	0x80},  	// 870.6		
	{0x73,	0x41,	0x00},  	// 865.2	27	
	{0x73,	0x87,	0x00},  	// 870.8		
	{0x73,	0x3e,	0x80},  	// 865		
	{0x73,	0x89,	0x80},  	// 871	30
	{0x73,	0x3c,	0x00},  	// 864.8		
	{0x73,	0x8c,	0x00},  	// 871.2		
	{0x73,	0x39,	0x80},  	// 864.6	33	
	{0x73,	0x8e,	0x80},  	// 871.4		
	{0x73,	0x37,	0x00},  	// 864.4		
	{0x73,	0x91,	0x00},  	// 871.6	36
	{0x73,	0x34,	0x80},  	// 864.2
	{0x73,	0x93,	0x80},  	// 871.8	
	{0x73,	0x32,	0x00},  	// 864	39	
	{0x73,	0x96,	0x00},  	// 872
	{0x73,	0x2f,	0x80},  	// 863.8		
	{0x73,	0x98,	0x80},  	// 872.2	42	
	{0x73,	0x2d,	0x00},  	// 863.6	
	{0x73,	0x9b,	0x00},  	// 872.4
	{0x73,	0x2a,	0x80},  	// 863.4	45		
	{0x73,	0x9d,	0x80},  	// 872.6	
	{0x73,	0x28,	0x00},  	// 863.2	
	{0x73,	0xa0,	0x00},  	// 872.8	48
	{0x73,	0x25,	0x80},  	// 863		
	{0x73,	0xa2,	0x80},  	// 873	
	{0x73,	0x23,	0x00},  	// 862.8	51	
	{0x73,	0xa5,	0x00},  	// 873.2		
	{0x73,	0x20,	0x80},  	// 862.6		
	{0x73,	0xa7,	0x80},  	// 873.4	54	
	{0x73,	0x1e,	0x00},  	// 862.4	
	{0x73,	0xaa,	0x00},  	// 873.6		
	{0x73,	0x1b,	0x80},  	// 862.2	57		
	{0x73,	0xac,	0x80},  	// 873.8	
	{0x73,	0x19,	0x00},  	// 862	
	{0x73,	0xaf,	0x00},  	// 874	60
	{0x73,	0x16,	0x80},  	// 861.8		
	{0x73,	0xb1,	0x80},  	// 874.2	
	{0x73,	0x14,	0x00},  	// 861.6	63
	{0x73,	0xb4,	0x00},  	// 874.4
	{0x73,	0x11,	0x80},  	// 861.4
	{0x73,	0xb6,	0x80},  	// 874.6	66
	{0x73,	0x0f,	0x00},  	// 861.2
	{0x73,	0xb9,	0x00},  	// 874.8
	{0x73,	0x0c,	0x80},  	// 861	69
	{0x73,	0xbb,	0x80},  	// 875
	{0x73,	0x0a,	0x00},  	// 860.8
	{0x73,	0xbe,	0x00},  	// 875.2	72
	{0x73,	0x07,	0x80},  	// 860.6
	{0x73,	0xc0,	0x80},	// 875.4
	{0x73,	0x05,	0x00},  	// 860.4	75
	{0x73,	0xc3,	0x00},  	// 875.6
	{0x73,	0x02,	0x80},  	// 860.2
	{0x73,	0xc5,	0x80},  	// 875.8	78
	{0x73,	0x00,	0x00},  	// 860
	{0x73,	0xc8,	0x00},  	// 876
	{0x72,	0xf7,	0x80},  	// 859.8	81		
	{0x73,	0xca,	0x80},  	// 876.2
	{0x72,	0xf5,	0x00},  	// 859.6
	{0x73,	0xcd,	0x00},  	// 876.4	84
	{0x72,	0xf2,	0x80},  	// 859.4		
	{0x73,	0xcf,	0x80},  	// 876.6
	{0x72,	0xf0,	0x00},  	// 859.2	87	
	{0x73,	0xd2,	0x00},  	// 876.8
	{0x72,	0xed,	0x80},  	// 859		
	{0x73,	0xd4,	0x80},  	// 877	90
	{0x72,	0xeb,	0x00},  	// 858.8
	{0x73,	0xd7,	0x00},  	// 877.2
	{0x72,	0xe8,	0x80},  	// 858.6	93
	{0x73,	0xd9,	0x80},  	// 877.4
	{0x72,	0xe6,	0x00},	// 858.4
	{0x73,	0xdc,	0x00},  	// 877.6	96
	{0x72,	0xe3,	0x80},  	// 858.2
	{0x73,	0xde,	0x80},  	// 877.8
	{0x72,	0xe1,	0x00},  	// 858	99
	{0x73,	0xe1,	0x00},  	// 878
	{0x72,	0xde,	0x80},  	// 857.8
	{0x73,	0xe3,	0x80},  	// 878.2	102
	{0x72,	0xdd,	0x00},  	// 857.6
	{0x73,	0xe6,	0x00},  	// 878.4
	{0x72,	0xd9,	0x80},  	// 857.4	105
	{0x74,	0xe8,	0x80},  	// 878.6
	{0x72,	0xd4,	0x00},  	// 857.2
	{0x73,	0xeb,	0x00},  	// 878.8	108
	{0x72,	0xd4,	0x80},  	// 857
	{0x73,	0xed,	0x80},  	// 879
	{0x72,	0xd2,	0x00},  	// 856.8	111
	{0x73,	0xf0,	0x00},  	// 879.2
	{0x72,	0xcf,	0x80},  	// 856.6
	{0x73,	0xf2,	0x80},  	// 879.4	114
	{0x72,	0xcd,	0x00},  	// 856.4
	{0x73,	0xf5,	0x00},  	// 879.6
	{0x72,	0xca,	0x80},  	// 856.2	117
	{0x73,	0xf7,	0x80},  	// 879.8
	{0x72,	0xc8,	0x00},  	// 856
	{0x74,	0x00,	0x00},  	// 880	120
	{0x72,	0xc5,	0x80},  	// 855.8
	{0x74,	0x02,	0x80},  	// 880.2
	{0x72,	0xc3,	0x00},  	// 855.6	123
	{0x74,	0x05,	0x00},  	// 880.4
	{0x72,	0xc0,	0x80},  	// 855.4
	{0x74,	0x07,	0x80},  	// 880.6	126
	{0x72,	0xbe,	0x00},  	// 855.2
	{0x74,	0x0a,	0x00},  	// 880.8
	{0x72,	0xbb,	0x80},  	// 855	129
	{0x74,	0x0c,	0x80},  	// 881
	{0x72,	0xb9,	0x00},  	// 854.8
	{0x74,	0x0f,	0x00},  	// 881.2	132
	{0x72,	0xb6,	0x80},  	// 854.6
	{0x74,	0x11,	0x80},  	// 881.4
	{0x72,	0xb4,	0x00},  	// 854.4	135
	{0x74,	0x14,	0x00},  	// 881.6
	{0x72,	0xb1,	0x80},  	// 854.2
	{0x74,	0x16,	0x80},  	// 881.8	138
	{0x72,	0xaf,	0x00},  	// 854
	{0x74,	0x19,	0x00}  	// 882
};

uint8_t ItStatus1,ItStatus2; 

void Rf232_gpio_init(void)
{
	nrf_gpio_cfg_output(RF232_MOSI);
	nrf_gpio_cfg_output(RF232_SCK);
	nrf_gpio_cfg_output(RF232_SEL);
	nrf_gpio_cfg_output(RF232_SDN);
	
	nrf_gpio_cfg_input(RF232_MISO,NRF_GPIO_PIN_NOPULL);
}

void Write8bitcommand(uint8_t command)    // keep sel to low 
{
	uint8_t i = 8;
	RF232_SEL_SET;
	RF232_SCK_CLR;
	RF232_SEL_CLR;
	while(i--)
	{
		if(command & 0x80)
		{
			RF232_SCK_CLR;
			RF232_MOSI_SET;
			RF232_SCK_SET;
		}
		else
		{
			RF232_SCK_CLR;
			RF232_MOSI_CLR;
			RF232_SCK_SET;
		}
		command = command << 1;
	}
	RF232_SCK_CLR;
}

void send_read_address(uint8_t i) 
{ 
	i &= 0x7f; 
	Write8bitcommand(i); 
}  

uint8_t read_8bit_data(void) 
{
	uint8_t i;
    uint8_t Result=0; 
	RF232_SCK_CLR;
	for(i = 0;i < 8;i++)
	{
		Result = Result << 1;
		RF232_SCK_SET;
		if(nrf_gpio_pin_read(RF232_MISO))
		{
			Result |= 1;
		}
		RF232_SCK_CLR;
	}
    return Result; 
}  

void send_8bit_data(uint8_t i) 
{ 
	uint8_t n = 8; 
	RF232_SCK_CLR;
    while(n--) 
    { 
         if(i&0x80) 
		 {
			RF232_SCK_CLR;
			 RF232_MOSI_SET;
			 RF232_SCK_SET;
		 }
         else 
		 {
			RF232_SCK_CLR;
			 RF232_MOSI_CLR;
			RF232_SCK_SET; 
		 }
         i = i << 1; 
    } 
    RF232_SCK_CLR;
} 

uint8_t spi_read(uint8_t address) 
{ 
	uint8_t result; 
	send_read_address(address); 
	result = read_8bit_data();  
	RF232_SEL_SET; 
	return(result); 
}

void spi_write(uint8_t address, uint8_t data) 
{ 
	address |= 0x80; 
	Write8bitcommand(address); 
	send_8bit_data(data);  
	RF232_SEL_SET; 
}

void InitParameterRFM23(uint8_t rate)
{
	RF232_SDN_SET;
	nrf_delay_ms(50);
	RF232_SDN_CLR;
	nrf_delay_ms(150);
	
	ItStatus1 = spi_read(0x03);	// read status, clear interrupt	
	ItStatus2 = spi_read(0x04);	
 	spi_write(0x06, 0x00);  // no wakeup up, lbd,	
	spi_write(0x07, 0x01);   // disable lbd, wakeup timer, use internal 32768,xton = 1; in ready mode 
	spi_write(0x09, 0x7f);  // c = 12.5p  
	spi_write(0x0a, 0x05);
	spi_write(0x0b, 0xf2); // gpio0 for received data output
	spi_write(0x0c, 0xF5); // gpio 1 for clk output
	spi_write(0x0d, 0xfd);  // gpio 2 micro-controller clk output
	spi_write(0x0e, 0x00);  // gpio  0, 1,2 NO OTHER FUNCTION.
	spi_write(0x1d, 0x40);  // enable afc
	switch(rate)
	{
		case 0:  // 1.2k
		{
			spi_write(0x70, 0x20);  // disable manchest   rate<30k
			spi_write(0x1c, 0x1B);			
			spi_write(0x20, 0x83); //0x20 calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
			spi_write(0x21, 0xc0); // 0x21 , rxosr[10--8] = 0; stalltr = 0; (default), ccoff[19:16] = 0;
			spi_write(0x22, 0x13);// 0x22  ncoff =5033 = 0x13a9
			spi_write(0x23, 0xa9); // 0x23
			spi_write(0x24, 0x00); // 0x24
			spi_write(0x25, 0x03); // 0x25
			spi_write(0x2a, 0x18);
			spi_write(0x6e, 0x09);
			spi_write(0x6f, 0xd5);
			break;
		}	
		case 1: // 2.4k
		{
			spi_write(0x70, 0x20);  // disable manchest   rate<30k
			spi_write(0x1c, 0x1B);
			spi_write(0x20, 0x41);   //0x20 calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
			spi_write(0x21, 0x60); // 0x21 , rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0;
			spi_write(0x22, 0x27);// 0x22  ncoff =5033 = 0x13a9
			spi_write(0x23, 0x52); // 0x23
			spi_write(0x24, 0x00); // 0x24
			spi_write(0x25, 0x07); // 0x25
			spi_write(0x2a, 0x18);
			spi_write(0x6e, 0x13);
			spi_write(0x6f, 0xa9);
			break;
		}	
		case 2: // 4.8k
		{
			spi_write(0x70, 0x20);  // disable manchest   rate<30k
			spi_write(0x1c, 0x1B);
			spi_write(0x20, 0xa1);   //0x20 calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
			spi_write(0x21, 0x20); // 0x21 , rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0;
			spi_write(0x22, 0x4e);// 0x22  ncoff =5033 = 0x13a9
			spi_write(0x23, 0xa5); // 0x23
			spi_write(0x24, 0x00); // 0x24
			spi_write(0x25, 0x18); // 0x25
			spi_write(0x2a, 0x18);			
			spi_write(0x6e, 0x27);
			spi_write(0x6f, 0x52);
			break;
		}	
			case 3: // 9.6k
		{
			spi_write(0x70, 0x20);  // disable manchest   rate<30k
			spi_write(0x1c, 0x1C);
			spi_write(0x20, 0xd0);  //0x20 calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
			spi_write(0x21, 0x00); // 0x21 , rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0;
			spi_write(0x22, 0x9d);// 0x22  ncoff =5033 = 0x13a9
			spi_write(0x23, 0x49); // 0x23
			spi_write(0x24, 0x00); // 0x24
			spi_write(0x25, 0x58); // 0x25
			spi_write(0x2a, 0x1a);
			spi_write(0x6e, 0x4e);
			spi_write(0x6f, 0xa5);			
			break;
		}
		case 4: // 24k
		{
			spi_write(0x70, 0x20);  // disable manchest   rate<30k
			spi_write(0x1c, 0x1d);
			spi_write(0x20, 0x53);  //0x20 calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
			spi_write(0x21, 0x01); // 0x21 , rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0;
			spi_write(0x22, 0x89);// 0x22  ncoff =5033 = 0x13a9
			spi_write(0x23, 0x37); // 0x23
			spi_write(0x24, 0x02); // 0x24
			spi_write(0x25, 0x1f); // 0x25
			spi_write(0x2a, 0x1e);
			spi_write(0x6e, 0xc4);
			spi_write(0x6f, 0x9c);			
			break;
		}
		case 5: // 50k
		{
			spi_write(0x70, 0x00);  // disable manchest   rate>30k
			spi_write(0x1c, 0x06);
			spi_write(0x20, 0x50);   //0x20 calculate from the datasheet  = 500*(1+2*down3_bypass)/(2^ndec*RB*(1+enmanch))
			spi_write(0x21, 0x01); // 0x21 , rxosr[10--8] = 0; stalltr = (default), ccoff[19:16] = 0;
			spi_write(0x22, 0x99);// 0x22  ncoff =5033 = 0x13a9
			spi_write(0x23, 0x9a); // 0x23
			spi_write(0x24, 0x04); // 0x24
			spi_write(0x25, 0x94); // 0x25			
			spi_write(0x2a, 0x2d);
			spi_write(0x6e, 0x0c);
			spi_write(0x6f, 0xcd);
			break;
		}
		default:break;				
	}	
	
#ifdef	RF23_Test
	spi_write(0x30, 0x00);   // enable packet handler, msb first, enable crc,
	spi_write(0x32, 0x00);  // 0x32address enable for headere byte 0, 1,2,3, receive header check for byte 0, 1,2,3		 
	spi_write(0x33, 0x22);// header 3, 2, 1,0 used for head length, fixed packet length, synchronize word length 3, 2,
#else 
	spi_write(0x30, 0x8c);   // enable packet handler, msb first, enable crc,
	spi_write(0x32, 0xff);  // 0x32address enable for headere byte 0, 1,2,3, receive header check for byte 0, 1,2,3		 
	spi_write(0x33, 0x42);// header 3, 2, 1,0 used for head length, fixed packet length, synchronize word length 3, 2,
#endif

	spi_write(0x34, 64);  // 64 nibble = 32byte preamble
	spi_write(0x35, 0x20);  //0x35 need to detect 20bit preamble
	spi_write(0x36, 0x2d);  // synchronize word
	spi_write(0x37, 0xd4);
	spi_write(0x38, 0x00);
	spi_write(0x39, 0x00);
	spi_write(0x3a, 's');  // tx header
	spi_write(0x3b, 'o');
	spi_write(0x3c, 'n');
	spi_write(0x3d, 'g');
	spi_write(0x3e, 17);  // total tx 17 byte
	spi_write(0x3f, 's'); // check hearder
	spi_write(0x40, 'o');
	spi_write(0x41, 'n');
	spi_write(0x42, 'g');
	spi_write(0x43, 0xff);  // all the bit to be checked
	spi_write(0x44, 0xff);  // all the bit to be checked
	spi_write(0x45, 0xff);  // all the bit to be checked
	spi_write(0x46, 0xff);  // all the bit to be checked

//	init_timing();  // 0x52, 53, 54, 55   set to default 
			// 0x56 ---------0x6c  ??????????????????????????
	
	spi_write(0x6d, 0x07);  // set power

	spi_write(0x79, 0x0);  // no hopping
	spi_write(0x7a, 0x0);  // no hopping

	spi_write(0x71, 0x22); // fsk, fd[8] =0, no invert for Tx/Rx data, fifo mode, txclk -->gpio
	spi_write(0x72, 0x38);  // frequency deviation setting to 35k	

	spi_write(0x73, 0x0);  
	spi_write(0x74, 0x0);  // no offset

	spi_write(0x75, 0x53);  // hbsel = 0, sbsel =1 ???, fb = 19
	spi_write(0x76, 0x64);  // 25600= 0x6400 for 434Mhz
	spi_write(0x77, 0x00);
} 

//----------------------------------------------------------------------- 
void SetChannel(uint8_t n)  
{
	if(n >= 129)
		return;
    
    spi_write(0x75, FreqTab868[n][0]);
    spi_write(0x76, FreqTab868[n][1]);
    spi_write(0x77, FreqTab868[n][2]);	
}

//----------------------------------------------------------------------- 
void ToReadyMode(void) 
{ 
	ItStatus1 = spi_read(0x03);   
	ItStatus2 = spi_read(0x04); 
	spi_write(0x07, RF23_PWRSTATE_READY); 
} 

//--------------------------------------------------------------
void ReadFifoRFM23(uint8_t *dest, uint8_t len)
{
	uint8_t i = 0;
//	uint8_t length = RF_BUFFER_SIZE;
	
	uint8_t length=len;
    ItStatus1 = spi_read(0x03);
    if(ItStatus1&0x02)	//rx irq
    {
        send_read_address(0x7f); 
        for(i = 0; i < length; i++) 
            dest[i] = read_8bit_data();
        nrf_delay_ms(10);
    }
}	

//----------------------------------------------------------------------- 

uint8_t rssiData[4];
uint8_t rssiCount=0;
void SampleRssi(void)
{
	rssiData[rssiCount]=spi_read(0x26);
	rssiCount=(rssiCount+1)&3;
}
//----------------------------------------------------------------------- 
uint8_t GetRssi(void)
{
	return rssiData[(rssiCount-2)&3];
}
//----------------------------------------------------------------------- 
void SetTxPower(uint8_t level)
{
    spi_write(0x6d, level);  // set power
}

/********************** transmitting **************************/	
void ToTxMode(uint8_t *buf) 
{ 
	uint8_t i; 
	uint8_t length = RF_BUFFER_SIZE;
	ToReadyMode();  
	spi_write(0x08, 0x03);    // disable AUTO TX MODE, enble multi packet clear fifo 
	spi_write(0x08, 0x00);    // disable AUTO TX MODE, enble multi packet, clear fifo 

	// ph +fifo mode 
	spi_write(0x34, 64);    // 64 nibble = 32byte preamble 
	spi_write(0x3e, length);    // total tx 17 byte 
	for (i = 0; i<length; i++) 
	{ 
		spi_write(0x7f, buf[i]);  
	} 
	spi_write(0x05, RF23_PACKET_SENT_INTERRUPT);  
	ItStatus1 = spi_read(0x03);    //read the Interrupt Status1 register 
	ItStatus2 = spi_read(0x04); 
	spi_write(0x07, RF23_PWRSTATE_TX);    // to tx mode 
} 

/*********************** receiving **************************/
void RxReset(void) 
{ 
	spi_write(0x07, RF23_PWRSTATE_READY); 
	spi_write(0x7e, 17);    // threshold for rx  almost full, interrupt when 1 byte received 
	spi_write(0x08, 0x03);    //clear fifo disable multi packet 
	spi_write(0x08, 0x00);    // clear fifo, disable multi packet 
	spi_write(0x07,RF23_PWRSTATE_RX );    // to rx mode 
	spi_write(0x05, RF23_Rx_packet_received_interrupt); 
	ItStatus1 = spi_read(0x03);  //read the Interrupt Status1 register 
	ItStatus2 = spi_read(0x04); 
} 

void ToRxMode(void) 
{
	ToReadyMode();   
	RxReset(); 
}  


void ResetRFCB(void)
{
	uint8_t *ptr = (uint8_t *)&rfcb;
	uint8_t i;
	for(i = 0; i < sizeof(struct RFCB); i++)
		*(ptr++) = 0;
}

void ResetRFM23(uint8_t rate,uint8_t frequency)
{
    RF232_SDN_CLR;
    nrf_delay_ms(10);//100
    
	InitParameterRFM23(rate);
	SetTxPower(7);	
	SetChannel(frequency);
	ToRxMode();
}


void InitRF(uint8_t rate, uint8_t frequency)
{
	uint8_t ptr[18] = {0};
	ResetRFCB();
    ResetRFM23(rate,frequency);                                                              //开机设定为0频段24K速率
    nrf_delay_ms(10); 
	
	ptr[0] = 0x00;
	ptr[1] = 0x01;
	ptr[2] = 0x02;
	ptr[3] = 0x03;
    ptr[4] = 0x04;
    ptr[5] = 0x05;
    ptr[6] = 0x06;
    ptr[7] = 0x07;
    ptr[8] = 0x08;
    ptr[9] = 0x09;
    ptr[10] = 0x10;
    ptr[11] = 0x11;
    ptr[12] = 0x12;
	ptr[13] = 0x13;
	ptr[14] = 0x14;
	ptr[15] = 0x15;
    
    ToTxMode(ptr);    
	
}


void RFM23_Init(void)
{
	InitRF(4,41);	
}


