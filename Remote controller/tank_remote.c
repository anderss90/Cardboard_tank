
#include "common_variables.h"
#include "nexa.h"

void buttons_init(){
	//setting inputs
	ClrBit(DDRC,RIGHT_PAD_UP);
	ClrBit(DDRC,RIGHT_PAD_DOWN);
	ClrBit(DDRC,RIGHT_PAD_LEFT);
	ClrBit(DDRC,RIGHT_PAD_RIGHT);
	
	ClrBit(DDRD,LEFT_PAD_UP);
	ClrBit(DDRB,LEFT_PAD_DOWN);
	ClrBit(DDRD,LEFT_PAD_LEFT);
	ClrBit(DDRD,LEFT_PAD_RIGHT);
	
	ClrBit(DDRC,OPT_BUTTON_LEFT);
	ClrBit(DDRC,OPT_BUTTON_RIGHT);
	
	//setting pull-up
	SetBit(PORTC,RIGHT_PAD_UP);
	SetBit(PORTC,RIGHT_PAD_DOWN);
	SetBit(PORTC,RIGHT_PAD_LEFT);
	SetBit(PORTC,RIGHT_PAD_RIGHT);
	
	SetBit(PORTD,LEFT_PAD_UP);
	SetBit(PORTB,LEFT_PAD_DOWN);
	SetBit(PORTD,LEFT_PAD_LEFT);
	SetBit(PORTD,LEFT_PAD_RIGHT);
	
	SetBit(PORTC,OPT_BUTTON_LEFT);
	SetBit(PORTC,OPT_BUTTON_RIGHT);
	
	
}

void led_init(){
	//Setting outputs
	SetBit(DDRB,LED1);
	SetBit(DDRB,LED2);
	SetBit(DDRB,LED3);
	SetBit(DDRB,LED4);
	
	//turning leds off
	SetBit(PORTB,LED1);
	SetBit(PORTB,LED2);
	SetBit(PORTB,LED3);
	SetBit(PORTB,LED4);
	
	//using led4 as pwr led
	ClrBit(PORTB,LED4);
}

void button_and_led_testing(){
	if (!CheckBit(PINC,OPT_BUTTON_LEFT)){
		ClrBit(PORTB,LED1);
		//_delay_ms(1000);
		nexa_1_on();
		
	}
	else SetBit(PORTB,LED1);
	
	if (!CheckBit(PINC,OPT_BUTTON_RIGHT)){
		ClrBit(PORTB,LED2);
		nexa_1_off();
	}
	else SetBit(PORTB,LED2);
	
	if (!CheckBit(PIND,LEFT_PAD_RIGHT)){
			ClrBit(PORTB,LED2);
			nexa_2_on();
			
	}
	else SetBit(PORTB,LED2);
	if (!CheckBit(PIND,LEFT_PAD_LEFT)){
		ClrBit(PORTB,LED1);
		nexa_2_off();
		
	}
	else SetBit(PORTB,LED1);
	
	if (!CheckBit(PIND,LEFT_PAD_UP)){
		ClrBit(PORTB,LED1);
		nexa_3_on();
		
	}
	else SetBit(PORTD,LED1);
	if (!CheckBit(PINB,LEFT_PAD_DOWN)){
		ClrBit(PORTB,LED2);
		nexa_3_off();
		
	}
	else SetBit(PORTB,LED2);
	
}




int main(void)
{
    nexa_init();
	led_init();
	buttons_init();
	radio_protocol_init();
    while(1)
    {
		
	    //button_and_led_testing();
		send_commands();
		_delay_ms(50);
    }

    return 0;
}