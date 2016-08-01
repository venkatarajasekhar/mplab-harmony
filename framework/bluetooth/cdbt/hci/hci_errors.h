/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hci_errors.h

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

#ifndef __HCI_ERRORS_H
#define __HCI_ERRORS_H

#define HCI_ERR_SUCCESS								0x00
#define HCI_ERR_AUTHENTICATION_FAILURE				0x05
#define HCI_ERR_MEMORY_CAPACITY_EXCEEDED            0x07
#define HCI_ERR_CONNECTION_TIMEOUT                  0x08
#define HCI_ERR_SCO_CONN_LIMIT_EXCEEDED				0x0a
#define HCI_ERR_ACL_CONN_ALREADY_EXISTS				0x0b
#define HCI_ERR_CONN_REJECT_LIMITED_RESOURCES		0x0d
#define HCI_ERR_INVALID_PARAMETERS					0x12
#define HCI_ERR_UNSPECIFIED							0x1F
#define HCI_ERR_SIMPLE_PAIRING_NOT_SUPPORTED		0x37

#endif // __HCI_ERRROS_H
