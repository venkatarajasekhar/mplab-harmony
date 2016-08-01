/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hcitr_uart.h

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

#ifndef __HCITR_UART_H_INCLUDED__
#define __HCITR_UART_H_INCLUDED__

/**
* \defgroup hcitr_uart HCI UART (H4) transport protocol
* \ingroup hcitr
*
* \details
* This module describes functions used to initialize and start HCI UART transport protocol.
* The transport uses common interface for exchanging data between the host CPU and HCI controller
* defined in bt_hcitr.h. This interface consist of two functions that must be implemented by the application:
*	\li bt_oem_send()
*	\li bt_oem_recv()
*
*/

#define HCI_UART_PACKET_TYPE_COMMAND    1
#define HCI_UART_PACKET_TYPE_ACL_DATA   2
#define HCI_UART_PACKET_TYPE_SCO_DATA   3
#define HCI_UART_PACKET_TYPE_EVENT      4

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

/**
* \brief  Initialize HCI UART (H4) transport protocol
* \ingroup hcitr_uart
*
* \details This function initializes internal structures of the transport. 
*          The application must call it as early as possible before bt_hcitr_uart_start
*          and before the stack is initialized and started with bt_sys_init and bt_sys_start.
*          
*/
void bt_hcitr_uart_init(void);

/**
* \brief  Re-initialize HCI UART (H4) transport protocol
* \ingroup hcitr_uart
*
* \details This function re-initializes the transport. Currently it simply calls bt_hcitr_uart_init.
*          After calling this function the application must perform the full initialization of the stack by calling
*          bt_sys_init, bt_sys_start and initialization functions of all other profile modules
*          the application is intending to use.
*
*/
void bt_hcitr_uart_reset(void);

/**
* \brief  Start HCI UART (H4) transport protocol
* \ingroup hcitr_uart
*
* \details This function starts the transport, i.e., makes it able to receive and send packets. 
*
*/
void bt_hcitr_uart_start(void);

#ifdef __cplusplus
}
#endif

#endif // __HCITR_UART_H_INCLUDED__

