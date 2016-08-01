/*******************************************************************************
  USB Host Controller Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usb_host.c

  Summary:
    USB Device Driver Implementation

  Description:
    The USB device driver provides a simple interface to manage the USB modules
    on Microchip microcontrollers.  This file Implements the  host mode
    interface routines for the USB driver.  While building the driver from
    source, ALWAYS use this file in the build if USB host mode operation is
    required.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
  Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

#include "system_config.h"
#include "driver/usb/beta_sw/drv_usb.h"
#include "driver/usb/beta_sw/usbhs/src/drv_usb_local.h"

/*****************************************
 * Pool of pipe objects that is used by
 * all driver instances.
 *****************************************/
DRV_USB_HOST_PIPE_OBJ gDrvUSBHostPipeObj[DRV_USB_HOST_PIPES_NUMBER];

extern DRV_USB_OBJ gDrvUSBObj[];

DRV_USB_HOST_PIPE_HANDLE _DRV_USB_HOST_FifoTableAllocate
(
    DRV_USB_OBJ * hDriver,
    DRV_USB_HOST_PIPE_OBJ * pipe,
    uint16_t wMaxPacketSize
)
{
    uint8_t *pFifoTable = (uint8_t *)(hDriver->gDrvUSBFifoTable);
    uint8_t *pFifoTableSecondary = (uint8_t *)(hDriver->gDrvUSBFifoTableSecondary);
    uint8_t indexFifoTable = 1;
    uint8_t noOfSlotsReq = 0;
    uint8_t noOfSlotsReqTemp = 0;
    uint8_t counter = 0;
    uint8_t byteLoop;
    uint8_t bitLoop;
    uint8_t byteStarting = 0;
    uint8_t bitStarting = 0;
    bool slotObtained = false;
    bool firstObtained = false;


    if(wMaxPacketSize <= 64)
    {
	/* For 9KB FIFO RAM we need total 144 bit slots where each bit slot
	 * represents 64 bytes of FIFO RAM memory. So that translates to 18
         * byte slots.
	 */
	while(indexFifoTable <= 18)
	{
	    /* Search whole byte bit by bit */
	    while(counter <= 7)
	    {
		if((*pFifoTable & (0x01 << counter)) == 0)
		{
		    /* Free slot obtained. Now grab as per the max packet size */
		    /* 1 slot will represent 64 bytes in the fifo.
		     * So for endpoints having maxpacket size less than
		     * 64 also we will allocate 64 bytes memory EP FIFO
		     */
		    pipe->startingOffset =
		       	(((indexFifoTable - 1) * 8) + 1 + counter) * 8;

		    pipe->noOfSlots = 1;
		    *pFifoTable = (*pFifoTable | (0x01 << counter));
		    slotObtained = true;
		    break;
		}
		counter++;
	    }/* end of (counter != 7) */
	    if(slotObtained == true)
	    {
		/* Exit from the main while() loop if FIFOTable obtained */
		break;
	    }
	    indexFifoTable++;
	    pFifoTable++;
	    /* Reset the counter to 0 for the next FIFOTable byte scan */
	    counter = 0;

	}/* end of (indexFifoTable <= 18) */
    }
    else
    {
	/* Here noOfSlotsReq is number of continous bits required in the FIFO
         table */
	noOfSlotsReq = (wMaxPacketSize / 64);
        if((wMaxPacketSize % 64) != 0)
        {
            noOfSlotsReq++;
        }
        /* Keeping a backup of the number of slots required */
	noOfSlotsReqTemp = noOfSlotsReq;

        /* 
         * Copy the latest content of the FIFOTable. The design idea is to
         * set the  gDrvUSBFifoTableSecondary data structure and then copy the
         * whole gDrvUSBFifoTableSecondary data to gDrvUSBFifoTable at the end.
         *
         * There is no chance that gDrvUSBFifoTable can get changed in the middle
         * as all are protected by Mutex lock on a per USBHCD driver instance level.
         */
	memcpy(hDriver->gDrvUSBFifoTableSecondary, hDriver->gDrvUSBFifoTable,
                sizeof(hDriver->gDrvUSBFifoTableSecondary));

	for(byteLoop = 1; byteLoop <=18; byteLoop++)
	{
	    for(bitLoop = 0; bitLoop <=7; bitLoop++)
	    {
		if((*pFifoTable & (0x01 << bitLoop)) == 0)
		{
		    if(firstObtained == false)
		    {
			firstObtained = true;
			byteStarting = byteLoop;
			bitStarting = bitLoop;
			*pFifoTableSecondary = (*pFifoTableSecondary | (0x01 << bitLoop));
		    }
                    else
                    {
                        *pFifoTableSecondary = (*pFifoTableSecondary | (0x01 << bitLoop));
                    }
		    noOfSlotsReqTemp--;
		}
		else
		{
		    firstObtained = false;
		    noOfSlotsReqTemp = noOfSlotsReq;
		    /*
                     * Reset the secondary array  to original array. This is
                     * required because it may happen that initially we got some
                     * free slots but not enough slots as required. In this case
                     * we need to recopy again the original FifoTable data.
                     */
		    memcpy(hDriver->gDrvUSBFifoTableSecondary, hDriver->gDrvUSBFifoTable,
                            sizeof(hDriver->gDrvUSBFifoTable));
		}
		if(noOfSlotsReqTemp == 0)
		{
		    /* Obtained all continous slots */
		    pipe->startingOffset = (((byteStarting - 1) * 8) + 1 + bitStarting) * 8;
		    pipe->noOfSlots = noOfSlotsReq;
		    slotObtained = true;
		    break;
		}

	    }/* end of for(bitLoop) */
	    if(slotObtained == true)
	    {
		memcpy(hDriver->gDrvUSBFifoTable, hDriver->gDrvUSBFifoTableSecondary,
                        sizeof(hDriver->gDrvUSBFifoTable));
		/* Exit from the main for() loop if FIFOTable obtained */
		break;
	    }
	    pFifoTable++;
	    pFifoTableSecondary++;
	}/* end of for(byteLoop) */
    }/*end of else(wmaxpacket > 64)*/
    
    if(slotObtained ==  false)
    {
	/* Slot NOT obtained */
	return DRV_USB_HOST_PIPE_HANDLE_INVALID;
    }
    else
    {
	return ((DRV_USB_HOST_PIPE_HANDLE)pipe);
    }

}/* end of _DRV_USB_HOST_FifoTableAllocate() */

void _DRV_USB_HOST_IRPTransmitFIFOLoad(USBHS_MODULE_ID usbID, USB_HOST_IRP_LOCAL * irp,
        uint8_t endpoint)
{
    /* This function will copy data from the irp to the fifo
     * base on the number of bytes that were completed and
     * then trigger the transmit */

    uint8_t * data;
    unsigned int count, pendingBytes;
    DRV_USB_HOST_PIPE_OBJ * pipe = (DRV_USB_HOST_PIPE_OBJ *)(irp->pipe);
    uint8_t dmaChannelGrabbed = 0;

    /* Load the fifo */
    pendingBytes = irp->size - irp->completedBytes;
    count = (pendingBytes > pipe->endpointSize)
            ? pipe->endpointSize : pendingBytes;
    data = (uint8_t *)(irp->data + irp->completedBytes);

    if(endpoint == 0)
    {
        irp->completedBytes += count;
        PLIB_USBHS_EndpointFIFOLoad(usbID, endpoint, data, count);
    }
    else
    {
        /* NON CONTROL transfer */
        dmaChannelGrabbed = _DRV_USB_HOST_GetFreeDMAChannel((DRV_USB_OBJ *)(pipe->hClient),
                                   USB_DATA_DIRECTION_HOST_TO_DEVICE, endpoint);
        if((dmaChannelGrabbed == 0))
        {
            /* NO DMA channel available. So do normal FIFO load */
            irp->completedBytes += count;
            PLIB_USBHS_EndpointFIFOLoad(usbID, endpoint, data, count);
        }
        else
        {
            /* DMA CHANNEL has been grabbed and DMA buffer address is OK
               (divisible by 4). So program the DMA registers now to start
                DMA operation
            */
            ((DRV_USB_OBJ *)(pipe->hClient))->gDrvUSBDMAPool[dmaChannelGrabbed]
                    .count = count;

            PLIB_USBHS_DMAOperationEnable(usbID, endpoint, dmaChannelGrabbed,
                    (void *)data, count, 0);
        }
    }
}/* end of _DRV_USB_HOST_IRPTransmitFIFOLoad() */

