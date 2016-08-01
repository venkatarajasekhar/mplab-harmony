/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hcitr_tih4.h

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

#ifndef __HCITR_TUH4_H_INCLUDED__
#define __HCITR_TUH4_H_INCLUDED__

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

typedef enum _hcitr_tih4_power_event_e
{
	HCITR_TIH4_POWER_EVENT_PREPARE_TO_SLEEP,
	HCITR_TIH4_POWER_EVENT_SLEEP,
	HCITR_TIH4_POWER_EVENT_WAKE_UP,
	HCITR_TIH4_POWER_EVENT_AWAKE

} bt_hcitr_tih4_power_event_e;


typedef void (*bt_hcitr_tih4_power_callback_fp)(bt_hcitr_tih4_power_event_e event);

void bt_hcitr_tih4_init(bt_hcitr_tih4_power_callback_fp callback);
void bt_hcitr_tih4_reset(void);
void bt_hcitr_tih4_start(void);
void bt_hcitr_tih4_wake_up(void);

#ifdef __cplusplus
}
#endif

#endif // __HCITR_TUH4_H_INCLUDED__

