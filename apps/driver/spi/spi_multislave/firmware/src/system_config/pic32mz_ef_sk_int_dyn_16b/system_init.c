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
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx2
#pragma config TRCEN =      ON
#pragma config BOOTISA =    MICROMIPS
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
#pragma config FCKSM =      CSDCMD
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
#pragma config FETHIO =     ON
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON
#pragma config FUSBIDIO =   ON

/*** BF1SEQ0 ***/

#pragma config TSEQ =       0x0000
#pragma config CSEQ =       0xffff
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_SPI Initialization Data"> 
 /*** SPI Driver Initialization Data ***/
  /*** Index 0  ***/
 DRV_SPI_INIT drvSpi0InitData =
 {
    .spiId = DRV_SPI_SPI_ID_IDX0,
    .taskMode = DRV_SPI_TASK_MODE_IDX0,
    .spiMode = DRV_SPI_SPI_MODE_IDX0,
    .allowIdleRun = DRV_SPI_ALLOW_IDLE_RUN_IDX0,
    .spiProtocolType = DRV_SPI_SPI_PROTOCOL_TYPE_IDX0,
    .commWidth = DRV_SPI_COMM_WIDTH_IDX0,
    .baudClockSource = DRV_SPI_CLOCK_SOURCE_IDX0,
    .spiClk = DRV_SPI_SPI_CLOCK_IDX0,
    .baudRate = DRV_SPI_BAUD_RATE_IDX0,
    .bufferType = DRV_SPI_BUFFER_TYPE_IDX0,
    .clockMode = DRV_SPI_CLOCK_MODE_IDX0,
    .inputSamplePhase = DRV_SPI_INPUT_PHASE_IDX0,
    .txInterruptSource = DRV_SPI_TX_INT_SOURCE_IDX0,
    .rxInterruptSource = DRV_SPI_RX_INT_SOURCE_IDX0,
    .errInterruptSource = DRV_SPI_ERROR_INT_SOURCE_IDX0,
    .queueSize = DRV_SPI_QUEUE_SIZE_IDX0,
    .jobQueueReserveSize = DRV_SPI_RESERVED_JOB_IDX0,
 };
  /*** Index 1  ***/
 DRV_SPI_INIT drvSpi1InitData =
 {
    .spiId = DRV_SPI_SPI_ID_IDX1,
    .taskMode = DRV_SPI_TASK_MODE_IDX1,
    .spiMode = DRV_SPI_SPI_MODE_IDX1,
    .allowIdleRun = DRV_SPI_ALLOW_IDLE_RUN_IDX1,
    .spiProtocolType = DRV_SPI_SPI_PROTOCOL_TYPE_IDX1,
    .spiSlaveSSPin = DRV_SPI_SPI_USE_SS_FOR_SLAVE_IDX1,
    .commWidth = DRV_SPI_COMM_WIDTH_IDX1,
    .baudClockSource = DRV_SPI_CLOCK_SOURCE_IDX1,
    .spiClk = DRV_SPI_SPI_CLOCK_IDX1,
    .baudRate = DRV_SPI_BAUD_RATE_IDX1,
    .bufferType = DRV_SPI_BUFFER_TYPE_IDX1,
    .clockMode = DRV_SPI_CLOCK_MODE_IDX1,
    .inputSamplePhase = DRV_SPI_INPUT_PHASE_IDX1,
    .txInterruptSource = DRV_SPI_TX_INT_SOURCE_IDX1,
    .rxInterruptSource = DRV_SPI_RX_INT_SOURCE_IDX1,
    .errInterruptSource = DRV_SPI_ERROR_INT_SOURCE_IDX1,
    .queueSize = DRV_SPI_QUEUE_SIZE_IDX1,
    .jobQueueReserveSize = DRV_SPI_RESERVED_JOB_IDX1,
 };
  /*** Index 2  ***/
 DRV_SPI_INIT drvSpi2InitData =
 {
    .spiId = DRV_SPI_SPI_ID_IDX2,
    .taskMode = DRV_SPI_TASK_MODE_IDX2,
    .spiMode = DRV_SPI_SPI_MODE_IDX2,
    .allowIdleRun = DRV_SPI_ALLOW_IDLE_RUN_IDX2,
    .spiProtocolType = DRV_SPI_SPI_PROTOCOL_TYPE_IDX2,
    .spiSlaveSSPin = DRV_SPI_SPI_USE_SS_FOR_SLAVE_IDX2,
    .commWidth = DRV_SPI_COMM_WIDTH_IDX2,
    .baudClockSource = DRV_SPI_CLOCK_SOURCE_IDX2,
    .spiClk = DRV_SPI_SPI_CLOCK_IDX2,
    .baudRate = DRV_SPI_BAUD_RATE_IDX2,
    .bufferType = DRV_SPI_BUFFER_TYPE_IDX2,
    .clockMode = DRV_SPI_CLOCK_MODE_IDX2,
    .inputSamplePhase = DRV_SPI_INPUT_PHASE_IDX2,
    .txInterruptSource = DRV_SPI_TX_INT_SOURCE_IDX2,
    .rxInterruptSource = DRV_SPI_RX_INT_SOURCE_IDX2,
    .errInterruptSource = DRV_SPI_ERROR_INT_SOURCE_IDX2,
    .queueSize = DRV_SPI_QUEUE_SIZE_IDX2,
    .jobQueueReserveSize = DRV_SPI_RESERVED_JOB_IDX2,
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
    SYS_PORTS_Initialize();
    /* Board Support Package Initialization */
    BSP_Initialize();        

    /* Initialize Drivers */

    /*** SPI Driver Index 0 initialization***/

    SYS_INT_VectorPrioritySet(DRV_SPI_TX_INT_VECTOR_IDX0, DRV_SPI_TX_INT_PRIORITY_IDX0);
    SYS_INT_VectorSubprioritySet(DRV_SPI_TX_INT_VECTOR_IDX0, DRV_SPI_TX_INT_SUB_PRIORITY_IDX0);
    SYS_INT_VectorPrioritySet(DRV_SPI_RX_INT_VECTOR_IDX0, DRV_SPI_RX_INT_PRIORITY_IDX0);
    SYS_INT_VectorSubprioritySet(DRV_SPI_RX_INT_VECTOR_IDX0, DRV_SPI_RX_INT_SUB_PRIORITY_IDX0);
    SYS_INT_VectorPrioritySet(DRV_DRV_SPI_ERROR_INT_VECTOR_IDX0, DRV_SPI_ERROR_INT_PRIORITY_IDX0);
    SYS_INT_VectorSubprioritySet(DRV_DRV_SPI_ERROR_INT_VECTOR_IDX0, DRV_SPI_ERROR_INT_SUB_PRIORITY_IDX0);
    sysObj.spiObjectIdx0 = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (const SYS_MODULE_INIT  * const)&drvSpi0InitData);

    /*** SPI Driver Index 1 initialization***/

    SYS_INT_VectorPrioritySet(DRV_SPI_TX_INT_VECTOR_IDX1, DRV_SPI_TX_INT_PRIORITY_IDX1);
    SYS_INT_VectorSubprioritySet(DRV_SPI_TX_INT_VECTOR_IDX1, DRV_SPI_TX_INT_SUB_PRIORITY_IDX1);
    SYS_INT_VectorPrioritySet(DRV_SPI_RX_INT_VECTOR_IDX1, DRV_SPI_RX_INT_PRIORITY_IDX1);
    SYS_INT_VectorSubprioritySet(DRV_SPI_RX_INT_VECTOR_IDX1, DRV_SPI_RX_INT_SUB_PRIORITY_IDX1);
    SYS_INT_VectorPrioritySet(DRV_DRV_SPI_ERROR_INT_VECTOR_IDX1, DRV_SPI_ERROR_INT_PRIORITY_IDX1);
    SYS_INT_VectorSubprioritySet(DRV_DRV_SPI_ERROR_INT_VECTOR_IDX1, DRV_SPI_ERROR_INT_SUB_PRIORITY_IDX1);
    sysObj.spiObjectIdx1 = DRV_SPI_Initialize(DRV_SPI_INDEX_1, (const SYS_MODULE_INIT  * const)&drvSpi1InitData);

    /*** SPI Driver Index 2 initialization***/

    SYS_INT_VectorPrioritySet(DRV_SPI_TX_INT_VECTOR_IDX2, DRV_SPI_TX_INT_PRIORITY_IDX2);
    SYS_INT_VectorSubprioritySet(DRV_SPI_TX_INT_VECTOR_IDX2, DRV_SPI_TX_INT_SUB_PRIORITY_IDX2);
    SYS_INT_VectorPrioritySet(DRV_SPI_RX_INT_VECTOR_IDX2, DRV_SPI_RX_INT_PRIORITY_IDX2);
    SYS_INT_VectorSubprioritySet(DRV_SPI_RX_INT_VECTOR_IDX2, DRV_SPI_RX_INT_SUB_PRIORITY_IDX2);
    SYS_INT_VectorPrioritySet(DRV_DRV_SPI_ERROR_INT_VECTOR_IDX2, DRV_SPI_ERROR_INT_PRIORITY_IDX2);
    SYS_INT_VectorSubprioritySet(DRV_DRV_SPI_ERROR_INT_VECTOR_IDX2, DRV_SPI_ERROR_INT_SUB_PRIORITY_IDX2);
    sysObj.spiObjectIdx2 = DRV_SPI_Initialize(DRV_SPI_INDEX_2, (const SYS_MODULE_INIT  * const)&drvSpi2InitData);

    /* Initialize System Services */

    /*** Interrupt Service Initialization Code ***/
    SYS_INT_Initialize();
  
    /* Initialize Middleware */

    /* Enable Global Interrupts */
    SYS_INT_Enable();

    /* Initialize the Application */
    APP_Initialize();
}


/*******************************************************************************
 End of File
*/

