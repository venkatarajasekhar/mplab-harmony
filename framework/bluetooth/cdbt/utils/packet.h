/*******************************************************************************
 Microchip Bluetooth Stack - Utilities

  Company:
    Searan LLC.

  File Name:
    packet.h

  Summary:
    Bluetooth API Library interface Utilities.

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

#ifndef __UTILS_PACKET_H  // Guards against multiple inclusion
#define __UTILS_PACKET_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

struct _bt_packet_t;

typedef bt_int (*bt_packet_assembler_fp)(struct _bt_packet_t* packet, bt_byte* buffer, bt_int buffer_len);

typedef struct _bt_packet_t
{
	bt_packet_assembler_fp packet_assembler;
	const bt_byte* data;
	bt_int len;
	bt_byte state;
	bt_int data_pos;
	void* param;
} bt_packet_t;

#ifdef __cplusplus
}
#endif

#endif // __UTILS_PACKET_H
