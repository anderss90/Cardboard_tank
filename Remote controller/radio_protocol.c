/*
 * radio_protocol.c
 *
 * Created: 02.05.2014 12:24:55
 *  Author: Anders
 */ 



#include "common_variables.h"

int button_table[12]=
	{RIGHT_PAD_UP,RIGHT_PAD_DOWN,RIGHT_PAD_LEFT,RIGHT_PAD_RIGHT,
	LEFT_PAD_UP,LEFT_PAD_DOWN,LEFT_PAD_LEFT,LEFT_PAD_RIGHT,
	OPT_BUTTON_LEFT,OPT_BUTTON_RIGHT,0,0};
	
char* msg_array;
char* id_array;
char* checksum;
char* package;
char* tank_id;



char* construct_button_array(char* msg_array){
	int i=0;
	for (i=0;i<n_buttons;i++){
		if (i==0 || i==1 || i==2 || i==3 || i==8 || i==9){
			msg_array[i]=!(char)CheckBit(PINC,button_table[i]);
		}
		else if (i==4 || i==6 || i==7){
			msg_array[i]=!(char)CheckBit(PIND,button_table[i]);
		}
		else if (i==5){
			msg_array[i]=!(char)CheckBit(PINB,button_table[i]);
		}
		
	}
	for (i=n_buttons;i<RF_MSG_LENGTH;i++){
		msg_array[i]=(char)0;
	}
	return msg_array;
}

char* construct_checksum(char*checksum,char* msg_array,char*id_array){
	int i=0;
	for (i=0;i<RF_CHECKSUM_LENGTH;i++){
		checksum[i]=(char)!(msg_array[i]==id_array[i]);
	}
	return checksum;
}

char* construct_package(char* package,char* id_array,char* msg_array,char *checksum){
	int i=0;
	int j=0;
	for (i=0;i<RF_ID_LENGTH;i++){
		package[i]=(char)id_array[i];
	}
	i=RF_ID_LENGTH;
	for (j=0;j<RF_MSG_LENGTH;j++){
		package[i]=(char)msg_array[j];
		i++;
	}
	i=RF_ID_LENGTH+RF_MSG_LENGTH;
	for (j=0;j<RF_CHECKSUM_LENGTH;j++){
		package[i]=(char)checksum[j];
		i++;
	}
	return package;
}

void send_commands(){
	msg_array=construct_button_array(msg_array);
	id_array=tank_id;
	checksum=construct_checksum(checksum,msg_array,id_array);
	package=construct_package(package,id_array,msg_array,checksum);
	nexa_send_cmd(package,RF_PACKAGE_LENGTH);
}

void radio_protocol_init(){
	msg_array = malloc(sizeof(char)*RF_MSG_LENGTH);
	id_array = malloc(sizeof(char)*RF_ID_LENGTH);
	checksum = malloc(sizeof(char)*RF_CHECKSUM_LENGTH);
	package = malloc(sizeof(char)*RF_PACKAGE_LENGTH);
	tank_id = malloc(sizeof(char)*RF_ID_LENGTH);
	tank_id[0]=0;
	tank_id[1]=1;
	tank_id[2]=0;
	tank_id[3]=1;
	tank_id[4]=0;
	tank_id[5]=1;
	tank_id[6]=0;
	tank_id[7]=1;
}