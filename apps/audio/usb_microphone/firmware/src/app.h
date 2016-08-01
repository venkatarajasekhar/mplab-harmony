/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H


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
#include "system_definitions.h"
#include "system/debug/sys_debug.h"
#include "app_config.h"  //Selected by project configuration

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_ID_INPUT_TERMINAL      0x01
#define APP_ID_OUTPUT_TERMINAL     0x02
#define APP_ID_MIXER_UNIT          0x03
#define APP_ID_SELECTOR_UNIT       0x04
#define APP_ID_FEATURE_UNIT        0x05
#define APP_ID_PROCESSING_UNIT     0x06
#define APP_ID_EXTENSION_UNIT      0x07

#define APP_ID_INPUT_TERMINAL_MIC  0x04
#define APP_ID_FEATURE_UNIT_MIC    0x05
#define APP_ID_OUTPUT_TERMINAL_MIC 0x06

#define USB_DEVICE_AUDIO_MAX_INTERFACE_COLLECTIONS      1
#define USB_DEVICE_AUDIO_NUM_FEATURE_UNITS              1
#define USB_DEVICE_AUDIO_FEATURE_UNIT_ID                APP_ID_FEATURE_UNIT
#define USB_DEVICE_AUDIO_CONTROL_INTERFACE_ID           0x00
#define USB_DEVICE_AUDIO_STREAMING_INTERFACE_ID_1       0x01
#define USB_DEVICE_AUDIO_STREAMING_INTERFACE_ID_2       0x02
#define USB_DEVICE_HID_INTERFACE_ID                     0x03

// *****************************************************************************
/* Application Audio Control

  Summary:
    Defines a list of audio controls supported by this application.

  Description:
    This enumeration defines audio controls supported by this application. This
 could be used for checking which Control Transfer is currently active.
*/
typedef enum
{
    APP_USB_CONTROL_NONE,
    APP_USB_AUDIO_MUTE_CONTROL
} APP_AUDIO_CONTROLS;


typedef enum
{
    APP_USB_SPEAKER_PLAYBACK_NONE  = 0,
    APP_USB_SPEAKER_PLAYBACK_STEREO_48KHZ = 1,
    APP_USB_MIC_RECORD_NONE = 0,
    APP_USB_MIC_RECORD_MONO_16KHZ = 1,
} APP_ALTERNATE_SETTINGS;

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
    APP_SUBMIT_INITIAL_READ_REQUEST,
    APP_PROCESS_DATA,
    APP_IDLE,
    APP_MUTE_AUDIO_PLAYBACK,
    APP_USB_INTERFACE_ALTERNATE_SETTING_RCVD,
    APP_STATE_WAIT_FOR_CONFIGURATION,
    APP_STATE_ERROR,
    APP_STATE_CODEC_OPEN,
    APP_STATE_CODEC_SET_BUFFER_HANDLER,
    APP_MIC_USB_INTERFACE_ALTERNATE_SETTING_RCVD
} APP_STATES;

//typedef enum
//{
///* Application's state machine's initial state. */
//	APP_MIC_STATE_INIT=0,
//
//	APP_MIC_STATE_WAIT_FOR_ALTERNATE_SETTING = 1,
//
//        APP_MIC_SUBMIT_READ_REQUEST = 2,
//
//        APP_MIC_SUBMIT_TRANSMIT_REQUEST = 3,
//
//        APP_MIC_PROCESS_DATA = 4,
//
//        APP_MIC_IDLE = 5,
//
//        APP_MIC_READ_DATA_FROM_CODEC = 6,
//
//        APP_MIC_MUTE_AUDIO_PLAYBACK = 7,
//
//        APP_MIC_USB_INTERFACE_ALTERNATE_SETTING_RCVD = 8,
//
//        MIC_INITIALIZE_AUDIO_CODEC  = 9,
//
//        APP_MIC_STATE_WAIT_FOR_CONFIGURATION = 10,
//
//        APP_MIC_STATE_WAIT_FOR_READ_COMPLETE = 11,
//
//        APP_MIC_STATE_WAIT_FOR_WRITE_COMPLETE = 11,
//
//        /* Application Error state*/
//        APP_MIC_STATE_ERROR = -1
//} APP_MIC_STATES;

