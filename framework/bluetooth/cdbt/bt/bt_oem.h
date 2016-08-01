/*******************************************************************************
 Microchip Bluetooth Stack - Bluetooth General Functions

  Company:
    Searan LLC.

  File Name:
    bt_oem.h

  Summary:
    Bluetooth API Library interface to Bluetooth General Functions.

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

#ifndef __BT_OEM_H
#define __BT_OEM_H

#include "bluetooth/cdbt/ssp/ssp_event.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

typedef struct _bt_linkkey_notification_t
{
	bt_bdaddr_t bdaddr_remote;
	bt_linkkey_t key;
	bt_byte key_type;

} bt_linkkey_notification_t;

typedef struct _bt_linkkey_request_t
{
	bt_bdaddr_t bdaddr_remote;

} bt_linkkey_request_t;

const char* bt_oem_get_device_name(void);

bt_long bt_oem_get_device_class(void);

void bt_oem_get_pin_code(bt_bdaddr_t* bdaddr_remote);

void bt_oem_ssp_callback(SPP_EVENT spp_event, void* event_param, void* init_param);

void bt_oem_schedule_signals(void);

void bt_oem_linkkey_notification(bt_linkkey_notification_t* lkn);

void bt_oem_linkkey_request(bt_linkkey_request_t* lkr);

void bt_oem_assert(const char* file, int line);


#ifdef __cplusplus
}
#endif

#endif // __BT_OEM_H
