/*******************************************************************************
 Microchip Bluetooth Stack - Secure Simple Pairing

  Company:
    Searan LLC.

  File Name:
    ssp_event_handler.h

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

#ifndef __SSP_EVENT_HANDLER_H // Guards against multiple inclusion
#define __SSP_EVENT_HANDLER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

void ssp_evt_io_capability_request(bt_hci_event_t* evt);
void ssp_evt_io_capability_response(bt_hci_event_t* evt);
void ssp_evt_user_confirmation_request(bt_hci_event_t* evt);
void ssp_evt_user_passkey_request(bt_hci_event_t* evt);
void ssp_evt_oob_data_request(bt_hci_event_t* evt);
void ssp_evt_ssp_complete(bt_hci_event_t* evt);
void ssp_evt_user_passkey_notification(bt_hci_event_t* evt);
void ssp_evt_keypress_notification(bt_hci_event_t* evt);

#ifdef __cplusplus
}
#endif

#endif // __SSP_EVENT_HANDLER_H
