/*****
    PIC18F46K42
    PWM7 module source file

    PWM7 PIN designations:  output	RC7
 
    01-FEB-2021
*****/
 
 /**
   Section: Included Files
 */

 #include <xc.h>
 #include "pwm7.h"

 /**
   Section: PWM Module APIs
 */

 void PWM7_Initialize(void)
 {
    // Set the PWM to the options selected in the PIC10 / PIC12 / PIC16 / PIC18 MCUs.
    // PWM7POL active_hi; PWM7EN enabled; 
    // PWM7CON = 0x80;   

    // Initialize duty cycle ratio to be zero
    PWM7DCH = 0x00;   
    PWM7DCL = 0x00;   

    // Select timer
    CCPTMRS1bits.P7TSEL = 1;
 }

 void PWM7_LoadDutyValue(uint16_t dutyValue)
 {
     // Writing to 8 MSBs of PWM duty cycle in PWMDCH register
     PWM7DCH = (dutyValue & 0x03FC)>>2;
     
     // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
     PWM7DCL = (dutyValue & 0x0003)<<6;
 }
 
 void PWM7_Stop(void)
 {
     PWM7CON = 0x00;
 }
 
 void PWM7_Start(void)
 {
     PWM7CON = 0x80;
 }
 /**
  End of File
 */
