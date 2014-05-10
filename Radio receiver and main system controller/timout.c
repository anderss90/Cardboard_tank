/*
 * timout.c
 *
 * Created: 07.05.2014 23:21:26
 *  Author: Anders
 */ 
#include "common_variables.h"

#define TIMEOUT_TIME 0xFF 

void timeout_reset(){
	TCNT2=0;
}

void timeout_init(){
	timeout_disable();
	timeout_reset();
	SetBit(TCCR2A,WGM21); // CTC mode
	SetBit(TIMSK2,OCIE2A); //enable interrupt on timer 0A
	OCR2A=0xFF; //set time
}

void timeout_start(){
	cli();
	timeout_disable();
	timeout_reset();
	SetBit(TCCR2B,CS22); //start timer in 256 prescaler mode
	sei();
	
}

//resetting the timer, it keeps counting from 0 again


void timeout_disable(){
	ClrBit(TCCR2B,CS22);
}


//time ran out since last received message
ISR(TIMER2_COMPA_vect){
	motor_failsafe();
	timeout_disable();
	timeout_reset();
	
	debug_by_running_tracks();
}