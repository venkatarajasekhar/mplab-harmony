/*******************************************************************************
 Microchip Bluetooth Stack - Platform

  Company:
    Searan LLC.

  File Name:
    types.h

  Summary:
    Bluetooth API Library interface to the Platform.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.  This module describe the type 
	definitions for the platform.
    
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

/*
 * Basic type definitions for the PIC32 architecture.
 */

#ifndef __PLAT_TYPES_H_INCLUDED__
#define __PLAT_TYPES_H_INCLUDED__

#define BYTE_SIZE 1

typedef short             bt_int;
typedef long              bt_long;
typedef unsigned char     bt_byte;
typedef unsigned short    bt_uint;
typedef unsigned long     bt_ulong;
typedef unsigned long long    bt_ulonglong;

#endif // __PLAT_TYPES_H_INCLUDED__
