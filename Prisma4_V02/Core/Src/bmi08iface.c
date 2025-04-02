/**
 * Copyright (C) 2024 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "main.h"
#include <bmi08iface.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "dwt_delay.h"

/******************************************************************************/
/*!                       Macro definitions                                   */

#define BMI08_READ_WRITE_LEN  UINT8_C(46)

/*! BMI085 shuttle id */
#define BMI085_SHUTTLE_ID     UINT16_C(0x46)

/*! BMI088 shuttle id */
#define BMI088_SHUTTLE_ID     UINT16_C(0x66)

// I2C Timeout in ms
#define BMI08_BUS_TIMEOUT     100

/******************************************************************************/
/*!                Static variable definition                                 */

/*! Variable that holds the I2C device address or SPI chip selection for accel */
uint8_t acc_dev_add;

/*! Variable that holds the I2C device address or SPI chip selection for gyro */
uint8_t gyro_dev_add;

extern I2C_HandleTypeDef BMI08_I2C_HANDLE;

/******************************************************************************/
/*!                User interface functions                                   */
BMI08_INTF_RET_TYPE bmi08_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t*)intf_ptr;
    uint8_t status;

    // CAUTION: MEM_READ not working with BMI088!!!
    status = HAL_I2C_Master_Transmit(& BMI08_I2C_HANDLE, dev_addr<<1, &reg_addr, 1,BMI08_BUS_TIMEOUT);

    if (status != HAL_OK)
    {
   		printf("ERROR: BMI Read (1) failed (dev 0x%2x reg 0x%02x status %i\r\n", dev_addr, reg_addr,status);
    }
    else
    {
    	status = HAL_I2C_Master_Receive(& BMI08_I2C_HANDLE, dev_addr<<1, (uint8_t *)reg_data, len, BMI08_BUS_TIMEOUT);
    	if (status != HAL_OK)
    	{
       		printf("ERROR: BMI Read (2) failed (dev 0x%2x reg 0x%02x status %i\r\n", dev_addr, reg_addr,status);
    	}
    }

    return status;
}

/*!
 * I2C write function map to COINES platform
 */
BMI08_INTF_RET_TYPE bmi08_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t*)intf_ptr;
    uint8_t status;

    status = HAL_I2C_Mem_Write(&BMI08_I2C_HANDLE, dev_addr<<1, reg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)reg_data, len, BMI08_BUS_TIMEOUT);
    if (status != HAL_OK)
    {
   		printf("ERROR: BMI Write (1) failed (dev 0x%2x reg 0x%02x status %i\r\n", dev_addr, reg_addr,status);
    }
    return status;
}

/*!
 * SPI read function map to COINES platform
 */
BMI08_INTF_RET_TYPE bmi08_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    //uint8_t dev_addr = *(uint8_t*)intf_ptr;

    return 0;//coines_read_spi(COINES_SPI_BUS_0, dev_addr, reg_addr, reg_data, (uint16_t)len);
}

/*!
 * SPI write function map to COINES platform
 */
BMI08_INTF_RET_TYPE bmi08_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    //uint8_t dev_addr = *(uint8_t*)intf_ptr;

    return 0;//coines_write_spi(COINES_SPI_BUS_0, dev_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)len);
}

/*!
 * Delay function map to COINES platform
 */
void bmi08_delay_us(uint32_t period, void *intf_ptr)
{
    //(void)intf_ptr;

	dwt_delay_us(period);
}

/*!
 *  @brief Function to select the interface between SPI and I2C.
 *  Also to initialize coines platform
 */
