/*******************************************************************************
 Microchip Bluetooth Stack - Logical Link Control and Adaptation Protocol

  Company:
    Searan LLC.

  File Name:
    l2cap_timer.h

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

#ifndef __L2CAP_TIMER
#define __L2CAP_TIMER

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

void _bt_l2cap_init_timer(void);
bt_long _bt_l2cap_get_tick_count(void);

#ifdef __cplusplus
}
#endif

#endif // __L2CAP_TIMER