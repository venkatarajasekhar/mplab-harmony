/*******************************************************************************
  ENCx24J600 Configure State Machine
  Company:
    Microchip Technology Inc.

  File Name:
    drv_encx24j600_configure_state.h
  Summary:

  Description:
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.
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
// DOM-IGNORE-END
#ifndef _DRV_ENCX24J600_CONFIGURE_STATE_H_
#define _DRV_ENCX24J600_CONFIGURE_STATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "system_config.h"
#include "system_definitions.h"


struct _DRV_ENCX24J600_DriverInfo;

typedef enum
{
    DRV_ENCX24J600_CS_SET_EGPRDPT,
    DRV_ENCX24J600_CS_SET_ERXRDPT,
    DRV_ENCX24J600_CS_SET_EUDARDPT,
    DRV_ENCX24J600_CS_SET_EGPWRPT,
    DRV_ENCX24J600_CS_SET_ERXWRPT,
    DRV_ENCX24J600_CS_SET_EUDAWRPT,
    DRV_ENCX24J600_CS_SET_ERXST,
    DRV_ENCX24J600_CS_SET_ERXTAIL,
    DRV_ENCX24J600_CS_SET_EUDAST,
    DRV_ENCX24J600_CS_SET_EUDAND,
    DRV_ENCX24J600_CS_READ_MACON2,
    DRV_ENCX24J600_CS_WRITE_MAADR1,
    DRV_ENCX24J600_CS_WRITE_MAADR2,
    DRV_ENCX24J600_CS_WRITE_MAADR3,
    DRV_ENCX24J600_CS_READ_MAADR1,
    DRV_ENCX24J600_CS_READ_MAADR2,
    DRV_ENCX24J600_CS_READ_MAADR3,
    DRV_ENCX24J600_CS_WAIT_FOR_MACON2,
    DRV_ENCX24J600_CS_SET_MACON2,
    DRV_ENCX24J600_CS_SET_PHANA,
    DRV_ENCX24J600_CS_SET_EIE,
    DRV_ENCX24J600_CS_WAIT_FOR_MAADR3,
}DRV_ENCX24J600_CONFIGURE_STATES;

typedef enum
{
    DRV_ENCX24J600_CS_OP_SET_EGPRDPT,
    DRV_ENCX24J600_CS_OP_SET_MACON2 = DRV_ENCX24J600_CS_OP_SET_EGPRDPT,
    DRV_ENCX24J600_CS_OP_SET_ERXRDPT,
    DRV_ENCX24J600_CS_OP_SET_PHANA_1 = DRV_ENCX24J600_CS_OP_SET_ERXRDPT,
    DRV_ENCX24J600_CS_OP_SET_EUDARDPT,
    DRV_ENCX24J600_CS_OP_SET_PHANA_2 = DRV_ENCX24J600_CS_OP_SET_EUDARDPT,
    DRV_ENCX24J600_CS_OP_SET_EGPWRPT,
    DRV_ENCX24J600_CS_OP_SET_EIE = DRV_ENCX24J600_CS_OP_SET_EGPWRPT,
    DRV_ENCX24J600_CS_OP_SET_ERXWRPT,
    DRV_ENCX24J600_CS_OP_SET_EUDAWRPT,
    DRV_ENCX24J600_CS_OP_SET_ERXST,
    DRV_ENCX24J600_CS_OP_SET_ERXTAIL,
    DRV_ENCX24J600_CS_OP_SET_EUDAST,
    DRV_ENCX24J600_CS_OP_SET_EUDAND,
    DRV_ENCX24J600_CS_OP_READ_MACON2,
    DRV_ENCX24J600_CS_OP_WRITE_MAADR1,
    DRV_ENCX24J600_CS_OP_WRITE_MAADR2,
    DRV_ENCX24J600_CS_OP_WRITE_MAADR3,
    DRV_ENCX24J600_CS_OP_READ_MAADR1,
    DRV_ENCX24J600_CS_OP_READ_MAADR2,
    DRV_ENCX24J600_CS_OP_READ_MAADR3,

}DRV_ENCX24J600_CONFIG_STATE_OPS;

typedef struct _DRV_ENCX24J600_CONFIGURE_STATE_INFO
{
    DRV_ENCX24J600_CONFIGURE_STATES state;
    uintptr_t waitForMacon2Op;
    uintptr_t waitForMaddr1Op;
    uintptr_t waitForMaddr2Op;
    uintptr_t waitForMaddr3Op;
}DRV_ENCX24J600_CONFIGURE_STATE_INFO;

int32_t DRV_ENCX24J600_ConfigStateTask(struct _DRV_ENCX24J600_DriverInfo * pDrvInst);
int32_t DRV_ENCX24J600_ConfigStateEnter(struct _DRV_ENCX24J600_DriverInfo * pDrvInst);
int32_t DRV_ENCX24J600_ConfigStateExit(struct _DRV_ENCX24J600_DriverInfo * pDrvInst);



#ifdef __cplusplus
}
#endif


#endif