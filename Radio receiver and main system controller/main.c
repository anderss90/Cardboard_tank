#include "common_variables.h"
void servo_disable(int PIN);
void servo_enable(int PIN);

void led_init(){
	//debugled
	SetBit(DDRC,debug_led1);
	ClrBit(PORTC,debug_led1);
	//debugled
	SetBit(DDRC,debug_led2);
	ClrBit(PORTC,debug_led2);
}



void derp_driving(){
	
		motor_forward();
		_delay_ms(delay_time);
		
		//turret_turn(COUNTER_CLOCKWISE);
		motor_backward();
		_delay_ms(delay_time);
		
		motor_turn_left();
		
		_delay_ms(delay_time);
		
		motor_turn_right();
		_delay_ms(delay_time);
		
		motor_spin_left();
		turret_turn(CLOCKWISE);
		_delay_ms(delay_time);
		//turret_turn(STOP);
		
		motor_spin_right();
		//
		_delay_ms(delay_time);
		//turret_turn(STOP);
}

void timing_test(){
	
	SetBit(PORTD,PD0);
	_delay_ms(1000);
	ClrBit(PORTD,PD0);
	_delay_ms(1000);
}

void blink_led(int led){
	SetBit(PORTC,led);
	_delay_ms(400);
	ClrBit(PORTC,led);
	_delay_ms(400);
}

 

void servo_card_init(){
	//Input
	ClrBit(DDRC,PC5);
	ClrBit(DDRC,PC4);
	ClrBit(DDRC,PC3);
	ClrBit(DDRC,PC2);
	
	//pullup
	SetBit(PORTC,PC5);
	SetBit(PORTC,PC4);
	SetBit(PORTC,PC3);
	SetBit(PORTC,PC2);
}

void servo_card_drive(){
	
	//right servo
	if (!CheckBit(PINC,PC5)){
		motor_right_forward();
	}
	else if (!CheckBit(PINC,PC4)){
		motor_right_backward();
	}
	else servo_disable(PIN_RIGHT_SERVO);
	
	//left servo
	if(!CheckBit(PINC,PC3)){
		motor_left_forward();
	}
	else if (!CheckBit(PINC,PC2)){
		motor_left_backward();
		
	}
	else servo_disable(PIN_LEFT_SERVO);
}







int main (void)
{
	turret_init();
	rf_init();
	motor_init();
	radio_protocol_init();
	timeout_init();
	while(1){
		
		//process_data_new();
		//if (dataready==1){
			//process_data_new();
			//timeout_start();
		//}
		//derp_driving();
		
	}
}