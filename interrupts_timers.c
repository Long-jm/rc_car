//-----------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include "msp430.h"
#include <string.h>

extern volatile unsigned char update_display;
volatile int displayCount;
volatile int debounced;
unsigned int lineTimer;
volatile unsigned int Time_Sequence;
volatile char one_time;
extern volatile unsigned char display_changed;
extern char display_line[NUM_LINES][NUM_CHARS];
extern unsigned short int pressed;
extern volatile unsigned short int pressed2;
unsigned int serialCount = RESET;
unsigned int cmdTimer = RESET;

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  //---------------------------------------------------------------------------
  // TimerB0 0 Interrupt handler 
  //---------------------------------------------------------------------------
  
  displayCount++;
  Time_Sequence++;
  lineTimer++;
  serialCount++;
  cmdTimer++;

  one_time = YES;
  
  switch(displayCount) {
    case  UPDATE_TIME:
      update_display = YES;
      displayCount = RESET;
  } 
  
  TB0CCR0 += TB0CCR0_INTERVAL;          // Add Offset to TBCCR0 
  //---------------------------------------------------------------------------
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //---------------------------------------------------------------------------
  // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler 
  //---------------------------------------------------------------------------
  
  debounced++;
  
  switch(__even_in_range(TB0IV,PICK_REGISTER)){ 
  case  NO: break;                   // No interrupt 
  case  CCR1:                        // CCR1
    
    if (debounced == DEBOUNCETIME) {
      
      P4IFG &= ~SW1;   
      P4IE  |=  SW1;
      
      P2IFG &= ~SW2;               // IFG SW2 cleared  
      P2IE  |=  SW2;
      
      pressed++;
      
      TB0CCTL1 &= ~CCIE;
      debounced = RESET;
    } 
    TB0CCR1 += TB0CCR1_INTERVAL;     // Add Offset to TBCCR1
    break; 
  case  CCR2:                        // CCR2 
    
    
    TB0CCR2 += TB0CCR2_INTERVAL;     // Add Offset to TBCCR2 
    break; 
  case CCR_OVERFLOW:                 // overflow disabled
    break; 
  default: break; 
  } 
  //---------------------------------------------------------------------------
}