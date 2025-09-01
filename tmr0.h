/*****
    PIC18F46K42
    Timer0 module header file
 
    01-FEB-2021
*****/

#ifndef TMR0_H
#define TMR0_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

// Bitmasks for T0CON0
// bit 7 is enable; bit 6 not used; bit 5 is TMR0 output
// bit 4
#define T0_8_BIT    0x8F
#define T0_16_BIT   0x9F

// bits 3-0
#define T0_POST_1_16    0x9F
#define T0_POST_1_15    0x9E
#define T0_POST_1_14    0x9D
#define T0_POST_1_13    0x9C
#define T0_POST_1_12    0x9B
#define T0_POST_1_11    0x9A
#define T0_POST_1_10    0x99
#define T0_POST_1_9     0x98
#define T0_POST_1_8     0x97
#define T0_POST_1_7     0x96
#define T0_POST_1_6     0x95
#define T0_POST_1_5     0x94
#define T0_POST_1_4     0x93
#define T0_POST_1_3     0x92
#define T0_POST_1_2     0x91
#define T0_POST_1_1     0x90

// Bitmasks for T0CON1
// bits 7-5
#define T0_SOURCE_INT   0x5F    // Fosc/4
#define T0_SOURCE_EXT   0x1F    // pin selected by T0CKIPPS, non-inverted

// bit 4
#define T0_ASYNC    0xFF
#define T0_SYNC     0xEF

// bits 3-0
#define T0_PRE_1_32768  0xFF    // 1:32768 prescale
#define T0_PRE_1_16384  0xFE    // 1:16384 prescale
#define T0_PRE_1_8192   0xFD    // 1:8192 prescale
#define T0_PRE_1_4096   0xFC    // 1:4096 prescale
#define T0_PRE_1_2048   0xFB    // 1:2048 prescale
#define T0_PRE_1_1024   0xFA    // 1:1024 prescale
#define T0_PRE_1_512    0xF9    // 1:512 prescale
#define T0_PRE_1_256    0xF8    // 1:256 prescale
#define T0_PRE_1_128    0xF7    // 1:128 prescale
#define T0_PRE_1_64    	0xF6    // 1:64 prescale
#define T0_PRE_1_32    	0xF5    // 1:32 prescale
#define T0_PRE_1_16   	0xF4    // 1:16 prescale
#define T0_PRE_1_8    	0xF3    // 1:8 prescale
#define T0_PRE_1_4    	0xF2    // 1:4 prescale
#define T0_PRE_1_2    	0xF1    // 1:2 prescale
#define T0_PRE_1_1    	0xF0    // 1:1 prescale



#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif



/**
  Section: TMR0 APIs
*/

/**
  @Description
    This function initializes the TMR0 Registers.
    This function must be called before any other TMR0 function is called.
   
  @Example
    <code>
    main()
    {
        // Initialize TMR0 module
        TMR0_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR0_Initialize(uint8_t TMR0control_0, uint8_t TMR0control_1);

/**
  @Description
    This function starts the TMR0 operation.
    This function must be called after the initialization of TMR0.

  @Example
    <code>
    // Initialize TMR0 module

    // Start TMR0
    TMR0_StartTimer();

    // Do something else...
    </code>
*/
void TMR0_StartTimer(void);

/**
  @Description
    This function stops the TMR0 operation.
    This function must be called after the start of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Example
    <code>
    // Initialize TMR0 module

    // Start TMR0
    TMR0_StartTimer();

    // Do something else...

    // Stop TMR0;
    TMR0_StopTimer();
    </code>
*/
void TMR0_StopTimer(void);

/**
  @Description
    This function reads the 8 bits TMR0 register value and return it.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Returns
    This function returns the 8 bits value of TMR0 register.

  @Example
    <code>
    // Initialize TMR0 module

    // Start TMR0
    TMR0_StartTimer();

    // Read the current value of TMR0
    if(0 == TMR0_ReadTimer())
    {
        // Do something else...

        // Stop TMR0;
        TMR0_StopTimer();
    }
    </code>
*/
uint8_t TMR0_Read8BitTimer(void);
uint16_t TMR0_Read16BitTimer(void);

/**
  @Description
    This function writes the 8 bits value to TMR0 register.
    This function must be called after the initialization of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    timerVal - Value to write into TMR0 register.

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR0 register
        if(ZERO == TMR0_ReadTimer())
        {
            // Do something else...

            // Write the TMR0 register
            TMR0_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR0_Write8BitTimer(uint8_t timerVal);
void TMR0_Write16BitTimer(uint16_t timerVal);

/**
  @Summary
    Load value to Period Register.

  @Description
    This function writes the value to TMR0H register.
    This function must be called after the initialization of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    periodVal - Value to load into TMR0 register.

  @Example
    <code>
    while(1)
    {
        if(TMR0IF)
        {
            // Do something else...

            // clear the TMR0 interrupt flag
            TMR0IF = 0;

            // Change the period value of TMR0
            TMR0_Reload(0x80);
        }
    }
    </code>
*/
void TMR0_Period8BitSet(uint8_t periodVal);


/**
  @Summary
    Boolean routine to poll or to check for the overflow flag on the fly.

  @Description
    This function is called to check for the timer overflow flag.
    This function is used in timer polling method.

  @Preconditions
    Initialize  the TMR0 module before calling this routine.

  @Returns
    true - timer overflow has occurred.
    false - timer overflow has not occurred.

  @Example
    <code>
    while(1)
    {
        // check the overflow flag
        if(TMR0_HasOverflowOccured())
        {
            // Do something else...

            // clear the TMR0 interrupt flag
            TMR0IF = 0;
        }
    }
    </code>
*/
bool TMR0_HasOverflowOccured(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // TMR0_H
/**
 End of File
*/