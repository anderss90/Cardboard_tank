/*
 * _433_rx.h
 *
 * Created: 19.04.2014 16:06:26
 *  Author: Anders
 */ 


#ifndef A433_RX_H
#define A433_RX_H

#define SYNC 0XAA// synchro signal
#define RADDR 0x44
#define LEDON 0x11//LED on command
#define LEDOFF 0x22//LED off command


void rf_Init();
uint8_t USART_vReceiveByte();




#endif /* A433_RX_H */