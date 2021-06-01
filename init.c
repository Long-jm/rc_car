
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



