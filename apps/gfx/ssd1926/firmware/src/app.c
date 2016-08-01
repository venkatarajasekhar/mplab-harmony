/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "driver/gfx/controller/ssd1926/drv_gfx_ssd1926.h"

/************************************************************
 * Defines
 ************************************************************/
#define START_ADD   0ul
#define FRAME_SIZE (320ul * 240ul * 2ul)
/************************************************************
 * Enumeration Structure
 ************************************************************/
typedef enum
{
    DEMO_FILE_TYPE_JPEG,
    DEMO_FILE_TYPE_RGB,
    DEMO_FILE_TYPE_OTHER
}DEMO_FILE_TYPE;

/************************************************************
 * Externs: Function Prototypes
 ************************************************************/
extern uint8_t FILEget_next_cluster(FSFILE *fo, uint32_t n);
extern uint32_t Cluster2Sector(DISK * disk, uint32_t cluster);
extern uint8_t SDSectorDMARead(uint32_t sector_addr, uint32_t dma_addr, uint16_t num_blk);

/************************************************************
 * Function Prototypes
 ************************************************************/
DEMO_FILE_TYPE GetFileType(char *fileName);
bool PlayRGB(const char * fileName);
void GFX_TMR_DelayMS ( unsigned int delayMs );

/************************************************************
 * Variables
 ************************************************************/
DEMO_FILE_TYPE currentFileType = DEMO_FILE_TYPE_RGB;

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    static SearchRec nextFile;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
//            if ( DRV_GFX_SSD1926_Status ( sysObj.drvSSD1926 ) != SYS_STATUS_READY )
//                return;
            
            if ( GFX_Status (sysObj.gfxObject0) == SYS_STATUS_READY )
                appData.state = APP_STATE_GFX_SETUP;
            
            FSInit();                   // File system

            break;

        case APP_STATE_GFX_SETUP:

            /* set drawing state */
            appData.state = APP_STATE_GFX_RUN;

            break;

        case APP_STATE_GFX_RUN:

           if(GetFileType(nextFile.filename) == DEMO_FILE_TYPE_JPEG)
                {
                    if(currentFileType != DEMO_FILE_TYPE_JPEG)
                    {
                        // Set YUV mode to display JPEG
                        GFX_ColorSet(GFX_INDEX_0, BLACK);
                        GFX_ScreenClear(GFX_INDEX_0);
                        currentFileType = DEMO_FILE_TYPE_JPEG;
                        return;
                    }

                    if(JPEGPutImage(nextFile.filename) == false)
                        return;
                    GFX_TMR_DelayMS(500);
                }
                else if(GetFileType(nextFile.filename) == DEMO_FILE_TYPE_RGB)
                {
                    if(currentFileType != DEMO_FILE_TYPE_RGB)
                    {
                        // Set YUV mode to display JPEG
                        GFX_ColorSet(GFX_INDEX_0, BLACK);
                        GFX_ScreenClear(GFX_INDEX_0);
                        currentFileType = DEMO_FILE_TYPE_RGB;
                        return;
                    }

                    if(PlayRGB(nextFile.filename) == false)
                        return;
                }

           if(-1 == FindNext(&nextFile))
           {
                nextFile.initialized = FALSE;
           }
           break;
    }
    }
}
/************************************************************
 * DEMO_FILE_TYPE GetFileType(char *fileName)
 ************************************************************/
DEMO_FILE_TYPE GetFileType(char *fileName)
{

    while(*fileName != '.')
        fileName++;

    fileName++;

    // check to see if it is a jpeg
    if((fileName[0] == 'J') && (fileName[1] == 'P') && (fileName[2] == 'G'))
        return DEMO_FILE_TYPE_JPEG;

    if((fileName[0] == 'j') && (fileName[1] == 'p') && (fileName[2] == 'g'))
        return DEMO_FILE_TYPE_JPEG;

    // check to see if it is a rgb movie
    if((fileName[0] == 'R') && (fileName[1] == 'G') && (fileName[2] == 'B'))
        return DEMO_FILE_TYPE_RGB;

    if((fileName[0] == 'r') && (fileName[1] == 'g') && (fileName[2] == 'b'))
        return DEMO_FILE_TYPE_RGB;

    return DEMO_FILE_TYPE_OTHER;
}


/************************************************************
 * WORD StreamRGBFrame(FSFILE *fileStream, WORD numSectors)
 * This is a hack of the MDD file system to be able to use
 * the SSD1926 SD Card DMA feature.
 ************************************************************/
