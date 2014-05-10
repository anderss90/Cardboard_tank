#ifndef NEXA
#define NEXA

#include "common_variables.h"

void nexa_init();
void nexa_pair();
void nexa_on();
void nexa_off();

void nexa_send_cmd(char* cmd, uint8_t msg_size);

#endif //NEXA
