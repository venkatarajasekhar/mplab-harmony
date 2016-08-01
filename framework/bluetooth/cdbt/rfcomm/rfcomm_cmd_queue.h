/*******************************************************************************
 Microchip Bluetooth Stack - RF Communication

  Company:
    Searan LLC.

  File Name:
    rfcomm_cmd_queue.h

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

#ifndef __RFCOMM_CMD_QUEUE  // Guards against multiple inclusion
#define __RFCOMM_CMD_QUEUE

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

struct _bt_rfcomm_session_t;
struct _bt_rfcomm_command_t;
struct _bt_rfcomm_dlc_t;

struct _bt_rfcomm_command_t* rfcomm_cq_ack_cmd(struct _bt_rfcomm_dlc_t* pdlc, struct _bt_rfcomm_command_t* pres);
void rfcomm_cq_ack_mx_cmd(struct _bt_rfcomm_dlc_t* pdlc, struct _bt_rfcomm_command_t* pres);

void rfcomm_send_commands_from_queue(struct _bt_rfcomm_session_t *psess);

#ifdef __cplusplus
}
#endif

#endif // __RFCOMM_CMD_QUEUE
