/*******************************************************************************
 Microchip Bluetooth Stack - Serial Port Profile

  Company:
    Searan LLC.

  File Name:
    spp.h

  Summary:
    Bluetooth API Library interface to the SPP.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.

	The DotStack SPP API is a simple API for communicating over a Bluetooth link using the
Bluetooth Serial Port Profile.

Here are the steps for using this API:

- Call the bt_spp_init() function.

- Allocate a serial port structure with bt_spp_allocate(). One of the parameters to
 this function is a pointer to a callback function. That callback function will be called
 by the stack whenever the state of the serial port changes.

- To connect to a remote device call bt_spp_connect(). The stack will notify when the
  connection is established by calling the state callback function.

- To wait for a connection from a remote device call bt_spp_listen(). The stack will
  notify when the connection is established by calling the state callback function.

- When the port is connected you can send data with bt_spp_send() and receive data with
  bt_spp_receive().

- To terminate the connection call bt_spp_disconnect().

- When you are finished using the port deallocate it with bt_spp_deallocate().

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

#ifndef __SPP_H   // Guards against multiple inclusion
#define __SPP_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif

#include "bluetooth/cdbt/l2cap/l2cap.h"
#include "bluetooth/cdbt/rfcomm/rfcomm.h"
#include "bluetooth/cdbt/sdp/sdp.h"
#include "bluetooth/cdbt/sdp/sdp_client.h"
#include "bluetooth/cdbt/bt/bt_signal.h"




#define SPP_RS232_DSR RFCOMM_MODEM_STATUS_RTC
#define SPP_RS232_DTR RFCOMM_MODEM_STATUS_RTC
#define SPP_RS232_RTS RFCOMM_MODEM_STATUS_RTR
#define SPP_RS232_CTS RFCOMM_MODEM_STATUS_RTR
#define SPP_RS232_RI  RFCOMM_MODEM_STATUS_IC
#define SPP_RS232_DCD RFCOMM_MODEM_STATUS_DV


/** Serial port state.
	Values of this enumeration represent states of the serial port.
*/
typedef enum _bt_spp_port_state_e {
	SPP_PORT_STATE_FREE,            /**< Used internally to mark a port structure
										as available for allocation. The application
										should never encounter a port in this state. */
	SPP_PORT_STATE_DISCONNECTED,    /**< Port is not connected. */
	SPP_PORT_STATE_DISCONNECTING,   /**< Disconnecting from remote device. */
	SPP_PORT_STATE_CONNECTING,      /**< Connecting to a remote device. */
	SPP_PORT_STATE_CONNECTED        /**< Port is connected to a remote device. */
} bt_spp_port_state_e;


/** Serial port event.
	Values of this enumeration represent serial port events. Events are reported to the
	application through a callback function. The callback function is specified when the
	port is allocated using bt_spp_allocate().
*/
typedef enum _bt_spp_port_event_e
{
	/** Connection with a remote device was successfully established.
		This event is reported independent of which side (local or remote) initiated the
		connection.
	 */
	SPP_PORT_EVENT_CONNECTED = 1,
	
	/** Connection with the remote device was terminated.
		This event is reported independent of which side (local or remote) initiated
		termination of the connection.
	*/
	SPP_PORT_EVENT_DISCONNECTED,
	
	/** Connection to a remote device failed.
		This event is reported when an attempt to establish a connection using
		bt_spp_connect() has failed.
	*/
	SPP_PORT_EVENT_CONNECTION_FAILED,
	
	/** Send operation progress.
		This event is reported periodically during sending data over the serial port
		connection. It can be used by the application to track send operation progress.
	*/
	SPP_PORT_EVENT_SEND_PROGRESS,

	/** Remote modem status.
		This event is reported when a remote device notifies the local device 
		about the status of its V.24 control signals. The actual value of the signals can
		be obtained by calling bt_spp_get_remote_modem_status(const bt_spp_port_t* port)
	*/
	SPP_PORT_EVENT_REMOTE_MODEM_STATUS_CHANGED,

	/** Local modem status.
		This event is reported when the local device has successfully sent 
		the state of its V.24 signals to the remote party.
	*/
	SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGED,

	/** Local modem status.
		This event is reported when the local device failed to send 
		the state of its V.24 signals to the remote party.
	*/
	SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGE_FAILED
} bt_spp_port_event_e;


