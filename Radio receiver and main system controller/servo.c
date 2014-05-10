#define SetBit(x,y) (x|=(1<<y))
#define ClrBit(x,y) (x&=~(1<<y))
#define ToggleBit(x,y) (x^=(1<<y))
#define CheckBit(adr,bit) (adr & (1<<bit))

#include <avr/delay.h>

#include <avr/io.h>

#define PIN_RIGHT_SERVO PB1
#define PIN_LEFT_SERVO PB2

void servo_disable(int PIN){
	if (PIN==PIN_RIGHT_SERVO){
		//ClrBit(DDRB,PB1);
		ClrBit(TCCR1A,COM1A1);
	}
	if (PIN==PIN_LEFT_SERVO){
		//ClrBit(DDRB,PB2);
		ClrBit(TCCR1A,COM1B1);
		
	}
}

int servo_init(){
	//general
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Mode 14, Prescaler 8
	ICR1 = 20000; // 160000 / 8 = 20000
	
	//clock A
	TCCR1A |= (1<<COM1A1) | (1<<WGM11); // non-inverting mode for OC1A
	DDRB |= (1<<PIN_RIGHT_SERVO) ; // OC1A set to output
	
	//clock B
	TCCR1A |= (1<<COM1B1) | (1<<WGM11); // non-inverting mode for OC1B
	DDRB |= (1<<PIN_LEFT_SERVO); // OC1B set to output
	
	servo_disable(PIN_LEFT_SERVO);
	servo_disable(PIN_RIGHT_SERVO);
	return 0;
}

void servo_set_angle(int PIN,int angle){
	int setpoint=((angle/360)*3000);
	if (PIN==PIN_RIGHT_SERVO)OCR1A=setpoint;
	if (PIN==PIN_LEFT_SERVO)OCR1B=setpoint;
}



void servo_enable(int PIN){
	if (PIN==PIN_RIGHT_SERVO)SetBit(TCCR1A,COM1A1);
	if (PIN==PIN_LEFT_SERVO)SetBit(TCCR1A,COM1B1);
}


void servo_testing(){
	servo_enable(PIN_RIGHT_SERVO);
	servo_enable(PIN_LEFT_SERVO);
	servo_set_angle(PIN_RIGHT_SERVO,200);
	servo_set_angle(PIN_LEFT_SERVO,500);
	_delay_ms(4000);
	servo_disable(PIN_RIGHT_SERVO);
	_delay_ms(100);
	servo_enable(PIN_RIGHT_SERVO);
	servo_set_angle(PIN_RIGHT_SERVO,0);
	servo_set_angle(PIN_LEFT_SERVO,0);
	_delay_ms(4000);
}

void servo_debug(){
	//servo_enable(PIN_RIGHT_SERVO);
	//servo_set_angle(PIN_RIGHT_SERVO,0);
	//OCR1A = 0;
	//servo_enable(PIN_LEFT_SERVO);
	//servo_set_angle(PIN_LEFT_SERVO,0);
	
}