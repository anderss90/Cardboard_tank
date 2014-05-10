#define SetBit(x,y) (x|=(1<<y))
#define ClrBit(x,y) (x&=~(1<<y))
#define ToggleBit(x,y) (x^=(1<<y))
#define CheckBit(adr,bit) (adr & (1<<bit))


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef F_CPU
//define cpu clock speed if not defined
#define F_CPU 8000000
#endif
//set desired baud rate
#define BAUDRATE 1200
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)
//define receive parameters
#define SYNC 0XAA// synchro signal
#define RADDR 0x44
#define LEDON 0x11//LED on command
#define LEDOFF 0x22//LED off command

void USART_Init()
{
	sei();
	//Set baud rate
	UBRR0L=(uint8_t)UBRRVAL;		//low byte
	UBRR0H=(UBRRVAL>>8);	//high byte
	//Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
	UCSR0C=(0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|
	(0<<USBS0)|(0<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00);
	//Enable Transmitter and Receiver and Interrupt on receive complete
	UCSR0B=(1<<RXEN0)|(1<<RXCIE0);//|(1<<TXEN);
	//enable global interrupts
	

}
uint8_t USART_vReceiveByte(void)
{
	// Wait until a byte has been received
	while((UCSR0A & (1<<RXC0)) == 0);
	// Return received data
	return UDR0;
}

void rf_Init()
{
	//enable global interrupts
	USART_Init();
}

ISR(USART_RX_vect){
	cli();
	//blink_led(debug_led1);
	//define variables
	uint8_t sync,raddress, data, chk;//transmitter address
	
	//if (USART_vReceiveByte()!=SYNC) return;
	while(USART_vReceiveByte()==SYNC){
		//wait until sync field is done
	}
	//receive destination address
	raddress=USART_vReceiveByte();
	//receive data
	data=USART_vReceiveByte();
	//receive checksum
	chk=USART_vReceiveByte();
	//compare received checksum with calculated
	if(chk==(raddress+data))//if match perform operations
	{
		//if transmitter address match
		if(raddress==RADDR)
		{
			if(data==LEDON)
			{
				blink_led(debug_led1);
			}
			else if(data==LEDOFF)
			{
				blink_led(debug_led1);
			}
			else
			{
				//blink led as error
				blink_led(debug_led2);
			}
		}
	}
	else
	{
		//blink led as error
		blink_led(debug_led2);
	}
	sei();
}