/** Send operation status. */
typedef enum _bt_spp_send_status_e
{
	SPP_SEND_STATUS_SUCCESS = 0,          /**< The operation completed successfuly. */
	SPP_SEND_STATUS_TIMEOUT,              /**< The operation timed out. */
	SPP_SEND_STATUS_NOT_ENOUGH_RESOURCES, /**< There was not enough resources to complete the operation. */
	SPP_SEND_STATUS_CANCELED              /**< There operation was canceled. */

} bt_spp_send_status_e;

#define SPP_PORT_OPTION_SECURE      0x0001
#define SPP_PORT_OPTION_ENCRYPTED   0x0002
#define SPP_PORT_OPTION_MASTER      0x0004

#define SPP_PORT_TYPE_INCOMING      0
#define SPP_PORT_TYPE_OUTGOING      1


/* Forward declaration of bt_spp_port_t */
struct _bt_spp_port_t;
typedef struct _bt_spp_port_t bt_spp_port_t;


/** Function: Serial port state callback.

	Summary: This callback function is called whenever the state of a serial port is changed.

	Parameters:  port - Serial port which state has changed.

	  evt - Event describing the nature of state change.
			It is one of the values defined in the ::bt_spp_port_event_e enumeration.

	  param - Callback parameter that was specified when bt_spp_allocate() was called.

*/
typedef void (*bt_spp_state_callback_fp)(bt_spp_port_t* port, bt_spp_port_event_e evt, void* param);


/** Function: Serial port send callback.

	Summary: This callback function is called when a send operation initiated by bt_spp_send()
	completes.

	Parameters:  port - Serial port on which the send operation completed.

	  bytes_sent - Number of bytes sent.
			This parameter is just a convenience as it always specifies the same number of
			bytes that was passed to bt_spp_send();

	  status - Completion status.
			It is one of the values defined in the ::bt_spp_send_status_e enumeration.

	  param - Callback parameter that was specified when bt_spp_allocate() was called.

*/
typedef void (*bt_spp_send_callback_fp)(bt_spp_port_t* port, bt_ulong bytes_sent, bt_spp_send_status_e status, void* param);


/** Function: Serial port receive callback.

	Summary: This callback function is called when a receive operation initiated by
	bt_spp_receive() completes.

	Parameters:  port - Serial port on which the receive operation completed.

	  bytes_received - Number of received bytes.

	  param - Callback parameter that was specified when bt_spp_allocate() was called.

*/
typedef void (*bt_spp_receive_callback_fp)(bt_spp_port_t* port, bt_int bytes_received, void* param);


typedef void (*bt_spp_find_server_callback_fp)(bt_byte server_channel, bt_bool found, void* param);

/** Function: Serial port structure.

	Summary: This structure represents a Bluetooth serial port. Application code may only use those
	fields that are documented. The rest of the fields are private to the SPP
	implementation.
*/
struct _bt_spp_port_t
{
	/** Function: Port state.
		Summary: The field is set to one of the values defined in the ::bt_spp_port_state_e
		enumeration. This field must never be modified by the application.
	*/
	bt_byte state;

	bt_byte type;
	bt_byte server_channel;
	bt_rfcomm_dlc_t* rfcomm_dlc;
	bt_byte cur_local_ms;

	struct _bt_spp_port_flags_t
	{
		unsigned int sig_tx:1;
		unsigned int sig_rx:1;
		unsigned int sig_state:1;
		unsigned int sig_credit:1;
		unsigned int open:1;
		unsigned int listening:1;
		unsigned int secure:1;
		unsigned int encrypted:1;
		unsigned int master:1;
	} flags;
	bt_signal_t signal;

