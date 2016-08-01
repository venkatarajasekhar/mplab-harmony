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

<#include "/utilities/mhc/templates/freemarker_functions.ftl">
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
<#if LIST_SYSTEM_INIT_C_CONFIG_BITS_INITIALIZATION?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_CONFIG_BITS_INITIALIZATION/>
</#if>
// <editor-fold defaultstate="collapsed" desc="Configuration Bits">

/*** DEVCFG0 ***/

<#if CONFIG_DEBUG?has_content>
#pragma config DEBUG =      ${CONFIG_DEBUG}
</#if>
<#if CONFIG_JTAGEN?has_content>
#pragma config JTAGEN =     ${CONFIG_JTAGEN}
</#if>
<#if CONFIG_ICESEL?has_content>
#pragma config ICESEL =     ${CONFIG_ICESEL}
</#if>
<#if CONFIG_TRCEN?has_content>
#pragma config TRCEN =      ${CONFIG_TRCEN}
</#if>
<#if CONFIG_BOOTISA?has_content>
#pragma config BOOTISA =    ${CONFIG_BOOTISA}
</#if>
<#if CONFIG_FECCCON?has_content>
#pragma config FECCCON =    ${CONFIG_FECCCON}
</#if>
<#if CONFIG_FSLEEP?has_content>
#pragma config FSLEEP =     ${CONFIG_FSLEEP}
</#if>
<#if CONFIG_DBGPER?has_content>
#pragma config DBGPER =     ${CONFIG_DBGPER}
</#if>
<#if CONFIG_SMCLR?has_content>
#pragma config SMCLR =      ${CONFIG_SMCLR}
</#if>
<#if CONFIG_SOSCGAIN?has_content>
#pragma config SOSCGAIN =   ${CONFIG_SOSCGAIN}
</#if>
<#if CONFIG_SOSCBOOST?has_content>
#pragma config SOSCBOOST =  ${CONFIG_SOSCBOOST}
</#if>
<#if CONFIG_POSCGAIN?has_content>
#pragma config POSCGAIN =   ${CONFIG_POSCGAIN}
</#if>
<#if CONFIG_POSCBOOST?has_content>
#pragma config POSCBOOST =  ${CONFIG_POSCBOOST}
</#if>
<#if CONFIG_EJTAGBEN?has_content>
#pragma config EJTAGBEN =   ${CONFIG_EJTAGBEN}
</#if>
<#if CONFIG_PWP?has_content>
#pragma config PWP =        ${CONFIG_PWP}
</#if>
<#if CONFIG_BWP?has_content>
#pragma config BWP =        ${CONFIG_BWP}
</#if>
<#if CONFIG_CP?has_content>
#pragma config CP =         ${CONFIG_CP}
</#if>
<#if CONFIG_TDOEN?has_content>
#pragma config TDOEN =         ${CONFIG_TDOEN}
</#if>
<#if CONFIG_TROEN?has_content>
#pragma config TROEN =         ${CONFIG_TROEN}
</#if>
<#if CONFIG_USBSSEN?has_content>
#pragma config USBSSEN =         ${CONFIG_USBSSEN}
</#if>
<#if CONFIG_PGLOCK?has_content>
#pragma config PGLOCK =         ${CONFIG_PGLOCK}
</#if>
<#if CONFIG_PMDLOCK?has_content>
#pragma config PMDLOCK =         ${CONFIG_PMDLOCK}
</#if>
<#if CONFIG_IOLOCK?has_content>
#pragma config IOLOCK =         ${CONFIG_IOLOCK}
</#if>
<#if CONFIG_CFGLOCK?has_content>
#pragma config CFGLOCK =         ${CONFIG_CFGLOCK}
</#if>
<#if CONFIG_OC_ACLK?has_content>
#pragma config OC_ACLK =         ${CONFIG_OC_ACLK}
</#if>
<#if CONFIG_IC_ACLK?has_content>
#pragma config IC_ACLK =         ${CONFIG_IC_ACLK}
</#if>
<#if CONFIG_EPGMCLK?has_content>
#pragma config EPGMCLK =         ${CONFIG_EPGMCLK}
</#if>

