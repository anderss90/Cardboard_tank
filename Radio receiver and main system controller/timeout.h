/*
 * timeout.h
 *
 * Created: 07.05.2014 23:21:34
 *  Author: Anders
 */ 


#ifndef TIMEOUT_H_
#define TIMEOUT_H_


void timeout_init();
void timeout_start();
//resetting the timer, it keeps counting from 0 again
void timeout_reset();
void timeout_disable();
//time ran out since last received message
ISR(TIMER0_COMPA_vect);


#endif /* TIMEOUT_H_ */