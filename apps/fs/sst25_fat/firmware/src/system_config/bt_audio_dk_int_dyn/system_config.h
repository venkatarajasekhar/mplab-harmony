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

    Created with MPLAB Harmony Version 2.01
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
#include "bsp.h"


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
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        80000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            40000000ul
#define SYS_CLK_UPLL_BEFORE_DIV2_FREQ       96000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         12000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       0ul
   // *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.01"
#define SYS_VERSION               20100

/*** File System Service Configuration ***/

#define SYS_FS_MEDIA_NUMBER         	1

#define SYS_FS_VOLUME_NUMBER		1

#define SYS_FS_AUTOMOUNT_ENABLE		false
#define SYS_FS_MAX_FILES	    	1
#define SYS_FS_MAX_FILE_SYSTEM_TYPE 	1
#define SYS_FS_MEDIA_MAX_BLOCK_SIZE  	512
#define SYS_FS_MEDIA_MANAGER_BUFFER_SIZE 512


#define SYS_FS_MEDIA_TYPE_IDX0 				
#define SYS_FS_TYPE_IDX0 					









/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true

/*** Ports System Service Configuration ***/
#define SYS_PORT_A_ANSEL        0x3900
#define SYS_PORT_A_TRIS         0xFD0F
#define SYS_PORT_A_LAT          0x0000
#define SYS_PORT_A_ODC          0x0400
#define SYS_PORT_A_CNPU         0x0403
#define SYS_PORT_A_CNPD         0x0000
#define SYS_PORT_A_CNEN         0x0000

#define SYS_PORT_B_ANSEL        0x0FFF
#define SYS_PORT_B_TRIS         0x7FFF
#define SYS_PORT_B_LAT          0x0000
#define SYS_PORT_B_ODC          0x0000
#define SYS_PORT_B_CNPU         0x7000
#define SYS_PORT_B_CNPD         0x0000
#define SYS_PORT_B_CNEN         0x0000

#define SYS_PORT_C_ANSEL        0xDFE1
#define SYS_PORT_C_TRIS         0xFFFD
#define SYS_PORT_C_LAT          0x0000
#define SYS_PORT_C_ODC          0x0000
#define SYS_PORT_C_CNPU         0x0000
#define SYS_PORT_C_CNPD         0x0000
#define SYS_PORT_C_CNEN         0x0000

#define SYS_PORT_D_ANSEL        0x0000
#define SYS_PORT_D_TRIS         0xE7F1
#define SYS_PORT_D_LAT          0x0000
#define SYS_PORT_D_ODC          0x0000
#define SYS_PORT_D_CNPU         0x0000
#define SYS_PORT_D_CNPD         0x0000
#define SYS_PORT_D_CNEN         0x0000

#define SYS_PORT_E_ANSEL        0xFC14
#define SYS_PORT_E_TRIS         0xFFFF
#define SYS_PORT_E_LAT          0x0000
#define SYS_PORT_E_ODC          0x0000
#define SYS_PORT_E_CNPU         0x0000
#define SYS_PORT_E_CNPD         0x0000
#define SYS_PORT_E_CNEN         0x0000

#define SYS_PORT_F_ANSEL        0xCEC0
#define SYS_PORT_F_TRIS         0xFFFF
#define SYS_PORT_F_LAT          0x0000
#define SYS_PORT_F_ODC          0x0000
#define SYS_PORT_F_CNPU         0x0000
#define SYS_PORT_F_CNPD         0x0000
#define SYS_PORT_F_CNEN         0x0000

#define SYS_PORT_G_ANSEL        0x0E3C
#define SYS_PORT_G_TRIS         0x7FFC
#define SYS_PORT_G_LAT          0x0000
#define SYS_PORT_G_ODC          0x0000
#define SYS_PORT_G_CNPU         0x0000
#define SYS_PORT_G_CNPD         0x0000
#define SYS_PORT_G_CNEN         0x0000


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

/*** SPI Driver Configuration ***/
#define DRV_SPI_NUMBER_OF_MODULES		2
/*** Driver Compilation and static configuration options. ***/
/*** Select SPI compilation units.***/
#define DRV_SPI_POLLED 				0
#define DRV_SPI_ISR 				1
#define DRV_SPI_MASTER 				1
#define DRV_SPI_SLAVE 				0
#define DRV_SPI_RM 					1
#define DRV_SPI_EBM 				0
#define DRV_SPI_8BIT 				1
#define DRV_SPI_16BIT 				0
#define DRV_SPI_32BIT 				0
#define DRV_SPI_DMA 				0