void _DRV_USB_HOST_IRPTransmitSetupPacket(USBHS_MODULE_ID usbID,
        USB_HOST_IRP_LOCAL * irp)
{
    /* This function will load the irp setup packet into endpoint 
     * 0 fifo and will then transmit the setup packet. */

    DRV_USB_HOST_PIPE_OBJ * pipe = (DRV_USB_HOST_PIPE_OBJ *)(irp->pipe);
    uint8_t * data = (uint8_t *)irp->setup;

    PLIB_USBHS_Endpoint0SetupPacketLoad(usbID,
            data, pipe->deviceAddress, pipe->hubAddress,
            pipe->hubPort, pipe->speed);
}/* end of _DRV_USB_HOST_IRPTransmitSetupPacket() */

unsigned int _DRV_USB_HOST_IRPReceiveFIFOUnload (USBHS_MODULE_ID usbID,
        USB_HOST_IRP_LOCAL * irp,
        uint8_t endpoint,
        bool * pisDMAUsed)
{
    /* This function will recover the count of the received data/
    * and will then unload the endpoint fifo. Finally the rx packet
    * ready bit will be cleared */

    uint32_t  count;
    uint8_t * data;
    DRV_USB_HOST_PIPE_OBJ * pipe = (DRV_USB_HOST_PIPE_OBJ *)(irp->pipe);
    uint8_t dmaChannelGrabbed = 0;

    /* Copy the data from the FIFO0 to the application
    * buffer and then update the complete byte count
    * and clear the RX packet ready bit */

    data = (uint8_t *)(irp->data + irp->completedBytes);
    if(endpoint == 0)
    {
        count = PLIB_USBHS_EndpointFIFOUnload(usbID, endpoint, data);
        irp->completedBytes += count;
        *pisDMAUsed = false;
    }
    else
    {
        dmaChannelGrabbed = _DRV_USB_HOST_GetFreeDMAChannel((DRV_USB_OBJ *)(pipe->hClient),
                                   USB_DATA_DIRECTION_DEVICE_TO_HOST, endpoint);
        if((dmaChannelGrabbed == 0))
        {
            /* NO DMA channel available. So do normal FIFO unload */
            count = PLIB_USBHS_EndpointFIFOUnload(usbID, endpoint, data);
            irp->completedBytes += count;
            *pisDMAUsed = false;
        }
        else
        {
            /* DMA CHANNEL has been grabbed and DMA buffer address is OK
             * (divisible by 4). So program the DMA registers now to start
             * DMA operation
             */
            
            /* Obtain the Recieved data count in bytes */
             count = (uint32_t) PLIB_USBHS_GetReceiveDataCount(usbID, endpoint);

             ((DRV_USB_OBJ *)(pipe->hClient))->gDrvUSBDMAPool[dmaChannelGrabbed]
                     .count = count;

             PLIB_USBHS_DMAOperationEnable(usbID, endpoint,dmaChannelGrabbed,
                         (void *)(data), count, 1);
             *pisDMAUsed = true;
        }
    }

    return (count);
}/* end of _DRV_USB_HOST_IRPReceiveFIFOUnload() */

void _DRV_USB_HOST_Initialize(DRV_USB_OBJ * drvObj, SYS_MODULE_INDEX index)
{
    
    USBHS_MODULE_ID usbID = drvObj->usbID;
   
    /* Enable the pull down resistor on the USBID pin. */
    //CNPDFbits.CNPDF3 = 1;

    /* Disable all endpoint interrupts 
     * Enable the desired interrupts. We have enabled
     * VBUS error, Session Request, Disconnect, Connect
     * Reset/Babble, Resume. */

    PLIB_USBHS_InterruptEnableSet(usbID, 0x7E, 0x0, 0x0);

    /* Based on the speed that we are initializing
     * set up the HS Enable bit in the Power register */

    if(drvObj->operationSpeed == USB_SPEED_HIGH)
    {
        /* Enable high speed */
        PLIB_USBHS_HighSpeedEnable(usbID);
    }
    else
    {
        /* Enable full speed */
        PLIB_USBHS_HighSpeedDisable(usbID);
    }

}/* end of _DRV_USB_HOST_Initialize() */

USB_ERROR DRV_USB_HOST_IRPSubmit(DRV_USB_HOST_PIPE_HANDLE  hPipe, USB_HOST_IRP * inputIRP)
{
    USB_HOST_IRP_LOCAL * irpIterator;
    DRV_USB_HOST_TRANSFER_GROUP * controlTransferGroup;
    bool interruptWasEnabled = false;
    unsigned int direction;
    uint8_t endpoint;
    
    USB_HOST_IRP_LOCAL * irp        = (USB_HOST_IRP_LOCAL *)inputIRP;
    DRV_USB_HOST_PIPE_OBJ * pipe = (DRV_USB_HOST_PIPE_OBJ *)(hPipe);
    DRV_USB_OBJ * hDriver;
    USBHS_MODULE_ID usbID;

    if((pipe == NULL) || (hPipe == (DRV_USB_HOST_PIPE_HANDLE_INVALID)))
    {
        /* This means an invalid pipe was specified. 
         * Return with an error */

        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Pipe handle is not valid");
        return USB_ERROR_PARAMETER_INVALID;
    }

    hDriver = (DRV_USB_OBJ *)(pipe->hClient);
    usbID = hDriver->usbID;
    controlTransferGroup = &hDriver->controlTransferGroup;

    /* Assign owner pipe */
    irp->pipe = hPipe;
    irp->status = USB_HOST_IRP_STATUS_PENDING;
    irp->tempState = DRV_USB_HOST_IRP_STATE_PROCESSING;
    endpoint = pipe->hostEndpoint;
    direction = (pipe->endpointAndDirection & 0x80) >> 7;

    /* We need to disable interrupts was the queue state
     * does not change asynchronously */

    if(!hDriver->isInInterruptContext)
    {
        // OSAL: Get Mutex
        if(OSAL_MUTEX_Lock(&(hDriver->mutexID), OSAL_WAIT_FOREVER) !=
                OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
            return USB_ERROR_OSAL_FUNCTION;
        }
        interruptWasEnabled = _DRV_USB_InterruptSourceDisable(hDriver->interruptSource);;
             
    }

    /* This needs to be done for all irp irrespective
     * of type or if there IRP is immediately processed */

    irp->next = NULL;
    irp->completedBytes = 0;
    irp->status = USB_HOST_IRP_STATUS_PENDING;

    if(pipe->irpQueueHead == NULL)
    {
        /* This means that there are no
         * IRPs on this pipe. We can add
         * this IRP directly */

        irp->previous = NULL;
        pipe->irpQueueHead = irp;

        if(pipe->pipeType == USB_TRANSFER_TYPE_CONTROL)
        {
            /* Set the initial stage of the IRP */
             irp->tempState = DRV_USB_HOST_IRP_STATE_SETUP_STAGE;

            /* We need to update the flags parameter of the IRP
             * to indicate the direction of the control transfer. */

            if(*((uint8_t*)(irp->setup)) & 0x80)
            {
                /* This means the data stage moves from device to 
                 * host. Set bit 15 of the flags parameter */

               irp->flags |= 0x8000;
            }
            else
            {
                /* This means the data stage moves from host to
                 * device. Clear bit 15 of the flags parameter. */

                irp->flags &= 0x7FFF;
            }

            /* We need to check if the endpoint 0 is free and if so
            * then start processing the IRP */

            if(controlTransferGroup->currentIRP == NULL)
            {
                /* This means that no IRPs are being processed
                 * So we should start the IRP processing. Else
                 * the IRP processing will start in interrupt.
                 * We start by copying the setup command */

                controlTransferGroup->currentIRP = irp;
                controlTransferGroup->currentPipe = pipe;
                irp->status = USB_HOST_IRP_STATUS_IN_PROGRESS;

                /* Send the setup packet to device */
                _DRV_USB_HOST_IRPTransmitSetupPacket(usbID, irp);
            }
        }
        else
        {
            /* For non control transfers, if this is the first
             * irp in the queue, then we can start the irp */

            irp->status = USB_HOST_IRP_STATUS_IN_PROGRESS;

            if(USB_DATA_DIRECTION_HOST_TO_DEVICE == direction)
            {
                /* Data is moving from host to device. We
                 * need to copy data into the FIFO and
                 * then and set the TX request bit. If the
                 * IRP size is greater than endpoint size then
                 * we must packetize. */

                _DRV_USB_HOST_IRPTransmitFIFOLoad(usbID, irp, endpoint);
            }
            else
            {
                /* Data is moving from device to host
                 * We need to set the Rx Packet Request
                 * bit */

                PLIB_USBHS_EndpointRxRequestEnable(usbID, endpoint);
            }
        }
    }
    else
    {
        /* We need to add the irp to the last irp
         * in the pipe queue (which is a linked list) */
        irpIterator = pipe->irpQueueHead;

        /* Find the last IRP in the linked list*/
        while(irpIterator->next != 0)
        {
            irpIterator = irpIterator->next;
        }

        /* Add the item to the last irp in the linked list */
        irpIterator->next = irp;
        irp->previous = irpIterator;
    }

    if(!hDriver->isInInterruptContext)
    {
        if(interruptWasEnabled)
        {
            _DRV_USB_InterruptSourceEnable(hDriver->interruptSource);
        }
        //OSAL: Return Mutex
        if(OSAL_MUTEX_Unlock(&hDriver->mutexID) != OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
        }
    }

    return USB_ERROR_NONE;
}/* end of DRV_USB_HOST_IRPSubmit() */