uint16_t StreamRGBFrame(FSFILE *fileStream, uint16_t numSectors)
{
    static DISK           *dsk;
    static uint32_t       sec_sel;
    static uint16_t       sectorsToRead;
    static uint32_t       currentCluster;
    static uint32_t       prevousCluster;
    static uint32_t       add = START_ADD;
    static uint8_t        state = 0;
    static uint8_t        result;

    switch(state)
    {
        case 0:
        dsk    = (DISK *)fileStream->dsk;

        sec_sel = Cluster2Sector(dsk, fileStream->ccls);
        sec_sel += (uint16_t)fileStream->sec;      // add the sector number to it

        currentCluster = fileStream->ccls;
        prevousCluster = currentCluster;

        // This will be the minimum sectors that are available by the card to be read
        sectorsToRead = (uint16_t)dsk->SecPerClus - (uint16_t)fileStream->sec;

        // get as many sectors from clusters that are contiguous
        while(sectorsToRead < numSectors)
        {
            if( FILEget_next_cluster( fileStream, 1) != CE_GOOD )
                return 0xFFFF;

            if((prevousCluster + 1) != fileStream->ccls)
            {
                fileStream->ccls = prevousCluster;
                break;
            }

            prevousCluster++;
            sectorsToRead += dsk->SecPerClus;
        }

    // make sure that we are not over the bounds
    if(sectorsToRead > numSectors)
        sectorsToRead = numSectors;

    state = 1;
    // do a DMA write of the information from the SD card to the display buffer
    case 1:
        result = SDSectorDMARead(sec_sel,  add, sectorsToRead);
        if(result == 0xff)
            break;
        if(result == 0)
        {
            fileStream->ccls = currentCluster;
            state = 0;
            break;
        }
        else
        {
        // update the address
        add += (dsk->sectorSize * (uint32_t)sectorsToRead);

        if (add >= (FRAME_SIZE + START_ADD))
        {
            add = START_ADD;
        }

        // update the pointers
        fileStream->seek += (dsk->sectorSize * sectorsToRead);

        if (fileStream->seek > fileStream->size)
        {
            fileStream->seek = fileStream->size;
            return 0xFFFF;
        }
        }

        // get the current sector within the current cluster
        currentCluster = fileStream->sec + sectorsToRead;
        while(currentCluster > dsk->SecPerClus)
        currentCluster -= dsk->SecPerClus;

        fileStream->sec = currentCluster;

        // get a new cluster if necessary
        if( fileStream->sec == dsk->SecPerClus )
        {
            fileStream->sec = 0;
            if( FILEget_next_cluster( fileStream, 1) != CE_GOOD )
                return 0xFFFF;
        }

        state = 0;
        return sectorsToRead;
    }
    return( 0 );
}
/************************************************************
 * void PlayRGB(const char * fileName)
 ************************************************************/
uint8_t DRV_GFX_SSD1926_SetRGB(void);

bool PlayRGB(const char * fileName)
{
    static uint32_t total_frames;
    static uint16_t sectorsToWrite;
    static FSFILE *pFile = NULL;
    static int i;
    static uint8_t reg;
    static uint8_t state = 0;
    static uint16_t result;

    switch(state)
    {
        case 0:
        if(DRV_GFX_SSD1926_SetRGB())    // Switching shows a little green flicker
            break;
        state = 1;
        case 1:
        if(DRV_GFX_SSD1926_GetReg(SSD1926_REG_SPECIAL_EFFECTS, &reg) == 1)
            break;
        state = 2;
        case 2:
        if(DRV_GFX_SSD1926_SetReg(SSD1926_REG_SPECIAL_EFFECTS, reg & 0xBF) == 1)
            break;
        state = 3;
        pFile = FSfopen(fileName, "rb");
        total_frames = (pFile->size / FRAME_SIZE);

        for (i = 0; i < total_frames; i++)
        {
            sectorsToWrite = FRAME_SIZE / pFile->dsk->sectorSize;

            while(sectorsToWrite)
            {
        case 3:
                result = StreamRGBFrame(pFile, sectorsToWrite);

                if(result == 0)
                    return( false );

                if(result == 0xFFFF)
                    break;

                sectorsToWrite -= result;
            }
        }
        state = 4;
        case 4:
        // Clear screen back to black before changing the hardware SFR byte swap back
        if(DRV_GFX_SSD1926_SetReg(SSD1926_REG_SPECIAL_EFFECTS, reg) == 1)
            break;

        FSfclose(pFile);
        state = 0;
        return( true );
    }
      return( false );
}

//void GFX_TMR_DelayMS ( unsigned int delayMs )
//{
//    if(delayMs)
//    {
//        uint32_t sysClk = SYS_CLK_FREQ;
//        uint32_t t0;
//        t0 = _CP0_GET_COUNT();
//        while (_CP0_GET_COUNT() - t0 < (sysClk/2000)*delayMs);
//    }
//}

/*******************************************************************************
 End of File
 */

