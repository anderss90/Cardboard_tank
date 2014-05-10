
#include "common_variables.h"
#include "radio.h"
#include "radio_protocol.h"

#define RX_GND_PIN PD0
#define RX_DTA_PIN PD0
#define RX_VCC_PIN PD3

 void rf_init(){
	 // Set up interrupts
	 PCMSK2 |= (1<<PCINT16);
	 PCICR |= (1<<PCIE2);
	 
	 // Set up timer, do not start it
	 TCCR1B |= (1 << WGM12); //CTC mode
	 TIMSK1 |= (1<<OCIE1A);
	 state = 0;
	 rawdata = 0;
	 data = 0;
	 dataready = 0;
	 ministate = -1;
	 // Set up 433MHz RX
	 DDRD &= ~(1<<RX_DTA_PIN);
	 
	 //setting GND and VCC output (not always needed)
	 //DDRD |= (1 << RX_GND_PIN) | (1 << RX_VCC_PIN);  
	 //setting VVC 5v and GND 0V
	 //PORTD &= ~(1 << RX_GND_PIN); // set to 0V
	 //PORTD |= (1 << RX_VCC_PIN);    // set to 5V
	 
	 //enabling interrupts
	 sei();
 }
 
 
   //reset state to initial  
  void inline resetstate()
  {
	  unsigned char sreg;
	  state=0;
	  ministate=-1;
	  data = 0;
	  rawdata = 0;
	  package_reset();
	  TCCR1B &= ~(1 << CS11); //stop timer 1
	  sreg = SREG; // save global interrupt flag
	  cli();
	  TCNT1 = 0;
	  SREG = sreg; // restore interrrupt flag
  }
  // start timer
  void inline starttimer(int v)
  {
	  unsigned char sreg;
	  sreg = SREG; // save global interrupt flag
	  cli();
	  TCNT1 = 0;
	  OCR1A = v;
	  SREG = sreg; // restore interrrupt flag
	  TCCR1B |= (1 << CS11); //prescale 8
  }
  // This interrupt is called when the 433 MHz RX pin changes state
  ISR(PCINT2_vect) 
  {
	  
	  char transition;
	  // determine the state change direction, 0->1 or 1->0
	  if (PIND & (1<<RX_DTA_PIN))transition = T01;
	  else transition = T10;
	  //state 0: should time out, we need 9.3 ms silence, otherwise try again
	  if (state == 0)
	  {
		  starttimer(kPulseTrainDelay-100);
		  return;
	  }
	  // state 1: we had a 9.3 ms delay, now we are recieving the init pulse
	  // start the pulsewidth timer
	  if ((state==1) && (transition == T01))
	  {
		  starttimer(kMaxPulseWidth);
		  return;
	  }
	  if ((state==1) && (transition == T10))
	  {
		  if (TCNT1<kMinPulseWidth)
		  {
			  resetstate();
			  return;
		  }
		  else // pulse OK, too long and it will time out in the timer part
		  {
			  state = 2;
			  starttimer(kMaxInitDelay);
			  return;
		  }
	  }
	  
	  // state 2: measure the init delay
	  if (state == 2)// && (transition == T01))
	  {
		  if (transition == T10)
		  {
			  resetstate();
			  return;
		  }
		  if (TCNT1<kMinInitDelay) // to short
		  {
			  resetstate();
			  return;
		  }
		  else // delay OK, too long and it times out
		  {
			  starttimer(kMaxPulseWidth);
			  rawdata = 0;
			  state = 3;
			  return;
		  }
	  }
	  
	  //state 3: check pulsewidth in data transmission
	  if ((state == 3))// && (transition==T10))
	  {
		  if (TCNT1<kMinPulseWidth)
		  {
			  resetstate();
			  return;
		  }
		  else // pulse OK, too long and it will time out from the timer
		  {
			  starttimer(kMaxDataDelay);
			  state = 4;
			  return;
		  }
	  }
	  //state 4: read data, '0' or '1'
	  
	  if (state == 4)
	  {
		  int t = TCNT1;
		  //observing 1310 or 320
		  if (t > kZeroDelay) // we read '1'
		  {
			  if (ministate==1) // error, two '1' in a row
			  {
				  resetstate();
				  return;
			  }
			  else if (ministate==-1) // OK, next bit should be '0'
			  {
				  ministate = 1;
			  }
			  else if (ministate==0) // OK, bit pair completed
			  {
				  ministate = -1;
				  rawdata = (rawdata<<1);
				  package_append(0);
				  
				  // no need to add '0'
			  }
		  }
		  else // we read '0'
		  {
			  if (ministate==0) // error, two '0' in a row
			  {
				  resetstate();
				  return;
			  }
			  else if (ministate==-1) // OK, next bit should be '1'
			  {
				  ministate = 0;
			  }
			  else if (ministate==1) // OK, bit pair completed
			  {
				  ministate = -1;
				  rawdata = (rawdata<<1);
				  rawdata +=1;
				  package_append(1);
			  }
		  }
		  state = 3;
		  starttimer(kMaxPulseWidth);
		  return;
	  }
  }
  
  ISR(TIMER1_COMPA_vect)
  {
	  if (state==0)
	  {
		  state = 1;
		  TCCR0B &= ~(1 << CS01); //stop the timer
		  return;
	  }
	  // pulsewidth/delay were to long
	  if ((state == 1) || (state == 2) || (state == 3))
	  {
		  resetstate();
		  return;
	  }
	  // end of data burst, wait for next burst
	  if (state==4)
	  {
		  data = rawdata;
		  rawdata = 0;
		  dataready=1;
		  //process_data_nexa();
		  process_data_new();
		  //timeout_start();
		  starttimer(kPulseTrainDelay>>1);
		  state = 0;
	  }
  }