void DRV_USB_HOST_IRPCancel(USB_HOST_IRP * inputIRP)
{
 /* This function cancels an IRP */

    USB_HOST_IRP_LOCAL * irp = (USB_HOST_IRP_LOCAL *) inputIRP;
    DRV_USB_OBJ * hDriver;
    DRV_USB_HOST_PIPE_OBJ * pipe;
    bool interruptWasEnabled = false;

    if(irp->pipe == DRV_USB_HOST_PIPE_HANDLE_INVALID)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid pipe");
        return;
    }

    if(irp->status <= USB_HOST_IRP_STATUS_COMPLETED_SHORT)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "IRP is not pending or in progress");
        return;
    }

    pipe = (DRV_USB_HOST_PIPE_OBJ *)irp->pipe;
    hDriver = (DRV_USB_OBJ *) pipe->hClient;

    if(!hDriver->isInInterruptContext)
    {
        //OSAL: Get Mutex
        if(OSAL_MUTEX_Lock(&(hDriver->mutexID), OSAL_WAIT_FOREVER) !=
                OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
        }
        interruptWasEnabled = _DRV_USB_InterruptSourceDisable(hDriver->interruptSource);
    }

    if(irp->previous == NULL)
    {
        /* This means this was the first
         * irp in the queue. Update the pipe
         * queue head directly */

        pipe->irpQueueHead = irp->next;
        if(irp->next != NULL)
        {
            irp->next->previous = NULL;
        }
    }
    else
    {
        /* Remove the IRP from the linked
         * list */
        irp->previous->next = irp->next;

        if(irp->next != NULL)
        {
            /* This applies if this is not the last
             * irp in the linked list */
            irp->next->previous = irp->previous;
        }
    }

    if(irp->status == USB_HOST_IRP_STATUS_IN_PROGRESS)
    {
        /* If the irp is already in progress then
         * we set the temporary state. This will get
         * caught in _DRV_USB_HOST_ControlXferProcess()
         * and _DRV_USB_HOST_NonControlIRPProcess()
         * functions. */

        irp->tempState = DRV_USB_HOST_IRP_STATE_ABORTED;
    }
    else
    {
        irp->status = USB_HOST_IRP_STATUS_ABORTED;
        if(irp->callback != NULL)
        {
            irp->callback((USB_HOST_IRP *)irp);
        }
    }

    if(!hDriver->isInInterruptContext)
    {
        if(interruptWasEnabled)
        {
            _DRV_USB_InterruptSourceEnable(hDriver->interruptSource);
        }
        //OSAL: Release Mutex
        if(OSAL_MUTEX_Unlock(&hDriver->mutexID) != OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
        }
    }
}/* end of DRV_USB_HOST_IRPCancel() */

void DRV_USB_HOST_PipeClose
(
    DRV_USB_HOST_PIPE_HANDLE pipeHandle
)
{
 /* This function closes an open pipe */

    bool                        interruptWasEnabled = false;
    DRV_USB_OBJ                 * hDriver;
    USB_HOST_IRP_LOCAL          * irp;
    DRV_USB_HOST_PIPE_OBJ       * pipe;
    DRV_USB_HOST_TRANSFER_GROUP * transferGroup;
    DRV_USB_HOST_ENDPOINT_OBJ   * endpointObj;
    USBHS_MODULE_ID               usbID;
    unsigned int direction;

    uint8_t *pFifoTable;
    uint8_t startingSlot;
    uint8_t byteLoop;
    uint8_t bitLoop;
    bool slotObtained = false;

    /* Make sure we have a valid pipe */
    if(pipeHandle == DRV_USB_HOST_PIPE_HANDLE_INVALID)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid pipe handle");
        return;
    }

    pipe = (DRV_USB_HOST_PIPE_OBJ*) pipeHandle;
    direction = (pipe->endpointAndDirection & 0x80) >> 7;

    /* Make sure tha we are working with a pipe
     * in use */
    if(pipe->inUse != true)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Pipe is not in use");
        return;
    }

    hDriver = (DRV_USB_OBJ *)pipe->hClient;
    usbID = hDriver->usbID;

    /* Disable the interrupt */

    if(!hDriver->isInInterruptContext)
    {
        //OSAL: Get Mutex
        if(OSAL_MUTEX_Lock(&hDriver->mutexID, OSAL_WAIT_FOREVER) !=
                OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
        }
        interruptWasEnabled = _DRV_USB_InterruptSourceDisable(hDriver->interruptSource);
    }

    if(USB_TRANSFER_TYPE_CONTROL == pipe->pipeType)
    {
        transferGroup = &hDriver->controlTransferGroup;

        if(pipe->previous == NULL)
        {
            /* The previous pipe could be null
             * if this was the first pipe in the
             * transfer group */

            transferGroup->pipe = pipe->next;
            if(pipe->next != NULL)
            {
                pipe->next->previous = NULL;
            }
        }
        else
        {
            /* Remove this pipe from the linked
             * list */

            pipe->previous->next = pipe->next;
            if(pipe->next != NULL)
            {
                pipe->next->previous = pipe->previous;
            }
        }

        if(transferGroup->nPipes != 0)
        {
            /* Reduce the count only if its
             * not zero already */

            transferGroup->nPipes --;
        }
    }
    else
    {
        /* Non control tranfer pipes are not stored as groups.
         * We deallocate the endpoint object that this pipe used */

        endpointObj = &hDriver->hostEndpointTable[pipe->hostEndpoint];
        endpointObj->endpoints[direction].inUse = false;
        endpointObj->endpoints[direction].pipe = NULL;


        if(direction == USB_DATA_DIRECTION_DEVICE_TO_HOST)
        {
            /* Clear the error status on and flush the fifo
             * on receive endpoint */

            
            PLIB_USBHS_EndpointRxFIFOFlush(usbID, pipe->hostEndpoint);
            PLIB_USBHS_RxEPStatusClear(usbID, pipe->hostEndpoint, USBHS_RXEP_ERROR_ALL);
            PLIB_USBHS_EndpointRxRequestClear(usbID, pipe->hostEndpoint);
        }
        else
        {
            /* Clear the error status on and flush the fifo
             * on transmit endpoint */
            PLIB_USBHS_EndpointTxFIFOFlush(usbID, pipe->hostEndpoint);
            PLIB_USBHS_TxEPStatusClear(usbID, pipe->hostEndpoint, USBHS_TXEP_ERROR_ALL);

        }
    }

    /* Now we invoke the call back for each IRP
     * in this pipe and say that it is aborted.
     * If the IRP is in progress, then that IRP
     * will be actually aborted on the next SOF
     * This will allow the USB module to complete
     * any transaction that was in progress. */

    irp = (USB_HOST_IRP_LOCAL *)pipe->irpQueueHead;
    while(irp != NULL)
    {
        irp->pipe = DRV_USB_HOST_PIPE_HANDLE_INVALID;

        if(irp->status == USB_HOST_IRP_STATUS_IN_PROGRESS)
        {
            /* If the IRP is in progress, then we set the
             * temp IRP state. This will be caught in
             * the _DRV_USB_HOST_NonControlIRPProcess()
             * and _DRV_USB_HOST_ControlXferProcess()
             * functions */
            irp->status = USB_HOST_IRP_STATUS_ABORTED;
            if(irp->callback != NULL)
            {
                irp->callback((USB_HOST_IRP*)irp);
            }
            irp->tempState = DRV_USB_HOST_IRP_STATE_ABORTED;
        }
        else
        {
            /* IRP is pending */
            irp->status = USB_HOST_IRP_STATUS_ABORTED;
            if(irp->callback != NULL)
            {
                irp->callback((USB_HOST_IRP*)irp);
            }
        }
        irp = irp->next;
    }

    /* Update the consumed FIFO size for non control
     * transfers. Control transfers have a dedicated FIFO
     * that is the first 64 bytes */

    if(USB_TRANSFER_TYPE_CONTROL != pipe->pipeType)
    {
        pFifoTable = (uint8_t *)(hDriver->gDrvUSBFifoTable);
        startingSlot = pipe->startingOffset/8;

        for(byteLoop = 1; byteLoop <=18; byteLoop++)
        {
            for(bitLoop=0; bitLoop <=7; bitLoop++)
            {
                /*
                 * The design here is to find the starting slot in the FiFoTable.
                 * Once found, we will start reseting all the slots allocated.
                 * We need not check for the slot value as slots during allocation
                 * needs to be continous. No segmented slots for a particluar
                 * pipe is possible.
                 */
                if( (slotObtained == false) && (( ((byteLoop - 1) * 8) + 1 + bitLoop) == startingSlot) )
                {
                    /* Starting Slot found. Reset the slot. Make sure it never
                     * enters this if() loop again for this pipe close operation
                     */
                    *pFifoTable = ( *pFifoTable & ~(0x01 << bitLoop) );
                    slotObtained = true;
                    pipe->noOfSlots--;
                }
                else if(slotObtained == true)
                {
                    /* Slot already found before.
                     * We can just continuing resetting all the slots allocated
                     * for the pipe.*/
                    *pFifoTable = ( *pFifoTable & ~(0x01 << bitLoop) );
                    pipe->noOfSlots--;
                }
                if(pipe->noOfSlots == 0)
                {
                    /* Done releasing slots. Exit the inner loop */
                    break;
                }
            }/* end of bitLoop */
            if((pipe->noOfSlots == 0))
            {
                /* Done releasing slots. Exit the outer loop */
                break;
            }
            pFifoTable++;
        }/* end of byteloop */
        if((pipe->noOfSlots != 0))
        {
            /* This is error scenaario */
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Error in releasing Fifo Table");
        }
    }

    /* Now we return the pipe back to the
     * driver */
    pipe->inUse = false ;

    /* Enable the interrupts */
    if(!hDriver->isInInterruptContext)
    {
        if(interruptWasEnabled)
        {
            _DRV_USB_InterruptSourceEnable(hDriver->interruptSource);
        }
        //OSAL: Return Mutex
        if(OSAL_MUTEX_Unlock(&hDriver->mutexID) != OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
        }
    }
}/* end of DRV_USB_HOST_PipeClose() */