int8_t bmi08_interface_init(struct bmi08_dev *bmi08, uint8_t intf, uint8_t variant)
{
    int8_t rslt = BMI08_OK;
    HAL_StatusTypeDef status;
    uint8_t data[2];

        rslt=dwt_delay_init();
        printf("dwt init: %i\r\n",rslt);
        /* Bus configuration : I2C */
		printf("I2C Interface \n");

		/* To initialize the user I2C function */
		acc_dev_add = BMI08_ACCEL_I2C_ADDR_SECONDARY;
		gyro_dev_add = BMI08_GYRO_I2C_ADDR_SECONDARY;
		bmi08->intf = BMI08_I2C_INTF;
		bmi08->read = bmi08_i2c_read;
		bmi08->write = bmi08_i2c_write;

		/* Check I2C access */
		//I2C_BusRecover(GPIOA, GPIO_PIN_15,GPIOB, GPIO_PIN_7);
		HAL_Delay(20);

		status = HAL_I2C_IsDeviceReady( & BMI08_I2C_HANDLE, acc_dev_add<<1, 1,500);
		if (status != HAL_OK)
		{
			printf("ERROR: BMI088 accelerometer 0x%02x not responding to I2C, status %i\r\n",acc_dev_add, status);
			HAL_Delay(100);	/* Time for printf */
			Error_Handler();
		}

		status = HAL_I2C_IsDeviceReady( & BMI08_I2C_HANDLE, gyro_dev_add<<1, 1,500);
		if (status != HAL_OK)
		{
			printf("ERROR: BMI088 gyrometer not responding to I2C\r\n");
			HAL_Delay(100);	/* Time for printf */
			Error_Handler();
		}

		// Soft Reset
		data[0] = BMI08_REG_ACCEL_SOFTRESET;
		data[1] = BMI08_SOFT_RESET_CMD;
		status = HAL_I2C_Master_Transmit(& BMI08_I2C_HANDLE, acc_dev_add<<1, data, 2,BMI08_BUS_TIMEOUT);
		printf("BMI Soft Reset acc %i\r\n",status);
		HAL_Delay(2);
		data[0] = BMI08_REG_GYRO_SOFTRESET;
		data[1] = BMI08_SOFT_RESET_CMD;
		HAL_I2C_Master_Transmit(& BMI08_I2C_HANDLE, gyro_dev_add<<1, data, 2,BMI08_BUS_TIMEOUT);
		printf("BMI Soft Reset gyro %i\r\n",status);
		HAL_Delay(100);

		/* SDO pin is made low */
		//(void)coines_set_pin_config(COINES_SHUTTLE_PIN_SDO, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);

		/* SDO pin is made low for selecting I2C address 0x76*/
		//(void)coines_set_pin_config(COINES_SHUTTLE_PIN_8, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);

		/* PS pin is made high for selecting I2C protocol (gyroscope)*/
		//(void)coines_set_pin_config(COINES_SHUTTLE_PIN_9, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_HIGH);

		//(void)coines_config_i2c_bus(COINES_I2C_BUS_0, COINES_I2C_STANDARD_MODE);
		//coines_delay_msec(10);

        /* Selection of bmi085 or bmi088 sensor variant */
        bmi08->variant = (enum bmi08_variant)variant;

        /* Assign accel device address to accel interface pointer */
        bmi08->intf_ptr_accel = &acc_dev_add;

        /* Assign gyro device address to gyro interface pointer */
        bmi08->intf_ptr_gyro = &gyro_dev_add;

        /* Configure delay in microseconds */
        bmi08->delay_us = bmi08_delay_us;

        /* Configure max read/write length (in bytes) ( Supported length depends on target machine) */
        bmi08->read_write_len = BMI08_READ_WRITE_LEN;

    return rslt;

}

/*!
 *  @brief Prints the execution status of the APIs.
 */
void bmi08_error_codes_print_result(const char api_name[], int8_t rslt)
{
    if (rslt != BMI08_OK)
    {
        printf("%s\t", api_name);
        if (rslt == BMI08_E_NULL_PTR)
        {
            printf("Error [%d] : Null pointer\r\n", rslt);
        }
        else if (rslt == BMI08_E_COM_FAIL)
        {
            printf("Error [%d] : Communication failure\r\n", rslt);
        }
        else if (rslt == BMI08_E_DEV_NOT_FOUND)
        {
            printf("Error [%d] : Device not found\r\n", rslt);
        }
        else if (rslt == BMI08_E_OUT_OF_RANGE)
        {
            printf("Error [%d] : Out of Range\r\n", rslt);
        }
        else if (rslt == BMI08_E_INVALID_INPUT)
        {
            printf("Error [%d] : Invalid input\r\n", rslt);
        }
        else if (rslt == BMI08_E_CONFIG_STREAM_ERROR)
        {
            printf("Error [%d] : Config stream error\r\n", rslt);
        }
        else if (rslt == BMI08_E_RD_WR_LENGTH_INVALID)
        {
            printf("Error [%d] : Invalid Read write length\r\n", rslt);
        }
        else if (rslt == BMI08_E_INVALID_CONFIG)
        {
            printf("Error [%d] : Invalid config\r\n", rslt);
        }
        else if (rslt == BMI08_E_FEATURE_NOT_SUPPORTED)
        {
            printf("Error [%d] : Feature not supported\r\n", rslt);
        }
        else if (rslt == BMI08_W_FIFO_EMPTY)
        {
            printf("Warning [%d] : FIFO empty\r\n", rslt);
        }
        else
        {
            printf("Error [%d] : Unknown error code\r\n", rslt);
        }
    }
}
