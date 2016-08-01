/*******************************************************************************
  SQI Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_sqi_static.c

  Summary:
    This file contains source code necessary to initialize the SQI driver.

  Description:
    The SQI device driver provides a simple interface to manage the SQI
    modules on Microchip microcontrollers. This file defines the interface
    Declarations for the SQI driver.

  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "drv_sqi_static.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************
uint8_t __attribute__((coherent)) sqiCmdBuffer[32];
uint32_t __attribute__((coherent)) jedecID;
static uint8_t __attribute__((coherent, aligned(4))) sqiTempRead[4];
static uint32_t __attribute__((coherent, aligned(4))) sqiReadWord;
// *****************************************************************************
// *****************************************************************************
// Function: Soft delay functions (local)
// *****************************************************************************
// *****************************************************************************
inline static uint32_t _DRV_SQI_ReadCoreTimer()
{
    volatile uint32_t timer;

    // get the readSize reg
    asm volatile("mfc0   %0, $9" : "=r"(timer));

    return(timer);
}

inline static void _DRV_SQI_StartCoreTimer(uint32_t period)
{
    /* Reset the coutner */
    volatile uint32_t loadZero = 0;

    asm volatile("mtc0   %0, $9" : "+r"(loadZero));
    asm volatile("mtc0   %0, $11" : "+r" (period));
}

inline void _DRV_SQI_CoreTimer_Delay(uint32_t delayValue)
{
    while ((_DRV_SQI_ReadCoreTimer() <= delayValue))
    asm("nop");
}

inline void _DRV_SQI_BufferThrSet(uint16_t conThr, uint16_t txThr, uint16_t rxThr)
{
    if (conThr != 0)
	    PLIB_SQI_ControlBufferThresholdSet(DRV_SQI_ID_0, conThr);
	if (txThr !=0)
    {
	    PLIB_SQI_TxBufferThresholdSet(DRV_SQI_ID_0, txThr);
	    PLIB_SQI_TxBufferThresholdIntSet(DRV_SQI_ID_0, txThr);
    }
    if (rxThr != 0)
    {
        PLIB_SQI_RxBufferThresholdSet(DRV_SQI_ID_0, rxThr);
        PLIB_SQI_RxBufferThresholdIntSet(DRV_SQI_ID_0, rxThr);
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: SQI Static Driver Functions
// *****************************************************************************
// *****************************************************************************
void DRV_SQI_Initialize(void)
{
    // Set up SQI Configuration (SQI1CFG) Register
    PLIB_SQI_ConfigWordSet(DRV_SQI_ID_0,
                           1,
                           DRV_SQI_CS_OEN_1,
			               DRV_SQI_DATA_OEN_QUAD,
			               0, // Resets control, transmit, receive buffers and state machines
			               1, // Burst Enable (always set to '1')
			               0, // SQID2 doesn?t act as HOLD# signal in single and dual lane modes
                           0, // SQID3 doesn?t act as WP# signal in single and dual lane modes
			               0, // Receive latch is not active in transmit mode
                           DRV_SQI_DATA_FORMAT_MSBF,
			               DRV_SQI_DATA_MODE_0,
			               DRV_SQI_XFER_MODE_PIO
			              );

    // Configure SQI1CLKCON
    PLIB_SQI_ClockDividerSet(DRV_SQI_ID_0, CLK_DIV_2);
    PLIB_SQI_ClockEnable(DRV_SQI_ID_0);
    while(!PLIB_SQI_ClockIsStable(DRV_SQI_ID_0));

}

void DRV_SQI_Flash_Initialize (void)
{
    /* Setup CONTROL, TX and RX buffer thresholds */
    _DRV_SQI_BufferThrSet(1, 4, 4);

    /* Reset the SQI Flash */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* RSTEN */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_SINGLE, DRV_SQI_CMD_TRANSMIT, 1);   /* RST */
    /* Transmit reset enable */
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (FLASH_RSTEN <<24) | (FLASH_NOP<< 16) |(FLASH_NOP << 8) | FLASH_NOP);

    /* Wait for 25ms for the reset cycle to be enabled */
    _DRV_SQI_StartCoreTimer(0);
    _DRV_SQI_CoreTimer_Delay(500000);

    /* Transmit reset */
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (FLASH_NOP << 24) | (FLASH_NOP << 16) | (FLASH_NOP << 8) | FLASH_RST);
    
    /* Wait for 1 ms for the rest to be finished */
    _DRV_SQI_StartCoreTimer(0);
    _DRV_SQI_CoreTimer_Delay(100000); 
}