DRV_USB_HOST_PIPE_HANDLE DRV_USB_HOST_PipeSetup
(
    DRV_HANDLE client,
    uint8_t deviceAddress,
    USB_ENDPOINT endpointAndDirection,
    uint8_t hubAddress,
    uint8_t hubPort,
    USB_TRANSFER_TYPE pipeType,
    uint8_t bInterval,
    uint16_t wMaxPacketSize,
    USB_SPEED speed
)
{
    int pipeIter;
    int fifoSize;
    bool epFound;
    uint8_t epIter;
    uint8_t endpoint;
    USBHS_MODULE_ID usbID;
    unsigned int epDirection;
    unsigned int shiftWord;
    unsigned int i, j, accumulate;

    DRV_USB_OBJ * hDriver;
    DRV_USB_HOST_PIPE_OBJ * pipe, * iteratorPipe;
    DRV_USB_HOST_TRANSFER_GROUP * transferGroup;
  
    if(client == DRV_HANDLE_INVALID)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid client handle");
        return DRV_USB_HOST_PIPE_HANDLE_INVALID;
    }

    if((speed == USB_SPEED_LOW) || (speed == USB_SPEED_FULL))
    {
        if(pipeType != USB_TRANSFER_TYPE_CONTROL)
        {
            if(wMaxPacketSize < 8)
            {
                wMaxPacketSize = 8;
            }
        }
    }

    if((wMaxPacketSize < 8) ||(wMaxPacketSize > 4096))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid pipe endpoint size");
        return DRV_USB_HOST_PIPE_HANDLE_INVALID;
    }

    /* Need to make sure that wMaxPacketSize is equal to
     * 2 to the power n where n is 3 >= n <= 12*/

    for(i = 3; i <= 12; i ++)
    {
        accumulate = 1;

        for (j = 0; j < i; j ++)
        {
            accumulate *= 2;
        }

        /* At this point accumulate will be
         * either 8 or 16 or 32...4096. Check
         * specified wMaxPacketSize against this. */

        if(wMaxPacketSize == accumulate)
        {
            /* This means the we dont have to do any adjustment*/

            break;
        }

        if((wMaxPacketSize > accumulate) &&
                (wMaxPacketSize < (accumulate * 2)))
        {
            /* This means the wMaxPacketSize is between
             * two valid ranges. Set wMaxPacketSize to the
             * higher range. */

            wMaxPacketSize = accumulate * 2;
            break;
        }
    }

    hDriver = (DRV_USB_OBJ *)client;
    endpoint = (endpointAndDirection & 0x7F);
    epDirection = (endpointAndDirection & 0x80) >> 7;

    usbID = hDriver->usbID;

    /* There are two things that we need to check
     * before we allocate a pipe. We check if
     * have a free pipe object and check if we have 
     * a free endpoint that we can use */

    /* All control transfer pipe are grouped together
     * as a linked list of pipes. Non control transfer
     * pipes are organized individually */

    /* We start by searching for a free pipe */

    //OSAL - mutex lock */
    if(OSAL_MUTEX_Lock(&hDriver->mutexID, OSAL_WAIT_FOREVER) !=
                OSAL_RESULT_TRUE)
    {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
    }

    for(pipeIter = 0; pipeIter < DRV_USB_HOST_PIPES_NUMBER; pipeIter ++)
    {
        if(gDrvUSBHostPipeObj[pipeIter].inUse == false)
        {
            /* This means we have found a free pipe object */

            pipe = &gDrvUSBHostPipeObj[pipeIter];

            if(pipeType != USB_TRANSFER_TYPE_CONTROL)
            {
                /* For non control transfer we need a free
                 * non zero endpoint object. */

                epFound = false;
                for(epIter = 1; 
                        epIter < DRV_USB_HOST_MAXIMUM_ENDPOINTS_NUMBER;
                        epIter ++)
                {
                    if(hDriver->hostEndpointTable[epIter]
                            .endpoints[epDirection].inUse == false)
                    {
                        /* This means we have found an endpoint. Capture
                         * this endpoint and indicate that we have found
                         * an endpoint */

                        epFound = true;
                        hDriver->hostEndpointTable[epIter].endpoints[epDirection].inUse = true;
                        hDriver->hostEndpointTable[epIter].endpoints[epDirection].pipe = pipe;

                        /* The following code maps the endpoint size to the value 
                         * that should be loaded in the FIFOSZ register */

                        fifoSize = 0;
                        shiftWord = wMaxPacketSize;

                        while((shiftWord & 0x1) != 1)
                        {
                            shiftWord = (shiftWord >> 1);
                            fifoSize ++;
                        }
                        fifoSize -= 3;

                        if(_DRV_USB_HOST_FifoTableAllocate(hDriver,pipe,wMaxPacketSize)
                                    == DRV_USB_HOST_PIPE_HANDLE_INVALID)
                        {
                            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Could not obtain FIFO");
                            return DRV_USB_HOST_PIPE_HANDLE_INVALID;
                        }
                        if(USB_DATA_DIRECTION_DEVICE_TO_HOST == epDirection)
                        {
                            /* This means host is receiving data. We need to
                             * setup all receive related registers. Setup the
                             * maximum packet size, fifo size, fifo start
                             * address,  target function address, rx type
                             * register, hub address and hub port  */

                            PLIB_USBHS_HostRxEndpointConfigure
                            (
                                usbID,          /* USB Module ID */
                                epIter,         /* Host Endpoint */
                                speed,          /* Endpoint speed */
                                pipeType,       /* Pipe Type */
                                wMaxPacketSize, /* Endpoint Size */
                                pipe->startingOffset,/* FIFO Address */
                                fifoSize,       /* FIFO size */
                                endpoint,       /* Target Endpoint */
                                deviceAddress,  /* Target Address */
                                hubAddress,     /* Target Hub Address */
                                hubPort,        /* Target Hub Port */
                                bInterval       /* NAK or period interval */
                            );
                        }
                        else
                        {
                            /* This means data flows host to device. We must
                             * setup TX registers */

                            PLIB_USBHS_HostTxEndpointConfigure
                            (
                                usbID,              /* USB Module ID */
                                epIter,             /* Host Endpoint */
                                speed,              /* Endpoint speed */
                                pipeType,           /* Pipe Type */
                                wMaxPacketSize,     /* Endpoint Size */
                                pipe->startingOffset,/* FIFO Address */
                                fifoSize,       /* FIFO size */
                                endpoint,       /* Target Endpoint */
                                deviceAddress,  /* Target Address */
                                hubAddress,     /* Target Hub Address */
                                hubPort,        /* Target Hub Port */
                                bInterval       /* NAK or period interval */
                            );
                        }
                        break;
                    }
                } /* End of search for host endpoint */

                if(!epFound)
                {
                    /* This means we could not find a spare endpoint for this
                     * non control transfer. */

                    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Could not allocate endpoint");
                    //OSAL mutex unlock
                    if(OSAL_MUTEX_Unlock(&hDriver->mutexID) != OSAL_RESULT_TRUE)
                    {
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
                    }
                    return DRV_USB_HOST_PIPE_HANDLE_INVALID;
                }
            } /* End of non zero endpoint handling */
            else
            {
                /* Set epIter to zero to indicate that we must
                 * use endpoint 0 for control transfers. We also
                 * add the control transfer pipe to the control
                 * transfer group. */

                epIter = 0;

                transferGroup = &hDriver->controlTransferGroup;

                if(transferGroup->pipe == NULL)
                {
                    /* This if the first pipe to be setup */

                    transferGroup->pipe = pipe;
                    transferGroup->currentPipe = pipe;
                    pipe->previous = NULL;
                }
                else
                {
                    /* This is not the first pipe. Find
                     * the last pipe in the linked list */

                    iteratorPipe = transferGroup->pipe;
                    while(iteratorPipe->next != NULL)
                    {
                        /* This is not the last pipe in 
                         * this transfer group */
                        iteratorPipe = iteratorPipe->next;
                    }
                    iteratorPipe->next = pipe;
                    pipe->previous = iteratorPipe;
                }
                pipe->next = NULL;

                /* Update the pipe count in the transfer 
                 * group */

                transferGroup->nPipes ++;

            }

            /* Setup the pipe object */
            pipe->inUse         = true;
            pipe->deviceAddress = deviceAddress;
            pipe->irpQueueHead  = NULL;
            pipe->bInterval     = bInterval;
            pipe->speed         = speed;
            pipe->hubAddress    = hubAddress;
            pipe->hubPort       = hubPort;
            pipe->pipeType      = pipeType;
            pipe->hClient       = client;
            pipe->endpointSize  = wMaxPacketSize;
            pipe->intervalCounter = bInterval;
            pipe->hostEndpoint  = epIter;
            pipe->endpointAndDirection   = endpointAndDirection;

            // OSAL release mutex
            if(OSAL_MUTEX_Unlock(&hDriver->mutexID) != OSAL_RESULT_TRUE)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
            }
            return((DRV_USB_HOST_PIPE_HANDLE)pipe);
        }
    }

    /* This means that we could not find a free
     * pipe object */
    //OSAL mutex release
    if(OSAL_MUTEX_Unlock(&hDriver->mutexID) != OSAL_RESULT_TRUE)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
    }
    return(DRV_USB_HOST_PIPE_HANDLE_INVALID);
}/* end of DRV_USB_HOST_PipeSetup() */

