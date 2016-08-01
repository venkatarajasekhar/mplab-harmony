/*******************************************************************************
  Graphics LCC Demo Application AlphaBlend Screen

  File Name:
    AlphaBlendScreen.c

  Summary:
    LCC Demo application

  Description:
    This file contains the LCC application logic.
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
#include "app.h"
#include "gfx/gfx.h"
#include "alpha_blend_screen.h"
#include "gfx/jpeg_image.h"
//#include "internal_resource.h"


#include "gfx/gfx_gol_button.h"

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT'S IDs
/////////////////////////////////////////////////////////////////////////////
#define BUTTON1_ID  1111                // button unique ID
#define BUTTON2_ID  2222                // button unique ID
#define BUTTON3_ID  3333                // button unique ID
    
#define BUTTON_WIDTH        (150)
#define BTN_X_START         ((GFX_MaxXGet(GFX_INDEX_0) - BUTTON_WIDTH) >> 1)
#define BTN_X_END           (BTN_X_START + BUTTON_WIDTH)
    
const GFX_XCHAR  Button1Str[] = {'B','u','t','t','o','n',' ','1',0};
const GFX_XCHAR  Button2Str[] = {'B','u','t','t','o','n',' ','2',0};
const GFX_XCHAR  Button3Str[] = {'B','u','t','t','o','n',' ','3',0};

extern GFX_GOL_OBJ_SCHEME      *AlphaScheme;                // alternative style scheme

    // filled by the keyboard driver and
    // passed to the message manager
    GFX_GOL_OBJ_HEADER * pFocusedObj;           // temporary variable for the widget

    // receiving the keyboard focus
    uint8_t previousKey1State;             // previous state of the button 1
    uint8_t previousKey2State;             // previous state of the button 2
   
/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t CreateAlphaBlendScreen(void)
// Input: None
// Output: Returns non-zero if the objects are created 
//         returns 0 when one of the objects was not created.
// Overview: Creates the AlphaBlend Demo screen.
/////////////////////////////////////////////////////////////////////////////
uint16_t CreateAlphaBlendScreen(void)
{

//    while(  ImageDecode
//           (
//            (void *)&Demo,
//            IMG_JPEG,
//            0,
//            0,
//            (GFX_MaxXGet(GFX_INDEX_0)),
//            (GFX_MaxYGet(GFX_INDEX_0)),
//            0,
//            &_jpegFileApi,
//            NULL
//            ) == 0xff);

    GFX_ImageDraw(GFX_INDEX_0, 0,0, (GFX_RESOURCE_HDR*)&harmony);

    GFX_GOL_ButtonCreate (
        GFX_INDEX_0,
        BUTTON2_ID,             // button unique ID
        BTN_X_START, 100,       // left, top corner coordinates
        BTN_X_END, 150,         // right, bottom corner
        0,                      // corner radius is zero, it�s a square button
        GFX_GOL_BUTTON_DRAW_STATE,               // will be dislayed after creation
        NULL,                   // no bitmap
        NULL,
        (GFX_XCHAR*)Button2Str,     // text
        GFX_ALIGN_HCENTER,
        AlphaScheme                     // default color scheme is used
               );

    GFX_GOL_ButtonCreate (
        GFX_INDEX_0,
        BUTTON3_ID,             // button unique ID
        BTN_X_START, 160,       // left, top corner coordinates
        BTN_X_END, 210,         // right, bottom corner
        0,                      // corner radius is zero, it�s a square button
        GFX_GOL_BUTTON_DRAW_STATE,    // will be dislayed and disabled after creation
        NULL,                   // no bitmap
        NULL,
        (GFX_XCHAR*)Button3Str,    // text
        GFX_ALIGN_HCENTER,
        AlphaScheme                     // default color scheme is used
              );

        // create button widgets
    GFX_GOL_ButtonCreate (
        GFX_INDEX_0,
        BUTTON1_ID,             // button unique ID
        BTN_X_START, 40,        // left, top corner coordinates
        BTN_X_END, 90,          // right, bottom corner
        0,                      // corner radius is zero, it�s a square button
        GFX_GOL_BUTTON_DRAW_STATE,               // will be dislayed after creation
        NULL,                   // no bitmap
        NULL,
        (GFX_XCHAR*)Button1Str,     // text for released state
        GFX_ALIGN_HCENTER,
        AlphaScheme                    // default color scheme is used
              );
  
    return (1);
}       

/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t MsgAlphaBlendScreenCallback(uint16_t objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns non-zero the message will be processed 
//         by default
// Overview: This is called by GOLMsgCallback() to determine if 
//           a valid message for objects in this demo needs to be processed.
/////////////////////////////////////////////////////////////////////////////
uint16_t MsgAlphaBlendScreenCallback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    return (1); // process the message by default
}               // end of GOLMessageCallback   