void DRV_SQI_Flash_Erase (void)
{
    /* Configure SQI for PIO mode */
    PLIB_SQI_TransferModeSet(DRV_SQI_ID_0, DRV_SQI_XFER_MODE_PIO);

    /* Setup CONTROL, TX and RX buffer thresholds */
	_DRV_SQI_BufferThrSet(1, 4, 4);

	/* Enable TXTHR interrupt signal */
	PLIB_SQI_InterruptSignalEnable(DRV_SQI_ID_0, DRV_SQI_TXTHR);

    /* Setup control buffer to send block un-protect command */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* WEN */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* GBLKUP */

    /* Send necessary commands to un-protect the flash blocks*/
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (FLASH_UNPROTECT_GLOBAL << 24) | (FLASH_WEN << 16) | (FLASH_NOP << 8) | FLASH_NOP);

    /* Wait for TXTHR to get set */
    while (PLIB_SQI_InterruptFlagGet(DRV_SQI_ID_0, DRV_SQI_TXTHR) == false);

    /* Setup control buffer to set SQI Flash in quad lane mode and  send erase the flash command  */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* WEN */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* ERASE */

    /* Send necessary commands to erase the flash */
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (FLASH_ERASE << 24) | (FLASH_WEN << 16) | (FLASH_NOP << 8) | (FLASH_NOP));

    /* Wait for TXTHR to get set and disable interrupt signal (deosn't trigger actual interupt) */
    while (PLIB_SQI_InterruptFlagGet(DRV_SQI_ID_0, DRV_SQI_TXTHR) == false);
    PLIB_SQI_InterruptSignalDisable(DRV_SQI_ID_0, DRV_SQI_TXTHR);

    // Wait 50 ms for the erase to complete (reason unknown for this delay even after BUSY/READY check) */
    _DRV_SQI_StartCoreTimer(0);
    _DRV_SQI_CoreTimer_Delay(5000000);
}

SQI_STATUS DRV_SQI_Flash_ID_Check (void)
{
    /* Configure SQI for PIO mode */
    PLIB_SQI_TransferModeSet(DRV_SQI_ID_0, DRV_SQI_XFER_MODE_PIO);

    /* Setup CONTROL, TX and RX buffer thresholds */
	_DRV_SQI_BufferThrSet(1, 4, 4);

	/* Enable TXTHR interrupt signal */
	PLIB_SQI_InterruptSignalEnable(DRV_SQI_ID_0, DRV_SQI_TXTHR);

    /* Configure to send the QJID command */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,1,DRV_SQI_CS_1,DRV_SQI_LANE_SINGLE,DRV_SQI_CMD_TRANSMIT,1);        /* EQIO */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,1,DRV_SQI_CS_1,DRV_SQI_LANE_QUAD,DRV_SQI_CMD_TRANSMIT,1);          /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,0,DRV_SQI_CS_1,DRV_SQI_LANE_QUAD,DRV_SQI_CMD_TRANSMIT,2);          /* QJID & DUMMY */   
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,1,DRV_SQI_CS_1,DRV_SQI_LANE_QUAD,DRV_SQI_CMD_RECEIVE,4);           /* ID READ */

    //Write the command to the transfer buffer
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (FLASH_NOP << 24) | (FLASH_QJID << 16) | (FLASH_NOP << 8) | (FLASH_EQIO));
        
    while (PLIB_SQI_InterruptFlagGet(DRV_SQI_ID_0, DRV_SQI_RXTHR) == false);

    jedecID = PLIB_SQI_ReceiveData(DRV_SQI_ID_0);
    
    jedecID = jedecID & 0x00FFFFFF;

    if (jedecID != FLASH_JEDECID_B)
        return SQI_STATUS_FAILURE;
    else

        return SQI_STATUS_SUCCESS;
}

void DRV_SQI_PIO_PageWrite (uint32_t flashAddress, uint8_t* writeBuffer)
{
    uint32_t txWord;
    uint32_t* writeBufferWord;
    uint8_t tempAddress1, tempAddress2, tempAddress3;
    uint32_t nCount = FLASH_PAGE_SIZE;

    // Address manipulation (LaZ logic)
    tempAddress1 = (uint8_t) (flashAddress >> 16);
    tempAddress2 = (uint8_t) (flashAddress >> 8);
    tempAddress3 = (uint8_t) flashAddress;
    flashAddress = tempAddress1 | tempAddress2 << 8 | tempAddress3 << 16;

    writeBufferWord = (uint32_t *) writeBuffer;
            
    /* configure for PIO mode */
    PLIB_SQI_TransferModeSet(DRV_SQI_ID_0, DRV_SQI_XFER_MODE_PIO);
    
    /* Setup CONTROL, TX and RX buffer thresholds */
	_DRV_SQI_BufferThrSet(1, 4, 4);    

    /* write the control words and WEN */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* WEN */

    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (FLASH_WEN << 24) | 0x00000000);

    /* write the command and address */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 0, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* PAGE WRITE */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 0, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 3);     /* ADDRESS */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 0x100); /* DATA */

    // Write the command to the transfer buffer
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, flashAddress << 8 | FLASH_PAGE_WRITE);

    while (!(PLIB_SQI_InterruptFlagGet(DRV_SQI_ID_0, DRV_SQI_TXTHR)));

    while (nCount >= 4) {
        txWord = *writeBufferWord++;
        PLIB_SQI_TransmitData(DRV_SQI_ID_0, txWord);
        while (PLIB_SQI_InterruptFlagGet(DRV_SQI_ID_0, DRV_SQI_TXTHR) == false);
        nCount -= 4;
    }    

    // Wait 10 ms for the write to complete */
    _DRV_SQI_StartCoreTimer(0);
    _DRV_SQI_CoreTimer_Delay(200000);
}

