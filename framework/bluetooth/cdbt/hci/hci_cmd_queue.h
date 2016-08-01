/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hci_cmd_queue.h

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

#ifndef __HCI_CMD_QUEUE_H
#define __HCI_CMD_QUEUE_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

void _hci_init_cmd_queues(void);
bt_hci_command_p hci_cq_find_by_opcode(bt_queue_element_t* head, bt_int opcode);
bt_hci_command_p hci_cq_find_by_hconn(bt_queue_element_t* head, bt_hci_hconn_t hconn);
bt_hci_command_p hci_cq_find_by_hconn_and_opcode(bt_queue_element_t* head, bt_hci_hconn_t hconnFind, bt_int opcode);
bt_hci_command_p hci_cq_find_by_bdaddr_and_opcode(bt_queue_element_t* head, bt_bdaddr_t bdaddrFind, bt_int opcode);


#ifdef __cplusplus
}
#endif

#endif // __HCI_CMD_QUEUE_H
