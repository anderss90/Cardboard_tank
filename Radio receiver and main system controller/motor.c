#include "common_variables.h"

#define PIN_RIGHT_SERVO PB1
#define PIN_LEFT_SERVO PB2

#define PIN_RIGHT_FORWARD PC2
#define PIN_RIGHT_BACKWARD PC3
#define PIN_LEFT_FORWARD PC4
#define PIN_LEFT_BACKWARD PC5

#include "servo.h"

void motor_init(){
	//output
	SetBit(DDRC,PIN_RIGHT_FORWARD);
	SetBit(DDRC,PIN_RIGHT_BACKWARD);
	SetBit(DDRC,PIN_LEFT_FORWARD);
	SetBit(DDRC,PIN_LEFT_BACKWARD);
	
	//init
	SetBit(PORTC,PIN_RIGHT_FORWARD);
	SetBit(PORTC,PIN_RIGHT_BACKWARD);
	SetBit(PORTC,PIN_LEFT_FORWARD);
	SetBit(PORTC,PIN_LEFT_BACKWARD);
}

void motor_right_forward(){
	//servo_enable(PIN_RIGHT_SERVO);
	//servo_set_angle(PIN_RIGHT_SERVO,0);
	ClrBit(PORTC,PIN_RIGHT_FORWARD);
}

void motor_right_backward(){
	//servo_enable(PIN_RIGHT_SERVO);
	//servo_set_angle(PIN_RIGHT_SERVO,400);
	ClrBit(PORTC,PIN_RIGHT_BACKWARD);
}

void motor_left_backward(){
	//servo_enable(PIN_LEFT_SERVO);
	//servo_set_angle(PIN_LEFT_SERVO,0);
	ClrBit(PORTC,PIN_LEFT_BACKWARD);
}

void motor_left_forward(){
	//servo_enable(PIN_LEFT_SERVO);
	//servo_set_angle(PIN_LEFT_SERVO,400);
	ClrBit(PORTC,PIN_LEFT_FORWARD);
}
void motor_forward(){
	motor_right_forward();
	motor_left_forward();
}

void motor_backward(){
	motor_right_backward();
	motor_left_backward();
}
void motor_spin_right(){
	motor_right_backward();
	motor_left_forward();
}
void motor_spin_left(){
	motor_right_forward();
	motor_left_backward();
}

void motor_turn_right(){
	motor_left_forward();
	//servo_disable(PIN_RIGHT_SERVO);
	SetBit(PORTC,PIN_RIGHT_FORWARD);
	SetBit(PORTC,PIN_RIGHT_BACKWARD);
}
void motor_turn_left(){
	motor_right_forward();
	//servo_disable(PIN_LEFT_SERVO);
	SetBit(PORTC,PIN_LEFT_FORWARD);
	SetBit(PORTC,PIN_LEFT_BACKWARD);
}

void motor_backward_right(){
	motor_left_backward();
	//servo_disable(PIN_RIGHT_SERVO);
	SetBit(PORTC,PIN_RIGHT_FORWARD);
	SetBit(PORTC,PIN_RIGHT_BACKWARD);
}
void motor_backward_left(){
	motor_right_backward();
	//servo_disable(PIN_LEFT_SERVO);
	SetBit(PORTC,PIN_LEFT_FORWARD);
	SetBit(PORTC,PIN_LEFT_BACKWARD);
}

void motor_stop(){
	//servo_disable(PIN_RIGHT_SERVO);
	//servo_disable(PIN_LEFT_SERVO);
	SetBit(PORTC,PIN_RIGHT_FORWARD);
	SetBit(PORTC,PIN_RIGHT_BACKWARD);
	SetBit(PORTC,PIN_LEFT_FORWARD);
	SetBit(PORTC,PIN_LEFT_BACKWARD);
}

void motor_failsafe(){
	motor_stop();
	turret_turn(STOP);
}