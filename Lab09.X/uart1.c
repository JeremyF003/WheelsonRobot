/*
    PIC18F46K42 
    UART1.c source code for UART1 module 
    
*/


/**
  Section: Included Files
*/
#include <xc.h>
#include "uart1.h"

static volatile uart1_status_t uart1RxLastError;

/**
  Section: UART1 APIs
*/
void (*UART1_FramingErrorHandler)(void);
void (*UART1_OverrunErrorHandler)(void);
void (*UART1_ErrorHandler)(void);

void UART1_DefaultFramingErrorHandler(void);
void UART1_DefaultOverrunErrorHandler(void);
void UART1_DefaultErrorHandler(void);

void UART1_Initialize(void)
{
    // Disable interrupts before changing states

    // Set the UART1 module to the options selected in the user interface.

    // P1L 0; 
    U1P1L = 0x00;

    // P1H 0; 
    U1P1H = 0x00;

    // P2L 0; 
    U1P2L = 0x00;

    // P2H 0; 
    U1P2H = 0x00;

    // P3L 0; 
    U1P3L = 0x00;

    // P3H 0; 
    U1P3H = 0x00;

    // BRGS high speed; MODE Asynchronous 8-bit mode; RXEN enabled; TXEN enabled; ABDEN disabled; 
    U1CON0 = 0xB0;

    // RXBIMD Set RXBKIF on rising RX input; BRKOVR disabled; WUE disabled; SENDB disabled; ON enabled; 
    U1CON1 = 0x80;

    // TXPOL not inverted; FLO off; C0EN Checksum Mode 0; RXPOL not inverted; RUNOVF RX input shifter stops all activity; STP Transmit 1Stop bit, receiver verifies first Stop bit; 
    U1CON2 = 0x00;

    // BRGL 103; 
    U1BRGL = 0x67;

    // BRGH 0; 
    U1BRGH = 0x00;

    // STPMD in middle of first Stop bit; TXWRE No error; 
    U1FIFO = 0x00;

    // ABDIF Auto-baud not enabled or not complete; WUIF WUE not enabled by software; ABDIE disabled; 
    U1UIR = 0x00;

    // ABDOVF Not overflowed; TXCIF 0; RXBKIF No Break detected; RXFOIF not overflowed; CERIF No Checksum error; 
    U1ERRIR = 0x00;

    // TXCIE disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; RXFOIE disabled; PERIE disabled; RXBKIE disabled; 
    U1ERRIE = 0x00;


    UART1_SetFramingErrorHandler(UART1_DefaultFramingErrorHandler);
    UART1_SetOverrunErrorHandler(UART1_DefaultOverrunErrorHandler);
    UART1_SetErrorHandler(UART1_DefaultErrorHandler);

    uart1RxLastError.status = 0;

}

bool UART1_is_rx_ready(void)
{
    return (bool)(PIR3bits.U1RXIF);
}

bool UART1_is_tx_ready(void)
{
    return (bool)(PIR3bits.U1TXIF && U1CON0bits.TXEN);
}

bool UART1_is_tx_done(void)
{
    return U1ERRIRbits.TXMTIF;
}

uart1_status_t UART1_get_last_status(void){
    return uart1RxLastError;
}

uint8_t UART1_Read(void)
{
    while(!PIR3bits.U1RXIF)
    {
    }

    uart1RxLastError.status = 0;

    if(U1ERRIRbits.FERIF){
        uart1RxLastError.ferr = 1;
        UART1_FramingErrorHandler();
    }

    if(U1ERRIRbits.RXFOIF){
        uart1RxLastError.oerr = 1;
        UART1_OverrunErrorHandler();
    }

    if(uart1RxLastError.status){
        UART1_ErrorHandler();
    }

    return U1RXB;
}

void UART1_Write(uint8_t txData)
{
    while(0 == PIR3bits.U1TXIF)
    {
    }

    U1TXB = txData;    // Write the data byte to the USART.
}





void UART1_DefaultFramingErrorHandler(void){}

void UART1_DefaultOverrunErrorHandler(void){}

void UART1_DefaultErrorHandler(void){
}

void UART1_SetFramingErrorHandler(void (* interruptHandler)(void)){
    UART1_FramingErrorHandler = interruptHandler;
}

void UART1_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    UART1_OverrunErrorHandler = interruptHandler;
}

void UART1_SetErrorHandler(void (* interruptHandler)(void)){
    UART1_ErrorHandler = interruptHandler;
}






/**
  End of File
*/
