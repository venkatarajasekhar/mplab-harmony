/*******************************************************************************
  PMP Peripheral Library Template Implementation

  File Name:
    pmp_WriteEnablePortControl_Default.h

  Summary:
    PMP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : WriteEnablePortControl
    and its Variant : Default
    For following APIs :
        PLIB_PMP_ExistsWriteEnablePortControl
        PLIB_PMP_WriteEnableStrobePortEnable
        PLIB_PMP_WriteEnableStrobePortDisable

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _PMP_WRITEENABLEPORTCONTROL_DEFAULT_H
#define _PMP_WRITEENABLEPORTCONTROL_DEFAULT_H

//******************************************************************************
/* Function :  PMP_ExistsWriteEnablePortControl_Default

  Summary:
    Implements Default variant of PLIB_PMP_ExistsWriteEnablePortControl

  Description:
    This template implements the Default variant of the PLIB_PMP_ExistsWriteEnablePortControl function.
*/
#define PLIB_PMP_ExistsWriteEnablePortControl PLIB_PMP_ExistsWriteEnablePortControl
PLIB_TEMPLATE bool PMP_ExistsWriteEnablePortControl_Default( PMP_MODULE_ID index )
{
    return true;
}

//******************************************************************************
/* Function :  PMP_WriteEnableStrobePortEnable_Default

  Summary:
    Implements Default variant of PLIB_PMP_WriteEnableStrobePortEnable 

  Description:
    This template implements the Default variant of the PLIB_PMP_WriteEnableStrobePortEnable function.
*/
PLIB_TEMPLATE void PMP_WriteEnableStrobePortEnable_Default( PMP_MODULE_ID index )
{
   (PMCONSET) = (_PMCON_PTWREN_MASK);
}

//******************************************************************************
/* Function :  PMP_WriteEnableStrobePortDisable_Default

  Summary:
    Implements Default variant of PLIB_PMP_WriteEnableStrobePortDisable 

  Description:
    This template implements the Default variant of the PLIB_PMP_WriteEnableStrobePortDisable function.
*/

PLIB_TEMPLATE void PMP_WriteEnableStrobePortDisable_Default( PMP_MODULE_ID index )
{
   (PMCONCLR) = (_PMCON_PTWREN_MASK);
}

#endif /*_PMP_WRITEENABLEPORTCONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

