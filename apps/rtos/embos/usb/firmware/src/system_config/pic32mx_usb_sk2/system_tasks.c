/*******************************************************************************
 System Tasks File

  File Name:
    system_tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled state
    machines.

  Description:
    This file contains source code necessary to maintain system's polled state
    machines.  It implements the "SYS_Tasks" function that calls the individual
    "Tasks" functions for all the MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"
#include "app.h"
#include "app1.h"


// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 

OS_TASK  _SYS_Tasks_TCB;
uint32_t _SYS_TasksStk[2048];























OS_TASK  _APP_Tasks_TCB;
uint32_t _APP_TasksStk[1024];
OS_TASK  _APP1_Tasks_TCB;
uint32_t _APP1_TasksStk[1024];
static void _SYS_Tasks ( void );

static void _APP_Tasks(void);
static void _APP1_Tasks(void);


// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/

void SYS_Tasks ( void )
{
    /*use macro for creating tasks, user defines which task create func is used in RTOS.h*/
    OS_CREATETASK(&_SYS_Tasks_TCB, "Sys Tasks",_SYS_Tasks,1, _SYS_TasksStk);

    /*use macro for creating tasks, user defines which task create func is used in RTOS.h*/
    OS_CREATETASK(&_APP_Tasks_TCB, "APP Tasks",_APP_Tasks,2, _APP_TasksStk);
    /*use macro for creating tasks, user defines which task create func is used in RTOS.h*/
    OS_CREATETASK(&_APP1_Tasks_TCB, "APP1 Tasks",_APP1_Tasks,2, _APP1_TasksStk);
    /**************
     * Start RTOS * 
     **************/
    OS_Start();
}


/*******************************************************************************
  Function:
    void _SYS_Tasks ( void )

  Summary:
    Maintains state machines of system modules.
*/
static void _SYS_Tasks ( void)
{
    while(1)
    {
        /* Maintain system services */
        SYS_DEVCON_Tasks(sysObj.sysDevcon);

        /* Maintain Device Drivers */

        /* Maintain Middleware */

 
    /* USB FS Driver Task Routine */ 
     DRV_USBFS_Tasks(sysObj.drvUSBObject);
     
    /* USB Device layer tasks routine */ 
    USB_DEVICE_Tasks(sysObj.usbDevObject0);
 

        /* Task Delay */
        OS_Delay(50);
    }
}



/*******************************************************************************
  Function:
    void _APP_Tasks ( void )

  Summary:
    Maintains state machine of APP.
*/

static void _APP_Tasks(void)
{
    while(1)
    {
        APP_Tasks();
        OS_Delay(500);
    }
}


/*******************************************************************************
  Function:
    void _APP1_Tasks ( void )

  Summary:
    Maintains state machine of APP1.
*/

static void _APP1_Tasks(void)
{
    while(1)
    {
        APP1_Tasks();
        OS_Delay(50);
    }
}


/*******************************************************************************
 End of File
 */

