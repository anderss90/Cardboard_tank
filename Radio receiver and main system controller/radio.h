
#ifndef RADIO_H_
#define RADIO_H_

#define T01 1
#define T10 0
// shortest and longest accepted pulsewidth
#define kMinPulseWidth 140
#define kMaxPulseWidth 300 //210
// Minimum time between two pulsetrains
#define kPulseTrainDelay 9700
// Minimum time between init pulse and data stream
#define kMinInitDelay 2200 //2600
#define kMaxInitDelay 2800
// Maximum time between two data pulses
#define kMaxDataDelay 1450 //1363
// A delay longer than reads as a '1'
#define kZeroDelay 687 //346
// The data arrives in pairs, '01' or '10', ministate
// keeps track of these pairs
//    -1    undefined, waiting for '0' or '1'
//     0    '0' read, waiting for '1'
//     1    '1'    read, waiting for '0'
volatile int8_t ministate;
//#state
//# 0 - wait for 9.3 ms (kPulseTrainDelay) silence
//# 1 - wait for and measure init pulse width
//# 2 - measure init delay
//# 3 - check data pulse width and start measuring data delay
//# 4 - read data delay and determine '0', '1'. n time out store data



volatile uint8_t state;
volatile uint32_t rawdata, data;
volatile uint8_t dataready;

//functions
 void rf_init();
 void inline resetstate();
 void inline starttimer(int v);
 ISR(TIMER0_COMPA_vect);
 ISR(PCINT2_vect);
 
#endif /* RADIO_H_ */