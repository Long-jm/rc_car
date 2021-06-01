//------------------------------------------------------------------------------
//
//  Description:
//  Jonathan Long
//
//------------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include "msp430.h"
#include <string.h>

extern char display_line[NUM_LINES][NUM_CHARS];
extern volatile unsigned char display_changed;
extern int ADC_Left_Detect = RESET;
extern int ADC_Right_Detect = RESET;
int ADC_Channel;
int ADC_Thumb;
extern char bcdVal[STRLEN+1];

#pragma vector=ADC_VECTOR 
__interrupt void ADC_ISR(void){   
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){     
  case ADCIV_NONE:       
    break;     
  case ADCIV_ADCOVIFG:   // When a conversion result is written to the ADCMEM0                             
    // before its previous conversion result was read.       
    break;     
  case ADCIV_ADCTOVIFG:   // ADC conversion-time overflow       
    break;     
  case ADCIV_ADCHIIFG:    // Window comparator interrupt flags       
    break;     
  case ADCIV_ADCLOIFG:    // Window comparator interrupt flag       
    break;     
  case ADCIV_ADCINIFG:    // Window comparator interrupt flag       
    break;     
  case ADCIV_ADCIFG:      // ADCMEM0 memory register with the conversion result       
    ADCCTL0 &= ~ADCENC;                         // Disable ENC bit.    
    switch (ADC_Channel++){       
    case CHANA2:                                // Channel A2 Interrupt         
      ADCMCTL0 &= ~ADCINCH_2;                 // Disable Last channel A2         
      ADCMCTL0 |= ADCINCH_3;                  // Enable Next channel A3         
      ADC_Left_Detect = ADCMEM0;              // Move result into Global         
      ADC_Left_Detect = ADC_Left_Detect >> 2; // Divide the result by 4         
      HEXtoBCD(ADC_Left_Detect);              // Convert result to String         
      adc_line4(bcdVal);                           // Place String in Display          
      break;       
    case CHANA3:         
      ADCMCTL0 &= ~ADCINCH_3;                 // Disable Last channel A2         
      ADCMCTL0 |= ADCINCH_5;                  // Enable Next channel A3         
      ADC_Right_Detect = ADCMEM0;              // Move result into Global         
      ADC_Right_Detect = ADC_Right_Detect >> 2; // Divide the result by 4         
      HEXtoBCD(ADC_Right_Detect);              // Convert result to String         
      adc_line3(bcdVal);                           // Place String in Display              
      break;       
    case CHANA5:  
      ADCMCTL0 &= ~ADCINCH_5;                 // Disable Last channel A2         
      ADCMCTL0 |= ADCINCH_2;                  // Enable Next channel A3         
      ADC_Thumb = ADCMEM0;              // Move result into Global         
      ADC_Thumb = ADC_Thumb >> 2;       // Divide the result by 4         
      //HEXtoBCD(ADC_Thumb);              // Convert result to String         
      //adc_line2(bcdVal);                           // Place String in Display          
      ADC_Channel=RESET;         
      break;       
    default:         
      break;     
    }     
    ADCCTL0 |= ADCENC;                // Enable Conversions     
    ADCCTL0 |= ADCSC;                 // Start next sample           
  default:       
    break;   
  } 
}

void HEXtoBCD(int hexVal) {
  int i;
  int thous=RESET, hunds=RESET, tens=RESET, ones=RESET;
  for (i=RESET; i<TENS; i++) {
    if (hexVal - THOU > RESET) {
      hexVal -= THOU;
      thous++;
    } else {break;}
  }
  for (i=RESET; i<TENS; i++) {
    if (hexVal - HUND > RESET) {
      hexVal -= HUND;
      hunds++;
    } else {break;}
  }
  for (i=RESET; i<TENS; i++) {
    if (hexVal - TENS > RESET) {
      hexVal -= TENS;
      tens++;
    } else {break;}
  }
  for (i=RESET; i<TENS; i++) {
    if (hexVal - ONES > RESET) {
      hexVal -= ONES;
      ones++;
    } else {break;}
  }
  bcdVal[THOUPLACE] = thous + ASCIIOFFSET;
  bcdVal[HUNDPLACE] = hunds + ASCIIOFFSET;
  bcdVal[TENSPLACE] = tens + ASCIIOFFSET;
  bcdVal[ONESPLACE] = ones + ASCIIOFFSET;
  bcdVal[SPACE1] = ' ';
  bcdVal[SPACE2] = ' ';
  bcdVal[SPACE3] = ' ';
  bcdVal[SPACE4] = ' ';
  bcdVal[SPACE5] = ' ';
  bcdVal[SPACE6] = ' ';
  bcdVal[STRNULL] = RESET;
}
     
void adc_line2(char* bcdVal) {
  strcpy(display_line[LINE_2], bcdVal);
  update_string(display_line[LINE_2], LINE_2);
  display_changed = YES;
}

void adc_line3(char* bcdVal) {
  strcpy(display_line[LINE_3], bcdVal);
  update_string(display_line[LINE_3], LINE_3);
  display_changed = YES;
}

void adc_line4(char* bcdVal) {
  strcpy(display_line[LINE_4], bcdVal);
  update_string(display_line[LINE_4], LINE_4);
  display_changed = YES;
}