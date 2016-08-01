/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hci_data_buffer.h

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

#ifndef __HCI_DATA_BUFFER_H
#define __HCI_DATA_BUFFER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#ifndef HCI_MAX_DATA_BUFFERS
#define HCI_MAX_DATA_BUFFERS 2
#endif

#define HCI_DATA_BUFFER_STATE_FREE 0
#define HCI_DATA_BUFFER_STATE_USED 1

typedef struct _bt_hci_data_buffer_s {
	bt_int state;
	bt_hci_data_t packet;
} bt_hci_data_buffer_t, *bt_hci_data_buffer_p;

void bt_hci_init_data_buffers(void);
bt_hci_data_p bt_hci_alloc_data_buffer(void);
void bt_hci_free_data_buffer(bt_hci_data_p p);

#ifdef __cplusplus
}
#endif

#endif // __HCI_DATA_BUFFER_H
