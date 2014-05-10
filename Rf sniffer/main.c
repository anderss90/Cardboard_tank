




#include "common_variables.h"

void led_init(){
	DDRB	|= (1<<PORTB5);
}



void test_uart_connection(){
	char i=0;
	for (i=0;i<120;i++){
		uart_putchar('s');
	}
}



int main (void)
{
	board_init();
	uart_init();
	led_init();
	
	rf_init();
	radio_protocol_init();
	while(1){
		sei();
		LED_ON;
		//test_uart_connection();
		if (dataready==1){
			led_toggle();
			process_data_new();
		}
		//led_toggle();
		//uart_putchar();
		
	}
	// Insert application code here, after the board has been initialized.
}
