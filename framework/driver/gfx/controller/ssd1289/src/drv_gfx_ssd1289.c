/*******************************************************************************
 Module for Microchip Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    drv_gfx_ssd1289.c

  Summary:
    This module initializes the SSD1289 Timing Controller (TCON) Module.
*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#include "../drv_gfx_ssd1289.h"

#if defined (GFX_USE_DISPLAY_CONTROLLER_SSD1926)
#include "driver/gfx/controller/ssd1926/drv_gfx_ssd1926.h"
#elif defined (GFX_USE_DISPLAY_CONTROLLER_S1D13517)
#include "driver/gfx/controller/s1d13517/drv_gfx_s1d13517.h"
#elif defined (GFX_USE_DISPLAY_CONTROLLER_LCC)
#include "driver/gfx/controller/lcc/drv_gfx_lcc.h"
#endif

void GFX_TCON_SSD1289Init(void);
void GFX_SSD_TMR_DelayMS ( unsigned int delayMs );

#if defined(USE_TCON_SSD1289)

/*
    This module can use SPI or bitbang the SPI transfer using
    the SSD1926 GPIO pins. 
    This assumes that the timing controller uses SPI to
    receive Timing Programming data.
    Select the usage using the hardware profile.
*/
    // BB means BitBang
    #define BB_CS                   0x01
    #define BB_SCL                  0x02
    #define BB_SDO                  0x04
    #define BB_DC                   0x08
    #define BB_BL                   0x10

#if defined (GFX_USE_DISPLAY_CONTROLLER_LCC)

    #define TCON_CSLow()            (BSP_TCON_CSOn())
    #define TCON_CSHigh()           (BSP_TCON_CSOff())
    #define TCON_CLKLow()           (BSP_TCON_SCLOn())
    #define TCON_CLKHigh()          (BSP_TCON_SCLOff())
    #define TCON_DataLow()          (BSP_TCON_SDOOn())
    #define TCON_DataHigh()         (BSP_TCON_SDOOff())

    #define TCON_SetCommand()       (BSP_TCON_DCOn())
    #define TCON_SetData()          (BSP_TCON_DCOff())

    // set the IOs used to outputs. and initialize them all to "1"
    // set up the TRIS first for outputs, then set the pins
    // to digital in case it is needed and initialize the signals
    // to all high.
    #define InitBitBangedIO()
    

#elif defined (GFX_USE_DISPLAY_CONTROLLER_MCHP_DA210) 

    #define TCON_CSLow()            (TCON_CS_LAT = 0)
    #define TCON_CSHigh()           (TCON_CS_LAT = 1)
    #define TCON_CLKLow()           (TCON_SCL_LAT = 0)
    #define TCON_CLKHigh()          (TCON_SCL_LAT = 1)
    #define TCON_DataLow()          (TCON_SDO_LAT = 0)
    #define TCON_DataHigh()         (TCON_SDO_LAT = 1)

    #define TCON_SetCommand()       (TCON_DC_LAT = 0)
    #define TCON_SetData()          (TCON_DC_LAT = 1)

    // set the IOs used to outputs. and initialize them all to "1"
    // set up the TRIS first for outputs, then set the pins
    // to digital in case it is needed and initialize the signals
    // to all high.
    #define InitBitBangedIO() {                     \
                                TCON_CS_TRIS = 0;   \
                                TCON_SCL_TRIS = 0;  \
                                TCON_SDO_TRIS = 0;  \
                                TCON_DC_TRIS = 0;   \
                        	  TCON_CS_DIG();      \
                                TCON_SCL_DIG();     \
                        	  TCON_SDO_DIG();     \
                                TCON_DC_DIG();      \
                                TCON_CSHigh();      \
                                TCON_CLKHigh();     \
                                TCON_DataHigh();    \
                                TCON_SetData();     \
                              }                                

// end of #if defined (USE_DISPLAY_CONTROLLER_MCHP_DA210) 
                                   

#elif defined (GFX_USE_DISPLAY_CONTROLLER_SSD1926)    
    
    // use the bitbang version using SSD1926 GPIO pins
    
    #define TCON_CSLow()            (GfxTconSetIO(BB_CS, 0))
    #define TCON_CSHigh()           (GfxTconSetIO(BB_CS, 1))
    #define TCON_CLKLow()           (GfxTconSetIO(BB_SCL, 0))
    #define TCON_CLKHigh()          (GfxTconSetIO(BB_SCL, 1))
    #define TCON_DataLow()          (GfxTconSetIO(BB_SDO, 0))
    #define TCON_DataHigh()         (GfxTconSetIO(BB_SDO, 1))

    #define TCON_SetCommand()       (GfxTconSetIO(BB_DC, 0))
    #define TCON_SetData()          (GfxTconSetIO(BB_DC, 1))

    // this is only needed here since the controller IO's are used
    // instead of the IO's from the PIC device.
    #define SetCtrlBitBangedIO(addr, data)    while(DRV_GFX_SSD1926_SetReg(addr, data)==1)

    // set the GPIO of SSD1926 to as outputs. (used for SSD1289 TCON signals)
    // and initialize them all to "1"
    #define InitBitBangedIO() {                                     \
                                SetCtrlBitBangedIO(0xA8, 0x1F);     \
                                SetCtrlBitBangedIO(0xAC, 0x1F);     \
                              }                                
