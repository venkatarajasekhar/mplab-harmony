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

/* Receive data buffer */
uint8_t receivedDataBuffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;

/* Transmit data buffer */
uint8_t  transmitDataBuffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;

/* The endpoint size is 64 for FS and 512 for HS */
uint16_t endpointSize;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/*********************************************
 * Application USB Device Layer Event Handler
 *********************************************/

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event, void * eventData, uintptr_t context)
{
    uint8_t * configurationValue;
    USB_SETUP_PACKET * setupPacket;
    switch(event)
    {
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:

            /* Device is reset or deconfigured. Provide LED indication.*/
            BSP_LEDOn  (APP_USB_LED_1);
            BSP_LEDOn (APP_USB_LED_2);
            BSP_LEDOff (APP_USB_LED_3);

            appData.deviceIsConfigured = false;

            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Check the configuration */
            configurationValue = (uint8_t *)eventData;
            if(*configurationValue == 1 )
            {
                /* The device is in configured state. Update LED indication */
                BSP_LEDOff  (APP_USB_LED_1);
                BSP_LEDOff (APP_USB_LED_2);
                BSP_LEDOn (APP_USB_LED_3);

                /* Reset endpoint data send & receive flag  */
                appData.deviceIsConfigured = true;
            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:

            /* Device is suspended. Update LED indication */
            BSP_LEDOff  (APP_USB_LED_1);
            BSP_LEDOn (APP_USB_LED_2);
            BSP_LEDOn (APP_USB_LED_3);
            break;


        case USB_DEVICE_EVENT_POWER_DETECTED:

            /* VBUS is detected. Attach the device */
            USB_DEVICE_Attach(appData.usbDevHandle);
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:

            /* VBUS is removed. Detach the device */
            USB_DEVICE_Detach (appData.usbDevHandle);
            break;

        case USB_DEVICE_EVENT_CONTROL_TRANSFER_SETUP_REQUEST:
            /* This means we have received a setup packet */
            setupPacket = (USB_SETUP_PACKET *)eventData;
            if(setupPacket->bRequest == USB_REQUEST_SET_INTERFACE)
            {
                /* If we have got the SET_INTERFACE request, we just acknowledge
                 for now. This demo has only one alternate setting which is already
                 active. */
                USB_DEVICE_ControlStatus(appData.usbDevHandle,USB_DEVICE_CONTROL_STATUS_OK);
            }
            else if(setupPacket->bRequest == USB_REQUEST_GET_INTERFACE)
            {
                /* We have only one alternate setting and this setting 0. So
                 * we send this information to the host. */

                USB_DEVICE_ControlSend(appData.usbDevHandle, &appData.altSetting, 1);
            }
            else
            {
                /* We have received a request that we cannot handle. Stall it*/
                USB_DEVICE_ControlStatus(appData.usbDevHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
            }
            break;

        case USB_DEVICE_EVENT_ENDPOINT_READ_COMPLETE:
           /* Endpoint read is complete */
            appData.epDataReadPending = false;
            break;

        case USB_DEVICE_EVENT_ENDPOINT_WRITE_COMPLETE:
            /* Endpoint write is complete */
            appData.epDataWritePending = false;
            break;

        /* These events are not used in this demo. */
        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;
    }
}



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
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    appData.usbDevHandle = USB_DEVICE_HANDLE_INVALID;
    appData.deviceIsConfigured = false;
    appData.endpointRx = 0x01;
    appData.endpointTx = 0x81;
    appData.epDataReadPending = false;
    appData.epDataWritePending = false;
    appData.altSetting = 0;
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks (void )
{
    switch(appData.state)
    {
        case APP_STATE_INIT:
            /* Open the device layer */
            appData.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );

            if(appData.usbDevHandle != USB_DEVICE_HANDLE_INVALID)
            {
                /* Register a callback with device layer to get event notification (for end point 0) */
                USB_DEVICE_EventHandlerSet(appData.usbDevHandle,  APP_USBDeviceEventHandler, 0);

                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            else
            {
                /* The Device Layer is not ready to be opened. We should try
                 * again later. */
            }

            break;

        case APP_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device is configured */
            if(appData.deviceIsConfigured == true)
            {
                if (USB_DEVICE_ActiveSpeedGet(appData.usbDevHandle) == USB_SPEED_FULL)
                {
                    endpointSize = 64;
                }
                else if (USB_DEVICE_ActiveSpeedGet(appData.usbDevHandle) == USB_SPEED_HIGH)
                {
                    endpointSize = 512;
                }
                if (USB_DEVICE_EndpointIsEnabled(appData.usbDevHandle, appData.endpointRx) == false )
                {
                    /* Enable Read Endpoint */
                    USB_DEVICE_EndpointEnable(appData.usbDevHandle, 0, appData.endpointRx,
                            USB_TRANSFER_TYPE_BULK, endpointSize);
                }
                if (USB_DEVICE_EndpointIsEnabled(appData.usbDevHandle, appData.endpointTx) == false )
                {
                    /* Enable Write Endpoint */
                    USB_DEVICE_EndpointEnable(appData.usbDevHandle, 0, appData.endpointTx,
                            USB_TRANSFER_TYPE_BULK, endpointSize);
                }
                /* Indicate that we are waiting for read */
                appData.epDataReadPending = true;

                /* Place a new read request. */
                USB_DEVICE_EndpointRead(appData.usbDevHandle, &appData.readTranferHandle,
                        appData.endpointRx, &receivedDataBuffer[0], sizeof(receivedDataBuffer) );

                /* Device is ready to run the main task */
                appData.state = APP_STATE_MAIN_TASK;
            }
            break;

        case APP_STATE_MAIN_TASK:

            if(!appData.deviceIsConfigured)
            {
                /* This means the device got deconfigured. Change the
                 * application state back to waiting for configuration. */
                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;

                /* Disable the endpoint*/
                USB_DEVICE_EndpointDisable(appData.usbDevHandle, appData.endpointRx);
                USB_DEVICE_EndpointDisable(appData.usbDevHandle, appData.endpointTx);
                appData.epDataReadPending = false;
                appData.epDataWritePending = false;
            }
            else if (appData.epDataReadPending == false)
            {
                /* Look at the data the host sent, to see what kind of
                 * application specific command it sent. */

                switch(receivedDataBuffer[0])
                {
                    case 0x80:

                        /* This is the toggle LED command */
                        BSP_LEDToggle( APP_USB_LED_1 );
                        BSP_LEDToggle( APP_USB_LED_2 );
                        break;

                    case 0x81:

                        /* This is a switch check command. Check if the TX is free
                         * for us to send a status. */

                        if(appData.epDataWritePending == false)
                        {
                            /* Echo back to the host PC the command we are fulfilling
                             * in the first byte.  In this case, the Get Pushbutton
                             * State command. */

                            transmitDataBuffer[0] = 0x81;

                            if(BSP_SwitchStateGet(APP_USB_SWITCH_1) == BSP_SWITCH_STATE_PRESSED)
                            {
                                transmitDataBuffer[1] = 0x00;
                            }
                            else
                            {
                                transmitDataBuffer[1] = 0x01;
                            }

                            /* Send the data to the host */

                            appData.epDataWritePending = true;

                            USB_DEVICE_EndpointWrite ( appData.usbDevHandle, &appData.writeTranferHandle,
                                    appData.endpointTx, &transmitDataBuffer[0],
                                    sizeof(transmitDataBuffer),
                                    USB_DEVICE_TRANSFER_FLAGS_MORE_DATA_PENDING);
                        }
                        break;
                    default:
                        break;
                }

                appData.epDataReadPending = true ;

                /* Place a new read request. */
                USB_DEVICE_EndpointRead ( appData.usbDevHandle, &appData.readTranferHandle,
                        appData.endpointRx, &receivedDataBuffer[0], sizeof(receivedDataBuffer) );
            }
            break;

        case APP_STATE_ERROR:
            break;

        default:
            break;
    }
}
 

/*******************************************************************************
 End of File
 */

