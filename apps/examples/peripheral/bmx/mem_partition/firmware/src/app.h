/*******************************************************************************
  MPLAB Harmony Application

  Application Header
  
  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
	Application definitions. 

  Description:
	 This file contains the  application definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef _APP_HEADER_H
#define _APP_HEADER_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system/common/sys_common.h"
#include "system/devcon/sys_devcon.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Application States

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,

    /* Set up the memory partitions */
    APP_STATE_MEM_PARTITIONS_SET,

    /* Get the sizes of the actual partitions */
    APP_STATE_PARTITION_SIZES_GET,

    /* Verify partition sizes */
    APP_STATE_PARTITION_SIZES_VERIFY,

    /* Spin when we're done */
    APP_STATE_SPIN

} APP_STATES;





// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
	/* The application's current state */
	APP_STATES state;

    /* Flash sizes */
    size_t totalFlashSize;
    size_t userPartitionSize; // User Mode

    /* Ram sizes */
    size_t totalRamSize;
    size_t kernDataRamSize; // Kernel Data
    size_t kernProgRamSize; // Kernel Program
    size_t userDataRamSize; // User Data
    size_t userProgRamSize; // User Program

    /* Flash offsets */
    size_t userPartitionOffset;

    /* Ram offsets */
    size_t userProgOffset;
    size_t userDataOffset;
    size_t kernProgOffset;

} APP_DATA;

/* Driver objects.

  Summary:
    Holds driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.

  Remarks:
    None.
*/

typedef struct
{
	//SYS_MODULE_OBJ   drvObject;
	 
} APP_DRV_OBJECTS;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony Demo application initialization routine

  Description:
    This routine initializes Harmony Demo application.  This function opens
    the necessary drivers, initializes the timer and registers the application
    callback with the USART driver.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    APP_Initialize();


  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks ( void );

void SYS_Initialize ( void* data );
void SYS_Tasks ( void );
// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************

extern APP_DRV_OBJECTS appDrvObject;

extern APP_DATA appData;


#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
 */