// end of #elif defined (USE_TCON_SSD1289) 

#elif defined (GFX_USE_DISPLAY_CONTROLLER_S1D13517)

     // use the bitbang version using S1D13517 GPIO pins
    
    #define TCON_CSLow()            (GfxTconSetIO(BB_CS, 0))
    #define TCON_CSHigh()           (GfxTconSetIO(BB_CS, 1))
    #define TCON_CLKLow()           (GfxTconSetIO(BB_SCL, 0))
    #define TCON_CLKHigh()          (GfxTconSetIO(BB_SCL, 1))
    #define TCON_DataLow()          (GfxTconSetIO(BB_SDO, 0))
    #define TCON_DataHigh()         (GfxTconSetIO(BB_SDO, 1))

    #define TCON_SetCommand()       (GfxTconSetIO(BB_DC, 0))
    #define TCON_SetData()          (GfxTconSetIO(BB_DC, 1))

    // this is only needed here since the controller IO's are used
    // instead of the IO's from the PIC device.
    #define SetCtrlBitBangedIO(addr, data)    (SetReg(addr, data))

    #define InitBitBangedIO()                                      Nop()


// end of #elif defined (USE_DISPLAY_CONTROLLER_S1D13517)

#endif 

/************************************************************************
* Function: void GfxTconSetIO(BYTE mask, BYTE level)                                           
*                                                                       
* Overview: This sets the IO specified by mask to the value set by 
*           level.
*                                                                       
* Input: mask - specifies the IO to be toggles.
*		 level - specifies the logic where the IO will be set.
*                                                                       
* Output: none                                 
*                                                                       
************************************************************************/
void GfxTconSetIO(uint8_t mask, uint8_t level)
{
  #if defined (GFX_USE_DISPLAY_CONTROLLER_MCHP_DA210) || defined (GFX_USE_DISPLAY_CONTROLLER_LCC)

    switch(mask)
    {
        case BB_CS:    (level == 1 ? BSP_TCON_CSOn() : BSP_TCON_CSOff());
                    break;

        case BB_SCL:   (level == 1 ? BSP_TCON_SCLOn() : BSP_TCON_SCLOff());
                    break;

        case BB_SDO:   (level == 1 ? BSP_TCON_SDOOn() : BSP_TCON_SDOOff());
                    break;

        case BB_DC:    (level == 1 ? BSP_TCON_DCOn() : BSP_TCON_DCOff());
                    break;
        default:
                    break;            
    }
    
    Nop();
    
  #elif defined (GFX_USE_DISPLAY_CONTROLLER_SSD1926)

    static uint8_t value = 0xFF;

    if(level == 0)
    {
        value &= ~mask;
    }
    else
    {
        value |= mask;
    }

    SetCtrlBitBangedIO(0xAC, value);

#elif defined (GFX_USE_DISPLAY_CONTROLLER_S1D13517)  

    static uint8_t temp = 0;

    switch(mask)
    {
        case BB_CS:      
                    while(temp = DRV_GFX_S1D13517_GetReg(S1D13517_REG6E_GPO_1) == 0);
                    if(level == 1)  temp  |= 0x02;
                    else            temp  &= 0xFD;       
                    while(DRV_GFX_S1D13517_SetReg(S1D13517_REG6E_GPO_1,temp));
                    break;

        case BB_SCL:   
                    (level == 1 ? TCON_CLKHigh() : TCON_CLKLow());
                    break;

        case BB_SDO:   
                    (level == 1 ? TCON_DataHigh() : TCON_DataLow());
                    break;

        case BB_DC:    
                    while(temp = DRV_GFX_S1D13517_GetReg(S1D13517_REG6E_GPO_1) == 0);
                    if(level == 1)  temp  |= 0x04;
                    else            temp  &= 0xFB;       
                    while(DRV_GFX_S1D13517_SetReg(S1D13517_REG6E_GPO_1,temp));
                    break;
    }
    
    Nop();

#else

    #warning "This TCON_SSD1289 is written for SSD1926, S1D13517 and Microchip Graphics Module driver. If you are not using those drivers you may need to re-write this driver and remove this error message."

#endif    

}

/************************************************************************
* Function: void GfxTconWriteByte(BYTE value)                                           
*                                                                       
* Overview: This writes a bytes to SPI.
*                                                                       
* Input: value - the byte data to be written.
*                                                                       
* Output: none                                 
*                                                                       
************************************************************************/
void GfxTconWriteByte(uint8_t value)
{
    uint8_t    mask;

    mask = 0x80;
    while(mask)
    {
        GfxTconSetIO(BB_SCL, 0);
        GFX_SSD_TMR_DelayMS(1);
        if(mask & value)
        {
            GfxTconSetIO(BB_SDO, 1);
        }
        else
        {
            GfxTconSetIO(BB_SDO, 0);
        }

        GfxTconSetIO(BB_SCL, 1);
        mask >>= 1;
    }
}

