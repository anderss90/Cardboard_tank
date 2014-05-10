/*
 * turret.c
 *
 * Created: 06.05.2014 19:28:55
 *  Author: Anders
 */ 
#include "common_variables.h"

void turret_init(){
	//Setting pins to output
	SetBit(DDRC,PIN_TURRET_CLOCKWISE);
	SetBit(DDRC,PIN_TURRET_COUNTER_CLOCKWISE);
	
	//stopping turret
	SetBit(PORTC,PIN_TURRET_CLOCKWISE);
	SetBit(PORTC,PIN_TURRET_COUNTER_CLOCKWISE);
}

void turret_turn(int direction){
	//0 means go
	if (direction==CLOCKWISE) {
		ClrBit(PORTC,PIN_TURRET_CLOCKWISE);
		SetBit(PORTC,PIN_TURRET_COUNTER_CLOCKWISE);
	}
	else if (direction==COUNTER_CLOCKWISE){
		ClrBit(PORTC,PIN_TURRET_COUNTER_CLOCKWISE);
		SetBit(PORTC,PIN_TURRET_CLOCKWISE);
	}
	
	
	else if (direction==STOP){
		SetBit(PORTC,PIN_TURRET_CLOCKWISE);
		SetBit(PORTC,PIN_TURRET_COUNTER_CLOCKWISE);
	}
}