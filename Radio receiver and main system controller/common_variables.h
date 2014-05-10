
#ifndef COMMON_VARIABLES_H_
#define COMMON_VARIABLES_H_

//includes
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>


#include "motor.h"
#include "radio.h"
#include "radio_protocol.h"
#include "servo.h"
#include "turret.h"
#include "timeout.h"

//macros
#define SetBit(x,y) (x|=(1<<y))
#define ClrBit(x,y) (x&=~(1<<y))
#define ToggleBit(x,y) (x^=(1<<y))
#define CheckBit(adr,bit) (adr & (1<<bit))

//protocol specific
#define RF_MSG_LENGTH 12
#define RF_ID_LENGTH 8
#define RF_CHECKSUM_LENGTH 8
#define n_buttons 10
#define RF_PACKAGE_LENGTH RF_ID_LENGTH+RF_MSG_LENGTH+RF_CHECKSUM_LENGTH

#define delay_time 2000

#define PIN_TURRET_CLOCKWISE PC0
#define PIN_TURRET_COUNTER_CLOCKWISE PC1

#define debug_led1 PC2
#define debug_led2 PC3

enum {CLOCKWISE,COUNTER_CLOCKWISE,STOP};




#endif /* COMMON_VARIABLES_H_ */