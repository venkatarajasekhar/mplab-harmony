/*******************************************************************************
 Microchip Bluetooth Stack - RF Communication

  Company:
    Searan LLC.

  File Name:
    rfcomm_mgr.h

  Summary:
    Bluetooth API Library interface to the RF Communications.

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

#ifndef __RFCOMM_MGR_H  // Guards against multiple inclusion
#define __RFCOMM_MGR_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

typedef struct _bt_rfcomm_session_listener_t
{
	struct _bt_rfcomm_session_listener_t* next_listener;

	bt_rfcomm_state_callback_fp callback;
	void* callback_param;
} bt_rfcomm_session_listener_t;

typedef struct _bt_rfcomm_server_channel_t
{
	bt_byte id;
	bt_rfcomm_dlc_state_callback_fp listen_cb;
	void* listen_param;
} bt_rfcomm_server_channel_t;

typedef struct _bt_rfcomm_mgr_t
{
	bt_rfcomm_session_listener_t* listeners;
	bt_rfcomm_server_channel_t* channels;
} bt_rfcomm_mgr_t;

bt_bool bt_rfcomm_register_listener(bt_rfcomm_session_listener_t* listener);
void bt_rfcomm_unregister_listener(bt_rfcomm_session_listener_t* listener);

void _rfcomm_init_mgr(void);
bt_rfcomm_mgr_t* _bt_rfcomm_get_mgr(void);

void _bt_rfcomm_mgr_notify_listeners(bt_rfcomm_session_t* session, bt_int evt);

bt_rfcomm_server_channel_t* _bt_rfcomm_allocate_channel(bt_byte id);
bt_rfcomm_server_channel_t* _bt_rfcomm_find_channel(bt_byte id);

void _bt_rfcomm_mgr_l2cap_listen_callback(bt_l2cap_channel_t* pch, void* param);


#ifdef __cplusplus
}
#endif

#endif // __RFCOMM_MGR_H