void _DRV_USB_HOST_ControlTransferProcess(DRV_USB_OBJ * hDriver)
{
    /* This function is called every time there is an endpoint 0
     interrupt. This means that a stage of the current control IRP
     has been completed. This function is called from an interrupt
     context */

    uint8_t status;
    USB_HOST_IRP_LOCAL * irp;
    DRV_USB_HOST_PIPE_OBJ * pipe, * iterPipe;
    DRV_USB_HOST_TRANSFER_GROUP * transferGroup;
    bool endIRP = false;
    unsigned int count, i;
    bool foundIRP = false;
    bool isDmaUsed = false;
    USBHS_MODULE_ID usbID;

    transferGroup = &hDriver->controlTransferGroup;
    usbID = hDriver->usbID;

    /* First check if the IRP was aborted */
    irp = transferGroup->currentIRP;
    pipe = transferGroup->currentPipe;

    /* If current IRP is null, or current pipe is null
     * then we have unknow failure. We just quit.
     * Nothing we can do.*/

    if((irp == NULL) || (pipe == NULL) ||
            (pipe == (DRV_USB_HOST_PIPE_OBJ *)DRV_USB_HOST_PIPE_HANDLE_INVALID))
    {
        /* Unknown error */
        return;
    }

    /* If here means, we have a valid IRP and pipe.  Check the status register.
     * The IRP could have been aborted. This would be known in the temp state.
     * */

    status = PLIB_USBHS_EP0StatusGet(usbID);
    if(irp->tempState == DRV_USB_HOST_IRP_STATE_ABORTED)
    {
        /* This means the application has aborted this
         IRP.*/

        endIRP = true;
        irp->status = USB_HOST_IRP_STATUS_ABORTED;

        /* Clear up the error status and we must also flush the fifo */

        PLIB_USBHS_EP0StatusClear(usbID, USBHS_EP0_ERROR_ALL);
        PLIB_USBHS_Endpoint0FIFOFlush(usbID);
    }
    else if(status & USBHS_EP0_ERROR_RXSTALL)
    {
        /* This means the packet was stalled. Set the
         * error status and then clear the stall bit */

        endIRP = true;
        irp->status = USB_HOST_IRP_STATUS_ERROR_STALL;
        PLIB_USBHS_EP0StatusClear(usbID, USBHS_EP0_ERROR_RXSTALL);
    }
    else if(status & USBHS_EP0_ERROR_NAK_TIMEOUT)
    {
        /* This means a NAK Time Out has occurred. Clear the
         * error status.  */

        endIRP = true;
        irp->status = USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT;
        PLIB_USBHS_EP0StatusClear(usbID, USBHS_EP0_ERROR_NAK_TIMEOUT);
    }
    else if(status & USBHS_EP0_ERROR_BUS)
    {
        /* This means there was an bus error. The packet
         * was tried three times and was not successfully 
         * processed */

        endIRP = true;
        irp->status = USB_HOST_IRP_STATUS_ERROR_DATA;
        PLIB_USBHS_EP0StatusClear(usbID, USBHS_EP0_ERROR_BUS);
    }
    else
    {
        /* This means there was no error. We should check
         * the current state of the IRP and then proceed
         * accordingly */

       switch(irp->tempState)
       {
           case DRV_USB_HOST_IRP_STATE_SETUP_STAGE:

               /* We got an interrupt after this stage. This 
                * means that the setup stage has completed.
                * We need to check if a data stage is required
                * and then start the data stage. */

               if((irp->data == NULL) || (irp->size == 0))
               {
                   /* This means there is no data stage. We can
                    * proceed to the handshake stage. In a case where
                    * there isnt a data stage, we need to send an IN
                    * token to the device to the device */

                   irp->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE_SENT;
                   PLIB_USBHS_EP0INHandshakeSend(usbID);
               }
               else
               {
                   /* This means that a data stage is required. We can
                    * find out the direction of the data stage by 
                    * investigating the flags parameter of the  
                    * IRP. */

                   irp->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE_SENT;
                   if(irp->flags & 0x8000)

                   {
                       /* This means the data stage moves from
                        * device to host. So the host would 
                        * have to send an IN token. 
                        *  */

                       PLIB_USBHS_EP0INTokenSend(usbID);
                   }
                   else
                   {
                       /* This function loads the fifo and sends the
                        * packet. The completed bytes field in the
                        * IRP will be updated. */

                       _DRV_USB_HOST_IRPTransmitFIFOLoad(usbID, irp, 0);
                   }
               }
               break;

           case DRV_USB_HOST_IRP_STATE_DATA_STAGE_SENT:

               /* We reach here after an interrupt which means that
                * a data stage interaction was completed. Find out what
                * was the direction the data stage */

               if(irp->flags & 0x8000)
               {
                   /* This means the data was moving from device
                    * to host. We got an interrupt, which means we
                    * have received data. Start by checking how much
                    * data we received from the device */

                   count = _DRV_USB_HOST_IRPReceiveFIFOUnload(usbID, irp, 0,
                           &isDmaUsed);

                   if((count < pipe->endpointSize) ||
                           (irp->completedBytes >= irp->size))
                   {
                       /* This means that we either received
                        * a short packet or we received the amount
                        * of data that we needed. We should
                        * move to the handshake stage. Send the  */

                       irp->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE_SENT;
                       PLIB_USBHS_EP0OUTHandshakeSend(usbID);

                   }
                   else
                   {
                       /* This means this is a multi stage control
                        * read transfer. Issue another IN token */

                       PLIB_USBHS_EP0INTokenSend(usbID);
                       break;
                   }
               }
               else
               {
                   /* Data stage was moving from host to device.
                    * Check if we need to send more data */

                   if(irp->completedBytes < irp->size)
                   {
                       _DRV_USB_HOST_IRPTransmitFIFOLoad(usbID, irp, 0);
                   }
                   else
                   {
                       /* We can move to the status stage */
                       irp->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE_SENT;
                       PLIB_USBHS_EP0INHandshakeSend(usbID);
                   }
               }
               break;

           case DRV_USB_HOST_IRP_STATE_HANDSHAKE_SENT:

               /* If we have reached here, it means that status
                * stage has completed. Check the direction of
                * the data stage, update the irp status flag
                * and then end the irp. */

               irp->status = USB_HOST_IRP_STATUS_COMPLETED;
               
               if(irp->flags & 0x8000)
               {
                   /* This means the data stage moved from
                    * device to host. We need to check the number
                    * of bytes the host sent. If it was less
                    * than expected, then irp status should
                    * say so */

                   if(irp->completedBytes < irp->size)
                   {
                       irp->size = irp->completedBytes;
                       irp->status = USB_HOST_IRP_STATUS_COMPLETED_SHORT;
                   }
               }
               else
               {
                   /* We need to clear the Status Pakcet bit and
                    the Rx packet ready bit */
                   PLIB_USBHS_EP0INHandshakeClear(usbID);
               }
               endIRP = true;
               break;

           default:
               break;
       }
    }

    if(endIRP)
    {
        /* This means this IRP needs to be terminated
         * and new one started. */

        if(irp->callback != NULL)
        {
            irp->callback((USB_HOST_IRP *)irp);
        }

        /* Expire the IRP */

        pipe->irpQueueHead = irp->next;

        /* Now we need to check if any more IRPs are
         * in this group are pending. We start searching
         * from the current pipe onwards. If we dont find
         * another pipe with an IRP, we should land back on
         * the current pipe and check if we have a IRP to 
         * process */

        iterPipe = transferGroup->currentPipe->next;
        for(i = 0; i < transferGroup->nPipes; i ++)
        {
            if(iterPipe == NULL)
            {
                /* We have reached the end of the pipe 
                 * group. Rewind the pipe iterator to
                 * the start of the pipe group. */

                iterPipe = transferGroup->pipe;
            }

            /* This means that we have a valid pipe.
             * Now check if there is irp to be processed. */

            if(iterPipe->irpQueueHead != NULL)
            {
                foundIRP = true;
                transferGroup->currentPipe = iterPipe;
                transferGroup->currentIRP = iterPipe->irpQueueHead;
                break;
            }

            iterPipe = iterPipe->next;
        }

        if(foundIRP)
        {
            /* This means we have found another IRP to 
             * process. We must load the endpoint. */
            
            irp = transferGroup->currentIRP;
            pipe = transferGroup->currentPipe;
            irp->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
            irp->tempState = DRV_USB_HOST_IRP_STATE_SETUP_STAGE;

            /* We need to update the flags parameter of the IRP
             * to indicate the direction of the control transfer. */

            if(*((uint8_t*)(irp->setup)) & 0x80)
            {
                /* This means the data stage moves from device to
                 * host. Set bit 15 of the flags parameter */
               irp->flags |= 0x8000;
            }
            else
            {
                /* This means the data stage moves from host to
                 * device. Clear bit 15 of the flags parameter. */
                irp->flags &= 0x7FFF;
            }

            /* Send the setup packet to the device */
            _DRV_USB_HOST_IRPTransmitSetupPacket(usbID, irp);
        }
        else
        {
            /* This means we dont have an IRP. Set
             * the current IRP and current pipe to 
             * NULL to indicate that we dont have
             * any active IRP */

            transferGroup->currentPipe = NULL;
            transferGroup->currentIRP = NULL;
        }
    }

    return;
}/* end of _DRV_USB_HOST_ControlTransferProcess() */

