/*******************************************************************************
 Microchip Bluetooth Stack - Logical Link Control and Adaptation Protocol

  Company:
    Searan LLC.

  File Name:
    l2cap_command_queue.h

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

#ifndef __L2CAP_COMMAND_QUEUE_H
#define __L2CAP_COMMAND_QUEUE_H

#include "bluetooth/cdbt/utils/queue.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#define L2CAP_MAX_CMD_QUEUE_LEN 5

struct _bt_l2cap_mgr_s;

void _bt_l2cap_send_commands_from_queue(struct _bt_l2cap_mgr_s* pmgr);
void _bt_l2cap_notify_and_remove(struct _bt_l2cap_mgr_s* pmgr, bt_l2cap_cmd_header_p pcmd);

#ifdef __cplusplus
}
#endif

#endif //__L2CAP_COMMAND_QUEUE_H
