/*
    PIC18F46K42
    Initialization header file for pin_manager.h in common folder
    
    02-MAR-2021
*/

#ifndef INITIALIZE_H
#define	INITIALIZE_H

#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>



/**
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 */
void SYSTEM_Initialize(void);

/**
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 */
void OSCILLATOR_Initialize(void);

/**
 * @Description
    Initializes the PMD module to the default states configured in the
 *                  MCC GUI
 */
void PMD_Initialize(void);

#endif	/* INITIALIZE_H */

