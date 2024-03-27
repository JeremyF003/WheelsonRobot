/*****
    PIC18F46K42
    
    Source file:  pin_manager.c
    Pin setting for modules:
        UART1 - RX1 - RC7; 
                TX1 - RC6;
  
        UART2 - RX2:  RB7; 
                TX2 - RB6; 

        I2C1 - 	SCL1:  RC3  
                SDA1:  RC4

        DIO - RD0-RD7:  Initialized as digital input
 
        TMR0 -	T0CL1 input, external clock:    RA4
                TMR0 output:                	RC0
 
        TMR2 - 	T2IN input, external clock: 	RC2
  
    	TMR4 - no pins selected
  
        PWM7 - output:	RC1
    
     	PWM5 - output:	RC5
 
        ADCC - 	ADACT pin input:	RB4
                ANB0 input:         RB0
                ANB1 input:         RB1
                ANB2 input:         RB2
                Vref+ input:    	RA3
                Vref- input:        RA2
 
    Oscillator clock out - 	RA6
	
    All pins digital except ADCC pins
  
    Date:  01-MAR-2021
*****/


#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISE = 0x07;
    TRISA = 0xFF;
    TRISB = 0xBF;
    TRISC = 0x84;
    TRISD = 0xFF;

    /**
    ANSELx registers
    */
    ANSELD = 0x00;
    ANSELC = 0x00;
    ANSELB = 0x2F;
    ANSELE = 0x07;
    ANSELA = 0xEF;

    /**
    WPUx registers
    */
    WPUD = 0x00;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    RxyI2C registers
    */
    RB1I2C = 0x00;
    RB2I2C = 0x00;
    RC3I2C = 0x00;
    RC4I2C = 0x00;
    RD0I2C = 0x00;
    RD1I2C = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x18;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x07;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0x0F;
    
	
    U2RXPPS = 0x0F;   //RB7->UART2:RX2;    
    RC0PPS = 0x25;   //RC0->TMR0:TMR0;    
    RB6PPS = 0x16;   //RB6->UART2:TX2;    
    RC3PPS = 0x21;   //RC3->I2C1:SCL1;    
    RC1PPS = 0x0F;   //RC1->PWM7:PWM7;    
    RC4PPS = 0x22;   //RC4->I2C1:SDA1;    
    U1RXPPS = 0x17;   //RC7->UART1:RX1;    
    T0CKIPPS = 0x04;   //RA4->TMR0:T0CKI;    
    I2C1SCLPPS = 0x13;   //RC3->I2C1:SCL1;    
    ADACTPPS = 0x0C;   //RB4->ADCC:ADACT;    
    I2C1SDAPPS = 0x14;   //RC4->I2C1:SDA1;    
    T2INPPS = 0x12;   //RC2->TMR2:T2IN;    
    RC5PPS = 0x0D;   //RC5->PWM5:PWM5;    
    RC6PPS = 0x13;   //RC6->UART1:TX1;    
}
  
void PIN_MANAGER_IOC(void)
{   
}

/**
 End of File
*/