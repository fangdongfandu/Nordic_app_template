/* Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "twi_master.h"
#include "mpu6050.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "nrf_delay.h"


/*lint ++flb "Enter library region" */

#define ADDRESS_WHO_AM_I          (0x75U) // !< WHO_AM_I register identifies the device. Expected value is 0x68.
#define ADDRESS_SIGNAL_PATH_RESET (0x68U) // !<

static const uint8_t expected_who_am_i = 0x68U; // !< Expected value to get from WHO_AM_I register.
static uint8_t       m_device_address;          // !< Device address in bits [7:1]

bool mpu6050_init(uint8_t device_address)
{
    bool transfer_succeeded = true;

    m_device_address = (uint8_t)(device_address << 1);

    // Do a reset on signal paths
    uint8_t reset_value = 0x04U | 0x02U | 0x01U; // Resets gyro, accelerometer and temperature sensor signal paths.
    transfer_succeeded &= mpu6050_register_write(ADDRESS_SIGNAL_PATH_RESET, reset_value);
	
    // Read and verify product ID
    transfer_succeeded &= mpu6050_verify_product_id();
	
    return transfer_succeeded;
}

bool mpu6050_verify_product_id(void)
{
    uint8_t who_am_i;

    if (mpu6050_register_read(ADDRESS_WHO_AM_I, &who_am_i, 1))
    {
        if (who_am_i != expected_who_am_i)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool mpu6050_register_write(uint8_t register_address, uint8_t value)
{
    uint8_t w2_data[2];

    w2_data[0] = register_address;
    w2_data[1] = value;
    return twi_master_transfer(m_device_address, w2_data, 2, TWI_ISSUE_STOP);
}

bool mpu6050_register_read(uint8_t register_address, uint8_t * destination, uint8_t number_of_bytes)
{
    bool transfer_succeeded;
    transfer_succeeded  = twi_master_transfer(m_device_address, &register_address, 1, TWI_DONT_ISSUE_STOP);
    transfer_succeeded &= twi_master_transfer(m_device_address|TWI_READ_BIT, destination, number_of_bytes, TWI_ISSUE_STOP);
    return transfer_succeeded;
}

uint16_t mpu6050_get_temperature(void)
{
	uint8_t buf[2];
	short raw;
	float temp;
	if(mpu6050_register_read(0x41,buf,2) != false)
	{
		raw = ((uint16_t)buf[0]<<8)|buf[1]; 
		temp=36.53+((double)raw)/340;  
		return temp*100;;
	}
	else
	{
		return 0;
	}
}

uint8_t mpu6050_write_len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
	uint8_t i;
	uint8_t buf_value[17] = {0};
	buf_value[0] = reg;
	for(i = 0;i < len;i++)
	{
		buf_value[i + 1] = buf[i];
	}
    if(twi_master_transfer(m_device_address, buf_value, len + 1, TWI_ISSUE_STOP) == true)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
}

uint8_t mpu6050_read_len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
	twi_master_transfer(m_device_address, &reg, 1, TWI_DONT_ISSUE_STOP);
	if(twi_master_transfer(m_device_address|TWI_READ_BIT, buf, len, TWI_ISSUE_STOP) == true)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


/*lint --flb "Leave library region" */
