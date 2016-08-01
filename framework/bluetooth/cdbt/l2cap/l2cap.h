/*******************************************************************************
 Microchip Bluetooth Stack - Logical Link Control and Adaptation Protocol

  Company:
    Searan LLC.

  File Name:
    l2cap.h

  Summary:
    Bluetooth API Library interface to the L2CAP Functions.

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

#ifndef __L2CAP_H
#define __L2CAP_H

#include "bluetooth/cdbt/hci/hci.h"

#include "bluetooth/cdbt/l2cap/command.h"
#include "bluetooth/cdbt/l2cap/cmdbuffer.h"
#include "bluetooth/cdbt/l2cap/frame_buffer.h"
#include "bluetooth/cdbt/utils/queue.h"
#include "bluetooth/cdbt/l2cap/l2cap_packet.h"
#include "bluetooth/cdbt/l2cap/channel.h"
#include "bluetooth/cdbt/l2cap/l2cap_command_queue.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#define PSM_SDP             0x0001
#define PSM_RFCOMM          0x0003
#define PSM_BNEP            0x000F
#define PSM_HID_Control     0x0011
#define PSM_HID_Interrupt   0x0013
#define PSM_AVCTP           0x0017
#define PSM_AVDTP           0x0019
#define PSM_AVCTP_Browsing  0x001B
#define PSM_ATT	            0x001F

#define L2CAP_MGR_STATE_FREE				0
#define L2CAP_MGR_STATE_USED				1
#define L2CAP_MGR_STATE_LISTENING_L2CAP		2

#define L2CAP_MAX_MANAGERS      1

#define L2CAP_HEADER_LEN        4
#define L2CAP_MAX_MTU           (_hci_l2cap_buffer_len - L2CAP_HEADER_LEN)

#ifndef L2CAP_DEFAULT_RTX
#define L2CAP_DEFAULT_RTX       3 /* seconds */
#endif

#ifndef L2CAP_DEFAULT_ERTX
#define L2CAP_DEFAULT_ERTX      60 /* seconds */
#endif

#ifndef L2CAP_MAX_RTX
#define L2CAP_MAX_RTX           4
#endif

#define L2CAP_HCI_CONNECT_PACKET_TYPE    _l2cap_hci_connect_packet_type

#define L2CAP_HCI_CONNECT_PAGE_SCAN_REPETITION_MODE _l2cap_hci_page_scan_repetition_mode

#define L2CAP_HCI_CONNECT_ROLE_SWITCH _l2cap_hci_role_switch

#define L2CAP_IDLE_HCI_CONNECTION_TIMEOUT _l2cap_idle_hci_connection_timeout

#define L2CAP_SAR_UNSEGMENTED		0x0
#define L2CAP_SAR_SDU_START			0x1
#define L2CAP_SAR_SDU_STOP			0x2
#define L2CAP_SAR_SDU_CONTINUE		0x3

#define L2CAP_SFUNCTION_RR			0x0
#define L2CAP_SFUNCTION_REJ			0x1
#define L2CAP_SFUNCTION_RNR			0x2
#define L2CAP_SFUNCTION_SREJ		0x3

#define L2CAP_FRAME_TYPE_I			0x0
#define L2CAP_FRAME_TYPE_S			0x1

#define L2CAP_RETR_TIMEOUT			(L2CAP_RFC_ERETR_TIMEOUT / 1000)
#define L2CAP_MONITOR_TIMEOUT		((L2CAP_RFC_MONITOR_TIMEOUT / 1000) - 2)

#define L2CAP_MIN_MTU               48

typedef void (*bt_l2cap_listen_callback_fp)(bt_l2cap_channel_t* pch, void* param);
typedef void (*bt_l2cap_connect_callback_fp)(bt_l2cap_channel_t* pch, void* param);

typedef struct _bt_l2cap_psm_s
{
	bt_int psm;
	bt_uint acl_config;
	bt_byte chmode;
	bt_l2cap_listen_callback_fp listen_cb;
	bt_l2cap_connect_callback_fp connect_cb;
	void* listen_cb_param;
	void* connect_cb_param;
} bt_l2cap_psm_t;