/*** DEVCFG1 ***/

<#if CONFIG_FNOSC?has_content>
#pragma config FNOSC =      ${CONFIG_FNOSC}
</#if>
<#if CONFIG_DMTINTV?has_content>
#pragma config DMTINTV =    ${CONFIG_DMTINTV}
</#if>
<#if CONFIG_FSOSCEN?has_content>
#pragma config FSOSCEN =    ${CONFIG_FSOSCEN}
</#if>
<#if CONFIG_IESO?has_content>
#pragma config IESO =       ${CONFIG_IESO}
</#if>
<#if CONFIG_POSCMOD?has_content>
#pragma config POSCMOD =    ${CONFIG_POSCMOD}
</#if>
<#if CONFIG_OSCIOFNC?has_content>
#pragma config OSCIOFNC =   ${CONFIG_OSCIOFNC}
</#if>
<#if CONFIG_FPBDIV?has_content>
#pragma config FPBDIV =     ${CONFIG_FPBDIV}
</#if>
<#if CONFIG_FCKSM?has_content>
#pragma config FCKSM =      ${CONFIG_FCKSM}
</#if>
<#if CONFIG_WDTPS?has_content>
#pragma config WDTPS =      ${CONFIG_WDTPS}
</#if>
<#if CONFIG_WDTSPGM?has_content>
#pragma config WDTSPGM =    ${CONFIG_WDTSPGM}
</#if>
<#if CONFIG_FWDTEN?has_content>
#pragma config FWDTEN =     ${CONFIG_FWDTEN}
</#if>
<#if CONFIG_WINDIS?has_content>
#pragma config WINDIS =     ${CONFIG_WINDIS}
</#if>
<#if CONFIG_FWDTWINSZ?has_content>
#pragma config FWDTWINSZ =  ${CONFIG_FWDTWINSZ}
</#if>
<#if CONFIG_DMTCNT?has_content>
#pragma config DMTCNT =     ${CONFIG_DMTCNT}
</#if>
<#if CONFIG_FDMTEN?has_content>
#pragma config FDMTEN =     ${CONFIG_FDMTEN}
</#if>
<#if CONFIG_HSUARTEN?has_content>
#pragma config HSUARTEN =     ${CONFIG_HSUARTEN}
</#if>
<#if CONFIG_CLASSBDIS?has_content>
#pragma config CLASSBDIS =     ${CONFIG_CLASSBDIS}
</#if>
<#if CONFIG_USBIDIO?has_content>
#pragma config USBIDIO =     ${CONFIG_USBIDIO}
</#if>
<#if CONFIG_VBUSIO?has_content>
#pragma config VBUSIO =     ${CONFIG_VBUSIO}
</#if>
<#if CONFIG_WDTPSS?has_content>
#pragma config WDTPSS =     ${CONFIG_WDTPSS}
</#if>
/*** DEVCFG2 ***/

