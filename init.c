//------------------------------------------------------------------------------
// 
// 
//
//Each file will contain a comment header that will contain the date, your name, and the compiler 
// revision used to build the file. The comment header must also identify any global variables that 
//are defined as part of the file as well as a two to three line description of the file and its contents. 
//-----------------------------------------------------------------------------


// Each function will have its own comment header, which will contain the same 
// information as in the file header, but will also contain the globals used or 
// changed, passed variables, local variables and returned values. These 
// function headers should identify the various options for each port pin and 
// what can be configured [alternate options]. The function header should list 
// all ports being configured by the function, and what they relate to, whether 
// it is General I/O, the switches, etc.

#include "macros.h"
#include "functions.h"
#include "msp430.h"

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern char display_line[NUM_LINES][NUM_CHARS];
extern char *display[NUM_LINES];



void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=RESET;i<NUM_CHARS;i++){
    display_line[LINE_1][i] = RESET;
    display_line[LINE_2][i] = RESET;
    display_line[LINE_3][i] = RESET;
    display_line[LINE_4][i] = RESET;
  }
  display_line[LINE_1][CHAR_END] = RESET;
  display_line[LINE_2][CHAR_END] = RESET;
  display_line[LINE_3][CHAR_END] = RESET;
  display_line[LINE_4][CHAR_END] = RESET;

  display[LINE_1] = &display_line[LINE_1][CHAR_1ST];
  display[LINE_2] = &display_line[LINE_2][CHAR_1ST];
  display[LINE_3] = &display_line[LINE_3][CHAR_1ST];
  display[LINE_4] = &display_line[LINE_4][CHAR_1ST];
  update_display = RESET;
  update_display_count = RESET;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}



