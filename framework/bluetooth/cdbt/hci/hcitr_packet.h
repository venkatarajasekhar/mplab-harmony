/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hcitr_packet.h

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

#ifndef __HCITR_PACKET_H
#define __HCITR_PACKET_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

void bt_hcitr_packet_init(void);
void bt_hcitr_packet_reset(void);
void bt_hcitr_packet_start(void);

#ifdef __cplusplus
}
#endif

#endif // __HCITR_PACKET_H
