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
#define SYS_CLK_FREQ                        120000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            60000000ul
#define SYS_CLK_BUS_PERIPHERAL_2            60000000ul
#define SYS_CLK_BUS_PERIPHERAL_3            60000000ul
#define SYS_CLK_BUS_PERIPHERAL_4            60000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         40000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       32768ul
   // *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.01"
#define SYS_VERSION               20100
   
/*** File System Service Configuration ***/

#define SYS_FS_MEDIA_NUMBER         	1

#define SYS_FS_VOLUME_NUMBER		(1)

#define SYS_FS_AUTOMOUNT_ENABLE		true
#define SYS_FS_MAX_FILES	    	1
#define SYS_FS_MAX_FILE_SYSTEM_TYPE 	1
#define SYS_FS_MEDIA_MAX_BLOCK_SIZE  	512
#define SYS_FS_MEDIA_MANAGER_BUFFER_SIZE 512


#define SYS_FS_MEDIA_TYPE_IDX0 				SYS_FS_MEDIA_TYPE_MSD
#define SYS_FS_TYPE_IDX0 					FAT







#define SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0 			"/mnt/myDrive1"
#define SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0 			"/dev/sda1"


/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true

/*** Ports System Service Configuration ***/
#define SYS_PORT_A_ANSEL        0x0D01
#define SYS_PORT_A_TRIS         0xFFFF
#define SYS_PORT_A_LAT          0x0000
#define SYS_PORT_A_ODC          0x0000
#define SYS_PORT_A_CNPU         0x0200
#define SYS_PORT_A_CNPD         0x0000
#define SYS_PORT_A_CNEN         0x0000

#define SYS_PORT_B_ANSEL        0xA7F3
#define SYS_PORT_B_TRIS         0xEFF7
#define SYS_PORT_B_LAT          0x0000
#define SYS_PORT_B_ODC          0x0000
#define SYS_PORT_B_CNPU         0x0004
#define SYS_PORT_B_CNPD         0x0000
#define SYS_PORT_B_CNEN         0x0000

#define SYS_PORT_C_ANSEL        0xFE00
#define SYS_PORT_C_TRIS         0xFFEF
#define SYS_PORT_C_LAT          0x0000
#define SYS_PORT_C_ODC          0x0000
#define SYS_PORT_C_CNPU         0x0000
#define SYS_PORT_C_CNPD         0x0000
#define SYS_PORT_C_CNEN         0x0000

#define SYS_PORT_K_ANSEL        0xF000
#define SYS_PORT_K_TRIS         0xFF7F
#define SYS_PORT_K_LAT          0x0000
#define SYS_PORT_K_ODC          0x0000
#define SYS_PORT_K_CNPU         0x0010
#define SYS_PORT_K_CNPD         0x0000
#define SYS_PORT_K_CNEN         0x0000

/*** Timer System Service Configuration ***/
#define SYS_TMR_POWER_STATE             SYS_MODULE_POWER_RUN_FULL
#define SYS_TMR_DRIVER_INDEX            DRV_TMR_INDEX_0
#define SYS_TMR_MAX_CLIENT_OBJECTS      5
#define SYS_TMR_FREQUENCY               1000
#define SYS_TMR_FREQUENCY_TOLERANCE     10
#define SYS_TMR_UNIT_RESOLUTION         10000
#define SYS_TMR_CLIENT_TOLERANCE        10
#define SYS_TMR_INTERRUPT_NOTIFICATION  false

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

/*** Graphics Display Configuration ***/
#define DISP_ORIENTATION                        0
#define DISP_HOR_RESOLUTION                     480
#define DISP_VER_RESOLUTION                     272
#define DISP_DATA_WIDTH			                24
#define DISP_HOR_PULSE_WIDTH                    42
#define DISP_HOR_BACK_PORCH                     2
#define DISP_HOR_FRONT_PORCH                    2
#define DISP_VER_PULSE_WIDTH                    10
#define DISP_VER_BACK_PORCH                     2
#define DISP_VER_FRONT_PORCH                    2
#define DISP_INV_LSHIFT                         0
#define GFX_LCD_TYPE                            GFX_LCD_TFT
#define BACKLIGHT_ENABLE_LEVEL                  1
#define BACKLIGHT_DISABLE_LEVEL                 0
#define TCON_MODULE                             NULL
// DOM-IGNORE-END
/*** Timer Driver Configuration ***/
#define DRV_TMR_INTERRUPT_MODE             true
#define DRV_TMR_INSTANCES_NUMBER           1
#define DRV_TMR_CLIENTS_NUMBER             1

