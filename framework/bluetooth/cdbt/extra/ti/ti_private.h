/*******************************************************************************
 Microchip Bluetooth Stack - Extra Files

  Company:
    Searan LLC.

  File Name:
    extra/ti_private.h

  Summary:
    Bluetooth API Library interface to the TI driver.

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

#ifndef __BTX_TI_TI_PRIVATE_H_INCLUDED
#define __BTX_TI_TI_PRIVATE_H_INCLUDED

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

// DOM-IGNORE-BEGIN
// Data in btx_ti_shared_data.c
extern bt_hci_cmd_callback_fp  g_btx_ti_hci_callback;
extern void*                   g_btx_ti_hci_callback_param;
// DOM-IGNORE-END

#ifdef __cplusplus
}
#endif

#endif // __BTX_TI_TI_PRIVATE_H_INCLUDED
