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
#define SYS_CLK_FREQ                        200000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_2            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_3            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_4            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_5            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_7            200000000ul
#define SYS_CLK_BUS_PERIPHERAL_8            100000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         24000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       32768ul
   // *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.01"
#define SYS_VERSION               20100

/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true

/*** Ports System Service Configuration ***/
#define SYS_PORT_A_ANSEL        0x3D20
#define SYS_PORT_A_TRIS         0xFDFF
#define SYS_PORT_A_LAT          0x0000
#define SYS_PORT_A_ODC          0x0000
#define SYS_PORT_A_CNPU         0x0001
#define SYS_PORT_A_CNPD         0x0000
#define SYS_PORT_A_CNEN         0x0000

#define SYS_PORT_B_ANSEL        0x8FC9
#define SYS_PORT_B_TRIS         0xFFC9
#define SYS_PORT_B_LAT          0x0000
#define SYS_PORT_B_ODC          0x0000
#define SYS_PORT_B_CNPU         0x7000
#define SYS_PORT_B_CNPD         0x0000
#define SYS_PORT_B_CNEN         0x0000

#define SYS_PORT_C_ANSEL        0xEFFF
#define SYS_PORT_C_TRIS         0xFFFF
#define SYS_PORT_C_LAT          0x0000
#define SYS_PORT_C_ODC          0x0000
#define SYS_PORT_C_CNPU         0x0000
#define SYS_PORT_C_CNPD         0x0000
#define SYS_PORT_C_CNEN         0x0000

#define SYS_PORT_D_ANSEL        0xC100
#define SYS_PORT_D_TRIS         0xFFFF
#define SYS_PORT_D_LAT          0x0000
#define SYS_PORT_D_ODC          0x0000
#define SYS_PORT_D_CNPU         0x0000
#define SYS_PORT_D_CNPD         0x0000
#define SYS_PORT_D_CNEN         0x0000

#define SYS_PORT_E_ANSEL        0xFFF0
#define SYS_PORT_E_TRIS         0xFFFF
#define SYS_PORT_E_LAT          0x0000
#define SYS_PORT_E_ODC          0x0000
#define SYS_PORT_E_CNPU         0x0000
#define SYS_PORT_E_CNPD         0x0000
#define SYS_PORT_E_CNEN         0x0000

#define SYS_PORT_F_ANSEL        0xDEC0
#define SYS_PORT_F_TRIS         0xDFFF
#define SYS_PORT_F_LAT          0x0000
#define SYS_PORT_F_ODC          0x0000
#define SYS_PORT_F_CNPU         0x0000
#define SYS_PORT_F_CNPD         0x0000
#define SYS_PORT_F_CNEN         0x0000

#define SYS_PORT_G_ANSEL        0x8FFC
#define SYS_PORT_G_TRIS         0xFFFF
#define SYS_PORT_G_LAT          0x0000
#define SYS_PORT_G_ODC          0x0000
#define SYS_PORT_G_CNPU         0x0000
#define SYS_PORT_G_CNPD         0x0000
#define SYS_PORT_G_CNEN         0x0000

#define SYS_PORT_H_ANSEL        0x0030
#define SYS_PORT_H_TRIS         0xF7B0
#define SYS_PORT_H_LAT          0x0000
#define SYS_PORT_H_ODC          0x0000
#define SYS_PORT_H_CNPU         0x0000
#define SYS_PORT_H_CNPD         0x0000
#define SYS_PORT_H_CNEN         0x0000

#define SYS_PORT_J_ANSEL        0x0B00
#define SYS_PORT_J_TRIS         0xEB27
#define SYS_PORT_J_LAT          0x0000
#define SYS_PORT_J_ODC          0x0000
#define SYS_PORT_J_CNPU         0x0000
#define SYS_PORT_J_CNPD         0x0000
#define SYS_PORT_J_CNEN         0x0000

#define SYS_PORT_K_ANSEL        0xFF00
#define SYS_PORT_K_TRIS         0xFFC6
#define SYS_PORT_K_LAT          0x0000
#define SYS_PORT_K_ODC          0x0000
#define SYS_PORT_K_CNPU         0x0000
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

#define GFX_USE_DISPLAY_CONTROLLER_LCC
#define DRV_GFX_LCC_INTERNAL_MEMORY
#define DRV_GFX_LCC_DMA_CHANNEL_INDEX                 DMA_CHANNEL_1
#define DRV_GFX_LCC_DMA_TRIGGER_SOURCE                DMA_TRIGGER_TIMER_4
#define DRV_GFX_LCC_DMA_TRANSFER_LENGTH               2
#define DRV_GFX_LCC_TMR_INDEX                         TMR_ID_4

