/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hci_linkkey_buffer.h

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

#ifndef __HCI_LINKKEY_BUFFER_H
#define __HCI_LINKKEY_BUFFER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

typedef struct _bt_hci_link_key_s
{
	bt_bdaddr_t bdaddr;
	bt_byte linkkey[HCI_LINK_KEY_LEN];

} bt_hci_link_key_t;

void bt_hci_init_linkkey_buffers(void);

#ifdef __cplusplus
}
#endif

#endif // __HCI_LINKKEY_BUFFER_H
