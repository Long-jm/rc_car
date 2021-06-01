//------------------------------------------------------------------------------
// Macros
//
//------------------------------------------------------------------------------


#define MCLK_FREQ_MHZ              8  // MCLK = 8MHz
#define CLEAR_REGISTER       (0X0000)

// Main Macros
#define ALWAYS                    (1)
#define YES                       (1)
#define NO                        (0)
#define RESET                  (0x00)
#define RED_LED                (0x01) // RED LED 0
#define GRN_LED                (0x40) // GREEN LED 1

// Port Defaults
#define D_OUT                  (0xFF) // Direction Out[HIGH]
#define D_IN                   (0x00) // Direction In[LOW]
#define OUT_LOW                (0x00) // Output Low

// Port 1 Pins 
#define RED_LED                (0x01) // 0 RED LED 0 
#define A1_SEEED               (0x02) // 1 A1_SEEED 
#define V_DETECT_L             (0x04) // 2 V_DETECT_L 
#define V_DETECT_R             (0x08) // 3 V_DETECT_R 
#define A4_SEEED               (0x10) // 4 A4_SEEED 
#define V_THUMB                (0x20) // 5 V_THUMB 
#define UCA0RXD                (0x40) // 6 Back Channel UCA0RXD 
#define UCA0TXD                (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins 
#define P2_0                   (0x01) // 0 
#define P2_1                   (0x02) // 1 
#define P2_2                   (0x04) // 2 
#define SW2                    (0x08) // 3 SW2 
#define P2_4                   (0x10) // 4 
#define P2_5                   (0x20) // 5 
#define LFXOUT                 (0x40) // XOUTR 
#define LFXIN                  (0x80) // XINR

// Port 3 Pins 
#define TEST_PROBE             (0x01) // 0 TEST PROBE 
#define CHECK_BAT              (0x02) // 1 CHECK_BAT 
#define OA2N                   (0x04) // 2 Photodiode Circuit 
#define OA2P                   (0x08) // 3 Photodiode Circuit 
#define SMCLK_OUT              (0x10) // 4 SMCLK 
#define IR_LED                 (0x20) // 5 IR_LED 
#define IOT_LINK               (0x40) // 6 IOT_LINK 
#define P3_7                   (0x80) // 7 P3_7

// Port 4 Pins 
#define RESET_LCD              (0x01) // 0 LCD Reset 
#define SW1                    (0x02) // 1 SW1 
#define UCA1RXD                (0x04) // 2 Back Channel UCA1RXD 
#define UCA1TXD                (0x08) // 3 Back Channel UCA1TXD 
#define UCB1_CS_LCD            (0x10) // 4 Chip Select 
#define UCB1CLK                (0x20) // 5 SPI mode - clock output—UCB1CLK 
#define UCB1SIMO               (0x40) // 6 UCB1SIMO 
#define UCB1SOMI               (0x80) // 7 UCB1SOMI

// Port 5 Pins
#define IOT_RESET              (0x01) // 0 
#define V_BAT                  (0x02) // 1 
#define IOT_PROG_SEL           (0x04) // 2
#define V_3_3                  (0x08) // 3  
#define IOT_PROG_MODE          (0x10) // 4  

// Port 6 Pins
#define R_FORWARD              (0x01) // 0 
#define L_FORWARD              (0x02) // 1 
#define R_REVERSE              (0x04) // 2
#define L_REVERSE              (0x08) // 3  
#define LCD_BACKLITE           (0x10) // 4  
#define P6_5                   (0x20) // 5  
#define GRN_LED                (0x40) // 6 

// Init Macros
#define LINE_1                 (0x00)
#define LINE_2                 (0x01)
#define LINE_3                 (0x02)
#define LINE_4                 (0x03)

#define CHAR_1ST               (0x00)
#define CHAR_2                 (0x01)
#define CHAR_3                 (0x02)
#define CHAR_4                 (0x03)
#define CHAR_5                 (0x04)
#define CHAR_6                 (0x05)
#define CHAR_7                 (0x06)
#define CHAR_8                 (0x07)
#define CHAR_END               (0x0A)
#define NUM_LINES              (0x04)
#define NUM_CHARS              (0x0B)

