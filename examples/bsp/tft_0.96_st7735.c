#include "tft_0.96_st7735.h"
#include "charcode.h"
#include "string.h"

void Tft_gpio_init(void)
{
	nrf_gpio_cfg_output(MOSI);
	nrf_gpio_cfg_output(SCK);
	nrf_gpio_cfg_output(CS);
	nrf_gpio_cfg_output(RES);
	nrf_gpio_cfg_output(A0);
}

void WriteCOM(unsigned char sdata)
{
	unsigned char i;
	A0_CLR;
	CS_CLR;
	for(i = 0;i < 8;i++)
	{
		if(sdata & 0x80)
		{
			MOSI_SET;
		}
		else
		{
			MOSI_CLR;
		}
		SCK_CLR;
		//_nop_();
		SCK_SET;
		//_nop_();
		sdata <<= 1;
	}
	CS_SET;
}

void WriteDAT(unsigned char DH,unsigned char DL)
{
	WriteRegister(DH);
	WriteRegister(DL);
}

void LCD_WriteData_16Bit(unsigned int Data)
{
	WriteRegister((Data >> 8) & 0xff);
	WriteRegister(Data & 0xff);
}


void WriteRegister(unsigned char sdata)
{
	unsigned char i;
	A0_SET;
	CS_CLR;
	for(i = 0;i < 8;i++)
	{
		if(sdata & 0x80)
		{
			MOSI_SET;
		}
		else
		{
			MOSI_CLR;
		}
		SCK_CLR;
		//_nop_();
		SCK_SET;
		//_nop_();
		sdata <<= 1;
	}
	CS_SET;
}


void dsp_single_color(unsigned int dat)
{
	unsigned int i,j;
	Lcd_SetRegion(0,0,0x7F,0x3F);

	for(i=0;i<64;i++)		
	{		
		for (j=0;j<128;j++)
		{
			//LCD_WriteData_16Bit(dat); 
			WriteDAT(dat >> 8, dat);
		}
	}	
}

void dsp_single_color_stripe(void)											
{
	unsigned int i,j;
    Lcd_SetRegion(0,0,0x7F,0x3F);

	for(i=0;i<20;i++)
	{	for (j=0;j<128;j++)
		{ WriteDAT(0xf8,0x00);}	//R	
	}

	for(i=20;i<40;i++)
	{	for (j=0;j<128;j++)
		{ WriteDAT(0x07,0xe0);}	//G
	}

	for(i=40;i<64;i++)
	{	for (j=0;j<128;j++)
		{ WriteDAT(0x00,0x1f);}	//B		
	}
}

void InitST7735B(void)
{
	RES_SET;
	delayms(100);
	RES_CLR;
	delayms(50);
	RES_SET;
	delayms(120);


	WriteCOM(0x11);//sleep out

	delayms(120);
	//=====set frame rate=====
	WriteCOM(0xB1);//frame rate control
	WriteRegister(0x05);
	WriteRegister(0x3A);
	WriteRegister(0x3A);

	WriteCOM(0x36);//
	WriteRegister(0x08);//RGB 18-bit
	
	WriteCOM(0xB2);
	WriteRegister(0x05);
	WriteRegister(0x3A);
	WriteRegister(0x3A);
	
	WriteCOM(0xB3);
	WriteRegister(0x05);
	WriteRegister(0x3A);
	WriteRegister(0x3A);
	WriteRegister(0x05);
	WriteRegister(0x3A);
	WriteRegister(0x3A);
	//==========
	WriteCOM(0xB4);//inversion setting
	WriteRegister(0x00);//0x00=dot inversion
	//=====set power sequence=====
	WriteCOM(0xC0);//Power Control 1
	WriteRegister(0xAA);//AVDD=4.5V;GVDD=4.2V         
	WriteRegister(0x0A);//GVCL=4.2V                
	WriteRegister(0x84);//Mode=AUTO;VRHP=VRHN=0
	
	WriteCOM(0xC1);//Power Control 2
	WriteRegister(0xC0);//V25=2.4V;VGH=2AVDD+VGH25-0.5=11.9V;
									 //         VGL=-7.5V
	
	WriteCOM(0xC2);//Power Control 3
	WriteRegister(0x0D);//
	WriteRegister(0x00);//
	
	WriteCOM(0xC3);//Power Control 4
	WriteRegister(0x8D);//
	WriteRegister(0x2A);//
	
	WriteCOM(0xC4);//Power Control 5
	WriteRegister(0x8D);
	WriteRegister(0xEE);
	//===========
	WriteCOM(0xC5);//VCOM setting
	WriteRegister(0x06);//
	//======Gamma=====
	WriteCOM(0xE0);
	WriteRegister(0x06);
	WriteRegister(0x1C);
	WriteRegister(0x10);	
	WriteRegister(0x14);
	WriteRegister(0x30);	
	WriteRegister(0x2B);
	WriteRegister(0x24);
	WriteRegister(0x29);
	WriteRegister(0x28);
	WriteRegister(0x26);
	WriteRegister(0x2E);
	WriteRegister(0x39);
	WriteRegister(0x00);
	WriteRegister(0x02);
	WriteRegister(0x01);
	WriteRegister(0x10);
	
	WriteCOM(0xE1);
	WriteRegister(0x06);
	WriteRegister(0x1C);
	WriteRegister(0x10);	
	WriteRegister(0x14);
	WriteRegister(0x30);	
	WriteRegister(0x2B);
	WriteRegister(0x24);
	WriteRegister(0x29);
	WriteRegister(0x28);
	WriteRegister(0x26);
	WriteRegister(0x2E);
	WriteRegister(0x39);
	WriteRegister(0x00);
	WriteRegister(0x02);
	WriteRegister(0x01);
	WriteRegister(0x10);
	//===========
//	WriteCOM(0xFB);//enable gate pump clk frequency variable
//	WriteRegister(0xA0);
	
//	WriteCOM(0x36);//
//	WriteRegister(0xC8);//RGB 18-bit
	
	
	
	WriteCOM(0x3A);//
	WriteRegister(0x05);//RGB 18-bit
	
	WriteCOM(0x29);//display on
	
	delayms(120);
}

