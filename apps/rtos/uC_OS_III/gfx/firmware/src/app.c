/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

#define APP1TASK_WAITGFXREADY       1
#define APP1TASK_UPDATESCREEN       2
#define APP1TASK_ERROR              3

#define MAXSCREENCOLORS             7
uint16_t ScreenColor[MAXSCREENCOLORS];
uint16_t ScreenColor_Index=0;
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback funtions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
   /*initialize the screen color array with correct RGB values*/
   ScreenColor[0] = BRIGHTBLUE;
   ScreenColor[1] = BRIGHTGREEN;
   ScreenColor[2] = BRIGHTCYAN;
   ScreenColor[3] = BRIGHTRED;
   ScreenColor[4] = BRIGHTMAGENTA;
   ScreenColor[5] = SIENNA;
   ScreenColor[6] = GOLD;

      /*setup rtos tick interrupt source, for 1ms tick*/
   __builtin_mtc0(11,0,100000);
   /*start counting from zero*/
   __builtin_mtc0(9,0,0);
   /*clear interrupt flag, before enabling*/
   PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_CORE);
   /*enable interrupt source and set IPL for core timer*/
   PLIB_INT_VectorPrioritySet(INT_ID_0,INT_VECTOR_CT,INT_PRIORITY_LEVEL2);
   PLIB_INT_SourceEnable(INT_ID_0,INT_SOURCE_TIMER_CORE);
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
   static uint32_t APP1Task_State = APP1TASK_WAITGFXREADY;

   switch(APP1Task_State)
   {
      case APP1TASK_WAITGFXREADY:
         if(GFX_Status(sysObj.gfxObject0) == SYS_STATUS_ERROR)
            APP1Task_State = APP1TASK_WAITGFXREADY;
         else
            APP1Task_State = APP1TASK_UPDATESCREEN;
         break;
      case APP1TASK_UPDATESCREEN:
         GFX_ColorSet(0, ScreenColor[ScreenColor_Index++]);
         GFX_ScreenClear(0);
         if(ScreenColor_Index == MAXSCREENCOLORS)
            ScreenColor_Index = 0;
         //stay in this state, update screen colors.
         APP1Task_State = APP1TASK_UPDATESCREEN;
         break;
      case APP1TASK_ERROR:
         //stay in error state once we get here...
         APP1Task_State = APP1TASK_ERROR;
         BSP_LEDToggle(BSP_LED_2);
         break;
      default:
         //get here, some kind of corruption occurred go to error state.
         //Indicate visually to user.
         APP1Task_State = APP1TASK_ERROR;
         break;
   }
   /*since this application task is already running at 500ms, toggle LED to let
    user know application is up and running.*/
   BSP_LEDToggle(BSP_LED_2);
}
 

/*******************************************************************************
 End of File
 */
