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

#pragma config DEBUG =      OFF
#pragma config JTAGEN =     ON
#pragma config ICESEL =     ICS_PGx2
#pragma config TRCEN =      ON
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config SMCLR =      MCLR_NORM
#pragma config SOSCGAIN =   GAIN_2X
#pragma config SOSCBOOST =  ON
#pragma config POSCGAIN =   GAIN_2X
#pragma config POSCBOOST =  ON
#pragma config EJTAGBEN =   NORMAL
#pragma config CP =         OFF

/*** DEVCFG1 ***/

#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF
#pragma config POSCMOD =    EC
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSECME
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     NORMAL
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF
/*** DEVCFG2 ***/

#pragma config FPLLIDIV =   DIV_3
#pragma config FPLLRNG =    RANGE_5_10_MHZ
#pragma config FPLLICLK =   PLL_POSC
#pragma config FPLLMULT =   MUL_50
#pragma config FPLLODIV =   DIV_2
#pragma config UPLLFSEL =   FREQ_24MHZ
/*** DEVCFG3 ***/

#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     OFF
#pragma config PGL1WAY =    OFF
#pragma config PMDL1WAY =   OFF
#pragma config IOL1WAY =    OFF
#pragma config FUSBIDIO =   OFF

/*** BF1SEQ0 ***/

#pragma config TSEQ =       0xffff
#pragma config CSEQ =       0xffff
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

GFX_COLOR __attribute__((coherent, aligned(16))) frameBuffer[1][DISP_HOR_RESOLUTION][DISP_VER_RESOLUTION];
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_I2C Initialization Data">
// *****************************************************************************
/* I2C Driver Initialization Data
*/

const DRV_I2C_INIT drvI2C0InitData =
{
    .i2cId = DRV_I2C_PERIPHERAL_ID_IDX0,
    .i2cPerph = DRV_I2C_BIT_BANG_IDX0,
    .i2cMode = DRV_I2C_OPERATION_MODE_IDX0,
    .portSCL = DRV_SCL_PORT_IDX0,
	.pinSCL  = DRV_SCL_PIN_POSITION_IDX0,
	.portSDA = DRV_SDA_PORT_IDX0,
	.pinSDA  = DRV_SDA_PIN_POSITION_IDX0,
    .baudRate = DRV_I2C_BIT_BANG_BAUD_RATE_IDX0,
	.tmrSource = DRV_I2C_BIT_BANG_TMR_MODULE_IDX0,
	.tmrInterruptSource = DRV_I2C_BIT_BANG_INT_SRC_IDX0,
    .busspeed = DRV_I2C_SLEW_RATE_CONTROL_IDX0,
    .buslevel = DRV_I2C_SMBus_SPECIFICATION_IDX0,
};




// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_Timer Initialization Data">
/*** TMR Driver Initialization Data ***/

