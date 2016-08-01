/*******************************************************************************
 Microchip Bluetooth Stack - Logical Link Control and Adaptation Protocol

  Company:
    Searan LLC.

  File Name:
    l2cap_psm.h

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

#ifndef __L2CAP_PSM_H
#define __L2CAP_PSM_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

void bt_l2cap_init_psms(bt_l2cap_mgr_p pmgr);
bt_l2cap_psm_t* bt_l2cap_find_psm(const bt_l2cap_mgr_p pmgr, bt_int psmId);
bt_l2cap_psm_t* bt_l2cap_allocate_psm(bt_l2cap_mgr_p pmgr, bt_int psmId);
void bt_l2cap_free_psm(bt_l2cap_psm_t* psm);

#ifdef __cplusplus
}
#endif

#endif // __L2CAP_PSM_H
