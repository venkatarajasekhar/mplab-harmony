/*******************************************************************************
 Microchip Bluetooth Stack - Utilities

  Company:
    Searan LLC.

  File Name:
    queue.h

  Summary:
    Bluetooth API Library interface Utilities.

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

#ifndef __UTILS_QUEUE_H  // Guards against multiple inclusion
#define __UTILS_QUEUE_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

typedef struct _bt_queue_element_t
{
	struct _bt_queue_element_t* next;
} bt_queue_element_t;

void bt_q_add(bt_queue_element_t** phead, void* element);
void bt_q_push(bt_queue_element_t** phead, void* element);
void* bt_q_get_head(bt_queue_element_t** phead, bt_bool remove);
void* bt_q_get_next(void* element);
void* bt_q_get(bt_queue_element_t* head, bt_int index);
void* bt_q_remove(bt_queue_element_t** phead, void* pdata);
void* bt_q_remove_by_idx(bt_queue_element_t* head, bt_int index);
bt_int bt_q_get_length(bt_queue_element_t* phead);

#ifdef __cplusplus
}
#endif

#endif // __UTILS_QUEUE_H
