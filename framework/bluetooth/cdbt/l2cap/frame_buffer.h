/*******************************************************************************
 Microchip Bluetooth Stack - Logical Link Control and Adaptation Protocol

  Company:
    Searan LLC.

  File Name:
    frame_buffer.h

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

#ifndef __L2CAP_FRAME_BUFFER_H
#define __L2CAP_FRAME_BUFFER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#ifndef L2CAP_MAX_FRAME_BUFFERS
#define L2CAP_MAX_FRAME_BUFFERS 2
#endif

void bt_l2cap_init_frame_buffers(void);
bt_byte_p bt_l2cap_alloc_frame_buffer(void);
void bt_l2cap_free_frame_buffer(bt_byte_p data);

#ifdef __cplusplus
}
#endif

#endif // __L2CAP_FRAME_BUFFER_H