/*** Graphics Display Configuration ***/
#define DISP_ORIENTATION                        0
#define DISP_HOR_RESOLUTION                     480
#define DISP_VER_RESOLUTION                     272
#define DISP_DATA_WIDTH			                24
#define DISP_HOR_PULSE_WIDTH                    41
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
#define TOUCHSCREEN_RESISTIVE_SWAP_XY

// DOM-IGNORE-END
/*** Timer Driver Configuration ***/
#define DRV_TMR_INTERRUPT_MODE             true
#define DRV_TMR_INSTANCES_NUMBER           1
#define DRV_TMR_CLIENTS_NUMBER             1

/*** Timer Driver 0 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX0          TMR_ID_2
#define DRV_TMR_INTERRUPT_SOURCE_IDX0       INT_SOURCE_TIMER_2
#define DRV_TMR_INTERRUPT_VECTOR_IDX0       INT_VECTOR_T2
#define DRV_TMR_ISR_VECTOR_IDX0             _TIMER_2_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX0     INT_PRIORITY_LEVEL4
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


/*** GFX Library Configuration ***/

#define GFX_INSTANCES_NUMBER                            1
#define GFX_SELF_PREEMPTION_LEVEL                       0
#define GFX_CONFIG_COLOR_DEPTH                          16

#define GFX_CONFIG_FONT_CHAR_SIZE                       8
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_CONFIG_FONT_RAM_DISABLE
#define GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
#define GFX_CONFIG_IMAGE_RAM_DISABLE
#define GFX_CONFIG_IPU_DECODE_DISABLE
#define GFX_CONFIG_ALPHABLEND_DISABLE
#define GFX_CONFIG_GRADIENT_DISABLE
#define GFX_CONFIG_PALETTE_DISABLE
#define GFX_CONFIG_FONT_ANTIALIASED_DISABLE
#define GFX_CONFIG_TRANSPARENT_COLOR_DISABLE
#define GFX_CONFIG_PALETTE_EXTERNAL_DISABLE
#define GFX_CONFIG_DOUBLE_BUFFERING_DISABLE
#define GFX_CONFIG_USE_KEYBOARD_DISABLE
#define GFX_CONFIG_USE_TOUCHSCREEN_DISABLE
#define GFX_CONFIG_FOCUS_DISABLE
#define GFX_malloc(size)                                    malloc(size)
#define GFX_free(pObj)                                      free(pObj)


/*** USB Driver Configuration ***/


/* Disable Device Support */
#define DRV_USBHS_DEVICE_SUPPORT      false

/* Enables Device Support */
#define DRV_USBHS_HOST_SUPPORT      true

/* Maximum USB driver instances */
#define DRV_USBHS_INSTANCES_NUMBER    1


/* Interrupt mode enabled */
#define DRV_USBHS_INTERRUPT_MODE      true


/* Number of Endpoints used */
#define DRV_USBHS_ENDPOINTS_NUMBER    1







#define DRV_USBHS_HOST_NAK_LIMIT      2000
/* Provides Host pipes number */
#define DRV_USBHS_HOST_PIPES_NUMBER    10
#define DRV_USBHS_HOST_ATTACH_DEBOUNCE_DURATION 500
#define DRV_USBHS_HOST_RESET_DURATION 100
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


/* Number of HID Client driver instances in the application */
#define USB_HOST_HID_INSTANCES_NUMBER        1

/* Maximum number of INTERRUPT IN endpoints supported per HID interface */
#define USB_HOST_HID_INTERRUPT_IN_ENDPOINTS_NUMBER 1

/* Number of total usage driver instances registered with HID client driver */
#define USB_HOST_HID_USAGE_DRIVER_SUPPORT_NUMBER  1

/* Maximum number PUSH items that can be saved in the Global item queue per field
 * per HID interface */
#define USB_HID_GLOBAL_PUSH_POP_STACK_SIZE 1


/* Maximum number Mouse buttons whose value will be captured per HID Mouse device */
#define USB_HOST_HID_MOUSE_BUTTONS_NUMBER 5





// *****************************************************************************
/* BSP Configuration Options
*/
#define BSP_OSC_FREQUENCY 24000000


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

/*** Application Defined Pins ***/

/*** Functions for APP_USB_LED_1 pin ***/
#define APP_USB_LED_1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0)
#define APP_USB_LED_1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0)
#define APP_USB_LED_1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0)
#define APP_USB_LED_1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0)

/*** Functions for APP_USB_LED_3 pin ***/
#define APP_USB_LED_3Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_1)
#define APP_USB_LED_3On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_1)
#define APP_USB_LED_3Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_1)
#define APP_USB_LED_3StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_1)

/*** Functions for APP_USB_LED_2 pin ***/
#define APP_USB_LED_2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2)
#define APP_USB_LED_2On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2)
#define APP_USB_LED_2Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2)
#define APP_USB_LED_2StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2)

