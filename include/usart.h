#ifndef USART_H
#define USART_H

#include "stm32h750xx.h"


// Assumes that USART runs on APB clock

typedef enum{
    USART_ERROR = 0,
    USART_SUCCESS
}usart_status;

// Word Length
typedef enum {
    USART_WORDLEN_8B = 0, // Standard (8 bits)
    USART_WORDLEN_9B = 1, // Used when Parity is enabled to keep 8 data bits
    USART_WORDLEN_7B = 2  
} usart_wordlen;

// Stop Bits
typedef enum {
    USART_STOPBITS_1   = 0, // Standard
    USART_STOPBITS_0_5 = 1, // Smartcard mode
    USART_STOPBITS_2   = 2, // Used for noisy environments
    USART_STOPBITS_1_5 = 3  // Smartcard mode
} usart_stopbits;

// Parity 
typedef enum {
    USART_PARITY_NONE = 0, // Standard
    USART_PARITY_EVEN = 1,
    USART_PARITY_ODD  = 2
} usart_parity;

// Communication Direction
typedef enum {
    USART_MODE_RX       = 0, // Receive only
    USART_MODE_TX       = 1, // Transmit only
    USART_MODE_TX_RX    = 2  // Standard bidirectional
} usart_mode;

// Hardware Flow Control (RTS/CTS)
typedef enum {
    USART_HWCONTROL_NONE    = 0, // Standard (3-wire UART: TX, RX, GND)
    USART_HWCONTROL_RTS     = 1,
    USART_HWCONTROL_CTS     = 2,
    USART_HWCONTROL_RTS_CTS = 3
} usart_hwcontrol;

// Oversampling 
typedef enum {
    USART_OVERSAMPLING_16 = 0, // Standard
    USART_OVERSAMPLING_8  = 1  // Used to achieve higher maximum baud rates
} usart_oversampling;


typedef struct {
    USART_TypeDef*      instance;      // e.g., USART1
    uint32_t            baud_rate;     // e.g., 9600, 115200, 921600
    usart_wordlen       word_length;   // 8 bits, 9 bits, etc.
    usart_stopbits      stop_bits;     // 1 or 2 stop bits
    usart_parity        parity;        // None, Even, Odd
    usart_mode          mode;          // TX, RX, or Both
    usart_hwcontrol     hw_flow_ctrl;  // None, RTS, CTS
    usart_oversampling  oversampling;  // 8 or 16
} usart_init_s;




usart_status usart_init(usart_init_s* usart);
usart_status usart_send_char(const char c, USART_TypeDef* usart, uint32_t timeout);
usart_status usart_print(const char* c, USART_TypeDef* usart ,uint32_t timeout);




#endif /* USART_H */