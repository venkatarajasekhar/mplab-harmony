/*******************************************************************************
 Microchip Bluetooth Stack - RF Communication

  Company:
    Searan LLC.

  File Name:
    rfcomm_signal.h

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

#ifndef __RFCOMM_SIGNAL_H  // Guards against multiple inclusion
#define __RFCOMM_SIGNAL_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

void _bt_rfcomm_init_signal(void);

void _bt_rfcomm_set_signal(void);

#ifdef __cplusplus
}
#endif

#endif // __RFCOMM_SIGNAL_H