const DRV_TMR_INIT drvTmr0InitData =
{
    .moduleInit.sys.powerState = DRV_TMR_POWER_STATE_IDX0,
    .tmrId = DRV_TMR_PERIPHERAL_ID_IDX0,
    .clockSource = DRV_TMR_CLOCK_SOURCE_IDX0, 
    .prescale = DRV_TMR_PRESCALE_IDX0,
    .mode = DRV_TMR_OPERATION_MODE_16_BIT,
    .interruptSource = DRV_TMR_INTERRUPT_SOURCE_IDX0,
    .asyncWriteEnable = false,
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_TOUCH_MTCH6301 Initialization Data">
/*** MTCH6301 Driver Initialization Data ***/

const DRV_TOUCH_INIT drvTouchInitData =
{
    .moduleInit                  = {0},
    .touchId                     = DRV_TOUCH_INDEX_0,
    .drvInitialize               = NULL,
    .drvOpen                     = DRV_I2C_Open,
    .orientation                 = DISP_ORIENTATION,
    .horizontalResolution        = DISP_HOR_RESOLUTION,
    .verticalResolution          = DISP_VER_RESOLUTION,
    .pReadFunc                   = NULL,
    .pWriteFunc                  = NULL,
    .pSectorErase                = NULL,
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
//<editor-fold defaultstate="collapsed" desc="SYS_DMA Initialization Data">
/*** System DMA Initialization Data ***/

const SYS_DMA_INIT sysDmaInit =
{
	.sidl = SYS_DMA_SIDL_DISABLE,

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
    .drvInitialize           = DRV_TOUCH_MTCH6301_Initialize,
    .drvOpen                 = DRV_TOUCH_MTCH6301_Open,
    .drvTouchStatus          = DRV_TOUCH_MTCH6301_TouchStatus,
    .drvTouchDataRead        = DRV_TOUCH_MTCH6301_TouchDataRead,
    .drvTouchGetX            = DRV_TOUCH_MTCH6301_TouchGetX,
    .drvTouchGetY            = DRV_TOUCH_MTCH6301_TouchGetY,
    .drvTouchPenGet          = NULL,
    .orientation             = DISP_ORIENTATION,
    .horizontalResolution    = DISP_HOR_RESOLUTION,
    .verticalResolution      = DISP_VER_RESOLUTION,
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_TMR Initialization Data">
/*** TMR Service Initialization Data ***/
const SYS_TMR_INIT sysTmrInitData =
{
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},
    .drvIndex = DRV_TMR_INDEX_0,
    .tmrFreq = 1000, 
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
    .drvOpen          = DRV_GFX_LCC_Open,
    .drvInterfaceSet  = DRV_GFX_LCC_InterfaceSet,
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
    sysObj.drvI2C0 = DRV_I2C_Initialize(DRV_I2C_INDEX_0, (SYS_MODULE_INIT *)&drvI2C0InitData);


    SYS_INT_VectorPrioritySet(INT_VECTOR_T9, INT_PRIORITY_LEVEL3);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T9, INT_SUBPRIORITY_LEVEL0);


    sysObj.sysDma = SYS_DMA_Initialize((SYS_MODULE_INIT *)&sysDmaInit);
    SYS_INT_VectorPrioritySet(INT_VECTOR_DMA0, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_DMA0, INT_SUBPRIORITY_LEVEL0);

    SYS_INT_SourceEnable(INT_SOURCE_DMA_0);


    DRV_GFX_LCC_FrameBufferAddressSet(&frameBuffer);
    DRV_GFX_LCC_Initialize(GFX_INDEX_0, (SYS_MODULE_INIT*)&drvGfxInit);

    /* Setting priority for LCC Refresh ISR */
    SYS_INT_VectorPrioritySet(INT_VECTOR_DMA1, INT_PRIORITY_LEVEL7);


    sysObj.drvTmr0 = DRV_TMR_Initialize(DRV_TMR_INDEX_0, (SYS_MODULE_INIT *)&drvTmr0InitData);

    SYS_INT_VectorPrioritySet(INT_VECTOR_T1, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T1, INT_SUBPRIORITY_LEVEL0);
 
 
     sysObj.drvMtch6301 = DRV_TOUCH_MTCH6301_Initialize(DRV_TOUCH_MTCH6301_INDEX_0,
                                    (SYS_MODULE_INIT *)&drvTouchInitData);

    /* Initialize System Services */

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();

    /*Setup the INT_SOURCE_EXTERNAL_1 and Enable it*/
    SYS_INT_VectorPrioritySet(INT_VECTOR_INT1, INT_PRIORITY_LEVEL5);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_INT1, INT_SUBPRIORITY_LEVEL0);
    SYS_INT_ExternalInterruptTriggerSet(INT_EXTERNAL_INT_SOURCE1,INT_EDGE_TRIGGER_RISING);
    SYS_INT_SourceEnable(INT_SOURCE_EXTERNAL_1);






    /*** Message Service Initialization Code ***/
    msg0Init.nQSizes = queuePriorities0;
    sysObj.sysMsg0 = SYS_MSG_Initialize(SYS_MSG_0, (SYS_OBJ_HANDLE)&msg0Init);
        sysObj.sysTouchObject0 = SYS_TOUCH_Initialize(SYS_TOUCH_INDEX_0, (SYS_MODULE_INIT*)&sysTouchInit0);


    /*** TMR Service Initialization Code ***/
    sysObj.sysTmr  = SYS_TMR_Initialize(SYS_TMR_INDEX_0, (const SYS_MODULE_INIT  * const)&sysTmrInitData);
  
    /* Initialize Middleware */

    sysObj.gfxObject0 = GFX_Initialize(GFX_INDEX_0, (SYS_MODULE_INIT *)&gfxInit0);


    /* Initialize the GFX HGC */
    GFX_HGC_Initialize();

    /* Enable Global Interrupts */
    SYS_INT_Enable();

    /* Initialize the Application */
    APP_Initialize();
}


/*******************************************************************************
 End of File
*/

