/*
 * radio_protocol.h
 *
 * Created: 06.05.2014 17:49:07
 *  Author: Anders
 */ 


#ifndef RADIO_PROTOCOL_H_
#define RADIO_PROTOCOL_H_

char* construct_button_array(char* msg_array);
char* construct_checksum(char*checksum,char* msg_array,char*id_array);
char* construct_package(char* package,char* id_array,char* msg_array,char *checksum);
void send_commands();





#endif /* RADIO_PROTOCOL_H_ */