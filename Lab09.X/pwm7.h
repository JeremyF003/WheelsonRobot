/*****
    PIC18F46K42
    PWM7 module header file
 
    01-FEB-2021
*****/

#ifndef PWM7_H
 #define PWM7_H
 
 /**
   Section: Included Files
 */

 #include <xc.h>
 #include <stdint.h>

 #ifdef __cplusplus  // Provide C++ Compatibility

     extern "C" {

 #endif

 /**
   Section: Macro Declarations
 */

 #define PWM7_INITIALIZE_DUTY_VALUE    511

 /**
   Section: PWM Module APIs
 */

 /**
   @Description
     This routine initializes the EPWM7_Initialize
     This routine must be called before any other PWM7 routine is called.
     This routine should only be called once during system initialization.

  @Example
     <code>
     uint16_t dutycycle;

     PWM7_Initialize();
     PWM7_LoadDutyValue(dutycycle);
     </code>
  */
 void PWM7_Initialize(void);

 /**
   @Description
     This routine loads the 16 bit duty cycle value.

   @Preconditions
     PWM7_Initialize() function should have been called 
         before calling this function.

   @Param
     Pass 16bit duty cycle value.

   @Example
     <code>
     uint16_t dutycycle;

     PWM7_Initialize();
     PWM7_LoadDutyValue(dutycycle);
     </code>
 */
 void PWM7_LoadDutyValue(uint16_t dutyValue);

//  enables PWM7
 void PWM7_Start(void);
 
 // disables PWM7
 void PWM7_Stop(void);

 
 #ifdef __cplusplus  // Provide C++ Compatibility

     }

 #endif

 #endif	//PWM7_H
 /**
  End of File
 */