<#if CONFIG_FPLLIDIV?has_content>
#pragma config FPLLIDIV =   ${CONFIG_FPLLIDIV}
</#if>
<#if CONFIG_FPLLRNG?has_content>
#pragma config FPLLRNG =    ${CONFIG_FPLLRNG}
</#if>
<#if CONFIG_FPLLICLK?has_content>
#pragma config FPLLICLK =   ${CONFIG_FPLLICLK}
</#if>
<#if CONFIG_FPLLMULT?has_content>
#pragma config FPLLMULT =   ${CONFIG_FPLLMULT}
</#if>
<#if CONFIG_FPLLMUL?has_content>
#pragma config FPLLMUL =    ${CONFIG_FPLLMUL}
</#if>
<#if CONFIG_FPLLODIV?has_content>
#pragma config FPLLODIV =   ${CONFIG_FPLLODIV}
</#if>
<#if CONFIG_VBATBOREN?has_content>
#pragma config VBATBOREN =  ${CONFIG_VBATBOREN}
</#if>
<#if CONFIG_DSBOREN?has_content>
#pragma config DSBOREN =    ${CONFIG_DSBOREN}
</#if>
<#if CONFIG_DSWDTPS?has_content>
#pragma config DSWDTPS =    ${CONFIG_DSWDTPS}
</#if>
<#if CONFIG_DSWDTOSC?has_content>
#pragma config DSWDTOSC =   ${CONFIG_DSWDTOSC}
</#if>
<#if CONFIG_DSWDTEN?has_content>
#pragma config DSWDTEN =    ${CONFIG_DSWDTEN}
</#if>
<#if CONFIG_FDSEN?has_content>
#pragma config FDSEN =      ${CONFIG_FDSEN}
</#if>
<#if CONFIG_UPLLFSEL?has_content>
#pragma config UPLLFSEL =   ${CONFIG_UPLLFSEL}
</#if>
<#if CONFIG_UPLLIDIV?has_content>
#pragma config UPLLIDIV =   ${CONFIG_UPLLIDIV}
</#if>
<#if CONFIG_UPLLEN?has_content>
#pragma config UPLLEN =     ${CONFIG_UPLLEN}
</#if>
<#if CONFIG_LPOSCEN?has_content>
#pragma config LPOSCEN =     ${CONFIG_LPOSCEN}
</#if>
<#if CONFIG_SOSCSEL?has_content>
#pragma config SOSCSEL =     ${CONFIG_SOSCSEL}
</#if>
<#if CONFIG_CKSWEN?has_content>
#pragma config CKSWEN =     ${CONFIG_CKSWEN}
</#if>
<#if CONFIG_FSCMEN?has_content>
#pragma config FSCMEN =     ${CONFIG_FSCMEN}
</#if>
<#if CONFIG_WDTPSR?has_content>
#pragma config WDTPSR =     ${CONFIG_WDTPSR}
</#if>
<#if CONFIG_WDT_EN?has_content>
#pragma config WDT_EN =     ${CONFIG_WDT_EN}
</#if>
<#if CONFIG_WINSZ?has_content>
#pragma config WINSZ =     ${CONFIG_WINSZ}
</#if>
<#if CONFIG_DMT_EN?has_content>
#pragma config DMT_EN =     ${CONFIG_DMT_EN}
</#if>
/*** DEVCFG3 ***/

<#if CONFIG_USERID?has_content>
#pragma config USERID =     ${CONFIG_USERID}
</#if>
<#if CONFIG_EXTDDRSIZE?has_content>
#pragma config EXTDDRSIZE = ${CONFIG_EXTDDRSIZE}
</#if>
<#if CONFIG_FSRSSEL?has_content>
#pragma config FSRSSEL =    ${CONFIG_FSRSSEL}
</#if>
<#if CONFIG_FMIIE?has_content>
#pragma config FMIIE =      ${CONFIG_FMIIE}
</#if>
<#if CONFIG_FMIIEN?has_content>
<#if CONFIG_FMIIEN != "">
#pragma config FMIIEN =     ${CONFIG_FMIIEN}
</#if>
</#if>
<#if CONFIG_FETHIO?has_content>
<#if CONFIG_FETHIO != "">
#pragma config FETHIO =     ${CONFIG_FETHIO}
</#if>
</#if>
<#if CONFIG_FUSBIDIO2?has_content>
#pragma config FUSBIDIO2 =   ${CONFIG_FUSBIDIO2}
</#if>
<#if CONFIG_FVBUSIO2?has_content>
#pragma config FVBUSIO2 =  ${CONFIG_FVBUSIO2}
</#if>
<#if CONFIG_PGL1WAY?has_content>
#pragma config PGL1WAY =    ${CONFIG_PGL1WAY}
</#if>
<#if CONFIG_PMDL1WAY?has_content>
#pragma config PMDL1WAY =   ${CONFIG_PMDL1WAY}
</#if>
<#if CONFIG_IOL1WAY?has_content>
#pragma config IOL1WAY =    ${CONFIG_IOL1WAY}
</#if>
<#if CONFIG_FCANIO?has_content>
#pragma config FCANIO =     ${CONFIG_FCANIO}
</#if>
<#if CONFIG_FUSBIDIO?has_content>
#pragma config FUSBIDIO =   ${CONFIG_FUSBIDIO}
</#if>
<#if CONFIG_FVBUSONIO?has_content>
#pragma config FVBUSONIO =  ${CONFIG_FVBUSONIO}
</#if>
<#if CONFIG_FUSBIDIO1?has_content>
#pragma config FUSBIDIO1 =   ${CONFIG_FUSBIDIO1}
</#if>
<#if CONFIG_FVBUSIO1?has_content>
#pragma config FVBUSIO1 =  ${CONFIG_FVBUSIO1}
</#if>
<#if CONFIG_USER_ID?has_content>
#pragma config USER_ID =  ${CONFIG_USER_ID}
</#if>
<#if CONFIG_SWDTPS?has_content>

