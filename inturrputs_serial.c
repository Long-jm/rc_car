//-----------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include "msp430.h"

volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
volatile char USB_Char_Rx[SMALL_RING_SIZE]; 
volatile char USB_Char_Tx[LARGE_RING_SIZE];

volatile unsigned int usb_rx_ring_wr1;
volatile unsigned int usb_rx_ring_rd1;
volatile unsigned int usb_tx_ring_wr1;
volatile unsigned int usb_tx_ring_rd1;
volatile char USB_Char_Rx1[SMALL_RING_SIZE]; 
volatile char USB_Char_Tx1[LARGE_RING_SIZE];
extern char transmit_array[TRANSMIT_SIZE];
char command_array[COMMAND_SIZE];
char command_array2[COMMAND_SIZE];
unsigned int cmd_wr = RESET;
unsigned int cmd_wr2 = RESET;
volatile int i=RESET;

extern int UCA0_index;
extern int UCA1_index;

char echo;
unsigned int wr_tx;
char ip_1[STRLEN];
char ip_2[STRLEN];
unsigned int ip1_wr = RESET;
unsigned int ip2_wr = RESET;
short unsigned int checkIP = RESET;
short unsigned int rYes = RESET;
short unsigned int eqYes = RESET;
short unsigned int pCount = RESET;
short unsigned int initCmd = RESET;
short unsigned int cmdReceived = RESET;
short unsigned int cmdReceived2 = RESET;

//-----------------------------------------------------------------------------
#pragma vector=USCI_A0_VECTOR 
__interrupt void USCI_A0_ISR(void){ 
  unsigned int temp;
    
      switch(__even_in_range(UCA0IV,COUNT8)){ 
      case NO:                                     // Vector 0 - no interrupt 
        break; 
      case RXIFG:                                     // Vector 2 - RXIFG 
        temp = usb_rx_ring_wr++; 
        USB_Char_Rx[temp] = UCA0RXBUF;            // RX -> USB_Char_Rx character 
        
        echo = UCA0RXBUF;
        UCA1TXBUF = echo;
        
        if (initCmd) {
          if (cmdReceived) {
            if (i<COMMAND_SIZE) {
            command_array2[cmd_wr2++] = echo;
            i++;
            }
            if (i==COMMAND_SIZE) { 
              i = RESET;
              cmd_wr2 = RESET;
              initCmd = NO;
              cmdReceived2 = YES;
            }
          }
          if (!cmdReceived) {
            if (i<COMMAND_SIZE) {
            command_array[cmd_wr++] = echo;
            i++;
            }
            if (i==COMMAND_SIZE) { 
              i = RESET;
              cmd_wr = RESET;
              initCmd = NO;
              cmdReceived = YES;
            }
          }
        }
        if (echo == '>') {
          initCmd = YES;
        }
        
        if (checkIP) {
          if (eqYes & echo == ' ') {
            checkIP = NO;
          }
          if (eqYes & echo != ' ') {
            if (pCount<TWO_DOT) {
              ip_1[ip1_wr++] = echo;
            }
            if (pCount>ONE_DOT) {
              ip_2[ip2_wr++] = echo;
            }
            if (echo == '.') {
              pCount++;
            }
          }
          if (echo == 'r') {
            rYes++;
          }
          if (rYes==TWO_DOT & echo == '=') {
            eqYes = YES;
          }
        }
       
        if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){ 
          usb_rx_ring_wr = BEGINNING;             // Circular buffer back to beginning 
        } 
        /*if (UCA0RXBUF == '\n' {
          gotMessage = YES;
          newVar = YES;
        }*/
        break;
        case TXIFG:                                    // Vector 4 – TXIFG 
          UCA0TXBUF = transmit_array[wr_tx++]; 
          if (transmit_array[wr_tx ] == RESET){  
            UCA0IE &= ~UCTXIE; 
          }
          break;
      default:
        break;
      }
}
//-----------------------------------------------------------------------------
        
//-----------------------------------------------------------------------------
#pragma vector=USCI_A1_VECTOR 
__interrupt void USCI_A1_ISR(void){ 
  unsigned int temp1; 
      switch(__even_in_range(UCA1IV,COUNT8)){ 
      case NO:                                     // Vector 0 - no interrupt 
        break; 
      case RXIFG:                                     // Vector 2 - RXIFG 
        temp1 = usb_rx_ring_wr1++; 
        USB_Char_Rx1[temp1] = UCA1RXBUF;            // RX -> USB_Char_Rx character 
        
        echo = UCA1RXBUF;
        UCA0TXBUF = echo;
        
        if (usb_rx_ring_wr1 >= (sizeof(USB_Char_Rx1))){ 
          usb_rx_ring_wr1 = BEGINNING;             // Circular buffer back to beginning 
        } 
         case TXIFG:                                    // Vector 4 – TXIFG 
          UCA1TXBUF = transmit_array[wr_tx++]; 
          if (transmit_array[wr_tx ] == RESET){  
            UCA1IE &= ~UCTXIE; 
          }
          break; 
      }
}
//-----------------------------------------------------------------------------
