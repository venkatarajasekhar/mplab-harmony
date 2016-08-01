/*******************************************************************************
 Microchip Bluetooth Stack - Bluetooth General Functions

  Company:
    Searan LLC.

  File Name:
    bt_hcitr.h

  Summary:
    Bluetooth API Library interface to Bluetooth General Functions.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.

	The DotStack library provides several HCI transport protocols (e.g., H4, 3-wire
	protocol). However, the code that actually moves octets of data between the CPU and
	HCI controller is application specific.

	This module declares an interface that allows DotStack to communicate with the HCI
	controller. The application has to implement this interface.

	The interface consist of the following functions that must be implemented by the
	application:
		-  bt_oem_send()
		-  bt_oem_recv()

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

#ifndef __BT_HCITR_H_INCLUDED__
#define __BT_HCITR_H_INCLUDED__

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

/** Function: Send callback.

	Description: This callback function is called when a send operation initiated by bt_oem_send() has
	completed.
*/
typedef void (*bt_oem_send_callback_fp)(void);


/** Function:Receive callback.

	Description: This callback function is called when a receive operation initiated by bt_oem_recv()
	has completed.

	Parameters:  len - Number of received bytes.
		The value of this parameter should always be the same as the number of bytes
		requested in a call to bt_oem_recv().
*/
typedef void (*bt_oem_recv_callback_fp)(bt_uint len);


/** Function:Send data.

	Description: This function is called by the HCI layer when it needs to send data to the HCI
	controller. Implementation of this function must send the specified number of bytes
	to the HCI controller and call the provided callback function.

	  buffer - Pointer to the data to be sent .

	  len - Number of bytes to send.

	  callback - A callback function that must be called when all data have been sent.
*/
void bt_oem_send(const bt_byte* buffer, bt_uint len, bt_oem_send_callback_fp callback);


/** Function:Receive data.

	Description: This function is called by the HCI layer when it needs more data from the HCI
	controller. Implementation of this function must receive the specified number of bytes
	from the HCI controller and call the provided callback function.

	Parameters:  buffer - Pointer to a buffer for the received data.
		The buffer must be long enough to accommodate the number of bytes specified by the
		len parameter.

	  len - Number of bytes to receive.

	  callback - A callback function that must be called when the requested number
		of bytes have been received.
*/
void bt_oem_recv(bt_byte* buffer, bt_uint len, bt_oem_recv_callback_fp callback);

/*@}*/ /* end doxygen group */

#ifdef __cplusplus
}
#endif

#endif // __BT_HCITR_H_INCLUDED__
