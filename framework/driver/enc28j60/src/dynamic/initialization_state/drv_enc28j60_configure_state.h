/*******************************************************************************
  ENC28J60 Configure State Machine
  Company:
    Microchip Technology Inc.

  File Name:
    drv_enc28j60_configure_state.h
  Summary:

  Description:
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.
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
#ifndef _DRV_ENC28J60_CONFIGURE_STATE_H_
#define _DRV_ENC28J60_CONFIGURE_STATE_H_

#include "system_config.h"
#include "system_definitions.h"


struct _DRV_ENC28J60_DriverInfo;

typedef enum
{
    DRV_ENC28J60_CS_SET_ERXST,
    DRV_ENC28J60_CS_WAIT_ERXST,
    DRV_ENC28J60_CS_SET_ERXRDPT,
    DRV_ENC28J60_CS_WAIT_ERXRDPT,
    DRV_ENC28J60_CS_SET_ERXND,
    DRV_ENC28J60_CS_WAIT_ERXND,

    DRV_ENC28J60_CS_SET_ETXST,
    DRV_ENC28J60_CS_WAIT_ETXST,
	DRV_ENC28J60_CS_SET_EWRPT,
    DRV_ENC28J60_CS_WAIT_EWRPT,

    DRV_ENC28J60_CS_SET_MACON1,
    DRV_ENC28J60_CS_WAIT_MACON1,
	DRV_ENC28J60_CS_SET_MACON3,
    DRV_ENC28J60_CS_WAIT_MACON3,
	DRV_ENC28J60_CS_SET_MABBIPG,
    DRV_ENC28J60_CS_WAIT_MABBIPG,
	DRV_ENC28J60_CS_SET_MACON4,
    DRV_ENC28J60_CS_WAIT_MACON4,

	DRV_ENC28J60_CS_SET_MACLCON2,
    DRV_ENC28J60_CS_WAIT_MACLCON2,
	DRV_ENC28J60_CS_SET_MAIPG,
    DRV_ENC28J60_CS_WAIT_MAIPG,
	DRV_ENC28J60_CS_SET_MAMXFL,	
    DRV_ENC28J60_CS_WAIT_MAMXFL,

    DRV_ENC28J60_CS_WRITE_MAADR5,
    DRV_ENC28J60_CS_WAIT_MAADR5,
    DRV_ENC28J60_CS_WRITE_MAADR3,
    DRV_ENC28J60_CS_WAIT_MAADR3,
    DRV_ENC28J60_CS_WRITE_MAADR1,
    DRV_ENC28J60_CS_WAIT_MAADR1,

	DRV_ENC28J60_CS_SET_ECOCON,
    DRV_ENC28J60_CS_WAIT_ECOCON,

	DRV_ENC28J60_CS_SET_PHCON2,
	DRV_ENC28J60_CS_WAIT_PHCON2,
	DRV_ENC28J60_CS_SET_PHLCON,
	DRV_ENC28J60_CS_WAIT_PHLCON,
	DRV_ENC28J60_CS_SET_PHCON1,
	DRV_ENC28J60_CS_WAIT_PHCON1,
	DRV_ENC28J60_CS_SET_PHIE,
	DRV_ENC28J60_CS_WAIT_PHIE,

    DRV_ENC28J60_CS_SET_EIE,
    DRV_ENC28J60_CS_WAIT_EIE,
    
    DRV_ENC28J60_CS_SET_ECON2,
    DRV_ENC28J60_CS_WAIT_ECON2,
    DRV_ENC28J60_CS_SET_ECON1,
    DRV_ENC28J60_CS_WAIT_ECON1,

    DRV_ENC28J60_CS_DONE,

}DRV_ENC28J60_CONFIGURE_STATES;


typedef struct _DRV_ENC28J60_CONFIGURE_STATE_INFO
{
    DRV_ENC28J60_CONFIGURE_STATES state;
    uintptr_t   op;

}DRV_ENC28J60_CONFIGURE_STATE_INFO;

int32_t DRV_ENC28J60_ConfigStateTask(struct _DRV_ENC28J60_DriverInfo * pDrvInst);
int32_t DRV_ENC28J60_ConfigStateEnter(struct _DRV_ENC28J60_DriverInfo * pDrvInst);
int32_t DRV_ENC28J60_ConfigStateExit(struct _DRV_ENC28J60_DriverInfo * pDrvInst);


#endif
