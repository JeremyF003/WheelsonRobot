/*****
    PIC18F46K42
    Timer0 module source file
 
    01-FEB-2021
*****/


/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr0.h"

#define MASK_BIT4   0x10
/**
  Section: TMR0 APIs
*/


void TMR0_Initialize(uint8_t TMR0control_0, uint8_t TMR0control_1)
{
    // T0control0:  set 8 or 16-bit timer; set post-scaler 
    T0CON0 = TMR0control_0;

    // T0control1:  set timer source, sync and pre-scaler
    T0CON1 = TMR0control_1;
    
    // Timer0 is initialized, but not enabled
    T0CON0bits.T0EN = 0;

    // Clearing IF flag
    PIR3bits.TMR0IF = 0;
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 0;
}

uint8_t TMR0_Read8BitTimer(void)
{
    uint8_t readVal;

    // read Timer0, low register only
    readVal = TMR0L;

    return readVal;
}

uint16_t TMR0_Read16BitTimer(void)
{
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow  = TMR0L;
    readValHigh = TMR0H;
    readVal  = ((uint16_t)readValHigh << 8) + readValLow;

    return readVal;
}

void TMR0_Write8BitTimer(uint8_t timerVal)
{
    // Write to Timer0 registers, low register only
    TMR0L = timerVal;
 }

void TMR0_Write16BitTimer(uint16_t timerVal)
{
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}


void TMR0_Period8BitSet(uint8_t periodVal)
{
   // Write to Timer0 registers, high register only
   TMR0H = periodVal;
}

bool TMR0_HasOverflowOccured(void)
{
    // check if  overflow has occurred by checking the TMRIF bit
    return(PIR3bits.TMR0IF);
}
/**
  End of File
*/