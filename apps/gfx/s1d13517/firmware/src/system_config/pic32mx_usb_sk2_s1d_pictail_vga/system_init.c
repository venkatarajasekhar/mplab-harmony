/*******************************************************************************
  System Initialization File

  File Name:
    system_init.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits, 
    and allocates any necessary global system resources, such as the 
    sysObj structure that contains the object handles to all the MPLAB Harmony 
    module objects in the system.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Configuration Bits">

/*** DEVCFG0 ***/

#pragma config DEBUG =      ON
#pragma config ICESEL =     ICS_PGx2
#pragma config PWP =        OFF
#pragma config BWP =        OFF
#pragma config CP =         OFF

/*** DEVCFG1 ***/

#pragma config FNOSC =      PRIPLL
#pragma config FSOSCEN =    ON
#pragma config IESO =       ON
#pragma config POSCMOD =    HS
#pragma config OSCIOFNC =   OFF
#pragma config FPBDIV =     DIV_1
#pragma config FCKSM =      CSECMD
#pragma config WDTPS =      PS1048576
#pragma config FWDTEN =     OFF
/*** DEVCFG2 ***/

#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_1
#pragma config UPLLIDIV =   DIV_1
#pragma config UPLLEN =     OFF
/*** DEVCFG3 ***/

#pragma config USERID =     0xffff
#pragma config FSRSSEL =    PRIORITY_7
#pragma config FMIIEN =     ON
#pragma config FETHIO =     ON
#pragma config FCANIO =     ON
#pragma config FUSBIDIO =   ON
#pragma config FVBUSONIO =  ON
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_GFX Initialization Data">
/*** DRV GFX Initialization Data ***/

DRV_GFX_INIT drvGfxInit =
{
    .orientation             = DISP_ORIENTATION,
    .horizontalResolution    = DISP_HOR_RESOLUTION,
    .verticalResolution      = DISP_VER_RESOLUTION,
    .dataWidth               = DISP_DATA_WIDTH,
    .horizontalPulseWidth    = DISP_HOR_PULSE_WIDTH,
    .horizontalBackPorch     = DISP_HOR_BACK_PORCH,
    .horizontalFrontPorch    = DISP_HOR_FRONT_PORCH,
    .verticalPulseWidth      = DISP_VER_PULSE_WIDTH,
    .verticalBackPorch       = DISP_VER_BACK_PORCH,
    .verticalFrontPorch      = DISP_VER_FRONT_PORCH,
    .logicShift              = DISP_INV_LSHIFT,
    .LCDType                 = 1,
    .colorType               = 0,
    .TCON_Init               = TCON_MODULE,
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_TOUCH_ADC10BIT Initialization Data">
/*** ADC10BIT Driver Initialization Data ***/

const DRV_TOUCH_INIT drvAdc10bitInitData =
{
    .moduleInit           = {0},
    .touchId              = DRV_TOUCH_INDEX_0,
    .drvInitialize        = NULL,
    .orientation          = DISP_ORIENTATION,
    .horizontalResolution = DISP_HOR_RESOLUTION,
    .verticalResolution   = DISP_VER_RESOLUTION,
};
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************

/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Module Initialization Data
// *****************************************************************************
// *****************************************************************************
//<editor-fold defaultstate="collapsed" desc="SYS_DEVCON Initialization Data">
/*******************************************************************************
  Device Control System Service Initialization Data
*/

const SYS_DEVCON_INIT sysDevconInit =
{
    .moduleInit = {0},
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_MSG Initialization Data">
/*** Message System Initialization Data ***/

static uint16_t queuePriorities0[2] = { 64, 32 };
SYS_MSG_INIT msg0Init =
{
    .nMaxMsgsDelivered = 1,
    .nMessagePriorities = 1,
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_TOUCH Initialization Data">
// *****************************************************************************
/* System Touch Initialization Data
*/

const DRV_TOUCH_INIT sysTouchInit0 =
{
    .drvInitialize           = DRV_TOUCH_ADC10BIT_Initialize,
    .drvOpen                 = DRV_TOUCH_ADC10BIT_Open,
    .drvTouchStatus          = DRV_TOUCH_ADC10BIT_TouchStatus,
    .drvTouchDataRead        = DRV_TOUCH_ADC10BIT_TouchDataRead,
    .drvCalibrationSet       = DRV_TOUCH_ADC10BIT_CalibrationSet,
    .drvTouchGetX            = DRV_TOUCH_ADC10BIT_TouchGetX,
    .drvTouchGetY            = DRV_TOUCH_ADC10BIT_TouchGetY,
    .drvTouchPenGet          = NULL,
    .orientation             = DISP_ORIENTATION,
    .horizontalResolution    = DISP_HOR_RESOLUTION,
    .verticalResolution      = DISP_VER_RESOLUTION,
};
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Graphics Library Initialization Data">
/*** GFX Initialization Data ***/

 const GFX_INIT gfxInit0 =
{
    .drvInitialize    = NULL,
    .drvOpen          = DRV_GFX_S1D13517_Open,
    .drvInterfaceSet  = DRV_GFX_S1D13517_InterfaceSet,
    .preemptionLevel  = GFX_SELF_PREEMPTION_LEVEL
};
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: Static Initialization Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
    See prototype in system/common/sys_module.h.
 */

void SYS_Initialize ( void* data )
{
    /* Core Processor Initialization */
    SYS_CLK_Initialize( NULL );
    sysObj.sysDevcon = SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*)&sysDevconInit);
    SYS_DEVCON_PerformanceConfig(SYS_CLK_SystemFrequencyGet());
    SYS_DEVCON_JTAGDisable();
    SYS_PORTS_Initialize();
    /* Board Support Package Initialization */
    BSP_Initialize();        

    /* Initialize Drivers */


    /*Initialize PMP0 */
    DRV_PMP0_Initialize();
    DRV_PMP0_ModeConfig();

    DRV_GFX_S1D13517_Initialize(GFX_INDEX_0, (SYS_MODULE_INIT*)&drvGfxInit);
    sysObj.drvAdc10bit = DRV_TOUCH_ADC10BIT_Initialize(DRV_TOUCH_INDEX_0, (SYS_MODULE_INIT *)&drvAdc10bitInitData);


    /* Initialize System Services */

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();

    /*** Message Service Initialization Code ***/
    msg0Init.nQSizes = queuePriorities0;
    sysObj.sysMsg0 = SYS_MSG_Initialize(SYS_MSG_0, (SYS_OBJ_HANDLE)&msg0Init);
        sysObj.sysTouchObject0 = SYS_TOUCH_Initialize(SYS_TOUCH_INDEX_0, (SYS_MODULE_INIT*)&sysTouchInit0);

  
    /* Initialize Middleware */

    sysObj.gfxObject0 = GFX_Initialize(GFX_INDEX_0, (SYS_MODULE_INIT *)&gfxInit0);



    /* Enable Global Interrupts */
    SYS_INT_Enable();

    /* Initialize the Application */
    APP_Initialize();
}


/*******************************************************************************
 End of File
*/

