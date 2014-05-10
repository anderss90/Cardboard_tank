
#ifndef COMMON_VARIABLES_H_
#define COMMON_VARIABLES_H_

//includes
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

//macros
#define SetBit(x,y) (x|=(1<<y))
#define ClrBit(x,y) (x&=~(1<<y))
#define ToggleBit(x,y) (x^=(1<<y))
#define CheckBit(adr,bit) (adr & (1<<bit))

//buttons
#define RIGHT_PAD_UP PC5
#define RIGHT_PAD_DOWN PC2
#define RIGHT_PAD_LEFT PC3
#define RIGHT_PAD_RIGHT PC4

#define LEFT_PAD_UP PD6
#define LEFT_PAD_DOWN PB0
#define LEFT_PAD_LEFT PD5
#define LEFT_PAD_RIGHT PD7

#define OPT_BUTTON_LEFT PC0
#define OPT_BUTTON_RIGHT PC1


//leds
#define LED1 PB6
#define LED2 PB7
#define LED3 PB1
#define LED4 PB2

//protocol specific
#define RF_MSG_LENGTH 12
#define RF_ID_LENGTH 8
#define RF_CHECKSUM_LENGTH 8
#define n_buttons 10
#define RF_PACKAGE_LENGTH RF_ID_LENGTH+RF_MSG_LENGTH+RF_CHECKSUM_LENGTH



//variables


#endif /* COMMON_VARIABLES_H_ */