/*** Functions for APP_USB_LED_4 pin ***/
#define APP_USB_LED_4Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_6)
#define APP_USB_LED_4On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_6)
#define APP_USB_LED_4Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_6)
#define APP_USB_LED_4StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_6)

/*** Functions for APP_USB_LED_5 pin ***/
#define APP_USB_LED_5Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)
#define APP_USB_LED_5On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)
#define APP_USB_LED_5Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)
#define APP_USB_LED_5StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)

/*** Functions for BSP_SWITCH_S1 pin ***/
#define BSP_SWITCH_S1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0)

/*** Functions for APP_USB_SWITCH_1 pin ***/
#define APP_USB_SWITCH_1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12)

/*** Functions for APP_USB_SWITCH_2 pin ***/
#define APP_USB_SWITCH_2StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13)

/*** Functions for BSP_SWITCH_3 pin ***/
#define BSP_SWITCH_3StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_14)

/*** Functions for BSP_SRAM_A16 pin ***/
#define BSP_SRAM_A16Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_0)
#define BSP_SRAM_A16On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_0)
#define BSP_SRAM_A16Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_0)
#define BSP_SRAM_A16StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_0)
#define BSP_SRAM_A16StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_0, Value)

/*** Functions for BSP_LCD_DE pin ***/
#define BSP_LCD_DEToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4)
#define BSP_LCD_DEOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4)
#define BSP_LCD_DEOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4)
#define BSP_LCD_DEStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4)
#define BSP_LCD_DEStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4, Value)

/*** Functions for BSP_BT_PIN pin ***/
#define BSP_BT_PINToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2)
#define BSP_BT_PINOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2)
#define BSP_BT_PINOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2)
#define BSP_BT_PINStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2)
#define BSP_BT_PINStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2, Value)

/*** Functions for BSP_LCD_HSYNC pin ***/
#define BSP_LCD_HSYNCToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1)
#define BSP_LCD_HSYNCOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1)
#define BSP_LCD_HSYNCOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1)
#define BSP_LCD_HSYNCStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1)
#define BSP_LCD_HSYNCStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1, Value)

/*** Functions for BSP_LCD_VSYNC pin ***/
#define BSP_LCD_VSYNCToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define BSP_LCD_VSYNCOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define BSP_LCD_VSYNCOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define BSP_LCD_VSYNCStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define BSP_LCD_VSYNCStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9, Value)

/*** Functions for BSP_SRAM_A17 pin ***/
#define BSP_SRAM_A17Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_3)
#define BSP_SRAM_A17On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_3)
#define BSP_SRAM_A17Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_3)
#define BSP_SRAM_A17StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_3)
#define BSP_SRAM_A17StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_3, Value)

/*** Functions for BSP_LCD_BACKLIGHT pin ***/
#define BSP_LCD_BACKLIGHTToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13)
#define BSP_LCD_BACKLIGHTOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13)
#define BSP_LCD_BACKLIGHTOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13)
#define BSP_LCD_BACKLIGHTStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13)
#define BSP_LCD_BACKLIGHTStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13, Value)

/*** Functions for BSP_SRAM_A18 pin ***/
#define BSP_SRAM_A18Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_4)
#define BSP_SRAM_A18On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_4)
#define BSP_SRAM_A18Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_4)
#define BSP_SRAM_A18StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_4)
#define BSP_SRAM_A18StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_4, Value)

/*** Functions for BSP_SRAM_A19 pin ***/
#define BSP_SRAM_A19Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_5)
#define BSP_SRAM_A19On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_5)
#define BSP_SRAM_A19Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_5)
#define BSP_SRAM_A19StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_5)
#define BSP_SRAM_A19StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_5, Value)

/*** Functions for BSP_LCD_RESET pin ***/
#define BSP_LCD_RESETToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_3)
#define BSP_LCD_RESETOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_3)
#define BSP_LCD_RESETOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_3)
#define BSP_LCD_RESETStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_3)
#define BSP_LCD_RESETStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_3, Value)

/*** Functions for BSP_SRAM_CS pin ***/
#define BSP_SRAM_CSToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_4)
#define BSP_SRAM_CSOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_4)
#define BSP_SRAM_CSOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_4)
#define BSP_SRAM_CSStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_4)
#define BSP_SRAM_CSStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_4, Value)

/*** Functions for BSP_LCD_CS pin ***/
#define BSP_LCD_CSToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_6)
#define BSP_LCD_CSOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_6)
#define BSP_LCD_CSOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_6)
#define BSP_LCD_CSStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_6)
#define BSP_LCD_CSStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_6, Value)

/*** Functions for BSP_CAM_PDN pin ***/
#define BSP_CAM_PDNToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_7)
#define BSP_CAM_PDNOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_7)
#define BSP_CAM_PDNOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_7)
#define BSP_CAM_PDNStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_7)
#define BSP_CAM_PDNStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_7, Value)



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

