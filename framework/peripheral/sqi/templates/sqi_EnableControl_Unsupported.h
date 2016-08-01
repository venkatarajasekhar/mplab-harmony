/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_EnableControl_Unsupported.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : EnableControl
    and its Variant : Unsupported
    For following APIs :
        PLIB_SQI_Enable
        PLIB_SQI_Disable
        PLIB_SQI_ExistsEnableControl

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/

//DOM-IGNORE-END

#ifndef _SQI_ENABLECONTROL_UNSUPPORTED_H
#define _SQI_ENABLECONTROL_UNSUPPORTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    None.

  MASKs: 
    None.

  POSs: 
    None.

  LENs: 
    None.

*/


//******************************************************************************
/* Function :  SQI_Enable_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_SQI_Enable 

  Description:
    This template implements the Unsupported variant of the PLIB_SQI_Enable function.
*/

PLIB_TEMPLATE void SQI_Enable_Unsupported( SQI_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_SQI_Enable");
}


//******************************************************************************
/* Function :  SQI_Disable_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_SQI_Disable 

  Description:
    This template implements the Unsupported variant of the PLIB_SQI_Disable function.
*/

PLIB_TEMPLATE void SQI_Disable_Unsupported( SQI_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_SQI_Disable");
}


//******************************************************************************
/* Function :  SQI_ExistsEnableControl_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_SQI_ExistsEnableControl

  Description:
    This template implements the Unsupported variant of the PLIB_SQI_ExistsEnableControl function.
*/

PLIB_TEMPLATE bool SQI_ExistsEnableControl_Unsupported( SQI_MODULE_ID index )
{
    return false;
}


#endif /*_SQI_ENABLECONTROL_UNSUPPORTED_H*/

/******************************************************************************
 End of File
*/

