/*******************************************************************************
 Microchip Bluetooth Stack - Bluetooth General Functions

  Company:
    Searan LLC.

  File Name:
    bt_config.h

  Summary:
    Bluetooth API Library interface to Bluetooth General Functions.

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

#ifndef __BT_CONFIG_H_INCLUDED__
#define __BT_CONFIG_H_INCLUDED__

#include "bluetooth/cdbt/plat/config.h"

/**
 * \defgroup btconfig DotStack Configuration
 */

/**
 * Summary:  BT_ENABLE_SCO.
 * , Functional Group:  btconfig
 *
 * Description:  Enables support of synchronous connections.
 * HCI_MAX_CONNECTIONS must be at least 2
 */
//#define BT_ENABLE_SCO
//#if defined(BT_ENABLE_SCO) && HCI_MAX_CONNECTIONS < 2
//#error "SCO links require at least 2 connections available"
//#endif


/**
* Summary:  BT_ENABLE_SSP.
* , Functional Group:  btconfig
*
* Description:  Enables support of Simple Secure Pairing.
*/
//#define BT_ENABLE_SSP

/**
 * Summary:  L2CAP_ENABLE_EXT_FEATURES.
 * , Functional Group:  btconfig
 *
 * Description:  Enables support of Enhanced Retransmission ans Streaming modes.
 */


#endif // __BT_CONFIG_H_INCLUDED__