/************************************************************************
* Function: void GfxTconWriteCommand(BYTE index, uint16_t value)                                           
*                                                                       
* Overview: This writes a word to SPI by calling the write byte 
*           routine.
*                                                                       
* Input: index - The index (or address) of the register to be written.
*        value - The value that will be written to the register.
*                                                                       
* Output: none                                 
*                                                                       
************************************************************************/
void GfxTconWriteCommand(uint16_t index, uint16_t value)
{
    GfxTconSetIO(BB_CS, 0);

    // Index
    GfxTconSetIO(BB_DC, 0);
    GfxTconWriteByte(index>>8);
    GfxTconWriteByte(index);

    GfxTconSetIO(BB_CS, 1);
    GFX_SSD_TMR_DelayMS(1);
    GfxTconSetIO(BB_CS, 0);

    // Data
    GfxTconSetIO(BB_DC, 1);
    GfxTconWriteByte(value>>8);
    GfxTconWriteByte(value);
    GfxTconSetIO(BB_CS, 1);
    GFX_SSD_TMR_DelayMS(1);
}

// *****************************************************************************
/*
  Function:
     void GfxTconInit(void)

  Summary:
     Initialize Solomon Systech ssd1289 Timing Controller

  Description:
     Initialize the IOs to implement Bitbanged SPI interface
     to connect to the Timing Controller through SPI.

  Returns:
     none

*/
void GFX_TCON_SSD1289Init(void)
{
        InitBitBangedIO();
  
 	GfxTconWriteCommand(0x0028, 0x0006);
	GfxTconWriteCommand(0x0000, 0x0001);

        GFX_SSD_TMR_DelayMS(15);

	GfxTconWriteCommand(0x002B, 0x9532);
	GfxTconWriteCommand(0x0003, 0xAAAC);
	GfxTconWriteCommand(0x000C, 0x0002);
	GfxTconWriteCommand(0x000D, 0x000A);
	GfxTconWriteCommand(0x000E, 0x2C00);
	GfxTconWriteCommand(0x001E, 0x00AA);
	GfxTconWriteCommand(0x0025, 0x8000);

        GFX_SSD_TMR_DelayMS(15);

	GfxTconWriteCommand(0x0001, 0x2B3F);
	GfxTconWriteCommand(0x0002, 0x0600);
	GfxTconWriteCommand(0x0010, 0x0000);
	GFX_SSD_TMR_DelayMS(20);

	GfxTconWriteCommand(0x0005, 0x0000);
	GfxTconWriteCommand(0x0006, 0x0000);

	GfxTconWriteCommand(0x0016, 0xEF1C);
	GfxTconWriteCommand(0x0017, 0x0003);
	GfxTconWriteCommand(0x0007, 0x0233);
	GfxTconWriteCommand(0x000B, 0x5312);
	GfxTconWriteCommand(0x000F, 0x0000);
	GFX_SSD_TMR_DelayMS(20);

	GfxTconWriteCommand(0x0041, 0x0000);
	GfxTconWriteCommand(0x0042, 0x0000);
	GfxTconWriteCommand(0x0048, 0x0000);
	GfxTconWriteCommand(0x0049, 0x013F);
	GfxTconWriteCommand(0x0044, 0xEF00);
	GfxTconWriteCommand(0x0045, 0x0000);
	GfxTconWriteCommand(0x0046, 0x013F);
	GfxTconWriteCommand(0x004A, 0x0000);
	GfxTconWriteCommand(0x004B, 0x0000);
	GFX_SSD_TMR_DelayMS(20);

	GfxTconWriteCommand(0x0030, 0x0707);
	GfxTconWriteCommand(0x0031, 0x0704);
	GfxTconWriteCommand(0x0032, 0x0204);
	GfxTconWriteCommand(0x0033, 0x0201);
	GfxTconWriteCommand(0x0034, 0x0203);
	GfxTconWriteCommand(0x0035, 0x0204);
	GfxTconWriteCommand(0x0036, 0x0204);
	GfxTconWriteCommand(0x0037, 0x0502);
	GfxTconWriteCommand(0x003A, 0x0302);
	GfxTconWriteCommand(0x003B, 0x0500);
	GFX_SSD_TMR_DelayMS(20);

    TCON_CLKLow();        
}

void GFX_SSD_TMR_DelayMS ( unsigned int delayMs )
{
#if (true == SYS_TMR_INTERRUPT_MODE)

#else      //Primitive Blocking Mode
    if(delayMs)
    {
        uint32_t sysClk = SYS_CLK_FREQ;
        uint32_t t0;
        #if   defined (__C32__)
        t0 = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() - t0 < (sysClk/2000)*delayMs);
        #elif defined (__C30__)
        t0 = ReadTimer23();
        while (ReadTimer23() -  t0 < (sysClk/2000)*mSec);
        #else
        #error "Neither __C32__ nor __C30__ is defined!"
        #endif
    }
#endif
}

#endif // #if defined (USE_TCON_SSD1289)


