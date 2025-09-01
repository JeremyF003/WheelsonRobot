/**
  uart2.h
*/
#ifndef UART2_H
#define UART2_H

/**
  Section: Included Files
*/
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Macro Declarations
*/
#define UART2_DataReady  (UART2_is_rx_ready())

/**
  Section: Data Type Definitions
*/
typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}uart2_status_t;


/**
  Section: UART2 APIs
*/
/**
 @Description
    This routine initializes the UART2 driver.
    This routine must be called before any other UART2 routine is called.
*/
void UART2_Initialize(void);

/**
  @Description
    This routine checks if UART2 receiver has received data 
    and ready to be read

  @Preconditions
    UART2_Initialize() function should be called
    before calling this function
    UART2 receiver should be enabled before calling this 
    function

  @Returns
    Status of UART2 receiver
    TRUE: UART2 receiver is ready for reading
    FALSE: UART2 receiver is not ready for reading
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(UART2_is_rx_ready())
            {
                rxData = UART2_Read();
                if(UART2_is_tx_ready())
                {
                    UART2_Write(rxData);
                }
            }
        }
    }
    </code>
*/
bool UART2_is_rx_ready(void);

/**
  @Description
    This routine checks if UART2 transmitter is ready 
    to accept and transmit data byte

  @Preconditions
    UART2_Initialize() function should have been called
    before calling this function.
    UART2 transmitter should be enabled before calling 
    this function

  @Returns
    Status of UART2 transmitter
    TRUE: UART2 transmitter is ready
    FALSE: UART2 transmitter is not ready
 */
bool UART2_is_tx_ready(void);

/**
  @Description
    This function return the status of transmit shift register

  @Preconditions
    UART2_Initialize() function should be called
    before calling this function
    UART2 transmitter should be enabled and UART2_Write
    should be called before calling this function

  @Returns
    Status of UART2 transmit shift register
    TRUE: Data completely shifted out if the UART shift register
    FALSE: Data is not completely shifted out of the shift register
 */
bool UART2_is_tx_done(void);

/**
 @Description
    This routine gets the error status of the last read byte.

  @Preconditions
    UART2_Initialize() function should have been called
    before calling this function. The returned value is only
    updated after a read is called.

  @Returns
    the status of the last read byte

  @Example
	<code>
    void main(void)
    {
        volatile uint8_t rxData;
        volatile uart2_status_t rxStatus;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        // Enable the Global Interrupts
        INTERRUPT_GlobalInterruptEnable();
        
        while(1)
        {
            // Logic to echo received data
            if(UART2_is_rx_ready())
            {
                rxData = UART2_Read();
                rxStatus = UART2_get_last_status();
                if(rxStatus.ferr){
                    LED_0_SetHigh();
                }
            }
        }
    }
    </code>
 */
uart2_status_t UART2_get_last_status(void);

/**
 @Description
    This routine reads a byte of data from the UART2.

  @Preconditions
    UART2_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if the receiver is not empty before calling this function.
	
	UART2_DataReady is a macro which checks if any byte is received.
	Call this macro before using this function.

  @Returns
    A data byte received by the driver.
	
  @Example
	<code>
            void main(void) {
                            // initialize the device
                            SYSTEM_Initialize();
                            uint8_t data;

                            // Enable the Global Interrupts
                            INTERRUPT_GlobalInterruptEnable();

                            // Enable the Peripheral Interrupts
                            INTERRUPT_PeripheralInterruptEnable();

                            printf("\t\tTEST CODE\n\r");		//Enable redirect STDIO to USART before using printf statements
                            printf("\t\t---- ----\n\r");
                            printf("\t\tECHO TEST\n\r");
                            printf("\t\t---- ----\n\n\r");
                            printf("Enter any string: ");
                            do{
                            data = UART2_Read();		// Read data received
                            UART2_Write(data);			// Echo back the data received
                            }while(!UART2_DataReady);		//check if any data is received

                    }
    </code>
*/
uint8_t UART2_Read(void);

 /**
 @Description
    This routine writes a byte of data to the UART2.

  @Preconditions
    UART2_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the UART2
*/
void UART2_Write(uint8_t txData);

/**
 @Description
    This API sets the function to be called upon UART2 framing error

  @Preconditions
    Initialize  the UART2 before calling this API

  @Param
    Address of function to be set as framing error handler
*/
void UART2_SetFramingErrorHandler(void (* interruptHandler)(void));

/**
 @Description
    This API sets the function to be called upon UART2 overrun error

  @Preconditions
    Initialize  the UART2 module before calling this API

  @Param
    Address of function to be set as overrun error handler

*/
void UART2_SetOverrunErrorHandler(void (* interruptHandler)(void));

/**
  @Description
    This API sets the function to be called upon UART2 error

  @Preconditions
    Initialize  the UART2 module before calling this API

  @Param
    Address of function to be set as error handler
*/
void UART2_SetErrorHandler(void (* interruptHandler)(void));

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // UART2_H
/**
 End of File
*/