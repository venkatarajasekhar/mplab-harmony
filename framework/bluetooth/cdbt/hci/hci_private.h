/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hci_private.h

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

#ifndef __HCI_PRIVATE_H
#define __HCI_PRIVATE_H

#include "bluetooth/cdbt/hci/hci_evt_handlers.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END
#define HCI_INIT_FLAG_SEND_HCI_RESET                       1 // HCI reset will be sent when bt_hci_init is called
#define HCI_INIT_FLAG_IGNORE_TOTAL_NUM_ACL_DATA_PACKETS    2 // The total number of ACL data packets read from the controller will be ignored.
                                                             // The stack will assume that he controller can accept only 1 ACL packet and sends
                                                             // HCI_EVT_NUM_OF_COMPLETED_PACKETS for each packet it has processed. This seems to be
                                                             // for controller working over SDIO (at least for Marvell's 88W8777).

//
// Global variables defined in HCI modules
// -------------------------------------------------------------------
//

// DOM-IGNORE-BEGIN
// In hci_cmd_buffer.c
extern bt_buffer_mgr_t   _hci_cmd_mgr;

// In hci_cmd_queue.c
extern bt_queue_element_t*  _send_cq_head;
extern bt_queue_element_t*  _resp_cq_head;
#ifdef _DEBUG
extern const bt_int _ram_size_hci_cmd_queue;
#endif

// In hci_data_buffer.c
extern bt_buffer_mgr_t   _hci_send_data_mgr;

// In hci_linkkey_buffer.c
extern bt_buffer_mgr_t            _hci_linkkey_mgr;
#ifdef _DEBUG
extern const bt_int _ram_size_hci_linkkey_buffer;
#endif

// In hci_param.c
extern bt_hci_ctrl_state_t* _phci_ctrl;
#ifdef _DEBUG
extern const bt_int _ram_size_hci_param;
#endif

// In hci_send.c
extern bt_hci_command_p _pcmd_being_sent;
extern bt_hci_data_p _pdata_being_sent;


//
// Global variables defined by OEM configuration
// -------------------------------------------------------------------
//

extern bt_buffer_header_t  _hci_cmd_buffer_headers[];
extern bt_hci_command_t    _hci_cmd_buffers[];
extern const bt_byte       _hci_max_cmd_buffers;
extern bt_byte             _hci_cmd_param_buffers[];
extern const bt_byte       _hci_max_cmd_param_len;

extern bt_buffer_header_t  _hci_send_data_buffer_headers[];
extern bt_hci_data_t       _hci_send_data_buffers[];
extern const bt_byte       _hci_max_data_buffers;

extern bt_hci_conn_state_t _hci_connections[];
extern const bt_byte       _hci_max_hci_connections;

extern bt_byte             _recv_buffer[];
extern bt_byte             _send_buffer[];
extern const bt_uint       _hci_rcv_buffer_len;
extern const bt_uint       _hci_tx_buffer_len;

extern bt_byte             _conn_state_recv_buffers[];
extern const bt_uint       _hci_l2cap_buffer_len;

extern const bt_bool       _hci_enable_ctrl_to_host_flow_control;

extern const bt_byte       _hci_max_connect_attempts;

extern const bt_bool       _hci_enable_sco;
extern bt_hci_event_handler_fp _hci_evt_synch_connection_complete_handler;
extern void (*_hci_recv_sco_data_packet_fp)(bt_byte* pbuf);

extern void (*_bt_ssp_init)(void);
extern void (*_bt_ssp_evt_handler)(bt_hci_event_t* evt);

extern void (*_bt_hci_le_init)(bt_hci_le_ctrl_state_t* le_ctrl_state);

extern const bt_hci_event_handler_fp _hci_event_handlers[];

#ifdef _DEBUG
extern const bt_uint _ram_size_hci_buffers;
extern const bt_int _ram_size_linkkey_storage;
#endif
// DOM-IGNORE-END
//
// Private global functions
// -------------------------------------------------------------------
//

// From hci_receive.c
void _hci_receive_start(void);

// From hci_send.c
void _hci_send_commands_from_queue(void);
void _hci_send_data_from_queue(void);
bt_bool _hci_send_data(bt_hci_data_p pdata);
void _hci_send_data_fragment(bt_hci_data_p pdata);
void _bt_hci_init_transport(void);

// From hci_sco.c
void _hci_recv_sco_data_packet(bt_byte_p pbuf);

// From hci_aux_info.c
bt_bool hci_check_aux_info(bt_long bdaddr_l, bt_long bdaddr_m);

// From hci_timer.c
void _bt_hci_init_timer(void);
bt_ulong _bt_hci_get_tick_count(void);

// Defined by OEM through library configuration
void _hci_allocate_buffers(void);

void _bt_le_evt_handler(bt_hci_event_t* evt);

void bt_hci_le_init(bt_hci_le_ctrl_state_t* le_ctrl_state);
void _bt_hci_le_command_complete_handler(bt_int status, bt_hci_command_t* pcmd, bt_hci_event_t* pevt);

void _bt_hci_notify_listeners(bt_hci_conn_state_t* pconn, bt_byte event_id, bt_hci_event_e* params);
void _bt_hci_ctrl_notify_listeners(bt_uint event_id, void* params);
void _bt_hci_ctrl_notify_data_listeners(bt_hci_conn_state_t* connection, const bt_byte* data, bt_int len, bt_bool sent);

void _bt_hci_set_init_flags(bt_byte flags);

#ifdef __cplusplus
}
#endif

#endif // __HCI_PRIVATE_H
