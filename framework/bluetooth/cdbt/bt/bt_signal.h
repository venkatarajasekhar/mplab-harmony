/*******************************************************************************
 Microchip Bluetooth Stack - Bluetooth General Functions

  Company:
    Searan LLC.

  File Name:
    bt_signal.h

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

#ifndef __BT_SIGNAL_H
#define __BT_SIGNAL_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

struct _bt_signal_t;
typedef struct _bt_signal_t bt_signal_t;

typedef void (*bt_signal_handler_fp)(bt_signal_t* signal, void* param);

struct _bt_signal_t
{
	bt_signal_t* next_signal;
	bt_byte signaled;
	bt_signal_handler_fp handler;
	void* handler_param;
};

bt_bool bt_signal_register(bt_signal_t* signal, bt_signal_handler_fp handler, void* handler_param);

void bt_signal_unregister(bt_signal_t* signal);

void bt_signal_set(bt_signal_t* signal);

void bt_signal_process_pending(void);

#ifdef __cplusplus
}
#endif

#endif // __BT_SIGNAL_H