	bt_spp_state_callback_fp state_cb;
	bt_spp_receive_callback_fp receive_cb;
	bt_spp_send_callback_fp send_cb;
	void* cb_param;

	bt_byte*    rx_buffer;
	bt_int      rx_buffer_len;

	bt_byte*    tx_data;
	bt_ulong    tx_data_len;
	bt_ulong    tx_remaining_len;
	bt_bool     tx_cancel;

	bt_rfcomm_session_listener_t rfcomm_session_listener;

	bt_byte* frame_buffers;
	bt_int*  frame_len;
	bt_byte read_frame_index;
	bt_byte write_frame_index;
	bt_int  read_frame_pos;
};


/** Function: Initialize the SPP module.

	Summary: This function initializes all internal variables of the SPP module. It must
	be called prior to using any other functions in this module.
*/
void bt_spp_init(void);


/** Function: Allocate a serial port.

	Description: The returned serial port is initially in the ::SPP_PORT_STATE_DISCONNECTED state. To
	establish a connection with a remote device, call bt_spp_connect(). To listen for
	incoming connections from other devices, call bt_spp_listen(). The \p callback
	parameter must specify a callback function that will be used to notify about serial
	port events and state changes. When the port is not needed any more it must be
	deallocated by bt_spp_deallocate(). The maximum number of serial ports that can be
	allocated simultaneously is specified by the ::SPP_MAX_PORTS configuration parameter.

	Parameters:  l2cap_mgr - L2CAP manager.

	  callback - Pointer to a callback function used to notify about serial port
			events. Cannot be NULL.

	  callback_param - An arbitrary pointer that is passed as a parameter to the
			callback function.

	Returns:  A pointer to the ::bt_spp_port_t structure. Returns NULL if the maximum
			number of ports has been already allocated or the   callback parameter is
			NULL.

*/
bt_spp_port_t* bt_spp_allocate(bt_l2cap_mgr_t* l2cap_mgr,
							   bt_spp_state_callback_fp callback,
							   void* callback_param);

void bt_spp_set_port_options(bt_spp_port_t* port, bt_uint options);

void bt_spp_clr_port_options(bt_spp_port_t* port, bt_uint options);

/** Function: Listen for incoming connections.

	Description: This function registers the port to accept incoming connections from remote devices on
	a particular RFCOMM server channel. The specified server channel should be listed in
	the SDP database. Otherwise, remote devices will not be able to find out which server
	channel to use.

	When a remote device successfully establishes a connection on the specified port the
	port's callback is called with the ::SPP_PORT_EVENT_CONNECTED event.

	The port must be in ::SPP_PORT_STATE_DISCONNECTED state. Otherwise, the function will
	fail.

	Parameters:  port - Serial port.
	  channel - The RFCOMM server channel on which to listen for connections.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_bool bt_spp_listen(bt_spp_port_t* port, bt_byte channel);


/** Function: Connect to a remote device.

	Description: This function initiates a connection to a remote device. When the connection is
	successfully established the port's callback is called with the
	::SPP_PORT_EVENT_CONNECTED event. If connection fails the callback is called with the
	::SPP_PORT_EVENT_CONNECTION_FAILED event.

	The port must be in ::SPP_PORT_STATE_DISCONNECTED state. Otherwise, the function will
	fail.

	Parameters:  port - Serial port.
	  remote_addr - Bluetooth address of the remote device.
	  channel - RFCOMM server channel on which the connection is to be established.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_bool bt_spp_connect(bt_spp_port_t* port, bt_bdaddr_p remote_addr, bt_byte channel);


/** Function: Disconnect from the remote device.

	Description: This function initiates the disconnection process. When it is complete the the port's
	callback is called with the SPP_PORT_EVENT_DISCONNECTED event.

	If the port is already in the disconnected state the function does nothing and the
	callback is not called.

	Parameters:  port Serial port.
*/
void bt_spp_disconnect(bt_spp_port_t* port);