/*** DEVCFG4 ***/

#pragma config SWDTPS = ${CONFIG_SWDTPS}
</#if>
<#if CONFIG_TSEQ?has_content>

/*** BF1SEQ0 ***/

#pragma config TSEQ =       ${CONFIG_TSEQ}
</#if>
<#if CONFIG_CSEQ?has_content>
#pragma config CSEQ =       ${CONFIG_CSEQ}
</#if>
<#if CONFIG_BOOTSEL?has_content>
#pragma config BOOTSEL =       ${CONFIG_BOOTSEL}
</#if>
// </editor-fold>

// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
<#if LIST_SYSTEM_INIT_C_DRIVER_INITIALIZATION_DATA?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_DRIVER_INITIALIZATION_DATA/>
</#if>

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
<#if LIST_SYSTEM_INIT_C_MODULE_INITIALIZATION_DATA?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_MODULE_INITIALIZATION_DATA/>
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
<#if LIST_SYSTEM_INIT_C_LIBRARY_INITIALIZATION_DATA?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_LIBRARY_INITIALIZATION_DATA/>
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Static Initialization Functions
// *****************************************************************************
// *****************************************************************************

<#if CONFIG_USE_SYS_CLK == true>
  <#if CONFIG_SYS_CLK_MODE = "DYNAMIC">
    <#include "/framework/system/clk/templates/sys_clk_init.c.ftl">
  </#if>
</#if>

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
<#if LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DATA?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DATA/>
</#if>
<#if (CONFIG_3RDPARTY_RTOS_USED == "uC/OS-III")>
    OS_ERR os_err;
    
</#if>
<#if (CONFIG_3RDPARTY_RTOS_USED == "uC/OS-III")>

    /*initialize RTOS */
    CPU_Init();
    OSInit(&os_err);
</#if>
<#if (CONFIG_3RDPARTY_RTOS_USED == "uC/OS-II")>

    /*initialize RTOS */
    OSInit();
</#if>
<#if (CONFIG_3RDPARTY_RTOS_USED == "embOS")>
    /*initialize RTOS */
    OS_InitKern();
    OS_InitHW();
</#if>
    /* Core Processor Initialization */
<#if LIST_SYSTEM_INIT_C_SYS_INITIALIZE_CORE?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_SYS_INITIALIZE_CORE/>
</#if>
<#if CONFIG_USE_SYS_CLK == true>
  <#if CONFIG_SYS_CLK_MODE = "DYNAMIC">
    SYS_CLK_Initialize(&sysClkInit);
    SYS_CLK_DYNAMIC_Initialize();
  <#else>
    SYS_CLK_Initialize( NULL );
  </#if>
</#if>
<#if CONFIG_USE_SYS_DEVCON == true>
    sysObj.sysDevcon = SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*)&sysDevconInit);
  <#if CONFIG_PIC32WK == false>
    SYS_DEVCON_PerformanceConfig(SYS_CLK_SystemFrequencyGet());
  </#if>
  <#if CONFIG_SYS_DEVCON_USE_JTAG == true>
    SYS_DEVCON_JTAGEnable();
  <#else>
    <#if CONFIG_JTAGEN?has_content>
      <#if CONFIG_JTAGEN == "ON">
    SYS_DEVCON_JTAGDisable();
      </#if>
    <#else>
    SYS_DEVCON_JTAGDisable();
    </#if>
  </#if>
  <#if CONFIG_SYS_DEVCON_USE_TRACE == true>
    SYS_DEVCON_TraceEnable();
  </#if>
