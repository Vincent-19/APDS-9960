/* 
 * File:   i2c.h
 * Author: Nurul Syuhada @ Cytron Technologies Sdn. Bhd.
 *
 * Created on July 3, 2015, 1:41 PM
*/
#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <util/twi.h>
#include <avr/io.h>
#include "I2C0,2.h"
// Define i2c pins
#define SDA			PORTE.PIN0_bp				// Data pin for i2c
#define SCK			PORTE.PIN1_bp				// Clock pin for i2c
#define I2C_ACK     0
#define I2C_NACK    1
#define I2C_READ    1
#define I2C_WRITE   0
// Define i2c speed
#define I2C_SPEED	100				// kbps

#define _XTAL_FREQ 20000000

 
//Function Declarations
void InitI2C(void);
//unsigned char b_i2c_check_error_flag(void);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_Write_Byte(unsigned char);
uint8_t i2c_read(TWI_t *twi, uint8_t ack);
#endif


