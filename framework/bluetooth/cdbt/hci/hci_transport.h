/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hci_transport.h

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

#ifndef __HCI_TRANSPORT_H
#define __HCI_TRANSPORT_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#define HCI_TRANSPORT_HEADER_LEN	1

typedef void (*bt_hci_transport_send_packet_callback_fp)(void);
typedef void (*bt_hci_transport_recv_packet_callback_fp)(bt_uint len);

typedef struct _hci_transport_t
{
    void (*send_packet)(const bt_byte* buffer, bt_uint len, bt_hci_transport_send_packet_callback_fp callback);
    void (*recv_packet)(bt_byte* buffer, bt_uint len, bt_hci_transport_recv_packet_callback_fp callback);
} hci_transport_t;


void bt_hci_transport_set_transport(const hci_transport_t* transport);
void bt_hci_transport_send_packet(const bt_byte* buffer, bt_uint len, bt_hci_transport_send_packet_callback_fp callback);
void bt_hci_transport_recv_packet(bt_byte* buffer, bt_uint len, bt_hci_transport_recv_packet_callback_fp callback);


void bt_hci_transport_send_cmd(const bt_byte* buffer, bt_uint len, bt_hci_transport_send_packet_callback_fp callback); // deprecated
void bt_hci_transport_send_data(bt_byte* buffer, bt_uint len, bt_hci_transport_send_packet_callback_fp callback); // deprecated


#ifdef __cplusplus
}
#endif

#endif // __HCI_TRANSPORT_H
