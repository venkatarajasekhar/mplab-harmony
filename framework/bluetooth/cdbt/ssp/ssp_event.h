/*******************************************************************************
 Microchip Bluetooth Stack - Secure Simple Pairing

  Company:
    Searan LLC.

  File Name:
    ssp_event.h

  Summary:
    Bluetooth API Library interface to the SSP.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.

*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
* Source contains proprietary and confidential information of SEARAN LLC.
* May not be used or disclosed to any other party except in accordance
* with a license from SEARAN LLC or Microchip Technology Inc.
* Copyright (c) 2011, 2012 SEARAN LLC. All Rights Reserved.
*
*
*******************************************************************************/
// DOM-IGNORE-END

#ifndef __SSP_EVENT_H
#define __SSP_EVENT_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

typedef enum _SPP_EVENT
{
	SSP_EVENT_IO_CAPABILITY_RESPONSE,
	SSP_EVENT_KEYPRESS_NOTIFICATION,
	SSP_EVENT_USER_PASSKEY_REQUEST,
	SSP_EVENT_USER_PASSKEY_NOTIFICATION,
	SSP_EVENT_USER_CONFIRMATION_REQUEST,
	SSP_EVENT_OOB_DATA_REQUEST,
	SSP_EVENT_IO_CAPABILITY_REQUEST,
	SSP_EVENT_SIMPLE_PAIRING_COMPLETE
} SPP_EVENT;

#ifdef __cplusplus
}
#endif

#endif //__SSP_EVENT_H