typedef struct _bt_l2cap_fixed_channel_s
{
	bt_id cid;
	bt_byte link_type;
	bt_l2cap_listen_callback_fp listen_cb;
	bt_l2cap_connect_callback_fp connect_cb;
	void* listen_cb_param;
	void* connect_cb_param;
} bt_l2cap_fixed_channel_t;

typedef struct _bt_l2cap_mgr_s 
{
	bt_int state;
	bt_l2cap_psm_t* _psms;
	bt_l2cap_fixed_channel_t* _fixed_channels;
	bt_l2cap_channel_t* _channels;
	bt_queue_element_t* cmd_queue;
	bt_queue_element_t* cmd_res_queue;
	bt_bool sending;
	bt_byte max_rtx;
	bt_hci_ctrl_state_t* hci_ctrl;
	bt_l2cap_packet_t cmd_tx_packet;

	bt_int connect_psm;
	bt_l2cap_connect_callback_fp connect_cb;
	void* connect_param;
	bt_l2cap_state_changed_callback_fp connect_state_cb;

	bt_hci_listener_t hci_disconnect_listener;

	bt_byte connect_chmode;

} bt_l2cap_mgr_t, *bt_l2cap_mgr_p;


/**
 * Summary:  Initialize the L2CAP layer.
 * , Functional Group:  l2cap
 *
 * Description:  This function initializes the L2CAP layer of the stack. It must be called prior to any other
 * L2CAP function can be called.
 */
void bt_l2cap_init(void);


/**
 * Summary:  Allocate L2CAP manager.
 * , Functional Group:  l2cap
 *
 * Description:  This function allocates and initializes an L2CAP manager structure.
 * One L2CAP manager manages all L2CAP connections for a particular local device.
 * The local device is specified by the hci_ctrl parameter.
 *
 * Parameters:  hci_ctrl - Pointer to the hci_ctrl_state structure that represents the local
 * device (HCI controller) for which a L2CAP manager is to be allocated.
 *
 * Returns:  A pointer to the allocated L2CAP manager structure. The returned
 *         L2CAP manager should be freed by a call to bt_l2cap_free_mgr when it
 *         is no longer needed.
 */
bt_l2cap_mgr_t* bt_l2cap_allocate_mgr(bt_hci_ctrl_state_t* hci_ctrl);


/**
 * Summary:  Release L2CAP manger.
 * , Functional Group:  l2cap
 *
 * Description:  This function releases the L2CAP manager structure.
 *
 * Parameters:  mgr - The L2CAP manager structure to be released.
 *
 */
void bt_l2cap_free_mgr(bt_l2cap_mgr_t* mgr);


/**
 * Summary:  Listen for incoming connections.
 * , Functional Group:  l2cap
 *
 * Description:  This function tells the L2CAP manager to listen for incoming connections
 * on a specific PSM. When a connection is established a callback function is called.
 *
 * Parameters:  mgr - The L2CAP manager.
 *   psm - The PSM on which the manager will listen and accept incoming connections.
 *   callback - The callback function that will be called when an incoming connection is established.
 *   param - An arbitrary data pointer that will be passed to the callback function specified by
 *              the callback parameter.
 *
 * Returns:
 *        - TRUE when the function succeeds.
 *        - FALSE otherwise. The callback function is not called in this case.
 */
bt_bool bt_l2cap_listen_ext(
	bt_l2cap_mgr_t* mgr, bt_int psm, bt_byte chmode,
	bt_uint acl_config,
	bt_l2cap_listen_callback_fp callback, void* param);

#define bt_l2cap_listen(mgr, psm, acl_config, callback, param)	bt_l2cap_listen_ext(mgr, psm, CMODE_BASIC, acl_config, callback, param)

bt_bool bt_l2cap_listen_fixed_channel(
	bt_l2cap_mgr_t* mgr, bt_id cid, bt_byte link_type, 
	bt_l2cap_listen_callback_fp callback, void* param);