/*** SPI Driver Static Allocation Options ***/
#define DRV_SPI_INSTANCES_NUMBER 		1
#define DRV_SPI_CLIENTS_NUMBER 			1
#define DRV_SPI_ELEMENTS_PER_QUEUE 		10
/* SPI Driver Instance 0 Configuration */
#define DRV_SPI_SPI_ID_IDX0 				SPI_ID_2
#define DRV_SPI_TASK_MODE_IDX0 				DRV_SPI_TASK_MODE_ISR
#define DRV_SPI_SPI_MODE_IDX0				DRV_SPI_MODE_MASTER
#define DRV_SPI_ALLOW_IDLE_RUN_IDX0			false
#define DRV_SPI_SPI_PROTOCOL_TYPE_IDX0 		DRV_SPI_PROTOCOL_TYPE_STANDARD
#define DRV_SPI_COMM_WIDTH_IDX0 			SPI_COMMUNICATION_WIDTH_8BITS
#define DRV_SPI_CLOCK_SOURCE_IDX0 		    SPI_BAUD_RATE_PBCLK_CLOCK
#define DRV_SPI_SPI_CLOCK_IDX0 				CLK_BUS_PERIPHERAL_2
#define DRV_SPI_BAUD_RATE_IDX0 				10000000
#define DRV_SPI_BUFFER_TYPE_IDX0 			DRV_SPI_BUFFER_TYPE_STANDARD
#define DRV_SPI_CLOCK_MODE_IDX0 			DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL
#define DRV_SPI_INPUT_PHASE_IDX0 			SPI_INPUT_SAMPLING_PHASE_AT_END
#define DRV_SPI_TX_INT_SOURCE_IDX0 			INT_SOURCE_SPI_2_TRANSMIT
#define DRV_SPI_RX_INT_SOURCE_IDX0 			INT_SOURCE_SPI_2_RECEIVE
#define DRV_SPI_ERROR_INT_SOURCE_IDX0 		INT_SOURCE_SPI_2_ERROR
#define DRV_SPI_INT_VECTOR_IDX0				INT_VECTOR_SPI2
#define DRV_SPI_INT_PRIORITY_IDX0			INT_PRIORITY_LEVEL1
#define DRV_SPI_INT_SUB_PRIORITY_IDX0		INT_SUBPRIORITY_LEVEL0        
#define DRV_SPI_QUEUE_SIZE_IDX0 			10
#define DRV_SPI_RESERVED_JOB_IDX0 			1
// *****************************************************************************
/* SST25 Driver Configuration Options
*/
#define DRV_SST25_BUFFER_OBJ_NUMBER                       5
#define DRV_SST25_CLIENTS_NUMBER                          1
#define DRV_SST25_INSTANCES_NUMBER                        1
#define DRV_SST25_SYS_FS_REGISTER

#define DRV_SST25_POWER_STATE_IDX0                        SYS_MODULE_POWER_RUN_FULL
#define DRV_SST25_SPI_DRIVER_INSTANCE_IDX0                0
#define DRV_SST25_HOLD_PIN_PORT_CHANNEL_IDX0              
#define DRV_SST25_HOLD_PIN_PORT_BIT_POS_IDX0              
#define DRV_SST25_WRITE_PROTECT_PIN_PORT_CHANNEL_IDX0     
#define DRV_SST25_WRITE_PROTECT_PIN_BIT_POS_IDX0          
#define DRV_SST25_CHIP_SELECT_PORT_CHANNEL_IDX0           PORT_CHANNEL_F
#define DRV_SST25_CHIP_SELECT_PORT_BIT_POS_IDX0           PORTS_BIT_POS_2





// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* BSP Configuration Options
*/
#define BSP_OSC_FREQUENCY 12000000


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

/*** Application Defined Pins ***/

/*** Functions for BSP_LED_9 pin ***/
#define BSP_LED_9Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define BSP_LED_9On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define BSP_LED_9Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define BSP_LED_9StateGet() ~(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9))

/*** Functions for BSP_LED_5 pin ***/
#define BSP_LED_5Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4)
#define BSP_LED_5On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4)
#define BSP_LED_5Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4)
#define BSP_LED_5StateGet() ~(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4))