void _DRV_USB_HOST_NonControlTransferProcess(DRV_USB_OBJ * hDriver,
        uint8_t endpoint, unsigned int direction)
{
    /* This function processes non zero endpoint transfers which
     would bulk, interrupt and isochronous transfers */

    DRV_USB_HOST_ENDPOINT_OBJ * endpointTable = &(hDriver->hostEndpointTable[0]);
    DRV_USB_HOST_PIPE_OBJ * pipe;
    USB_HOST_IRP_LOCAL * irp;
    uint8_t status;
    bool endIRP = false;
    bool isDmaUsed = false;
    unsigned int count;
    USBHS_MODULE_ID usbID;

    endpointTable += endpoint;
    usbID = hDriver->usbID;

    pipe = endpointTable->endpoints[direction].pipe;

    if((!endpointTable->endpoints[direction].inUse) ||
       (pipe == NULL) ||
       (pipe == (DRV_USB_HOST_PIPE_OBJ *)(DRV_USB_HOST_PIPE_HANDLE_INVALID)))
    {
        /* This means the pipe was closed. We dont do anything */
        return;
    }

    irp = pipe->irpQueueHead;

    if(USB_DATA_DIRECTION_HOST_TO_DEVICE == direction)
    {
        /* We got an interrupt for data moving from host to
         * to device. Check if there were any transmission
         * errors. Then check if there is any more data to be
         * sent in the IRP. If we are done, then end the IRP
         * and start a new one. */

        status = PLIB_USBHS_TxEPStatusGet(usbID, endpoint);
        /* Check if the IRP was aborted */
        if(irp->tempState == DRV_USB_HOST_IRP_STATE_ABORTED)
        {
            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ABORTED;

            /* Clear the error bits and the FIFO */
            PLIB_USBHS_TxEPStatusClear(usbID, endpoint, USBHS_TXEP_ERROR_ALL);
            PLIB_USBHS_EndpointTxFIFOFlush(usbID, endpoint);
        }
        else if(status & USBHS_TXEP_ERROR_RXSTALL)
        {
            /* This means the packet was stalled. Set the
             * error status and then clear the stall bit */

            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ERROR_STALL;
            PLIB_USBHS_TxEPStatusClear(usbID, endpoint, USBHS_TXEP_ERROR_RXSTALL);

        }
        else if(status & USBHS_TXEP_ERROR_NAK_TIMEOUT)
        {
            /* This means a NAK Time Out has occurred. Clear the
             * error status.  */

            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT;
            PLIB_USBHS_TxEPStatusClear(usbID, endpoint, USBHS_TXEP_ERROR_NAK_TIMEOUT);
        }
        else if(status & USBHS_TXEP_ERROR_BUS)
        {
            /* This means there was an bus error. The packet
             * was tried three times and was not successfully
             * processed */

            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ERROR_DATA;
            PLIB_USBHS_TxEPStatusClear(usbID, endpoint, USBHS_TXEP_ERROR_BUS);
        }
        else
        {
            /* This means this transaction completed successfully.
             * We should check if there are any spare bytes remaining
             * to be sent and then send it */

            if(irp->completedBytes >= irp->size)
            {
                endIRP = true;
                irp->status = USB_HOST_IRP_STATUS_COMPLETED;
            }
            else
            {
                /* This means we have more data to send */
                endIRP = false;

                /* This function will load the next packet for this IRP into
                 * the endpoint FIFO and then transmit it. */
                _DRV_USB_HOST_IRPTransmitFIFOLoad(usbID, irp, endpoint);
            }
        }

        if(endIRP)
        {
            /* This means we need to end the IRP */

            pipe->irpQueueHead = irp->next;

            if(irp->callback)
            {
                /* Invoke the call back*/
                irp->callback((USB_HOST_IRP *)irp);
            }

            irp = pipe->irpQueueHead;

            if((irp != NULL) && (!(irp->status == USB_HOST_IRP_STATUS_IN_PROGRESS)))
            {
                /* We do have another IRP to process. */
                irp->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
                _DRV_USB_HOST_IRPTransmitFIFOLoad(usbID, irp, endpoint);
            }
        }
    }
    else
    {
         /* We got an interrupt for data moving from device to
         * to host. Check if there were any receptions
         * errors. Then check if there is any more data to be
         * received in the IRP. If we are done, then end the IRP
         * and start a new one. */

        status = PLIB_USBHS_RxEPStatusGet(usbID, endpoint);

        /* Check if the IRP was aborted */
        if(irp->tempState == DRV_USB_HOST_IRP_STATE_ABORTED)
        {
            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ABORTED;

            /* Clear the error flags and then flush the fifo if a data is
             * available */
            PLIB_USBHS_RxEPStatusClear(usbID, endpoint, USBHS_RXEP_ERROR_ALL);
            PLIB_USBHS_EndpointRxFIFOFlush(usbID, endpoint);
        }
        else if(status & USBHS_RXEP_ERROR_RXSTALL)
        {
            /* This means the packet was stalled. Set the
             * error status and then clear the stall bit */

            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ERROR_STALL;
            PLIB_USBHS_RxEPStatusClear(usbID, endpoint, USBHS_RXEP_ERROR_RXSTALL);
            PLIB_USBHS_EndpointRxFIFOFlush(usbID, endpoint);
        }
        else if(status & USBHS_RXEP_ERROR_NAK_TIMEOUT)
        {
            /* This means a NAK Time Out has occurred. Clear the
             * error status.  */

            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT;
            PLIB_USBHS_RxEPStatusClear(usbID, endpoint, USBHS_RXEP_ERROR_NAK_TIMEOUT);
            PLIB_USBHS_EndpointRxFIFOFlush(usbID, endpoint);
        }
        else if(status & USBHS_RXEP_ERROR_BUS)
        {
            /* This means there was an bus error. The packet
             * was tried three times and was not successfully
             * processed */

            endIRP = true;
            irp->status = USB_HOST_IRP_STATUS_ERROR_DATA;
            PLIB_USBHS_RxEPStatusClear(usbID, endpoint, USBHS_RXEP_ERROR_BUS);
            PLIB_USBHS_EndpointRxFIFOFlush(usbID, endpoint);
        }
        else
        {
            /* This means that data was received without errors. */

            count = _DRV_USB_HOST_IRPReceiveFIFOUnload(usbID, irp, endpoint, &isDmaUsed);
            if(isDmaUsed == false)
            {
                if((count < pipe->endpointSize) ||
                        (irp->completedBytes >= irp->size))
                {
                    endIRP = true;
                    irp->status = USB_HOST_IRP_STATUS_COMPLETED;

                    if(irp->completedBytes < irp->size)
                    {
                        /* This means the device ended the transfer and
                         * and we have a short transfer */
                        irp->status = USB_HOST_IRP_STATUS_COMPLETED_SHORT;
                    }

                    /* Update the actual amount of data received */
                    irp->size = irp->completedBytes;
                }
                else
                {
                    /* This means we have more data to send
                     * We request another packet */

                    endIRP = false;
                    PLIB_USBHS_RxEPINTokenSend(usbID, endpoint);
                }
            }
            else
            {
                /* DMA has been used. Do not end the IRP here.
                 It will be done in DMA ISR handler */
                endIRP = false;
            }
        }

        if(endIRP)
        {
            /* This means we need to end the IRP */

            pipe->irpQueueHead = irp->next;
          
            if(irp->callback)
            {
                /* Invoke the call back*/
                irp->callback((USB_HOST_IRP *)irp);
            }

            irp = pipe->irpQueueHead;

            /* A IRP could have been submitted in the callback. If that is the case
             * and the IRP status would indicate that it already in progress. If
             * the IRP in the queue head is not in progress then we shold initiate
             * the transaction */

            if((irp != NULL) && (!(irp->status == USB_HOST_IRP_STATUS_IN_PROGRESS)))
            {
                irp->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
                
                /* We do have another IRP to process. Request for
                 * an IN packet. */

                PLIB_USBHS_RxEPINTokenSend(usbID, endpoint);
            }
        }
    }
}/* end of _DRV_USB_HOST_NonControlTransferProcess() */

