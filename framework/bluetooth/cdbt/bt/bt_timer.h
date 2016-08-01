/*******************************************************************************
 Microchip Bluetooth Stack - Bluetooth General Functions

  Company:
    Searan LLC.

  File Name:
    bt_timer.h

  Summary:
    Bluetooth API Library interface to Bluetooth General Functions.  Timer Interface.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.

	DotStack requires a facility to measure various time intervals.
    This module declares an interface that the application has to implement in
    order to provide DotStack with such functionality.

   The minimum required timer resolution is 100 milliseconds.

   The maximum number of timers is defined by the BT_TIMER_MAX constant.

   Timer ID values used in the interface are from 0 to <tt>BT_TIMER_MAX-1</tt>.

   The interface consists of the following function:
       -  bt_oem_timer_set()
       -  bt_oem_timer_clear()

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

#ifndef __BTTIMER_H
#define __BTTIMER_H


// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

typedef enum _bt_timer_id_enum
{
	BT_TIMER_L2CAP,
	BT_TIMER_RFCOMM,
	BT_TIMER_WAKEUP_ACK,
	BT_TIMER_TEST,
	BT_TIMER_HCI,
	BT_TIMER_IAP,
	BT_TIMER_HSP_AG,
	BT_TIMER_HFP_AG,
	BT_TIMER_ATT,
	BT_TIMER_ATT_CLIENT,
	BT_TIMER_AVRCP,
	BT_TIMER_SMP,
	BT_TIMER_IAP2,

	BT_TIMER_3WIRE_T0,
	BT_TIMER_3WIRE_T1,

	BT_TIMER_MAX

} bt_timer_id;


/**
 * Summary:  Timer callback.
 *
 * Description:  This callback is called when a timer expires.
 */
typedef void (*bt_timer_callback_fp)(void);


/**
 * Summary:  Set timer.
 *
 * Description:  This function must be implemented by the application.
 * When it is called, the application must set the specified timer. When the timer
 * expires, the application must call the passed callback function. The function
 * must not wait until the timer expires. It must set the timer and exit immediately.
 *
 * Parameters:  timerId - ID of the timer to set.
 *   milliseconds - Timer interval in milliseconds
 *   callback - Timer expiration callback function.
 */
void bt_oem_timer_set(bt_uint timerId, bt_ulong milliseconds, bt_timer_callback_fp callback);


/**
 * Summary:  Clear timer.
 *
 * Description:  This function must be implemented by the application.
 * When this function is called the application must clear the specified timer.
 * If it is already expired and a callback is currently pending, the application
 * should also take measures to cancel the callback.
 *
 * Parameters:  timerId - ID of the timer to clear.
 */
void bt_oem_timer_clear(bt_uint timerId);


#ifdef __cplusplus
}
#endif

/*@}*/ /* end doxygen group */

#endif // __BTTIMER_H
