/*
 * motor.h
 *
 * Created: 20.04.2014 14:59:05
 *  Author: Anders
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

void motor_right_forward();
void motor_right_backward();
void motor_left_backward();
void motor_left_forward();
void motor_forward();
void motor_backward();
void motor_spin_right();
void motor_spin_left();
void motor_turn_right();
void motor_turn_left();
void motor_backward_right();
void motor_backward_left();

void motor_stop();
void motor_init();

void motor_failsafe();

#endif /* MOTOR_H_ */