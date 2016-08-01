/*******************************************************************************
 Microchip Bluetooth Stack - Bluetooth General Functions

  Company:
    Searan LLC.

  File Name:
    bt_system.h

  Summary:
    Bluetooth API Library interface to Bluetooth General Functions.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.

	Functions in this module provide interface to DotStack functionality that is common to
	all protocols and profiles.

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

#ifndef __BT_SYSTEM_H_INCLUDED__
#define __BT_SYSTEM_H_INCLUDED__

#include "bluetooth/cdbt/l2cap/l2cap.h"
#include "bluetooth/cdbt/gap/gap.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

/** Function: System start callback.

	Description: This callback function is called when system start initiated by bt_sys_start() has
	completed.

	Parameters:  success - Success of the operation:
			BT_TRUE if successfull, BT_FALSE otherwise.

	  param - Callback parameter that was specified when bt_sys_start() was called.
*/
typedef void (*bt_sys_callback_fp)(bt_bool success, void* param);


/** Function: Initialize the Bluetooth system.

	Description: This function initializes all internal variables of HCI, L2CAP and SDP modules. It
	must be called by the application before it can access any functionality provided by
	the library. In addition to this initialization function the application must call
	initialization functions of all other profile modules the application is intended to
	use. E.g., if the application is using the SPP module the bt_spp_init() must be called
	right after calling bt_sys_init().

	Also, the caller must provide an SDP database.

	Parameters:  sdp_db - SDP database data.
	  sdp_db_len - Length of SDP database data.
*/
void bt_sys_init(void);


/** Function: Start the Bluetooth system.

	Description: After all modules used by the application have been initialized this function should
	be called to start the Bluetooth system operation. During the start up sequence it
	will reset and initialize the HCI controller and then create the L2CAP manager. The
	application will be notified when the start up sequence completes by calling the
	provided callback function.

	Parameters:  callback - A callback function that will be called when the start up sequence is
			complete.

	  callback_param - An arbitrary pointer that will be passed to the callback
			function.

*/
void bt_sys_start(bt_bool discoverable, bt_bool connectable,
		const bt_byte* sdp_db, bt_uint sdp_db_len, bt_sys_callback_fp callback,
		void* callback_param);

void bt_sys_set_modes(bt_bool discoverable, bt_bool connectable,
		bt_sys_callback_fp callback, void* callback_param);

bt_bool bt_sys_get_discoverable(void);

bt_bool bt_sys_get_connectable(void);

/** Function: Get the L2CAP manager.

	Description: This function returns the L2CAP manager. The L2CAP manager is created as part of the
	start up sequence.

	Returns:  The L2CAP manager.
*/
bt_l2cap_mgr_t* bt_sys_get_l2cap_manager(void);


/*@}*/ /* end doxygen group */

#ifdef __cplusplus
}
#endif

#endif /* __BT_SYSTEM_H_INCLUDED__  */