void _DRV_USB_HOST_Tasks_ISR(DRV_USB_OBJ * hDriver)
{
    unsigned int i;
    USBHS_GEN_INTERRUPT interruptStatus;
    USBHS_EPTXRX_INTERRUPT interruptRxStatus;
    USBHS_EPTXRX_INTERRUPT interruptTxStatus;
   
    USBHS_MODULE_ID usbID = hDriver->usbID;

    interruptStatus = PLIB_USBHS_GenInterruptFlagsGet(usbID);

    DRV_USB_EVENT_CALLBACK eventHandler = NULL ;
    
    if(hDriver->isOpened != false)
    {
        /* This means we have valid client. 
         * Get the event handler */

        eventHandler = hDriver->pEventCallBack;
    }
    
    if(interruptStatus & USBHS_GENINT_DEVCONN)
    {
        /* This means we got an attach interrupt */
        
        if(eventHandler != NULL)
        {
            eventHandler(hDriver->hClientArg, DRV_USB_EVENT_HOST_ATTACH, NULL);
        }

    }
    else if(interruptStatus & USBHS_GENINT_DEVDISCONN)
    {
        /* This means we got an detach interrupt. Clear
         * all other interrupts */
        
        //interruptTxStatus = PLIB_USBHS_TxInterruptFlagsGet(usbID);
        //interruptRxStatus = PLIB_USBHS_RxInterruptFlagsGet(usbID);

        if(eventHandler != NULL)
        {
            eventHandler(hDriver->hClientArg, DRV_USB_EVENT_HOST_DETACH, NULL);
        }

        /* Dont do any thing else if a detach interrupt has occurred */
        //return;
    }


    interruptTxStatus = PLIB_USBHS_TxInterruptFlagsGet(usbID);
    interruptRxStatus = PLIB_USBHS_RxInterruptFlagsGet(usbID);

    /* Check if we have an endpoint interrupt */
    
    if(interruptTxStatus & USBHS_TXRXINT_EP0)
    {
        /* Process control transfers */
        _DRV_USB_HOST_ControlTransferProcess(hDriver);
    }

    /* Process non control transfers */
    for(i = 1; i < DRV_USB_HOST_MAXIMUM_ENDPOINTS_NUMBER; i++ )
    {
        if(interruptTxStatus & (1 << i))
        {
            /* This means an interrupt occurred on a non
             * zero endpoint. */

            _DRV_USB_HOST_NonControlTransferProcess(hDriver, i,
                    USB_DATA_DIRECTION_HOST_TO_DEVICE);

        }

        if(interruptRxStatus & (1 << i))
        {
            /* This means an receive endpoint interrupt occurred
             * on a non zero endpoint. */

            _DRV_USB_HOST_NonControlTransferProcess(hDriver, i,
                    USB_DATA_DIRECTION_DEVICE_TO_HOST);
        }
    }
}/* end of _DRV_USB_HOST_Tasks_ISR() */

