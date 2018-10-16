#ifndef __TFT_0_96_ST7735_H
#define __TFT_0_96_ST7735_H

#include "nrf_gpio.h"
#include "nrf_delay.h"

//引脚定义
#define MOSI 20
#define SCK 19
#define CS 17
#define RES 18
#define A0 6

#define MOSI_SET nrf_gpio_pin_set(MOSI)
#define MOSI_CLR nrf_gpio_pin_clear(MOSI)

#define SCK_SET nrf_gpio_pin_set(SCK)
#define SCK_CLR nrf_gpio_pin_clear(SCK)

#define CS_SET nrf_gpio_pin_set(CS)
#define CS_CLR nrf_gpio_pin_clear(CS)

#define RES_SET nrf_gpio_pin_set(RES)
#define RES_CLR nrf_gpio_pin_clear(RES)

#define A0_SET nrf_gpio_pin_set(A0)
#define A0_CLR nrf_gpio_pin_clear(A0)

//颜色定义
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


#define delayms nrf_delay_ms
//函数说明
void Tft_gpio_init(void);
void WriteCOM(unsigned char sdata);
void WriteDAT(unsigned char DH,unsigned char DL);
void WriteRegister(unsigned char sdata);
void InitST7735B(void);
void dsp_single_color(unsigned int dat);
void dsp_single_color_stripe(void);
void Lcd_SetRegion(unsigned char x_start,unsigned char y_start,unsigned char x_end,unsigned char y_end);
void PutPixel(unsigned char x_start,unsigned char y_start,unsigned int color);
void GUI_DrowSign(unsigned char x, unsigned char y, unsigned int color);
void GUI_Line(unsigned char xStart, unsigned char yStart, unsigned char xEnd, unsigned char yEnd, unsigned int color);
void GUI_WriteASCII16x24(unsigned char  x, unsigned char y, char *p, unsigned int wordColor, unsigned int backColor);
void GUI_Write_ASCII8X12(unsigned char  x, unsigned char y, char *p, unsigned int wordColor, unsigned int backColor);
void GUI_Write_Num(unsigned char  x, unsigned char y, unsigned int num, unsigned int wordColor, unsigned int backColor,unsigned char word_x,unsigned char word_y,unsigned char num_len);
void GUI_Write14CnChar(unsigned char x,unsigned char y,char *cn,unsigned int wordColor,unsigned int backColor);	 
void GUI_ShowPicture(unsigned char x, unsigned char y, unsigned char wide, unsigned char high);

#endif
