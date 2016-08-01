/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version 2.00
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.00"
#define SYS_VERSION               20000

// *****************************************************************************
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        200000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_2            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_3            50000000ul
#define SYS_CLK_BUS_PERIPHERAL_4            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_5            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_7            200000000ul
#define SYS_CLK_BUS_PERIPHERAL_8            100000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         24000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       0ul
   
/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Sample Library Module Configuration Options
  
  <editor-fold defaultstate="collapsed"
   desc="Sample Library Module Configuration Options">
*/
    
#define SAMPLE_MODULE_INSTANCES_NUMBER  2
#define SAMPLE_MODULE_INTERRUPT_MODE    true
#define SAMPLE_MODULE_TIMEOUT           100

#define SAMPLE_MODULE_POWER_STATE_IDX0  SYS_MODULE_POWER_RUN_FULL
#define SAMPLE_MODULE_SOME_DATA_IDX0    42
#define SAMPLE_MODULE_TIMER_ID_IDX0                     TMR_ID_2
#define SAMPLE_MODULE_TIMER_CLOCK_PRESCALER_IDX0        TMR_PRESCALE_VALUE_16
#define SAMPLE_MODULE_TIMER_PERIOD_IDX0                 50000
#define SAMPLE_MODULE_INTERRUPT_SOURCE_IDX0             INT_SOURCE_TIMER_2
#define SAMPLE_MODULE_INTERRUPT_VECTOR_IDX0             INT_VECTOR_T2
#define SAMPLE_MODULE_INTERRUPT_PRIORITY_IDX0           INT_PRIORITY_LEVEL2
#define SAMPLE_MODULE_TIMER_INTERRUPT_SUBPRIORITY_IDX0  INT_SUBPRIORITY_LEVEL0

#define SAMPLE_MODULE_POWER_STATE_IDX1  SYS_MODULE_POWER_RUN_FULL
#define SAMPLE_MODULE_SOME_DATA_IDX1    43
#define SAMPLE_MODULE_TIMER_ID_IDX1                     TMR_ID_3
#define SAMPLE_MODULE_TIMER_CLOCK_PRESCALER_IDX1        TMR_PRESCALE_VALUE_32
#define SAMPLE_MODULE_TIMER_PERIOD_IDX1                 50000
#define SAMPLE_MODULE_INTERRUPT_SOURCE_IDX1             INT_SOURCE_TIMER_3
#define SAMPLE_MODULE_INTERRUPT_VECTOR_IDX1             INT_VECTOR_T3
#define SAMPLE_MODULE_INTERRUPT_PRIORITY_IDX1           INT_PRIORITY_LEVEL2
#define SAMPLE_MODULE_TIMER_INTERRUPT_SUBPRIORITY_IDX1  INT_SUBPRIORITY_LEVEL0
// </editor-fold>

/******************************************************************************
  Test Harness Configuration Options
  
  <editor-fold defaultstate="collapsed"
   desc="Test Harness Configuration Options">
*/

#define TEST_HARNESS_MAX_NUM_TASKS                      2
#define TEST_HARNESS_MAX_NUM_INSTANCES_PER_LIBRARY      3
#define TEST_HARNESS_MAX_NUM_TASKS_PER_LIBRARY          5

/* Test Timeout Timer configuration Options. */
#define TEST_TIMER_ID                       TMR_ID_1
#define TEST_TIMER_INTERRUPT_SOURCE         INT_SOURCE_TIMER_1
#define TEST_TIMER_CLOCK_SOURCE             TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK
#define TEST_TIMER_CLOCK_PRESCALER          TMR_PRESCALE_VALUE_1
#define TEST_TIMER_INCREMENT_PERIOD         50000
#define TEST_TIMER_MS_PER_INCREMENT         1
#define TEST_TIMER_MS_TIMEOUT               5000
#define TEST_TIMER_INTERRUPT_VECTOR         INT_VECTOR_T1
#define TEST_TIMER_INTERRUPT_PRIORITY       INT_PRIORITY_LEVEL1
#define TEST_TIMER_INTERRUPT_SUBPRIORITY    INT_SUBPRIORITY_LEVEL0

/* Test OSAL Idle Sleep Time Configuration Options. */
#define TEST_IDLE_SLEEP_MS_LIBRARY          5
#define TEST_IDLE_SLEEP_MS                  50
// </editor-fold>

/*******************************************************************************
  Sample Functional Test Configuration Options
  
  <editor-fold defaultstate="collapsed"
   desc="Sample Functional Test Configuration Options">
*/

#define TEST_SAMPLE_FUNC_LIB_INSTANCES_NUMBER   2
#define TEST_SAMPLE_MAX_ITERATIONS              5
// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

/*** Application Defined Pins ***/



/*** Application Instance 0 Configuration ***/

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/

