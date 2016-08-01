/*******************************************************************************
  USART Driver Dynamic to Static mapping

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart_mapping.c

  Summary:
    Source code for the USART driver dynamic APIs to static API mapping.

  Description:
    This file contains code that maps dynamic APIs to static whenever
    the static mode of the driver is selected..

  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.

    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "system_config.h"
#include "system_definitions.h"


SYS_MODULE_OBJ DRV_USART_Initialize(const SYS_MODULE_INDEX index,const SYS_MODULE_INIT * const init)
{
    SYS_MODULE_OBJ returnValue;

    switch(index)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_Initialize();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            returnValue = DRV_USART1_Initialize();
            break;
        }
        default:
        {
            returnValue = SYS_MODULE_OBJ_INVALID;
            break;
        }
    }
    return returnValue;
}

void DRV_USART_Deinitialize( SYS_MODULE_OBJ object)
{
    switch(object)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_Deinitialize();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_Deinitialize();
            break;
        }
        default:
        {
            break;
        }
    }
}

SYS_STATUS DRV_USART_Status( SYS_MODULE_OBJ object)
{
    SYS_STATUS returnValue;

    switch(object)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_Status();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            returnValue = DRV_USART1_Status();
            break;
        }
        default:
        {
            returnValue = SYS_STATUS_ERROR;
            break;
        }
    }
    return returnValue;
}

void DRV_USART_TasksTransmit ( SYS_MODULE_OBJ object )
{
    switch(object)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_TasksTransmit();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_TasksTransmit();
            break;
        }
        default:
        {
            break;
        }
    }
}

void DRV_USART_TasksReceive ( SYS_MODULE_OBJ object )
{
    switch(object)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_TasksReceive();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_TasksReceive();
            break;
        }
        default:
        {
            break;
        }
    }
}

void DRV_USART_TasksError ( SYS_MODULE_OBJ object )
{
    switch(object)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_TasksError();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_TasksError();
            break;
        }
        default:
        {
            break;
        }
    }
}


//client interface
DRV_HANDLE DRV_USART_Open( const SYS_MODULE_INDEX index, const DRV_IO_INTENT ioIntent)
{
    DRV_HANDLE returnValue;

    switch(index)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_Open(index,ioIntent);
            break;
        }
        case DRV_USART_INDEX_1:
        {
            returnValue = DRV_USART1_Open(index,ioIntent);
            break;
        }
        default:
        {
            returnValue = DRV_HANDLE_INVALID;
            break;
        }
    }
    return returnValue;
}

void DRV_USART_Close( const DRV_HANDLE handle)
{
    uintptr_t instance;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_Close();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_Close();
            break;
        }
        default:
        {
            break;
        }
    }
}

DRV_USART_CLIENT_STATUS DRV_USART_ClientStatus ( DRV_HANDLE handle )
{
    uintptr_t instance;
    DRV_USART_CLIENT_STATUS returnValue;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_ClientStatus();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            returnValue = DRV_USART1_ClientStatus();
            break;
        }
        default:
        {
            returnValue = DRV_CLIENT_STATUS_ERROR;
            break;
        }
    }
    return returnValue;
}

DRV_USART_TRANSFER_STATUS DRV_USART_TransferStatus( const DRV_HANDLE handle )
{
    uintptr_t instance;
    DRV_USART_TRANSFER_STATUS returnValue;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_TransferStatus();
            break;
        }
        case DRV_USART_INDEX_1:
        {
            returnValue = DRV_USART1_TransferStatus();
            break;
        }
        default:
        {
            returnValue = (DRV_USART_TRANSFER_STATUS)NULL;
            break;
        }
    }
    return returnValue;
}

//Buffer Queuing Model Interface
void DRV_USART_BufferAddWrite(const DRV_HANDLE handle,DRV_USART_BUFFER_HANDLE * bufferHandle, void * buffer, const size_t size)
{
    uintptr_t instance;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_BufferAddWrite (bufferHandle, buffer, size);
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_BufferAddWrite (bufferHandle, buffer, size);
            break;
        }
        default:
        {
            break;
        }
    }
}

void DRV_USART_BufferAddRead(const DRV_HANDLE handle,DRV_USART_BUFFER_HANDLE * const bufferHandle,void * buffer,const size_t size)
{
    uintptr_t instance;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_BufferAddRead (bufferHandle, buffer, size);
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_BufferAddRead (bufferHandle, buffer, size);
            break;
        }
        default:
        {
            break;
        }
    }
}

void DRV_USART_BufferEventHandlerSet (const DRV_HANDLE handle,const DRV_USART_BUFFER_EVENT_HANDLER eventHandler,const uintptr_t context)
{
    uintptr_t instance;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            DRV_USART0_BufferEventHandlerSet (eventHandler, context);
            break;
        }
        case DRV_USART_INDEX_1:
        {
            DRV_USART1_BufferEventHandlerSet (eventHandler, context);
            break;
        }
        default:
        {
            break;
        }
    }
}

size_t DRV_USART_BufferProcessedSizeGet( DRV_USART_BUFFER_HANDLE bufferHandle )
{
    //This function is independent of instance or client.
    return DRV_USART0_BufferProcessedSizeGet (bufferHandle);
}



DRV_USART_BAUD_SET_RESULT DRV_USART_BaudSet(const DRV_HANDLE handle, uint32_t baud)
{
    uintptr_t instance;
    DRV_USART_BAUD_SET_RESULT returnValue;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_BaudSet(baud);
            break;
        }
        case DRV_USART_INDEX_1:
        {
            returnValue = DRV_USART1_BaudSet(baud);
            break;
        }
        default:
        {
            returnValue = DRV_USART_BAUD_SET_ERROR;
            break;
        }
    }
    return returnValue;
}

DRV_USART_LINE_CONTROL_SET_RESULT DRV_USART_LineControlSet(const DRV_HANDLE handle,const DRV_USART_LINE_CONTROL lineControl)
{
    uintptr_t instance;
    DRV_USART_LINE_CONTROL_SET_RESULT returnValue;

    instance = handle & 0x00FF;
    //As we are handling single client, only multiple instance is taken care.
    switch(instance)
    {
        case DRV_USART_INDEX_0:
        {
            returnValue = DRV_USART0_LineControlSet(lineControl);
            break;
        }
        case DRV_USART_INDEX_1:
        {
            returnValue = DRV_USART1_LineControlSet(lineControl);
            break;
        }
        default:
        {
            returnValue = DRV_USART_LINE_CONTROL_SET_ERROR;
            break;
        }
    }
    return returnValue;
}


/*******************************************************************************
 End of File
*/