/*** Timer Driver 0 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX0          TMR_ID_1
#define DRV_TMR_INTERRUPT_SOURCE_IDX0       INT_SOURCE_TIMER_1
#define DRV_TMR_INTERRUPT_VECTOR_IDX0       INT_VECTOR_T1
#define DRV_TMR_ISR_VECTOR_IDX0             _TIMER_1_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX0     INT_PRIORITY_LEVEL1
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX0 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX0           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX0               TMR_PRESCALE_VALUE_256
#define DRV_TMR_OPERATION_MODE_IDX0         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX0     false
#define DRV_TMR_POWER_STATE_IDX0            SYS_MODULE_POWER_RUN_FULL

 
// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

/*** USB Driver Configuration ***/


/* Disable Device Support */
#define DRV_USBFS_DEVICE_SUPPORT      false

/* Enables Device Support */
#define DRV_USBFS_HOST_SUPPORT      true

/* Maximum USB driver instances */
#define DRV_USBFS_INSTANCES_NUMBER    1


/* Interrupt mode enabled */
#define DRV_USBFS_INTERRUPT_MODE      true


/* Number of Endpoints used */
#define DRV_USBFS_ENDPOINTS_NUMBER    1






#define DRV_USBFS_HOST_NAK_LIMIT      2000
/* Provides Host pipes number */
#define DRV_USBFS_HOST_PIPES_NUMBER    10
#define DRV_USBFS_HOST_ATTACH_DEBOUNCE_DURATION 500
#define DRV_USBFS_HOST_RESET_DURATION 100
// *****************************************************************************
// *****************************************************************************
// Section: USB Device Layer Configuration
// *****************************************************************************
// *****************************************************************************
/* Provides Host pipes number */
#define USB_HOST_PIPES_NUMBER    10
/* NAK Limit for Control transfer data stage and Status Stage */
#define DRV_USB_HOST_NAK_LIMIT		200

// *****************************************************************************
// *****************************************************************************
// Section: USB Host Layer Configuration
// *****************************************************************************
// **************************************************************************
 
/* Total number of devices to be supported */
#define USB_HOST_DEVICES_NUMBER         1

/* Target peripheral list entries */
#define  USB_HOST_TPL_ENTRIES           1 

/* Maximum number of configurations supported per device */
#define USB_HOST_DEVICE_INTERFACES_NUMBER     5    

#define USB_HOST_CONTROLLERS_NUMBER           1

#define USB_HOST_TRANSFERS_NUMBER             10

/* Number of Host Layer Clients */
#define USB_HOST_CLIENTS_NUMBER               1   

/* Number of MSD Function driver instances in the application */
#define USB_HOST_MSD_INSTANCES_NUMBER         1

/* Number of Logical Units */
#define USB_HOST_SCSI_INSTANCES_NUMBER        1
#define USB_HOST_MSD_LUN_NUMBERS              1






// *****************************************************************************
/* BSP Configuration Options
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

/*** Application Defined Pins ***/

/*** Functions for BSP_LED_1 pin ***/
#define BSP_LED_1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4)
#define BSP_LED_1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4)
#define BSP_LED_1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4)
#define BSP_LED_1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4)

/*** Functions for BSP_LED_3 pin ***/
#define BSP_LED_3Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_7)
#define BSP_LED_3On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_7)
#define BSP_LED_3Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_7)
#define BSP_LED_3StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_7)

/*** Functions for BSP_LED_2 pin ***/
#define BSP_LED_2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_3)
#define BSP_LED_2On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_3)
#define BSP_LED_2Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_3)
#define BSP_LED_2StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_3)

/*** Functions for BSP_SWITCH_1 pin ***/
#define BSP_SWITCH_1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2)

/*** Functions for BSP_SWITCH_2 pin ***/
#define BSP_SWITCH_2StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)

/*** Functions for BSP_SWITCH_3 pin ***/
#define BSP_SWITCH_3StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_4)



/*** Application Instance 0 Configuration ***/
#define       APP_USB_LED_1                   BSP_LED_1
#define       APP_USB_LED_2                   BSP_LED_2
#define       APP_USB_LED_3                   BSP_LED_3

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/