/** Function: Deallocate serial port.

	Description: This function deallocates the specified port structure and other resources associated
	with it.

	The port must be in ::SPP_PORT_STATE_DISCONNECTED state. Otherwise, the function will
	fail.

	If the function completes successfully the application must not try to access any
	fields in the structure and must not use it with any other SPP functions. Also, it
	becomes available for subsequent allocation by bt_spp_port_allocate().

	Parameters:  port - Serial port structure to deallocate.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_bool bt_spp_deallocate(bt_spp_port_t* port);


/** Function: Send data.

	Description: This function starts sending data over the serial port connection. Along with the data
	the caller must provide a callback function that is called when all data has been
	sent. Also, during execution of this operation the port's state callback function is
	called periodically with the ::SPP_PORT_EVENT_SEND_PROGRESS event.
	
	The port must be in ::SPP_PORT_STATE_CONNECTED state. Otherwise, the function will
	fail. Also, the function will fail if a previously started send operation is still in
	progress.
	
	The callback function is passed the same callback parameter that was specified when
	the port was allocated with bt_spp_allocate().

	Parameters:  port - Serial port.
	  data - Pointer to the data to be sent.
	  data_len - Length of the data.
	  callback - Send callback function.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_bool bt_spp_send(bt_spp_port_t* port, const void* data, bt_ulong data_len, bt_spp_send_callback_fp callback);


/** Function: Receive data.

	Description: This function receives data from the serial port connection. The caller must provide a
	buffer and a callback function. Whenever the port receives data they are copied to the
	provided buffer and the callback function is called. The callback function is passed
	the length of received data and the same callback parameter that was specified when the
	port was allocated with bt_spp_allocate(). This function does not wait until the
	buffer is filled out completely. Any amount of received data will complete the
	operation.
	
	The port must be in ::SPP_PORT_STATE_CONNECTED state. Otherwise, the function will
	fail. Also, the function will fail if a previously started receive operation is still
	in progress.

	Parameters:  port - Serial port.
	  data - Pointer to the data to be sent.
	  data_len - Length of the data.
	  callback - Send callback function.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_bool bt_spp_receive(bt_spp_port_t* port, void* buffer, bt_int buffer_len, bt_spp_receive_callback_fp callback);


/** Function: Cancel send data.

	Description: If a send operation is currently in progress this function will try to cancel it. When
	the operation is canceled the send callback function will be called with the
	::SPP_SEND_STATUS_CANCELED status.

	If this function is called but the active send operation completes successfuly before
	the stack can actually cancel it the call back function will still be called with the
	::SPP_SEND_STATUS_CANCELED status.

	If there is no send operation in progess calling this function has no effect.

	Parameters:  port - Serial port.
*/
void bt_spp_cancel_send(bt_spp_port_t* port);


/** Function: Cancel receive data.

	Description: If a receive operation is currently in progress this function will cancel it. After
	calling this function the receive callback specified in bt_spp_receive() will not be
	called.

	If there is no receive operation in progress calling this function has no effect.

	Parameters:  port - Serial port.
*/
void bt_spp_cancel_receive(bt_spp_port_t* port);


/** Function: Get frame length.

	Description: This function returns the RFCOMM frame length used by the RFCOMM protocol. The frame
	length depends on configuration of DotStack and configuration of the Bluetooth stack
	running on the remote device. In order to achieve maximum throughput over the serial
	port connection the application should send and receive data in chunks that are
	multiple of this frame length.

	Returns:  RFCOMM frame length in bytes.
*/
bt_int bt_spp_get_frame_length(bt_spp_port_t* port);


bt_bool bt_spp_find_server(
	bt_bdaddr_t* deviceAddress, const bt_uuid_t* service_class_id,
	bt_spp_find_server_callback_fp callback, void* callback_param);