void _DRV_USB_HOST_Tasks_ISR_USBDMA(DRV_USB_OBJ * hDriver)
{
    USBHS_MODULE_ID usbID = hDriver->usbID;
    uint8_t usbDMAInterrupts;
    uint8_t  iEndpoint;
    uint8_t usbDMAChannel = 0;
    bool endpointDir;
    bool usbDMAError = false;
    bool endIRP = false;
    USB_HOST_IRP_LOCAL * irp = (USB_HOST_IRP_LOCAL *)NULL;

    if(!hDriver->isOpened)
    {
        /* We need a valid client */
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Driver does not have a client");
        return;
    }

    if(hDriver->pEventCallBack == NULL)
    {
        /* We need a valid event handler */
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Driver needs a event handler");
        return;
    }

    /* Reading the interrupt flags will cause the
     * flags to get cleared */
    usbDMAInterrupts = PLIB_USBHS_DMAInterruptGet(usbID);

    for(usbDMAChannel = 1; usbDMAChannel < 9; usbDMAChannel++)
    {
        if((usbDMAInterrupts >> (usbDMAChannel - 1)) & 0x01)
        {
            /* DMA interrupt set for this channel.
             * Map the EP it is assigned for
             */
            usbDMAError = PLIB_USBHS_DMAErrorGet(usbID, usbDMAChannel);
            if(usbDMAError == true)
            {
                continue;
            }
            iEndpoint = hDriver->gDrvUSBDMAPool[usbDMAChannel].iEndpoint;
            endpointDir = hDriver->gDrvUSBDMAPool[usbDMAChannel].endpointDir;

            /* Check the EP direction */
            if(endpointDir == USB_DATA_DIRECTION_HOST_TO_DEVICE)
            {
                /* This is TX Endpoint */
                irp = hDriver->hostEndpointTable[iEndpoint]
                        .endpoints[endpointDir].pipe->irpQueueHead;
                irp->completedBytes +=
                        hDriver->gDrvUSBDMAPool[usbDMAChannel].count;
                PLIB_USBHS_DeviceTxEndpointPacketReady(usbID, iEndpoint);
                /* Release the DMA channel */
                hDriver->gDrvUSBDMAPool[usbDMAChannel].inUse = false;
            }
            else
            {
                /* This is RX Endpoint */

                /* Release the DMA channel */
                hDriver->gDrvUSBDMAPool[usbDMAChannel].inUse = false;

                irp = hDriver->hostEndpointTable[iEndpoint]
                        .endpoints[endpointDir].pipe->irpQueueHead;
                irp->completedBytes +=
                        hDriver->gDrvUSBDMAPool[usbDMAChannel].count;

                /* Clear RXPktRDY bit in the corresponding register */
                PLIB_USBHS_RxEPStatusClear(usbID, iEndpoint, USBHS_RXEP_PKTRDY);

                if(((hDriver->gDrvUSBDMAPool[usbDMAChannel].count) <
                        (hDriver->hostEndpointTable[iEndpoint]
                        .endpoints[endpointDir].pipe->endpointSize)) ||
                        (irp->completedBytes >= irp->size))
                {
                    endIRP = true;
                    irp->status = USB_HOST_IRP_STATUS_COMPLETED;

                    if(irp->completedBytes < irp->size)
                    {
                        /* This means the device ended the transfer and
                         * and we have a short transfer */
                        irp->status = USB_HOST_IRP_STATUS_COMPLETED_SHORT;
                    }
                    irp->size = irp->completedBytes;
                }
                else
                {
                    /* This means we have more data to send
                     * We request another packet */

                    endIRP = false;
                    PLIB_USBHS_RxEPINTokenSend(usbID, iEndpoint);
                }

                if(endIRP)
                {
                    /* This means we need to end the IRP */

                    hDriver->hostEndpointTable[iEndpoint]
                        .endpoints[endpointDir].pipe->irpQueueHead = irp->next;

                    if(irp->callback)
                    {
                        /* Invoke the call back*/
                        irp->callback((USB_HOST_IRP *)irp);
                    }

                    irp = hDriver->hostEndpointTable[iEndpoint]
                        .endpoints[endpointDir].pipe->irpQueueHead;

                    /* A IRP could have been submitted in the callback. If that is the case
                     * and the IRP status would indicate that it already in progress. If
                     * the IRP in the queue head is not in progress then we shold initiate
                     * the transaction */

                    if((irp != NULL) && (!(irp->status == USB_HOST_IRP_STATUS_IN_PROGRESS)))
                    {
                        irp->status = USB_HOST_IRP_STATUS_IN_PROGRESS;

                        /* We do have another IRP to process. Request for
                         * an IN packet. */

                        PLIB_USBHS_RxEPINTokenSend(usbID, iEndpoint);
                    }
                }
            }
        }
    }

}/* end of _DRV_USB_HOST_Tasks_ISR_USBDMA() */

void DRV_USB_HOST_BusResetControl(DRV_HANDLE client, bool control)
{
    DRV_USB_OBJ * hDriver;
    USBHS_MODULE_ID usbID;

    if((client == DRV_HANDLE_INVALID) || (((DRV_USB_OBJ *)client) == NULL))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid client");
        return;
    }

    hDriver = (DRV_USB_OBJ *)client;
    usbID = hDriver->usbID;

    /* If control is true, then enable reset */

    if(control == true)
    {
        /* Enable the rest signalling */
        PLIB_USBHS_ResetEnable(usbID);
    }
    else
    {
        /* Clear the reset signalling. At this point we
         * can check the speed of the connected device. */
        PLIB_USBHS_ResetDisable(usbID);

        if(PLIB_USBHS_HighSpeedIsConnected(usbID))
        {
            /* This means the device attached at high speed */
            hDriver->deviceSpeed = USB_SPEED_HIGH;
        }
        else if(PLIB_USBHS_FullOrHighSpeedIsConnected(usbID))
        {
            hDriver->deviceSpeed = USB_SPEED_FULL;
        }
        else
        {
            hDriver->deviceSpeed = USB_SPEED_LOW;
        }
    }
}/* end of DRV_USB_HOST_BusResetControl() */

void DRV_USB_HOST_StartOfFrameControl(DRV_HANDLE client, bool control)
{
    /* At the point this function does not do any thing.
     * The Start of frame signalling in this HCD is controlled
     * automatically by the module. */
}/* end of DRV_USB_HOST_StartOfFrameControl() */

USB_SPEED DRV_USB_HOST_DeviceCurrentSpeedGet(DRV_HANDLE client)
{
    /* This function returns the current device speed */

    DRV_USB_OBJ * hDriver;

    if((client == DRV_HANDLE_INVALID) || (((DRV_USB_OBJ *)client) == NULL))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid client");
    }

    hDriver = (DRV_USB_OBJ *)client;
    return(hDriver->deviceSpeed);

}/* end of DRV_USB_HOST_DeviceCurrentSpeedGet() */


void DRV_USB_HOST_OperationEnable(DRV_HANDLE hClient, bool enable)
{
    /* For this driver, this function does not do anything. The
     * PIC32MZ USB module does not have a explicit USB HOST mode
     * enable bit */

}

bool DRV_USB_HOST_OperationIsEnabled(DRV_HANDLE hClient)
{
    DRV_USB_OBJ * hDriver;
    USBHS_MODULE_ID usbID;

    if((hClient == DRV_HANDLE_INVALID) || (((DRV_USB_OBJ *)hClient) == NULL))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid client");
    }

    hDriver = (DRV_USB_OBJ *)hClient;
    usbID = hDriver->usbID;
  
    /* This function sets the session bit if the VBUS voltage
     * level is correct and then returns true. */

    if(PLIB_USBHS_VBUSLevelGet(usbID) == USBHS_VBUS_VALID)
    {
        PLIB_USBHS_SessionEnable(usbID);
        return(true);
     
    }
    /* The VBUS voltage level is not yet set. */
    return(false);
    
}/* end of DRV_USB_HOST_OperationIsEnabled() */

uint8_t _DRV_USB_HOST_GetFreeDMAChannel
(
    DRV_USB_OBJ * hDriver,
    bool endpointDir,
    uint8_t iEndpoint
)
{
    /* Start of local variables */
    uint8_t dmaChannel = 0;
    /* end of local variables */

    for(dmaChannel = 1; dmaChannel < 9; dmaChannel++)
    {
        if((hDriver->gDrvUSBDMAPool[dmaChannel]).inUse == false)
        {
            /* Found Not used DMA Channel */
            hDriver->gDrvUSBDMAPool[dmaChannel].inUse = true;
            hDriver->gDrvUSBDMAPool[dmaChannel].endpointDir = endpointDir;
            hDriver->gDrvUSBDMAPool[dmaChannel].iEndpoint = iEndpoint;
            break;
        }
    }
    /* DMA operation blocked */
    return 0;
}/* end of _DRV_USB_HOST_GetFreeDMAChannel() */
