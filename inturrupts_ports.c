//------------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include "msp430.h"
#include <string.h>

extern volatile unsigned char display_changed;
extern char display_line[NUM_LINES][NUM_CHARS];
extern char *display[NUM_LINES];
extern unsigned int start_moving;
extern unsigned int lineTimer;
unsigned short int baudRate = RESET;
extern volatile int debounced;
extern volatile int received;
extern unsigned int waitOver;
extern volatile unsigned short int pressed2;
extern volatile unsigned short int goAhead;

#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){ 
  // Switch 1 
  if (P4IFG & SW1) { 
    P4IFG &= ~SW1;               // IFG SW1 cleared 
    P4IE  &= ~SW1;
    P2IFG &= ~SW2;               // IFG SW2 cleared  
    P2IE  &= ~SW2;
    
    //baudRate = BAUD115;                 // 115 baud rate
    //Init_Serial_UCA0();
    //Init_Serial_UCA1();
    debounced = RESET;
    waitOver = YES;
    goAhead = YES;
    
    TB0CCR1 = TB0R + TB0CCR1_INTERVAL;    // CCR1
    TB0CCTL1 |= CCIE;              // CCR1 enable interrupt
  }  
}

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  // Switch 2 
  if (P2IFG & SW2) { 
    P2IFG &= ~SW2;               // IFG SW2 cleared  
    P2IE  &= ~SW2;
    P4IFG &= ~SW1;               // IFG SW1 cleared 
    P4IE  &= ~SW1;
    
    if (baudRate == BAUD460) {                // 460 baud rate
      baudRate = BAUD115;
    }
    else {
      baudRate = BAUD460;
    }
    pressed2 = YES;
    //Init_Serial_UCA0();
    Init_Serial_UCA1();
    debounced = RESET;
    waitOver = YES;
    
    TB0CCR1 = TB0R + TB0CCR1_INTERVAL;    // CCR1
    TB0CCTL1 |= CCIE;              // CCR1 enable interrupt
  }
}