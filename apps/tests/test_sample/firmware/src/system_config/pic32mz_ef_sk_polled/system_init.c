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
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx2
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     ALLOW_PG2
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
#pragma config DMTCNT =     DMT9
#pragma config FDMTEN =     OFF
/*** DEVCFG2 ***/

#pragma config FPLLIDIV =   DIV_3
#pragma config FPLLRNG =    RANGE_8_16_MHZ
#pragma config FPLLICLK =   PLL_POSC
#pragma config FPLLMULT =   MUL_50
#pragma config FPLLODIV =   DIV_2
#pragma config UPLLFSEL =   FREQ_24MHZ
/*** DEVCFG3 ***/

#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     OFF
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON
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
// <editor-fold defaultstate="collapsed" desc="Sample Library Initialization Data">
/******************************************************************************
  Sample Library Module Initialization Data
*/

const SAMPLE_MODULE_INIT_DATA sampleModule0InitData =
{
    .moduleInit     = {SAMPLE_MODULE_POWER_STATE_IDX0},
    .dataSome       = SAMPLE_MODULE_SOME_DATA_IDX0
};

const SAMPLE_MODULE_INIT_DATA sampleModule1InitData =
{
    .moduleInit = {SAMPLE_MODULE_POWER_STATE_IDX1},
    .dataSome   = SAMPLE_MODULE_SOME_DATA_IDX1
};

// </editor-fold>
//<editor-fold defaultstate="collapsed" desc="SYS_DEVCON Initialization Data">
/*******************************************************************************
  Device Control System Service Initialization Data
*/

const SYS_DEVCON_INIT sysDevconInit =
{
    .moduleInit = {0},
};

// </editor-fold>
/******************************************************************************
  Test Harness Initialization Data
  
  <editor-fold defaultstate="collapsed"
   desc="Test Harness Initialization Data">
*/

/* Library Under Test Data */
static LIBRARY_UNDER_TEST testSample0LUTdata = 
{
    .initialize         = SAMPLE_Initialize,
    .reinitialize       = SAMPLE_Reinitialize,
    .deinitialize       = SAMPLE_Deinitialize,
    .status             = SAMPLE_Status,
    .numberOfInstances  = 2,
    .numberOfTasks      = 1,
    .tasks              = {
                              SAMPLE_Tasks,
                              NULL,
                              NULL,
                              NULL,
                              NULL
                          },
    .initData           = {
                              (SYS_MODULE_INIT *)&sampleModule0InitData,
                              (SYS_MODULE_INIT *)&sampleModule1InitData,
                              (SYS_MODULE_INIT *)NULL
                          }
};

/* Sample Functional Test Initialization Data */
TEST_SAMPLE_FUNCTIONAL_INIT_DATA testSampleInit = 
{
    .modulesInitData =
    {
        &sampleModule0InitData,
        &sampleModule1InitData
    }
};

/* Test List */
static TEST_DATA testList[] = 
{
    {
        .name       = "Sample Module Functional Test 0",
        .initialize = TEST_SampleFunctionalInitialize,
        .tasks      = {
                        TEST_SampleFunctionalTasks,
                        TEST_SampleFunctionalTasks,
                      },
        .start      = TEST_SampleFunctionalStart,
        .status     = TEST_SampleFunctionalStatus,
        .index      = 0,
        .initData   = (SYS_MODULE_INIT *)&testSampleInit,
        .library    = &testSample0LUTdata
    }
};

/* Test Harness Initialization Structure */
static const TEST_INIT_DATA testData =
{
    .numberOfTests  = sizeof(testList)/sizeof(TEST_DATA),
    .tests          = testList
};

// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************

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

    /* Initialize Drivers */

    /* Initialize System Services */

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();
  
    /* Initialize Middleware */

    /* Enable Global Interrupts */
    SYS_INT_Enable();

    /* Initialize the Application */
    APP_Initialize();

    /* Initialize the test harness. */
    TEST_Initialize(&testData);
}


/*******************************************************************************
 End of File
*/