// *****************************************************************************
/* Application USART client for BT

  Summary:
    Application USART client for BT.

  Description:
    This object holds the BT USART's client handle, read and write buffer handle
    created and the context
*/
typedef struct
{
    DRV_HANDLE handle;
    DRV_CODEC_BUFFER_HANDLE readBufHandle1;
    DRV_CODEC_BUFFER_HANDLE readBufHandle2;    
    DRV_CODEC_BUFFER_EVENT_HANDLER bufferHandler;
    uintptr_t context;
    uint8_t *txbufferObject1;
    uint8_t *txbufferObject2;
    size_t bufferSize;
//    bool isReadBufHandleAvailable1;
//    bool isReadBufHandleAvailable2;
} APP_CODEC_CLIENT;

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
    /* Application's current state*/
    volatile APP_STATES state;

     /* device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE   usbDevHandle;

    /* Instance number of Audio Function driver */
    USB_DEVICE_AUDIO_INDEX audioInstance;

    /* device configured state */
    bool isConfigured;

    /* True if a character was read */
    bool isReadComplete1;
    bool isReadComplete2;
    
    /* True if a character was written*/
    bool isWriteComplete;

    USB_DEVICE_AUDIO_TRANSFER_HANDLE writeTransferHandle1;
    USB_DEVICE_AUDIO_TRANSFER_HANDLE writeTransferHandle2;
    
    //USB_DEVICE_AUDIO_TRANSFER_HANDLE writeTransferHandle;

    /* Holds active value of USB Audio Streaming Interface Alternate setting.
     * Every USB Audio Streaming should have 1 or more Alternate settings.
     * Alternate setting Zero (or Default Alternate setting) never has any
     * data payload. An audio streaming can have multiple number of alternate
     settings each having it own sampling rate, bandwidth etc. */
    APP_ALTERNATE_SETTINGS activeInterfaceAlternateSetting;
    APP_ALTERNATE_SETTINGS activeInterfaceAlternateSettingMic;
    uint8_t activeInterface;

    /* Holds current value of Audio Control Mute settings. A value True indicates
     * audio is currently muted. */
     bool dacMute;

     unsigned char midCtrl;
     unsigned char midMax;
     unsigned char midMin;
     unsigned char midRes;

     bool autoGain;
    /* This is to indicate which Audio Control Transfer is currently
     * in progress. */
    APP_AUDIO_CONTROLS currentAudioControl;

    /* CODEC client handle */
    APP_CODEC_CLIENT codecClient;

    bool isReadBufHandleAvailable1;
    bool isReadBufHandleAvailable2;
    
    DRV_CODEC_BUFFER_HANDLE readBufHandle1;
    DRV_CODEC_BUFFER_HANDLE readBufHandle2;

    bool ping1Pong2; //codec read buffer 1 - T, else read buffer 2

} APP_DATA;

//typedef struct
//{
//    APP_MIC_STATES state;
//
//} APP_MIC_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.*/
void APP_USBDeviceEventHandler
(
    USB_DEVICE_EVENT events,
    void * eventData,
    uintptr_t context
);

void APP_USBDeviceAudioEventHandler
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT event ,
    void * pData,
    uintptr_t context
);


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

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

/*******************************************************************************
  Function:
    void APP_CODECBufferEventHandler(DRV_CODEC_BUFFER_EVENT event,
        DRV_CODEC_BUFFER_HANDLE handle, uintptr_t context )

  Summary:
    Event Handler for codec Task.

  Description:
    This is the Event Handler for Codec Tx Complete Events.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
*/
void APP_CODECBufferEventHandler(DRV_CODEC_BUFFER_EVENT event, DRV_CODEC_BUFFER_HANDLE handle, uintptr_t context );

#endif /* _APP_H */
/*******************************************************************************
 End of File
 */