bt_bool bt_spp_find_server_ex(
   bt_bdaddr_t* deviceAddress, const bt_uuid_t* service_class_id,
   bt_spp_find_server_callback_fp callback,
   bt_sdp_client_callback_fp client_callback,
   void* callback_param);

bt_hci_conn_state_t* bt_spp_get_hci_connection(const bt_spp_port_t* port);

bt_bdaddr_t* bt_spp_get_remote_address(const bt_spp_port_t* port);

/** Function: Get local device's TS 07.10 control signals.

	Description: This function returns current state of the local device's TS 07.10 controls signals.
	The signals are defined as a mask of the following constants:
		SPP_RS232_DSR
		SPP_RS232_RTS
		SPP_RS232_RI
		SPP_RS232_DCD


	Parameters:  port - Serial port.

	Returns:  local device's TS 07.10 control signals.
*/
bt_byte bt_spp_get_local_modem_status(const bt_spp_port_t* port);

/** Function: Set local device's TS 07.10 control signals.

	Description: Changes the state of local device's TS 07.10 control signals
	and notifies the remote device of the change.

	If there are resources to send a command to the remote device
	this command will return TRUE.

	If the remote party has been successfully notified SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGED
	event will be reported. If the command could not be send to the remote party for any reason
	other than lack of resources SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGE_FAILED will be reported.

	If the status cannot be changed because there is no resources
	to send a command to the remote device this function will return FALSE
	and no events will be reported.

	Parameters:  port - Serial port.
	  ms - Signals mask.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_byte bt_spp_set_local_modem_status(bt_spp_port_t* port, bt_byte ms);

/** Function: Get remote device's TS 07.10 control signals.

	Summary: This function returns current state of the remote device's V.24 controls signals.
	The signals are defined as a mask of the following constants:
		SPP_RS232_DTR
		SPP_RS232_CTS
		SPP_RS232_RI
		SPP_RS232_DCD


	Parameters:  port - Serial port.

	Returns:  remote device's TS 07.10 control signals.
*/
bt_byte bt_spp_get_remote_modem_status(const bt_spp_port_t* port);

/** Function: Set local device's RS-232 DTR signal.

	Description: Changes the state of local device's RS-232 DTR signal
	and notifies the remote device of the change. This signal corresponds
	to the TS 07.10's RFCOMM_MODEM_STATUS_RTC signal.

	If there are resources to send a command to the remote device
	this command will return TRUE.

	If the remote party has been successfully notified SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGED
	event will be reported. If the command could not be send to the remote party for any reason
	other than lack of resources SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGE_FAILED will be reported.

	If the status cannot be changed because there is no resources
	to send a command to the remote device this function will return FALSE
	and no events will be reported.

	Parameters:  port - Serial port.
	  on - Value indicating weather to set or clear the signal.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_byte bt_spp_set_dtr(bt_spp_port_t* port, bt_bool on);

/** Function: Set local device's RS-232 RTS signal.

	Description: Changes the state of local device's RS-232 DTR signal
	and notifies the remote device of the change. This signal corresponds
	to the TS 07.10's RFCOMM_MODEM_STATUS_RTR signal.

	If there are resources to send a command to the remote device
	this command will return TRUE.

	If the remote party has been successfully notified SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGED
	event will be reported. If the command could not be send to the remote party for any reason
	other than lack of resources SPP_PORT_EVENT_LOCAL_MODEM_STATUS_CHANGE_FAILED will be reported.

	If the status cannot be changed because there is no resources
	to send a command to the remote device this function will return FALSE
	and no events will be reported.

	Parameters:  port - Serial port.
	  on - Value indicating weather to set or clear the signal.

	Returns:    TRUE if successful,   FALSE otherwise.
*/
bt_byte bt_spp_set_rts(bt_spp_port_t* port, bt_bool on);

/*@}*/

#ifdef __cplusplus
}
#endif

#include "bluetooth/cdbt/spp/spp_private.h"

#endif // __SPP_H
