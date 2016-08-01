/*****************************************************************************
 * Microchip Graphics Library Demo Application
 * This program shows how to use the Graphics Objects Layer.
 *****************************************************************************
 * File Name:       main_screen.c
 * Dependencies:    See Includes Section
 * Processor:       PIC24, PIC32
 * Compiler:       	MPLAB C30 V3.00, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Inc.
 *
 *
 * Copyright � 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/

/*****************************************************************************
 * SECTION: Includes
 *****************************************************************************/

#include "app.h"
#include "driver/pmp/drv_pmp.h"
#include "gfx_screens.h"
#include "gfx_strings.h"
#include "gol_ids.h"
//#include "src/gfx_primitive_local.h"
//#include "src/gfx_local.h"

/*****************************************************************************
 * SECTION: Defines
 *****************************************************************************/
#define ALPHA_BLEND_DELAY_MS    (1)
/*****************************************************************************
 * SECTION: Variables
 *****************************************************************************/
static uint8_t alphaBlendPercentage = 0;
/*****************************************************************************
 * void DisplayAlphaBlendScreen(void)
 *****************************************************************************/
void CreateAlphaBlendScreen(void) {

    static uint8_t currentPage;
    static uint8_t timeThrough = 0;

    if(timeThrough == 0)
    {

    currentPage = GFX_PageGet(GFX_INDEX_0, ACTIVE_PAGE);

    GFX_AlphaParamsSet(GFX_INDEX_0, BACKGROUND_BUFFER,0,0,
                       BACKGROUND_BUFFER,0,0,
                       ALPHA_PAGE_BUFFER,0,0);

    while(GFX_CopyPageWindow(GFX_INDEX_0,
                        GFX_MaxXGet(GFX_INDEX_0), GFX_MaxYGet(GFX_INDEX_0)) == GFX_STATUS_FAILURE);

    while (GFX_PageSet(GFX_INDEX_0, ACTIVE_PAGE, ALPHA_PAGE_BUFFER) == GFX_STATUS_FAILURE); //Draw Image to be shown fading in

    GFX_GradientColorSet(GFX_INDEX_0, BRIGHTBLUE,BRIGHTRED);
    GFX_FillStyleSet(GFX_INDEX_0, GFX_FILL_STYLE_GRADIENT_RIGHT);

    while (GFX_BevelGradientDraw(GFX_INDEX_0, (GFX_MaxXGet(GFX_INDEX_0) >> 2) + 20, 90, GFX_MaxXGet(GFX_INDEX_0) - 10,
            GFX_MaxYGet(GFX_INDEX_0) - 40, 5) == GFX_STATUS_FAILURE);

    GFX_ColorSet(GFX_INDEX_0, WHITE);

    GFX_FontSet(GFX_INDEX_0, (void *) &Gentium_16);

    while (GFX_TextStringDraw(GFX_INDEX_0, (GFX_MaxXGet(GFX_INDEX_0) >> 2) + 60, 100, (GFX_XCHAR *) FadingStr, 0) == GFX_STATUS_FAILURE);

    while (GFX_PageSet(GFX_INDEX_0, ACTIVE_PAGE, currentPage) == GFX_STATUS_FAILURE);

    timeThrough = 1;

    }
}

bool DisplayAlphaBlendScreen(void)
{
	
	GFX_AlphaParamsSet(GFX_INDEX_0, BACKGROUND_BUFFER, (GFX_MaxXGet(GFX_INDEX_0) >> 2) + 15, 85,
                            ALPHA_PAGE_BUFFER, (GFX_MaxXGet(GFX_INDEX_0) >> 2) + 15, 85,
                            GFX_PageGet(GFX_INDEX_0, VISUAL_PAGE), (GFX_MaxXGet(GFX_INDEX_0) >> 2) + 15, 85);

	while(GFX_AlphaBlendWindow(GFX_INDEX_0,
				     (GFX_MaxXGet(GFX_INDEX_0))-((GFX_MaxXGet(GFX_INDEX_0) >> 2) + 20),
				     GFX_MaxYGet(GFX_INDEX_0) - 90,
				     alphaBlendPercentage) == GFX_STATUS_FAILURE);

	if(++alphaBlendPercentage > 99)
        {
 		alphaBlendPercentage = 0;
                return(true);
        }

        return(false);
	     				
}
