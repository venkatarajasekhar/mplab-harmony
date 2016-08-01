/*******************************************************************************
 Microchip Bluetooth Stack - Bluetooth General Functions

  Company:
    Searan LLC.

  File Name:
    bt_storage.h

  Summary:
    Bluetooth API Library interface to Bluetooth General Functions.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.

	DotStack requires a non-volatile storage for storing link keys.
    This module declares an interface for accessing such storage. The application
    must provide implementations of all functions of this interface.

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

#ifndef __BLUETOOTH_BT_storage_H
#define __BLUETOOTH_BT_storage_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#define HCI_BDADDR_LEN		6
#define LKS_MAX_LINK_KEYS	5
#define LKS_SIGNATURE_ADDR	0
#define LKS_SIGNATURE		0x9D
#define LKS_FIRST_KEY_ADDR	2

#define HIDS_SIGNATURE_ADDR 	LKS_SIGNATURE_ADDR + 2 + (HCI_BDADDR_LEN + HCI_LINK_KEY_LEN) * LKS_MAX_LINK_KEYS
#define HIDS_SIGNATURE			0x8E
#define HIDS_LAST_DEVICE_ADDR	HIDS_SIGNATURE_ADDR + 1

#define CDS_SIGNATURE_ADDR 		HIDS_SIGNATURE_ADDR
#define CDS_SIGNATURE			HIDS_SIGNATURE
#define CDS_LAST_DEVICE_ADDR	HIDS_LAST_DEVICE_ADDR


/**
 * Summary:  Storage callback.
 *
 * Description:  This callback is called when a non-volatile storage operation completes.
 */
typedef void (*bt_storage_callback_fp) (void);


/**
 * Summary:  Get non-volatile storage capacity.
 * , Functional Group:  BT_storage
 *
 * Description:  Implementation of this function must return the capacity of its non-volatile
 * storage.
 */
bt_uint bt_oem_storage_get_capacity(void);


/**
 * Summary:  Begin a sequence of non-volatile storage operations.
 * , Functional Group:  BT_storage
 *
 * Description:  DotStack calls this function when it starts a sequence of non-volatile storage
 * operations. When the sequence is finished, DotStack will call bt_oem_storage_stop().
 */
void bt_oem_storage_start(void);


/**
 * Summary:  End a sequence of non-volatile storage operations.
 * , Functional Group:  BT_storage
 *
 * Description:  DotStack calls this function when it finishes executing a sequence of
 * non-volatile storage operations.
 */
void bt_oem_storage_stop(void);


/**
 * Summary:  Write to non-volatile storage.
 * , Functional Group:  BT_storage
 *
 * Description:  This function is called by the stack to write data to the non-volatile storage.
 * This function must be implemented by the application. When this function is called, the
 * application must start writing specified data to the non-volatile storage. When all data
 * has been written, the application must call the callback function passed in the callback
 * parameter. The application does not have to complete the write operation during the call
 * to this function. It may complete the operation later and then call the callback function.
 * In this case, the application does not have to store the data in an internal buffer. The
 * stack guarantees that the passed data will be present until the completion callback is
 * called by the application.
 *
 * Parameters:  addr - The persitent storage address where to write data to.
 *   data - Pointer to data.
 *   len - Data length.
 *   callback - The completion callback function.
 *
 */
void bt_oem_storage_write(bt_int addr, const bt_byte* data, bt_int len, bt_storage_callback_fp callback);


/**
 * Summary:  Read from the non-volatile storage.
 * , Functional Group:  BT_storage
 *
 * Description:  This function is called by the stack to read from the non-volatile storage.
 * This function must be implemented by the application. When this function is called
 * the application must start a read operation. When the number of bytes specified by
 * the len parameter is read, the application must call the callback function
 * specified by the callback parameter. The application does not have to
 * read the whole number of bytes during the call to this function. It may complete
 * reading later and then call the completion callback. The stack guarantees that
 * the destination data buffer will be available until the application calls the
 * completion callback.
 *
 * Parameters:  addr - The non-volatile storage address where to read data from.
 *   buffer - The receiving buffer.
 *   len - The number of bytes to read.
 *   callback - The completion callback function.
 *
 */
void bt_oem_storage_read(bt_int addr, bt_byte* buffer, bt_int len, bt_storage_callback_fp callback);

#ifdef __cplusplus
}
#endif

#endif // __BLUETOOTH_BT_storage_H
