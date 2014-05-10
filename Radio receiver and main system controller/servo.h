/*
 * servo.h
 *
 * Created: 20.04.2014 14:56:32
 *  Author: Anders
 */ 


#ifndef SERVO_H_
#define SERVO_H_
#define PIN_RIGHT_SERVO PB1
#define PIN_LEFT_SERVO PB2
int servo_init();
void servo_set_angle(int PIN,int angle);
void servo_disable(int PIN);
void servo_enable(int PIN);
void servo_testing();
void servo_debug();



#endif /* SERVO_H_ */