void DRV_SQI_PIO_PageRead(uint32_t flashAddress, uint32_t* readBuffer)
{
    uint32_t readLoop, bufLoop;

    memset(sqiCmdBuffer, 0, sizeof(sqiCmdBuffer));
    sqiCmdBuffer[0] = (uint8_t) FLASH_FAST_READ;
    sqiCmdBuffer[1] = (uint8_t) (flashAddress >> 16);
    sqiCmdBuffer[2] = (uint8_t) (flashAddress >> 8);
    sqiCmdBuffer[3] = (uint8_t) (flashAddress);
    sqiCmdBuffer[4] = 0;                            /* dummy byte */
    sqiCmdBuffer[5] = 0;                            /* dummy byte */
    sqiCmdBuffer[6] = 0;                            /* dummy byte */

    _DRV_SQI_BufferThrSet(1, 4, 4);

    /* SQI Transfer Configuration */
    /* Setup control word to send NOP command */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,1,DRV_SQI_CS_1,DRV_SQI_LANE_QUAD,DRV_SQI_CMD_TRANSMIT,1);
    /* Setup control word to send FAST READ and address<15:0> */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,0,DRV_SQI_CS_1,DRV_SQI_LANE_QUAD,DRV_SQI_CMD_TRANSMIT,3);
    /* Setup control word to send address<23:16> and 3 dummy cycles */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,0,DRV_SQI_CS_1,DRV_SQI_LANE_QUAD,DRV_SQI_CMD_TRANSMIT,4);

    /* Write the command to the transfer buffer {WEN,NOP,NOP,NOP} */
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, sqiCmdBuffer[2] << 24 | sqiCmdBuffer[1] << 16 | (sqiCmdBuffer[0] << 8) | FLASH_NOP);

    /* Write address and dummy bytes {DUMMY, ADDRESS[3:0]} */
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (0x000000 << 8) | sqiCmdBuffer[3]);

    /* Setup control word to read 256 bytes */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0,1,SQI_CS_1,DRV_SQI_LANE_QUAD,DRV_SQI_CMD_RECEIVE,FLASH_PAGE_SIZE);

    /* Setup receive buffer threshold */
    _DRV_SQI_BufferThrSet(0, 0, 24);

    for (readLoop=0; readLoop < 8; readLoop++)
    {
        while ((PLIB_SQI_RxBufferThresholdGet(DRV_SQI_ID_0)& 0xFF) != 24);
        for (bufLoop=0; bufLoop < 8; bufLoop++){
            *readBuffer++ = PLIB_SQI_ReceiveData(DRV_SQI_ID_0);
        }
    }
}

uint8_t DRV_SQI_FlashIsBusy(void)
{
    uint8_t readStatus = 0;

    readStatus = DRV_SQI_FlashReadStatus();

    if ( (readStatus & FLASH_BUSY_MASK) | (readStatus & FLASH_BUSY_MASK_DUPLICATE) ) {
        return FLASH_BUSY;
    }

    return FLASH_READY;
}

uint8_t DRV_SQI_FlashReadStatus(void)
{
    /* Configure SQI in PIO mode */
    PLIB_SQI_TransferModeSet(DRV_SQI_ID_0, DRV_SQI_XFER_MODE_PIO);

    /* Setup CONTROL, TX and RX buffer thresholds */
	_DRV_SQI_BufferThrSet(1, 4, 4);

	/* Enable SQIRHR interrupt signal*/
	PLIB_SQI_InterruptSignalEnable(DRV_SQI_ID_0, DRV_SQI_RXTHR);

    // Configure to send the RDSR command */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 0, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* RDSR */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 0, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_TRANSMIT, 1);     /* NOP */
    PLIB_SQI_ControlWordSet(DRV_SQI_ID_0, 1, DRV_SQI_CS_1, DRV_SQI_LANE_QUAD, DRV_SQI_CMD_RECEIVE, 4);      /* Status Register Value */

    /* Transmit RDSR */
    PLIB_SQI_TransmitData(DRV_SQI_ID_0, (FLASH_NOP << 24) | (FLASH_RDSR << 16) | (FLASH_NOP << 8) | FLASH_NOP);

    /* Wait until transmission finished */
    while (PLIB_SQI_InterruptFlagGet(DRV_SQI_ID_0, DRV_SQI_RXTHR) == false);
    sqiReadWord = PLIB_SQI_ReceiveData(DRV_SQI_ID_0);

    memcpy(&sqiTempRead[0], &sqiReadWord, 4);

    PLIB_SQI_InterruptSignalDisable(DRV_SQI_ID_0, DRV_SQI_RXTHR);

    return (sqiTempRead[3] | sqiTempRead[2] | sqiTempRead[1] | sqiTempRead[0]);
}
