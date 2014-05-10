/*
 * radio_protocol.c
 *
 * Created: 06.05.2014 18:33:08
 *  Author: Anders
 */ 
#include "common_variables.h"
#include "radio_protocol.h"


//global variables
int bit_counter=0;
char* msg_array;
char* id_array;
char* received_checksum;
char* constructed_checksum;
char* package;
char* tank_id;
char* my_id;

void led_toggle(){
	LED_OFF;
	_delay_ms(500);
	LED_ON;
	_delay_ms(500);
}

void print_string(char* string,uint8_t length){
	int i=0;
	for (i=0;i<length;i++){
		
		if (string[i]==0){
			uart_putchar('0');
		}
		else if (string[i]==1){
			uart_putchar('1');
		}
		
		else uart_putchar(string[i]);
		
	}
	uart_putchar('\n');
}

void package_append(char bit){
	package[bit_counter]=bit;
	bit_counter++;
}
void package_reset(){
	int i=0;
	for (i=0;i>RF_PACKAGE_LENGTH;i++){
		package[i]=0;
	}
	bit_counter=0;
}


char* extract_id(char* package,char* id_array){
	int i=0;
	for (i=0;i<RF_ID_LENGTH;i++){
		id_array[i]=package[i];
	}
	return id_array;
}

char* extract_msg(char*package,char*msg_array){
	int i=0;
	for (i=0;i<RF_MSG_LENGTH;i++){
		msg_array[i]=package[i+RF_ID_LENGTH];
	}
	return msg_array;
}

char* extract_checksum(char*package,char*received_checksum){
	int i=0;
	for (i=0;i<RF_CHECKSUM_LENGTH;i++){
		received_checksum[i]=package[i+RF_ID_LENGTH+RF_MSG_LENGTH];
	}
	return received_checksum;
}

char* construct_checksum(char*constructed_checksum,char* msg_array,char*id_array){
	int i=0;
	for (i=0;i<RF_CHECKSUM_LENGTH;i++){
		constructed_checksum[i]=(char)!(msg_array[i]==id_array[i]);
	}
	return constructed_checksum;
}
void process_data_new(){
	{
		cli();
		id_array=extract_id(package,id_array);
		msg_array=extract_msg(package,msg_array);
		received_checksum=extract_checksum(package,received_checksum);
		constructed_checksum=construct_checksum(constructed_checksum,msg_array,id_array);
		
		print_string("package",7);
		print_string(package,RF_PACKAGE_LENGTH);
		print_string("id",2);
		print_string(id_array,RF_ID_LENGTH);
		print_string("msg",3);
		print_string(msg_array,RF_MSG_LENGTH);
		print_string("c_checksum\n",10);
		print_string(constructed_checksum,RF_CHECKSUM_LENGTH);
		print_string("r_checksum",10);
		print_string(received_checksum,RF_CHECKSUM_LENGTH);
		print_string("\n\n\n",3);
		
		dataready = 0;
		package_reset();
		sei();
	}
}


void radio_protocol_init(){
	msg_array = malloc(sizeof(char)*RF_MSG_LENGTH);
	id_array = malloc(sizeof(char)*RF_ID_LENGTH);
	received_checksum = malloc(sizeof(char)*RF_CHECKSUM_LENGTH);
	constructed_checksum = malloc(sizeof(char)*RF_CHECKSUM_LENGTH);
	package = malloc(sizeof(char)*RF_PACKAGE_LENGTH);
	tank_id = malloc(sizeof(char)*RF_ID_LENGTH);
	my_id = malloc(sizeof(char)*RF_ID_LENGTH);
	tank_id[0]=0;
	tank_id[1]=1;
	tank_id[2]=0;
	tank_id[3]=1;
	tank_id[4]=0;
	tank_id[5]=1;
	tank_id[6]=0;
	tank_id[7]=1;
	my_id=tank_id;
}