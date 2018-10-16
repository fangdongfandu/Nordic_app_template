#ifndef __RF232_H
#define __RF232_H

#include "nrf_gpio.h"
#include "nrf_delay.h"

//引脚定义
#define RF232_MOSI 15
#define RF232_MISO 16
#define RF232_SCK 14
#define RF232_SEL 13
#define RF232_IRQ 12
#define RF232_SDN 11

#define RF232_MOSI_SET nrf_gpio_pin_set(RF232_MOSI)
#define RF232_MOSI_CLR nrf_gpio_pin_clear(RF232_MOSI)

//#define RF232_MISO_SET nrf_gpio_pin_set(RF232_MISO)
//#define RF232_MISO_CLR nrf_gpio_pin_clear(RF232_MISO)

#define RF232_SCK_SET nrf_gpio_pin_set(RF232_SCK)
#define RF232_SCK_CLR nrf_gpio_pin_clear(RF232_SCK)

#define RF232_SEL_SET nrf_gpio_pin_set(RF232_SEL)
#define RF232_SEL_CLR nrf_gpio_pin_clear(RF232_SEL)

//#define RF232_IRQ_SET nrf_gpio_pin_set(RF232_IRQ)
//#define RF232_IRQ_CLR nrf_gpio_pin_clear(RF232_IRQ)

#define RF232_SDN_SET nrf_gpio_pin_set(RF232_SDN)
#define RF232_SDN_CLR nrf_gpio_pin_clear(RF232_SDN)

#define RF23_PWRSTATE_READY    							0x01 
#define RF23_PWRSTATE_RX        						0x05
#define RF23_Rx_packet_received_interrupt               0x02 
#define RF23_PWRSTATE_POWERDOWN   						0x00 
#define RF23_PWRSTATE_TX        						0x09  
#define RF23_PACKET_SENT_INTERRUPT  				    0x04 

#define RF_BUFFER_SIZE 16
//RF control block
struct RFCB
{
	uint8_t deviceID;
	uint8_t rate;
	uint8_t frequency;//频段为：10-24 对应的主机号是：1-15号
	uint8_t receiveFlag;
	uint8_t rxen;
	uint8_t txen;
	uint8_t buffer[RF_BUFFER_SIZE];
};

extern struct RFCB rfcb;

void Rf232_gpio_init(void);

void RFM23_Init(void);

extern void ReadFifoRFM23(uint8_t *dest, uint8_t len);

extern void ToRxMode(void); 

extern void InitRF(uint8_t rate, uint8_t frequency);

void ToTxMode(uint8_t *buf);

void ResetRFM23(uint8_t rate,uint8_t frequency);

void SetChannel(uint8_t n);


#endif