/**
 * Summary:  Connect to a remote device.
 * , Functional Group:  l2cap
 *
 * Description:  This function establishes an L2CAP connection with a remote device on a specific PSM.
 * When connect operation completes a callback function is called.
 *
 * Parameters:  mgr - The L2CAP manager.
 *   remote_addr - The address of the remote device.
 *   psm - The PSM for the connection.
 *   connect_cb - The Callback function that is called when the connect operation completes.
 *   param - A pointer to arbitrary data to be passed to the connect_cb callback.
 *   state_cb - The callback function that is called when the state of the established connection changes.
 *
 * Returns:
 *        - TRUE when the function succeeds.
 *        - FALSE otherwise. None of the callback functions is called in this case.
 *
 */
bt_bool bt_l2cap_connect_ext(
	bt_l2cap_mgr_t* mgr, 
	bt_bdaddr_t* remote_addr,
	bt_int psm, bt_byte chmode, 
	bt_uint acl_config,
	bt_l2cap_connect_callback_fp connect_cb, void* param,
	bt_l2cap_state_changed_callback_fp state_cb);

#define bt_l2cap_connect(mgr, remote_addr, psm, acl_config, connect_cb, param, state_cb)	bt_l2cap_connect_ext(mgr, remote_addr, psm, CMODE_BASIC, acl_config, connect_cb, param, state_cb)

bt_bool bt_l2cap_connect_fixed_channel(
	bt_l2cap_mgr_p pmgr, 
	bt_bdaddr_p pbdaddr_remote,
	bt_id cid, 
	bt_uint acl_config,
	bt_l2cap_connect_callback_fp cb, void* param,
	bt_l2cap_state_changed_callback_fp state_cb);

/**
 * Summary:  Close L2CAP channel.
 * , Functional Group:  l2cap
 *
 * Description:  This function closes an L2CAP channel. The channel can be established
 * either by a call to bt_l2cap_connect() or by an incoming connection request.
 *
 * Parameters:  ch - The L2CAP channel to be closed.
 *
 * Returns:
 *        - TRUE when the function succeeds.
 *        - FALSE otherwise. The callback function is not called in this case.
 */
bt_bool bt_l2cap_disconnect(bt_l2cap_channel_t* ch);

bt_bool bt_l2cap_disconnect_ex(bt_l2cap_channel_t* pch, bt_bool force_hci_disconnect);

/**
* Summary:  Send reject command (used to reject unknown or invalid commands)
*
*/
bt_bool bt_l2cap_reject(bt_l2cap_mgr_p pmgr, bt_hci_conn_state_p pconn, bt_byte cmd_id, bt_byte reason, bt_l2cap_cmd_reject_param_t* param);

/**
* Summary:  Send echo command
*
*/
bt_bool bt_l2cap_echo(bt_l2cap_mgr_p pmgr, bt_hci_conn_state_p pconn, bt_byte_p data, bt_int len);
bt_bool bt_l2cap_send_config(bt_l2cap_mgr_p pmgr, bt_l2cap_channel_t* pch);

bt_bool bt_l2cap_update_conn_parameters(
	bt_l2cap_channel_t* channel,
	bt_uint min_interval, bt_uint max_interval,
	bt_uint slave_latency, bt_uint supervision_timeout);

bt_bool bt_l2cap_is_channel_open(bt_l2cap_channel_t* channel);

bt_l2cap_mgr_p bt_l2cap_get_mgr(bt_hci_hconn_t h);

bt_bool bt_l2cap_hci_has_open_channels(bt_hci_conn_state_t* conn);

#ifdef __cplusplus
}
#endif

#include "bluetooth/cdbt/l2cap/chmanager.h"
#include "bluetooth/cdbt/l2cap/l2cap_psm.h"
#include "bluetooth/cdbt/l2cap/l2cap_fixed_channel.h"

#include "bluetooth/cdbt/l2cap/l2cap_eretr.h"
#include "bluetooth/cdbt/l2cap/l2cap_private.h"

#endif // __L2CAP_H
