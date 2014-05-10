/*
 * radio_protocol.h
 *
 * Created: 06.05.2014 18:33:19
 *  Author: Anders
 */ 


#ifndef RADIO_PROTOCOL_H_
#define RADIO_PROTOCOL_H_

#define RF_MSG_LENGTH 12
#define RF_ID_LENGTH 8
#define RF_CHECKSUM_LENGTH 8
#define n_buttons 10
#define RF_PACKAGE_LENGTH RF_ID_LENGTH+RF_MSG_LENGTH+RF_CHECKSUM_LENGTH

enum BUTTONS{RIGHT_PAD_UP,RIGHT_PAD_DOWN,RIGHT_PAD_LEFT,RIGHT_PAD_RIGHT,
	LEFT_PAD_UP,LEFT_PAD_DOWN,LEFT_PAD_LEFT,LEFT_PAD_RIGHT,
OPT_BUTTON_LEFT,OPT_BUTTON_RIGHT,UNUSED1,UNUSED2};



void package_append(char bit);
void package_reset();
char* extract_id();
char* extract_msg();
char* extract_checksum();
char* construct_checksum(char*checksum,char* msg,char*id);
void process_data_new();

void radio_protocol_init();

#endif /* RADIO_PROTOCOL_H_ */