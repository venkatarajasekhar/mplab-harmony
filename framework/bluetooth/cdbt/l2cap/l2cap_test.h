/*******************************************************************************
 Microchip Bluetooth Stack - Logical Link Control and Adaptation Protocol

  Company:
    Searan LLC.

  File Name:
    l2cap_test.h

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

#ifndef __L2CAP_TEST
#define __L2CAP_TEST

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#ifdef _ENABLE_TEST

// DOM-IGNORE-BEGIN
/* if set to FALSE, l2cap_send_config will do nothing */
extern bt_bool _enable_local_config;
extern bt_bool _enable_remote_config;
// DOM-IGNORE-END

#define bt_l2cap_test_enable_local_config(enable)	_enable_local_config = enable

#define bt_l2cap_test_enable_remote_config(enable)	_enable_remote_config = enable

#else

#define bt_l2cap_test_enable_local_config(enable)

#define bt_l2cap_test_enable_remote_config(enable)

#endif

#ifdef __cplusplus
}
#endif

#endif // __L2CAP_TEST
