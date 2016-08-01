/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hcitr_3wire.h

  Summary:
    Bluetooth API Library interface to the HCI Functions.

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

#ifndef __HCITR_3WIRE_H_INCLUDED__
#define __HCITR_3WIRE_H_INCLUDED__

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#define HCITR_3WIRE_DEFAULT_ACK_TIMEOUT    250

#define bt_hcitr_3wire_init()              bt_hcitr_3wire_init_ex(HCITR_3WIRE_DEFAULT_ACK_TIMEOUT, BT_FALSE)
#define bt_hcitr_3wire_reset()             bt_hcitr_3wire_reset_ex(HCITR_3WIRE_DEFAULT_ACK_TIMEOUT, BT_FALSE)
void bt_hcitr_3wire_start(void);

void bt_hcitr_3wire_init_ex(bt_ulong ack_timeout, bt_bool data_integrity_check_enabled);
void bt_hcitr_3wire_reset_ex(bt_ulong ack_timeout, bt_bool data_integrity_check_enabled);

#ifdef __cplusplus
}
#endif

#endif // __HCITR_3WIRE_H_INCLUDED__

