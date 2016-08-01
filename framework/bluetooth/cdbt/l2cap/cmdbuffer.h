/*******************************************************************************
 Microchip Bluetooth Stack - Logical Link Control and Adaptation Protocol

  Company:
    Searan LLC.

  File Name:
    cmdbuffer.h

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

#ifndef __L2CAP_CMDBUFFER_H
#define __L2CAP_CMDBUFFER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

void bt_l2cap_init_cmd_buffers(void);
bt_l2cap_cmd_header_p bt_l2cap_alloc_cmd_buffer(bt_byte code);
void bt_l2cap_free_cmd_buffer(void* p);

bt_l2cap_cmd_reject_p bt_l2cap_alloc_cmd_reject(void);
bt_l2cap_cmd_connection_req_p bt_l2cap_alloc_cmd_connection_req(void);
bt_l2cap_cmd_connection_res_p bt_l2cap_alloc_cmd_connection_res(void);
bt_l2cap_cmd_config_req_p bt_l2cap_alloc_cmd_config_req(void);
bt_l2cap_cmd_config_res_p bt_l2cap_alloc_cmd_config_res(void);
bt_l2cap_cmd_disconnection_req_p bt_l2cap_alloc_cmd_disconnection_req(void);
pcmd_disconnection_res bt_l2cap_alloc_cmd_disconnection_res(void);
bt_l2cap_cmd_info_req_p bt_l2cap_alloc_cmd_info_req(void);
bt_l2cap_cmd_info_res_p bt_l2cap_alloc_cmd_info_res(void);
bt_l2cap_cmd_echo_req_p bt_l2cap_alloc_cmd_echo_req(void);
bt_l2cap_cmd_echo_res_p bt_l2cap_alloc_cmd_echo_res(void);
bt_l2cap_cmd_conn_param_update_req_t* bt_l2cap_alloc_cmd_conn_param_update_req(void);
bt_l2cap_cmd_conn_param_update_res_t* bt_l2cap_alloc_cmd_conn_param_update_res(void);

#ifdef __cplusplus
}
#endif

#endif // __L2CAP_CMDBUFFER_H
