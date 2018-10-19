/* 
 * File       : GestureTest.c
 * Author     : Nurul Syuhada @Cytron Technologies Sdn. Bhd.
 * Description: This sample code is for Gesture sensor(APDS-9960). This sample code is to
 *              detect the motion of the hand gesture/ swiping will be display on LCD. 
 *              This sample code is by using PIC16F877A.
 *              Compatible with MPLABX IDE with XC8 C compiler
 * Created on July 21, 2015, 1:51 PM 
 */


//#include  <xc.h>       //Define PIC Registers 
#include  <stdio.h>
#include  <stdbool.h>
#include "lcd.h"
#include "I2C0,2.h"
#include "ADPS9960.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "clock.h"
#include <util/delay.h>
#include <limits.h>
#include <stdint.h>
//#include <stdlib.h>
#include "serialF0.h"

#define F_CPU 2000000UL
#define BAUD_100K        100000UL
#define TWI_BAUD(F_CPU, BAUD_100K)   ((F_CPU / (2 * BAUD_100K)) - 5)

// #pragma config FOSC = HS      // Oscillator Selection bits (HS oscillator)
// #pragma config WDTE = OFF     // Watchdog Timer Enable bit (WDT disabled)
// #pragma config PWRTE = OFF    // Power-up Timer Enable bit (PWRT disabled)
// #pragma config BOREN = OFF    // Brown-out Reset Enable bit (BOR disabled)
// #pragma config LVP = OFF      // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming disabled)
// #pragma config CPD = OFF      // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
// #pragma config WRT = OFF      // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
// #pragma config CP = OFF       // Flash Program Memory Code Protection bit (Code protection off)                  
                              
unsigned int id;
int t;
bool handleGestureFlag = 0;

void handleGesture();
void DelayMs(unsigned int Ms);

ISR(PORTA_INT0_vect)
{
    handleGestureFlag = 1;
	printf("int");
}

int main(void)
{
/* Config32MHzClock;*/
init_stream(F_CPU);
  PORTA.INT0MASK = PIN0_bm; //A0 as input(interrupt)
  PORTA.PIN0CTRL = PORT_ISC_FALLING_gc;
  PORTA_INTCTRL = PORT_INT0LVL_LO_gc;
  PMIC.CTRL |= PMIC_LOLVLEN_bm;
  sei();
  
  	/*i2c_init(&TWIE, TWI_BAUD(F_CPU, BAUD_100K));
  	PORTE.DIRSET    = PIN1_bm|PIN0_bm;            // SDA 0 SCL 1
  	PORTE.PIN0CTRL  = PORT_OPC_WIREDANDPULL_gc;   // Pullup SDA
  	PORTE.PIN1CTRL  = PORT_OPC_WIREDANDPULL_gc;   // Pullup SCL*/
  	

  // Initialize interrupt service routine
  
  
  _delay_ms(20);

  lcd_clear();
  printf("gesture test\n");

  if (initialize())
  {
    lcd_clear();
    printf("Initialize");

  } else {
    lcd_clear();
    printf("Error");
   // _delay_ms(1000);

  }
  printf("still working");
  if (enableGestureSensor(true))
  {
    lcd_clear();
    printf("enable sensor");
    _delay_ms(1000);
  }
  else
  {
    lcd_clear();
    printf("st wrong");
    _delay_ms(1000);
  }


  while (1)
  {
    if(handleGestureFlag)
    {
      
      handleGestureFlag = 0;
      handleGesture();  
     printf("help"); 
    }
     
  }
     printf("help"); 
}

void handleGesture()
{
  if (isGestureAvailable())
  {
    switch (readGesture())
    {
      case DIR_UP:
        lcd_clear();
        printf("up");
        _delay_ms(1000);
        break;
      case DIR_DOWN:
        lcd_clear();
        printf("down");
        _delay_ms(1000);
        break;
      case DIR_LEFT:
        lcd_clear();
        printf("left");
        _delay_ms(1000);
        break;
      case DIR_RIGHT:
        lcd_clear();
        printf("right");
        _delay_ms(1000);
        break;
      case DIR_NEAR:
        lcd_clear();
        lcd_home();
        printf("near");
        _delay_ms(1000);
        break;
      case DIR_FAR:
        lcd_clear();
        printf("far");
        _delay_ms(1000);
        break;
      default:
        lcd_clear();
        printf("NONE");
        _delay_ms(1000);
    }
    lcd_clear();
  }
}

void DelayMs(unsigned int Ms)
{
  int delay_cnst;
  while (Ms > 0)
  {
    Ms--;
    for (delay_cnst = 0; delay_cnst < 220; delay_cnst++);
  }
}