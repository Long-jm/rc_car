//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//  Jonathan Long
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

// Function Prototypes
void main(void);


// Global Variables
volatile char slow_input_down;
extern char display_line[NUM_LINES][NUM_CHARS];
extern char *display[NUM_LINES];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
char change;

char bcdVal[STRLEN+1];
unsigned int timerVal;
extern unsigned int lineTimer;
unsigned int start_moving = RESET;
unsigned int follow = RESET;
unsigned int startSpeed = YES;
unsigned int linePosition;
short int detected = RESET;
extern int ADC_Left_Detect;
extern int ADC_Right_Detect;
extern short int wait = RESET;

extern unsigned short int pressed = RESET;
extern volatile unsigned short int pressed2 = RESET;
extern volatile unsigned short int goAhead = RESET;
extern int UCA0_index;
extern int UCA1_index;
unsigned short int splash = YES;
extern unsigned int serialCount;
extern unsigned short int baudRate;
unsigned int waitOver = RESET;
extern volatile char USB_Char_Rx1[SMALL_RING_SIZE];
char message[NUM_CHARS];
extern volatile unsigned int usb_rx_ring_wr1;

short unsigned int stop = RESET;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE]; 
char Processbuff[PROCESS_SIZE];
unsigned int pb_wr;
extern short unsigned int checkIP;
extern short unsigned int eqYes;
extern char ip_1[STRLEN];
extern char ip_2[STRLEN];
char transmit_array[TRANSMIT_SIZE];
const char nstat[] = {
  'A','T','+','N','S','T','A','T','=','?','\r','\n','\0'
};
const char nstcp[] = {
  'A','T','+','N','S','T','C','P','=','5','5','0','0','0',',','1','\r','\n','\0'
};
extern unsigned int wr_tx;
extern short unsigned int cmdReceived;
extern short unsigned int cmdReceived2;
short unsigned int flag = RESET;
extern unsigned int cmdTimer;
char dispCmd[STRLEN] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
extern char command_array[COMMAND_SIZE];
extern char command_array2[COMMAND_SIZE];
unsigned int tHund;
unsigned short int tTen;
unsigned short int tOne;
int cmdTime;
unsigned short int action=RESET;
unsigned short int flag1=RESET;
unsigned short int flag2=RESET;
unsigned short int flag3=RESET;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Timer_B0();                     // Initialize Timers
  Init_Timer_B3();
  Init_LCD();                          // Initialize LCD
  //Init_ADC();
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Serial_UCA0();                  // Initialize Serial Port for USB 
  Init_Serial_UCA1();

// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  
  strcpy(display_line[LINE_1], "Project 09");
  update_string(display_line[LINE_1], LINE_1);
  strcpy(display_line[LINE_2], "          ");
  update_string(display_line[LINE_2], LINE_2);
  strcpy(display_line[LINE_3], "          ");
  update_string(display_line[LINE_3], LINE_3);
  strcpy(display_line[LINE_4], "          ");
  update_string(display_line[LINE_4], LINE_4);
  //enable_display_update();
  display_changed = YES;
  
  pressed = RESET;
  serialCount = RESET;
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  
  while(ALWAYS) {                      // Can the Operating system run
    
    if (cmdReceived2 & !cmdReceived) {
      strcpy(command_array, command_array2);
      cmdReceived = YES;
      cmdReceived2 = NO;
    }
    if (cmdReceived) {
      if (!flag2) {
        strcpy(display_line[LINE_1], "          ");
        update_string(display_line[LINE_1], LINE_1);
        strcpy(display_line[LINE_3], "          ");
        update_string(display_line[LINE_3], LINE_3);
        strcpy(display_line[LINE_4], "          ");
        update_string(display_line[LINE_4], LINE_4);
        display_changed = YES;
        dispCmd[CHAR_4] = command_array[CHAR_5];
        dispCmd[CHAR_5] = command_array[CHAR_6];
        dispCmd[CHAR_6] = command_array[CHAR_7];
        dispCmd[CHAR_7] = command_array[CHAR_8];
        flag2 = YES;
      }
      if (command_array[CHAR_1ST]=='5' & command_array[CHAR_2]=='5' &  
          command_array[CHAR_3]=='0' & command_array[CHAR_4]=='0') {
        if (!flag1) {
          tHund = (command_array[CHAR_6] - ASCIIOFFSET) * HUND;
          tTen = (command_array[CHAR_7] - ASCIIOFFSET) * TENS;
          tOne = (command_array[CHAR_8] - ASCIIOFFSET);
          cmdTime = (tHund + tTen + tOne);
          cmdTimer = RESET;
          flag1 = YES;
        }
        switch(command_array[CHAR_5]) {
        case 'F':
          if (!action){
            RIGHT_FORWARD_SPEED = WHEEL_40;
            LEFT_FORWARD_SPEED = WHEEL_40;
            lcd_BIG_mid(); 
            strcpy(display_line[LINE_2], dispCmd);
            update_string(display_line[LINE_2], LINE_2);
            display_changed = YES;
            action = YES;
          }
          break;
        case 'B':
          if (!action){
            RIGHT_REVERSE_SPEED = WHEEL_40;
            LEFT_REVERSE_SPEED = WHEEL_40;
            lcd_BIG_mid(); 
            strcpy(display_line[LINE_2], dispCmd);
            update_string(display_line[LINE_2], LINE_2);
            display_changed = YES;
            action = YES;
          }
          break;
        case 'R':
          if (!action){
            LEFT_FORWARD_SPEED = WHEEL_25;
            lcd_BIG_mid(); 
            strcpy(display_line[LINE_2], dispCmd);
            update_string(display_line[LINE_2], LINE_2);
            display_changed = YES;
            action = YES;
          }
          break;
        case 'L':
          if (!action){
            RIGHT_FORWARD_SPEED = WHEEL_25;
            lcd_BIG_mid(); 
            strcpy(display_line[LINE_2], dispCmd);
            update_string(display_line[LINE_2], LINE_2);
            display_changed = YES;
            action = YES;
          }
          break;
        default: break;
        }
        if (cmdTimer>cmdTime) {
          RIGHT_FORWARD_SPEED = WHEEL_OFF;
          RIGHT_REVERSE_SPEED = WHEEL_OFF;
          LEFT_REVERSE_SPEED = WHEEL_OFF;
          LEFT_FORWARD_SPEED = WHEEL_OFF;
          
          action = NO;
          cmdReceived = NO;
          flag1 = NO;
          flag2 = NO;
        }
      }
    }
    if (!stop) {
      switch(serialCount) {
      case ONE_SEC:
        P5OUT |= IOT_RESET;
        break;
      case TEN_SEC:
        checkIP = YES;
        break;
      case TWENTY_SEC:
        if (!flag) {
          strcpy(transmit_array, nstat);
          wr_tx = RESET; 
          UCA0IE |= UCTXIE; 
          flag = YES;
        }
        break;
      case TWENTY_ONE_SEC:
        strcpy(transmit_array, nstcp);
        wr_tx = RESET; 
        UCA0IE |= UCTXIE;
        stop = YES;
        break;
      default: break;
      }
    }
    if (!checkIP & eqYes & !flag3) {
      strcpy(display_line[LINE_1], " Wireless ");
      update_string(display_line[LINE_1], LINE_1);
      strcpy(display_line[LINE_2], "IP address");
      update_string(display_line[LINE_2], LINE_2);
      strcpy(display_line[LINE_3], ip_1);
      update_string(display_line[LINE_3], LINE_3);
      strcpy(display_line[LINE_4], ip_2);
      update_string(display_line[LINE_4], LINE_4);
      display_changed = YES;
      flag3 = YES;
    }
    if (usb_rx_ring_wr != usb_rx_ring_rd){ 
      Processbuff[pb_wr++] = USB_Char_Rx[usb_rx_ring_rd++] ;     
      if (pb_wr >= (sizeof(Processbuff))){         
        pb_wr = BEGINNING;     // Circular buffer back to beginning     
      }     
      if (usb_rx_ring_rd >= (sizeof(USB_Char_Rx))){         
        usb_rx_ring_rd = BEGINNING;  // Circular buffer back to beginning  
      } 
    }
    
    switch(Time_Sequence){
      case FIVE_SEC:                        //
        if(one_time){
          Init_LEDs();
          display_changed = YES;
          one_time = RESET;
        }
        Time_Sequence = RESET;             //
        break;
      case FOUR_SEC:                        //
        if(one_time){
          P6OUT |= GRN_LED;            // Change State of LED 5
          one_time = RESET;
        }
        break;
      case THREE_SEC:                         //
        if(one_time){
          P1OUT |= RED_LED;            // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = RESET;
        }
        break;
      case TWO_SEC:                         //
        if(one_time){
          P6OUT |= GRN_LED;            // Change State of LED 5
          display_changed = YES;
          one_time = RESET;
        }
        break;
      case  ONE_SEC:                        //
        if(one_time){
          P1OUT &= ~RED_LED;           // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = RESET;
        }
        break;                         //
      default: break;
    } 
    //Switches_Process();                // Check for switch state change
    Display_Process();
  }
//------------------------------------------------------------------------------
}