// Shapes Macros
#define PERIOD                  (820)
#define OFF_TIME                 (20)
#define ON_TIME                   (2)
#define TIME_FWD                (200)
#define TIME_TURN               (215)

// Switches Macros
#define CIR_CHECK                 (1)
#define FIG8_CHECK                (2)
#define TRI_CHECK                 (3)
#define CHECK_RESET               (3)

// Clock Macros
#define USE_GPIO               (0x00)  
#define USE_SMCLK              (0x01) 
#define GPIO_CHECK                (1)
#define SMCLK_CHECK               (2)

// Interrupt Timers Macros
#define TB0CCR0_INTERVAL      (50000)
#define TB0CCR1_INTERVAL     (0xFFFF)
#define TB0CCR2_INTERVAL     (0xFFFF)

#define LCD_BLINK_ON             (10)
#define LCD_BLINK_OFF            (20)
#define UPDATE_TIME               (4)

#define PICK_REGISTER            (14)
#define CCR1                      (2)
#define CCR2                      (4)
#define CCR_OVERFLOW             (14)

// ADC Macros
#define THOU                   (1000)
#define HUND                    (100)
#define TENS                     (10)
#define ONES                      (1)
#define THOUPLACE                 (0)
#define HUNDPLACE                 (1)
#define TENSPLACE                 (2)
#define ONESPLACE                 (3)
#define STREND                    (4)
#define STRLEN                   (10)
#define ASCIIOFFSET            (0x30)

// PWM Macros
#define RIGHT_FORWARD_SPEED (TB3CCR1) 
#define LEFT_FORWARD_SPEED  (TB3CCR2) 
#define RIGHT_REVERSE_SPEED (TB3CCR3) 
#define LEFT_REVERSE_SPEED  (TB3CCR4)
#define WHEEL_PERIOD          (40005)
#define WHEEL_OFF                 (0)
#define WHEEL_15               (6000)
#define WHEEL_20               (8000)
#define WHEEL_25              (10000)
#define WHEEL_30              (12000)
#define WHEEL_40              (16000)
#define WHEEL_60              (24000)
#define WHEEL_75              (30000)
#define WHEEL_99              (40000)

// Black Line Macros
#define BLACK                (0x01F4)
#define BEGIN                     (2)
#define GO                       (20)
#define TURN                     (80)

#define CHANA2                 (0x00)
#define CHANA3                 (0x01)
#define CHANA5                 (0x02)

#define SPACE1                    (4)
#define SPACE2                    (5)
#define SPACE3                    (6)
#define SPACE4                    (7)
#define SPACE5                    (8)
#define SPACE6                    (9)
#define STRNULL                  (10)

#define LEFT                      (1)
#define MID                       (2)
#define RIGHT                     (3)

// Serial Macros
#define BEGINNING                 (0) 
#define DEBOUNCETIME              (2)
#define SMALL_RING_SIZE          (16) 
#define LARGE_RING_SIZE          (32) 
#define BAUD115                   (1) 
#define BAUD460                   (2) 
#define COUNT2                   (10) 
#define COUNT6                   (30)
#define COUNT8                 (0x08)
#define RXIFG                     (2)
#define TXIFG                     (4)

#define BRW115                 (0x04)
#define MCTLW115               (0x55)
#define BRW460                 (0x11)
#define MCTLW1460              (0x4A)

#define PROCESS_SIZE             (32)
#define TRANSMIT_SIZE            (32)
#define COMMAND_SIZE              (8)

// IOT Macros
#define ONE_SEC                   (5)
#define TWO_SEC                  (10)
#define THREE_SEC                (15)
#define FOUR_SEC                 (20)
#define FIVE_SEC                 (25)
#define TEN_SEC                  (50)
#define TWENTY_SEC              (100)
#define TWENTY_ONE_SEC          (105)

#define ONE_DOT                   (1)
#define TWO_DOT                   (2)

