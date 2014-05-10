/*
 * radio_protocol.c
 *
 * Created: 06.05.2014 18:33:08
 *  Author: Anders
 */ 
#include "common_variables.h"
#include "motor.h"
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

void debug_by_running_tracks(){
	motor_forward();
	_delay_ms(1000);
	motor_stop();
	_delay_ms(1000);
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

void process_button_info(char* msg_array){
	
	
	
	//combination of buttons
	if (msg_array[LEFT_PAD_UP] && msg_array[LEFT_PAD_LEFT]) motor_turn_left();
	else if (msg_array[LEFT_PAD_UP] && msg_array[LEFT_PAD_RIGHT]) motor_turn_right();
	else if (msg_array[LEFT_PAD_DOWN] && msg_array[LEFT_PAD_LEFT]) motor_backward_left();
	else if (msg_array[LEFT_PAD_DOWN] && msg_array[LEFT_PAD_RIGHT]) motor_backward_right();
	
	//forward/backward
	else if (msg_array[LEFT_PAD_UP]) motor_forward();
	else if (msg_array[LEFT_PAD_DOWN])motor_backward();
	
	//spinning
	else if (msg_array[LEFT_PAD_LEFT])motor_spin_left();
	else if (msg_array[LEFT_PAD_RIGHT])motor_spin_right();
	//else stop
	else motor_stop();
	
	
	
	//turret
	if (msg_array[RIGHT_PAD_LEFT]) turret_turn(COUNTER_CLOCKWISE);
	else if (msg_array[RIGHT_PAD_RIGHT]) turret_turn(CLOCKWISE);
	else turret_turn(STOP);
}



void process_data_new(){
	{
		cli();
		id_array=extract_id(package,id_array);
		msg_array=extract_msg(package,msg_array);
		received_checksum=extract_checksum(package,received_checksum);
		constructed_checksum=construct_checksum(constructed_checksum,msg_array,id_array);
		
		if (package==NULL || id_array==NULL || msg_array==NULL || received_checksum==NULL){
			dataready = 0;
			package_reset();
			sei();
			return;
		}
		
		//checking checksum
		int i=0;
		for (i=0;i<RF_CHECKSUM_LENGTH;i++){
			if (received_checksum[i]!=constructed_checksum[i]){
				 //debug_by_running_tracks();
				 dataready = 0;
				 package_reset();
				 sei();
				 return;
			}
		}
		
		//checksum OK, checking id
		for (i=0;i<RF_ID_LENGTH;i++){
			if (id_array[i]!=my_id[i]) {
				//debug_by_running_tracks();
				dataready = 0;
				package_reset();
				sei();
				return;
			}
		}
		//debug_by_running_tracks();
		
		//ID OK, processing msg received
		process_button_info(msg_array);
		
		
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

void process_data_nexa(){
	{
		cli();
		
		char buff[8];
		uint8_t tmp = data &0x000000FF;
		sprintf(buff,"%04X", (data>>(16+6))&0x0000FFFF);
		sprintf(buff,"%04X", (data>>6)&0xFFFF);
		
		// ON or OFF
		if (tmp & 0x10)  //ON
		{
			if ((tmp & 0x0F) == 0x00) motor_forward();
			if ((tmp & 0x0F) == 0x01) motor_spin_left();
			if ((tmp & 0x0F) == 0x02){
				turret_turn(COUNTER_CLOCKWISE);
				//_delay_ms(50);
			}
			//blink_led(debug_led2);
		}
		else
		{
			if ((tmp & 0x0F) == 0x00) {
				//motor_backward();
				motor_stop();
				//_delay_ms(50);
			}
			if ((tmp & 0x0F) == 0x01){
				//motor_spin_right();
				motor_stop();
				//_delay_ms(50);
			}
			
			if ((tmp & 0x0F) == 0x02){
				turret_turn(STOP);
				//_delay_ms(50);
			}
			turret_turn(STOP);
			motor_stop();
			//blink_led(debug_led1);
			
		}
		sei();
		dataready = 0;
		cli();
		sei();
	}
}