/*** Functions for BSP_LED_6 pin ***/
#define BSP_LED_6Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5)
#define BSP_LED_6On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5)
#define BSP_LED_6Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5)
#define BSP_LED_6StateGet() ~(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5))

/*** Functions for BSP_LED_7 pin ***/
#define BSP_LED_7Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)
#define BSP_LED_7On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)
#define BSP_LED_7Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)
#define BSP_LED_7StateGet() ~(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6))

/*** Functions for BSP_LED_8 pin ***/
#define BSP_LED_8Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)
#define BSP_LED_8On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)
#define BSP_LED_8Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)
#define BSP_LED_8StateGet() ~(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7))

/*** Functions for BSP_SWITCH_1 pin ***/
#define BSP_SWITCH_1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0)

/*** Functions for BSP_SWITCH_3 pin ***/
#define BSP_SWITCH_3StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10)

/*** Functions for BSP_SWITCH_2 pin ***/
#define BSP_SWITCH_2StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)

/*** Functions for BSP_SWITCH_4 pin ***/
#define BSP_SWITCH_4StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12)

/*** Functions for BSP_SWITCH_5 pin ***/
#define BSP_SWITCH_5StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13)

/*** Functions for BSP_SWITCH_6 pin ***/
#define BSP_SWITCH_6StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_14)

/*** Functions for BSP_AK4384_PDN pin ***/
#define BSP_AK4384_PDNToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define BSP_AK4384_PDNOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define BSP_AK4384_PDNOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define BSP_AK4384_PDNStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define BSP_AK4384_PDNStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15, Value)

/*** Functions for BSP_DisplayReset pin ***/
#define BSP_DisplayResetToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1)
#define BSP_DisplayResetOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1)
#define BSP_DisplayResetOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1)
#define BSP_DisplayResetStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1)
#define BSP_DisplayResetStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1, Value)

/*** Functions for BSP_DisplaySet pin ***/
#define BSP_DisplaySetToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define BSP_DisplaySetOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define BSP_DisplaySetOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define BSP_DisplaySetStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define BSP_DisplaySetStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15, Value)

/*** Functions for BSP_Display pin ***/
#define BSP_DisplayToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define BSP_DisplayOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define BSP_DisplayOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define BSP_DisplayStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define BSP_DisplayStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11, Value)

/*** Functions for BSP_AK4201_AMPLIFIER_PDN pin ***/
#define BSP_AK4201_AMPLIFIER_PDNToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1)
#define BSP_AK4201_AMPLIFIER_PDNOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1)
#define BSP_AK4201_AMPLIFIER_PDNOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1)
#define BSP_AK4201_AMPLIFIER_PDNStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1)
#define BSP_AK4201_AMPLIFIER_PDNStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1, Value)

/*** Functions for BSP_AK4384_CONTROL_CS pin ***/
#define BSP_AK4384_CONTROL_CSToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define BSP_AK4384_CONTROL_CSOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define BSP_AK4384_CONTROL_CSOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define BSP_AK4384_CONTROL_CSStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define BSP_AK4384_CONTROL_CSStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2, Value)

/*** Functions for BSP_AK4384_CONTROL_CLK pin ***/
#define BSP_AK4384_CONTROL_CLKToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)
#define BSP_AK4384_CONTROL_CLKOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)
#define BSP_AK4384_CONTROL_CLKOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)
#define BSP_AK4384_CONTROL_CLKStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)
#define BSP_AK4384_CONTROL_CLKStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3, Value)

/*** Functions for BSP_AK4384_CONTROL_DO pin ***/
#define BSP_AK4384_CONTROL_DOToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)
#define BSP_AK4384_CONTROL_DOOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)
#define BSP_AK4384_CONTROL_DOOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)
#define BSP_AK4384_CONTROL_DOStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)
#define BSP_AK4384_CONTROL_DOStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12, Value)

/*** Functions for BSP_USB_SW1 pin ***/
#define BSP_USB_SW1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1)
#define BSP_USB_SW1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1)
#define BSP_USB_SW1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1)
#define BSP_USB_SW1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1)
#define BSP_USB_SW1StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, Value)

/*** Functions for BSP_USB_SW0 pin ***/
#define BSP_USB_SW0Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0)
#define BSP_USB_SW0On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0)
#define BSP_USB_SW0Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0)
#define BSP_USB_SW0StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0)
#define BSP_USB_SW0StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0, Value)



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

