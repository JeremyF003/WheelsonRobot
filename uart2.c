/**
  uart2.c
*/
/**
  Section: Included Files
*/

#include "uart2.h"
#include <xc.h>

static volatile uart2_status_t uart2RxLastError;

/**
  Section: UART2 APIs
*/
void (*UART2_FramingErrorHandler)(void);
void (*UART2_OverrunErrorHandler)(void);
void (*UART2_ErrorHandler)(void);

void UART2_DefaultFramingErrorHandler(void);
void UART2_DefaultOverrunErrorHandler(void);
void UART2_DefaultErrorHandler(void);

void UART2_Initialize(void)
{
    // Disable interrupts before changing states

    // Set the UART2 module to the options selected in the user interface.

    // P1L 0; 
    U2P1L = 0x00;

    // P2L 0; 
    U2P2L = 0x00;

    // P3L 0; 
    U2P3L = 0x00;

    // BRGS high speed; MODE Asynchronous 8-bit mode; RXEN enabled; TXEN enabled; ABDEN disabled; 
    U2CON0 = 0xB0;

    // RXBIMD Set RXBKIF on rising RX input; BRKOVR disabled; WUE disabled; SENDB disabled; ON enabled; 
    U2CON1 = 0x80;

    // TXPOL not inverted; FLO off; RXPOL not inverted; RUNOVF RX input shifter stops all activity; STP Transmit 1Stop bit, receiver verifies first Stop bit; 
    U2CON2 = 0x00;

    // BRGL 225; 
    U2BRGL = 0xE1;

    // BRGH 4; 
    U2BRGH = 0x04;

    // STPMD in middle of first Stop bit; TXWRE No error; 
    U2FIFO = 0x00;

    // ABDIF Auto-baud not enabled or not complete; WUIF WUE not enabled by software; ABDIE disabled; 
    U2UIR = 0x00;

    // ABDOVF Not overflowed; TXCIF 0; RXBKIF No Break detected; RXFOIF not overflowed; CERIF No Checksum error; 
    U2ERRIR = 0x00;

    // TXCIE disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; RXFOIE disabled; PERIE disabled; RXBKIE disabled; 
    U2ERRIE = 0x00;

    UART2_SetFramingErrorHandler(UART2_DefaultFramingErrorHandler);
    UART2_SetOverrunErrorHandler(UART2_DefaultOverrunErrorHandler);
    UART2_SetErrorHandler(UART2_DefaultErrorHandler);

    uart2RxLastError.status = 0;
}

bool UART2_is_rx_ready(void)
{
    return (bool)(PIR6bits.U2RXIF);
}

bool UART2_is_tx_ready(void)
{
    return (bool)(PIR6bits.U2TXIF && U2CON0bits.TXEN);
}

bool UART2_is_tx_done(void)
{
    return U2ERRIRbits.TXMTIF;
}

uart2_status_t UART2_get_last_status(void){
    return uart2RxLastError;
}

uint8_t UART2_Read(void)
{
    while(!PIR6bits.U2RXIF)
    {
    }
    uart2RxLastError.status = 0;

    if(U2ERRIRbits.FERIF){
        uart2RxLastError.ferr = 1;
        UART2_FramingErrorHandler();
    }

    if(U2ERRIRbits.RXFOIF){
        uart2RxLastError.oerr = 1;
        UART2_OverrunErrorHandler();
    }

    if(uart2RxLastError.status){
        UART2_ErrorHandler();
    }
    return U2RXB;
}

void UART2_Write(uint8_t txData)
{
    while(0 == PIR6bits.U2TXIF)
    {
    }
    U2TXB = txData;    // Write the data byte to the USART.
}

int getch(void)
{
    return UART2_Read();
}

void putch(char txData)
{
    UART2_Write(txData);
}

void UART2_DefaultFramingErrorHandler(void){}

void UART2_DefaultOverrunErrorHandler(void){}

void UART2_DefaultErrorHandler(void){
}

void UART2_SetFramingErrorHandler(void (* interruptHandler)(void)){
    UART2_FramingErrorHandler = interruptHandler;
}

void UART2_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    UART2_OverrunErrorHandler = interruptHandler;
}

void UART2_SetErrorHandler(void (* interruptHandler)(void)){
    UART2_ErrorHandler = interruptHandler;
}
/**
  End of File
*/