</#if>
<#if CONFIG_USE_SYS_PORTS == true>
    SYS_PORTS_Initialize();
</#if>
<#if CONFIG_USE_BSP == true>
    <#include "/bsp/templates/bsp_init.c.ftl">
</#if>

<#if (CONFIG_3RDPARTY_RTOS_USED == "uC/OS-III") || (CONFIG_3RDPARTY_RTOS_USED == "ThreadX") || (CONFIG_3RDPARTY_RTOS_USED == "uC/OS-II")>
    /*
     * core timer is enabled in crt0.S, file included by XC32 compiler,
     * responsible for initializing C runtime environment.  The reset vector
     * jumps to the entry of crt0.S.  crt0.S will enable core timer to start
     * counting.  Core timer increments every other CPU clock cycle.  This is
     * designed as part of the MIPS core.
     *
     * The CPU is set to run at 200MHz, per configuartion words, see
     * config_words.c.  Therefore, the core timer counts as a rate of 10ns
     * (100MHz).
     *
     */
    /*setup core timer priority, IPL = 2*/
    PLIB_INT_VectorPrioritySet(INT_ID_0,INT_VECTOR_CT,INT_PRIORITY_LEVEL2);
    /*setup CP0 compare register, to yield a 1ms timer tick*/
    __builtin_mtc0(11,0,(SYS_CLK_SystemFrequencyGet())/(2*1000));
    /*make sure the core timer starts counting from zero*/
    __builtin_mtc0(9,0,0);
    /*clear core timer interrupt flag, incase it has been triggered since
      counting started during crt0.S*/
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_CORE);
    /*enable core timer interrupt*/
    PLIB_INT_SourceEnable(INT_ID_0,INT_SOURCE_TIMER_CORE);
</#if>
    /* Initialize Drivers */
<#if LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DEPENDENT_DRIVERS?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DEPENDENT_DRIVERS/>
</#if>
<#if LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DRIVERS?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DRIVERS/>
</#if>

    /* Initialize System Services */
<#if LIST_SYSTEM_INIT_C_INITIALIZE_SYSTEM_SERVICES?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_INITIALIZE_SYSTEM_SERVICES/>
</#if>
  
    /* Initialize Middleware */
<#if LIST_SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE/>
</#if>

  <#if CONFIG_USE_SYS_INT == true && !CONFIG_USE_3RDPARTY_RTOS>
    /* Enable Global Interrupts */
    SYS_INT_Enable();
  </#if>

    /* Initialize the Application */
<#if LIST_SYSTEM_INIT_C_SYS_INITIALIZE_APP?has_content>
<@mhc_expand_list list=LIST_SYSTEM_INIT_C_SYS_INITIALIZE_APP/>
</#if>
  <#if CONFIG_APP_IDX_0?has_content>
    ${CONFIG_APP_NAME_0?upper_case}_Initialize();
  <#else>
    App_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_1?has_content>
  <#if CONFIG_APP_IDX_1 == true>
    ${CONFIG_APP_NAME_1?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_2 == true>
    ${CONFIG_APP_NAME_2?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_3 == true>
    ${CONFIG_APP_NAME_3?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_4 == true>
    ${CONFIG_APP_NAME_4?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_5 == true>
    ${CONFIG_APP_NAME_5?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_6 == true>
    ${CONFIG_APP_NAME_6?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_7 == true>
    ${CONFIG_APP_NAME_7?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_8 == true>
    ${CONFIG_APP_NAME_8?upper_case}_Initialize();
  </#if>
  <#if CONFIG_APP_IDX_9 == true>
    ${CONFIG_APP_NAME_9?upper_case}_Initialize();
  </#if>
  </#if>
  <#if CONFIG_USE_TEST_HARNESS == true>
    <#include "/framework/test/templates/system_init.c.call.ftl">
  </#if>
}


/*******************************************************************************
 End of File
*/

