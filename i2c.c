/* I2C library*/

#include "i2c.h"

// The flag to indicate whether an I2C error has occured.
unsigned char b_i2c_error_flag1 = 0;

// Function Purpose: Configure I2C module
void InitI2C(void)
{
	
		i2c_init(&TWIE, TWI_BAUD(F_CPU, BAUD_100K));
	
}

unsigned char b_i2c_check_error_flag(void)
{
	return b_i2c_error_flag1;
}

// Function Purpose: I2C_Start sends start bit sequence
void I2C_Start(void)
{
	i2c_start(&TWIE, 0x39, I2C_WRITE);
}

// Function Purpose: I2C_ReStart sends start bit sequence
void I2C_ReStart(void)
{
	i2c_restart(&TWIE, 0x39, I2C_READ);
}

//Function : I2C_Stop sends stop bit sequence
void I2C_Stop(void)
{
	i2c_stop(&TWIE);
}

//Function : I2C_Send_ACK sends ACK bit sequence

void I2C_Write_Byte(unsigned char Byte)
{
i2c_write(&TWIE, Byte);
	}
	


// Function Purpose: i2c_read reads one byte
uint8_t i2c_read(TWI_t *twi, uint8_t ack)
{
	uint8_t SSPBUF;

	while( ! (twi->MASTER.STATUS & TWI_MASTER_RIF_bm) );                       // wait until received
	SSPBUF = twi->MASTER.DATA;                                                   // read data
	twi->MASTER.CTRLC = ((ack==I2C_ACK) ? TWI_MASTER_CMD_RECVTRANS_gc :        // send ack (go on) or
	TWI_MASTER_ACKACT_bm|TWI_MASTER_CMD_STOP_gc); //     nack (and stop)

	if ( ack == I2C_NACK ) {
		while( ! (twi->MASTER.STATUS & TWI_MASTER_BUSSTATE_IDLE_gc) );
	}

	return SSPBUF;
}
	