//设置LCD显示区域，在此区域写点数据自动换行
void Lcd_SetRegion(unsigned char x_start,unsigned char y_start,unsigned char x_end,unsigned char y_end)
{
	WriteCOM(0x2A);
	WriteRegister(0x00);
	WriteRegister(x_start + 2);
	WriteRegister(0x00);
	WriteRegister(x_end + 2);

	WriteCOM(0x2B);
	WriteRegister(0x00);
	WriteRegister(y_start + 1);
	WriteRegister(0x00);
	WriteRegister(y_end + 1);
	
	WriteCOM(0x2C);
}

void PutPixel(unsigned char x_start,unsigned char y_start,unsigned int color)//3*3的像素点
{
	unsigned char i;
	Lcd_SetRegion(x_start - 1, y_start - 1, x_start + 1, y_start + 1);
	for(i = 0;i < 9;i++)
		{
			LCD_WriteData_16Bit(color);
		}
}

void GUI_DrowSign(unsigned char x, unsigned char y, unsigned int color)
{
    unsigned char i;

    Lcd_SetRegion(x-3, y, x+3, y);
    for(i=0; i<7; i++)
    {
        LCD_WriteData_16Bit(color);    
    }
    Lcd_SetRegion(x, y-3, x, y+3);
    for(i=0; i<7; i++)
    {
        LCD_WriteData_16Bit(color);    
    }
}
 
void GUI_Line(unsigned char xStart, unsigned char yStart, unsigned char xEnd, unsigned char yEnd, unsigned int color)
{
	unsigned char t;  
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;  
	int incx, incy;  
	unsigned char row, col;  
	delta_x = xEnd - xStart;//计算坐标增量  
	delta_y = yEnd - yStart;  
	col = xStart;  
	row = yStart;  
	if (delta_x > 0)
	{
		incx=1;//设置单步方向
	} 	  
	else    
	{  
	    if (delta_x == 0)
		{
			incx = 0;//垂直线 
		} 		 
	    else 
			{
				incx = -1;
				delta_x = -delta_x;
			}  
	}  
	if (delta_y > 0)
	{
		incy = 1;
	}	  
	else  
	{  
	    if (delta_y == 0)
		{
			incy = 0;//水平线  
		} 
	    else 
		{
			incy = -1;
			delta_y = -delta_y;
		}  
	}  
	if (delta_x > delta_y)
	{ 
		distance = delta_x;//选取基本增量坐标轴  
	}
	else
	{
		distance = delta_y; 
	} 	
	for (t=0; t<=distance+1; t++)  
	{                                     //画线输出  
	    PutPixel(col, row, color);
	    xerr += delta_x;  
	    yerr += delta_y;  
	  	if(xerr > distance)  
	    {  
	        xerr -= distance;  
	        col += incx;  
	    }  
	    if(yerr > distance)  
	    {  
	        yerr -= distance;  
	        row += incy;  
	    }  
	}  
}
//显示ASCII
void GUI_WriteASCII(unsigned char  x, unsigned char y, char *p, unsigned int wordColor, unsigned int backColor)
{
	unsigned char j, wordByte,wordNum;
	unsigned int color;
	while(*p != '\0')
	{
		wordNum = *p - 32;
		Lcd_SetRegion(x,y,x+15, y+23);
		for (wordByte=0; wordByte<48; wordByte++)
		{
			color = ASCII16x24[wordNum][wordByte];
			for (j=0; j<8; j++) 
			{
				if ((color&0x80) == 0x80)
				{
					LCD_WriteData_16Bit(wordColor);
				} 						
				else
				{
					LCD_WriteData_16Bit(backColor);
				} 	
				color <<= 1;
			}
		}
		p++;
		x +=16;
	}
}

void GUI_Write14CnChar(unsigned char x,unsigned char y,char *cn,unsigned int wordColor,unsigned int backColor)	 
{  
	unsigned char i, j, wordNum;
	unsigned int color;
	while (*cn != '\0')
	{
		Lcd_SetRegion(x, y, x+23, y+18);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNum扫描字库的字数
			if ((CnChar19x24[wordNum].Index[0]==*cn)
			     &&(CnChar19x24[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<57; i++) 
				{	//MSK的位数
					color=CnChar19x24[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_WriteData_16Bit(wordColor);
						} 						
						else
						{
							LCD_WriteData_16Bit(backColor);
						} 
						color<<=1;
					}//for(j=0;j<8;j++)结束
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)结束 	
		cn += 2;
		x += 24;
	}
}

void GUI_ShowPicture(unsigned char x, unsigned char y, unsigned char wide, unsigned char high)
{
	unsigned int temp = 0, tmp = 0, num = 0;
	Lcd_SetRegion(x, y, x+wide-1, y+high-1);
	num = wide * high * 2;
	do
	{   
		temp = gImage_pic[tmp + 1];
		temp = temp << 8;
		temp = temp | gImage_pic[tmp];
		LCD_WriteData_16Bit(temp);   //逐点显示
		tmp += 2;
	}
	while(tmp < num);	
}








