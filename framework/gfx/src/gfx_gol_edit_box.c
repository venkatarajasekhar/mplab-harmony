/*******************************************************************************
 Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol_edit_box.c

  Summary:
    This implements the edit box object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    EditBox Object.
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

#include <stdlib.h>
#include <stdint.h>
#include "system_config.h"
#include "system_definitions.h"

// *****************************************************************************
/*  Function:
    GFX_GOL_EDITBOX  *GFX_GOL_EditBoxCreate(
                                SYS_MODULE_INDEX    gfxIndex,
                                uint16_t            ID,
                                uint16_t            left,
                                uint16_t            top,
                                uint16_t            right,
                                uint16_t            bottom,
                                uint16_t            state,
                                GFX_XCHAR           *pText,
                                uint16_t            charMax,
                                GFX_ALIGNMENT       alignment,
                                GFX_GOL_OBJ_SCHEME  *pScheme)
    Summary:
        This function creates a GFX_GOL_EDITBOX object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.

    Description:
        This function creates a GFX_GOL_EDITBOX object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.

        This function returns the pointer to the newly created object.
        If the object is not successfully created, it returns NULL.

        The behavior of GFX_GOL_ListBoxCreate() will be undefined if one
        of the following is true:
        - left >= right
        - top >= bottom
        - pScheme is not pointing to a GFX_GOL_OBJ_SCHEME
        - pText is an unterminated string

*/
// *****************************************************************************
GFX_GOL_EDITBOX  *GFX_GOL_EditBoxCreate(
                                SYS_MODULE_INDEX    gfxIndex,
                                uint16_t            ID,
                                uint16_t            left,
                                uint16_t            top,
                                uint16_t            right,
                                uint16_t            bottom,
                                uint16_t            state,
                                GFX_XCHAR           *pText,
                                uint16_t            charMax,
                                GFX_ALIGNMENT       alignment,
                                GFX_GOL_OBJ_SCHEME  *pScheme)
{
    GFX_GOL_EDITBOX *pEb = NULL;
    
    // ending zero is not included into charMax
    pEb = (GFX_GOL_EDITBOX*) GFX_malloc( sizeof(GFX_GOL_EDITBOX) +
                                        (charMax + 1)*sizeof(GFX_XCHAR));

    if (pEb == NULL)
        return pEb;

    // allocate space for the text buffer
    pEb->pText    = (GFX_XCHAR*)((uint8_t*)pEb + sizeof(GFX_GOL_EDITBOX));
    // initialize to contain nothing
    *pEb->pText             = 0;
    pEb->length             = 0;
    pEb->charMax            = charMax;

    pEb->hdr.gfxIndex       = gfxIndex;
    pEb->hdr.ID      	    = ID;
    pEb->hdr.pNxtObj 	    = NULL;
    pEb->hdr.type    	    = GFX_GOL_EDITBOX_TYPE;
    pEb->hdr.left    	    = left;
    pEb->hdr.top     	    = top;
    pEb->hdr.right   	    = right;
    pEb->hdr.bottom  	    = bottom;
    pEb->hdr.state   	    = state;

    // draw function
    pEb->hdr.DrawObj        = GFX_GOL_EditBoxDraw;

    // free function
    pEb->hdr.FreeObj        = NULL;

    // action get function
    pEb->hdr.actionGet      = GFX_GOL_EditBoxActionGet;

    // default action function
    pEb->hdr.actionSet      = GFX_GOL_EditBoxActionSet; 

    // copy the text to the buffer
    if(pText != NULL)
    {
        GFX_GOL_EditBoxTextSet(pEb, pText);
        pEb->cursorPosition = pEb->length;
    }
    else
    {
        pEb->cursorPosition = 0;
    }

    // set the alignment
    GFX_GOL_EditBoxTextAlignmentSet(pEb, alignment);

    // Set the style scheme to be used
    pEb->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *)pScheme;

    pEb->textHeight = GFX_TextStringHeightGet(pEb->hdr.pGolScheme->pFont);

    GFX_GOL_ObjectAdd(pEb->hdr.gfxIndex, (GFX_GOL_OBJ_HEADER *)pEb);

    return pEb;
}

// *****************************************************************************
/*  Function:
    GFX_XCHAR *GFX_GOL_EditBoxTextSet(
                                GFX_GOL_EDITBOX *pObject,
                                GFX_XCHAR *pText)

    Summary:
        This function sets the text in the object.

    Description:
        This function sets the text in the object. This function
        copies the text located in the address pointed to by pText
        to the object text buffer.

        The string length must be less than or equal to the maximum
        characters allowed in the object. The object will truncate
        the string once it reaches the maximum length.

*/
// *****************************************************************************
void GFX_GOL_EditBoxTextSet(GFX_GOL_EDITBOX *pObject, GFX_XCHAR* pText)
{
    uint16_t    ch;
    uint16_t    length;
    GFX_XCHAR*  pointerFrom;
    GFX_XCHAR*  pointerTo;

    // Copy and count length
    pointerFrom = pText;
    pointerTo   = pObject->pText;
    length      = 0;

    do{
        ch = *pointerFrom++;
        *pointerTo++ = ch;
        length++;
        if(length >= pObject->charMax){
            *pointerTo = 0;
            break;
        }
        if(ch == 0){
            break;
        }
    }while(ch);

    pObject->length = length-1;
    pObject->cursorPosition = length - 1;
}

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_EditBoxCharAdd(
                                GFX_GOL_EDITBOX *pObject,
                                GFX_XCHAR ch)

    Summary:
        This function adds a character at the end of the text used by
        the object. It also updates the cursor position.

    Description:
        This function adds a character at the end of the text used by
        the object. When the object contains the maximum number of
        characters any addition call to this function will
        not affect the text in the object. It also updates the cursor position.

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_EditBoxCharAdd(GFX_GOL_EDITBOX *pObject, GFX_XCHAR ch)
{
    uint32_t charCount;

    // check if max length has been reached
    if(pObject->length >= pObject->charMax)
        return (GFX_STATUS_FAILURE);

    if( pObject->cursorPosition == pObject->length )
    {
        // Add character
        pObject->pText[pObject->length] = ch;
    
        // terminate the string
        pObject->pText[pObject->length + 1] = 0;
        
    }
    else
    {
        for( charCount = pObject->length + 1; 
             charCount > pObject->cursorPosition; 
             charCount-- )
        {
            pObject->pText[charCount] = pObject->pText[charCount - 1];
        }
        
        pObject->pText[pObject->cursorPosition] = ch;
    }

    pObject->length++;
    pObject->cursorPosition ++;
    
    return (GFX_STATUS_SUCCESS);
}

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_EditBoxCharRemove(
                                GFX_GOL_EDITBOX *pObject)

    Summary:
        This function removes a character at the end of the text used by
        the object. It also updates cursor position.

    Description:
        This function removes a character at the end of the text used by
        the object. It also updates cursor position.

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_EditBoxCharRemove(
                                GFX_GOL_EDITBOX *pObject)
{
    uint32_t charCount;

    // check if empty
    if(pObject->length == 0 || pObject->cursorPosition == 0)
        return (GFX_STATUS_FAILURE);

    if( pObject->length == pObject->cursorPosition )
    {
        pObject->pText[pObject->length - 1] = 0;
    }
    else
    {
        for( charCount = pObject->cursorPosition;
             charCount <= pObject->length;
             charCount++ )
        {
            pObject->pText[charCount - 1] = pObject->pText[charCount];
        }
    }
    
    // Delete character
    pObject->length--;
    pObject->cursorPosition--;
    
    return (GFX_STATUS_SUCCESS);

}

// *****************************************************************************
/*  GFX GOL edit box cursor position increment.

    Function:
        GFX_STATUS GFX_GOL_EditBoxCursorPostionIncrement(
                                GFX_GOL_EDITBOX *pObject)

    Summary:
        Increment cursor position.

    Description:
        This function increments cursor position.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - Pointer to the object.

    Returns:
        The status of the addition.
        - GFX_STATUS_SUCCESS - Cursor position increment successful.
        - GFX_STATUS_FAILURE - Cursor position increment failed.

    Example:
        None.

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_EditBoxCursorPositionIncrement( GFX_GOL_EDITBOX *pObject )
{
    // check if max length has been reached
    if( pObject->cursorPosition >= pObject->length )
        return (GFX_STATUS_FAILURE);

    pObject->cursorPosition ++;
    
    return (GFX_STATUS_SUCCESS);

}

// *****************************************************************************
/*  GFX GOL edit box cursor position decrement.

    Function:
        GFX_STATUS GFX_GOL_EditBoxCursorPositionDecrement(
                                GFX_GOL_EDITBOX *pObject)

    Summary:
        Decrement cursor position.

    Description:
        This function decrements cursor position.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - Pointer to the object.

    Returns:
        The status of the addition.
        - GFX_STATUS_SUCCESS - Cursor position decrement successful.
        - GFX_STATUS_FAILURE - Cursor position decrement failed.

    Example:
        None.

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_EditBoxCursorPositionDecrement( GFX_GOL_EDITBOX *pObject )
{

    // check if empty
    if(pObject->length == 0)
        return (GFX_STATUS_FAILURE);

    if(pObject->cursorPosition == 0)
        return (GFX_STATUS_FAILURE);
    
    pObject->cursorPosition --;
    
    return (GFX_STATUS_SUCCESS);

}

// *****************************************************************************
/*  Function:
    GFX_GOL_TRANSLATED_ACTION GFX_GOL_EditBoxActionGet(
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage);

    Summary:
        This function evaluates the message from a user if the
        message will affect the object or not.

    Description:
        This function evaluates the message from a user if the
        message will affect the object or not. 

*/
// *****************************************************************************
GFX_GOL_TRANSLATED_ACTION GFX_GOL_EditBoxActionGet(
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_EDITBOX *pEb;

    pEb = (GFX_GOL_EDITBOX *)pObject;

    // Evaluate if the message is for the edit box
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifndef  GFX_CONFIG_USE_TOUCHSCREEN_DISABLE
    if(pMessage->type == TYPE_TOUCHSCREEN)
    {
        // Check if it falls in edit box borders
        if( (pEb->hdr.left     < pMessage->param1) &&
            (pEb->hdr.right    > pMessage->param1) &&
            (pEb->hdr.top      < pMessage->param2) &&
            (pEb->hdr.bottom   > pMessage->param2))
        {
            return GFX_GOL_EDITBOX_ACTION_TOUCHSCREEN;
        }

        return GFX_GOL_OBJECT_ACTION_INVALID;
	}
#endif

#ifndef GFX_CONFIG_USE_KEYBOARD_DISABLE
    if(pMessage->type == TYPE_KEYBOARD) {

        if(pMessage->uiEvent == EVENT_CHARCODE)
            return GFX_GOL_EDITBOX_ACTION_ADD_CHAR;

        if(pMessage->uiEvent == EVENT_KEYSCAN)
            if(pMessage->param2 == SCAN_BS_PRESSED)
                return GFX_GOL_EDITBOX_ACTION_DEL_CHAR;

	    return GFX_GOL_OBJECT_ACTION_INVALID;
	}
#endif


	return GFX_GOL_OBJECT_ACTION_INVALID;
}

// *****************************************************************************
/*  Function:
    void GFX_GOL_EditBoxActionSet(
                                GFX_GOL_TRANSLATED_ACTION translatedMsg,
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage)

    Summary:
        This function performs the state change of the object based on the
        translated action.

    Description:
        This function performs the state change of the object based on the
        translated action. This change can be overridden by the application
        using the application defined GFX_GOL_MESSAGE_CALLBACK_FUNC.
        When the user message is determined to affect the object, application
        can perform the state change in the message callback function.

*/
// *****************************************************************************
void GFX_GOL_EditBoxActionSet(
                                GFX_GOL_TRANSLATED_ACTION translatedMsg,
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage)
{

    GFX_GOL_EDITBOX *pEb;

    pEb = (GFX_GOL_EDITBOX *)pObject;

#if defined(GFX_LIB_CFG_USE_FOCUS)
#ifndef  GFX_CONFIG_USE_TOUCHSCREEN_DISABLE
    if(pMessage->type == TYPE_TOUCHSCREEN)
    {
        if(!GFX_GOL_ObjectStateGet(pEb,GFX_GOL_EDITBOX_FOCUSED_STATE))
        {
            GFX_GOL_ObjectFocusSet( pEb->hdr.gfxIndex, (GFX_GOL_OBJ_HEADER *)pEb);
        }
    }
#endif
#endif

    switch(translatedMsg)
    {

        case GFX_GOL_EDITBOX_ACTION_ADD_CHAR:
            GFX_GOL_EditBoxCharAdd(pEb,(GFX_XCHAR)pMessage->param2);
            GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
            break;

        case GFX_GOL_EDITBOX_ACTION_DEL_CHAR:
            GFX_GOL_EditBoxCharRemove(pEb);
            GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
            break;

        default:
            // do nothing
            break;

    }
}


// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_EditBoxDraw(void *pObject)

    Summary:
        This function renders the object on the screen based on the
        current state of the object.

    Description:
        This function renders the object on the screen based on the
        current state of the object. Location of the object is
        determined by the left, top, right and bottom parameters.
        The colors used are dependent on the state of the object.
        The font used is determined by the style scheme set.

        When rendering objects of the same type, each object
        must be rendered completely before the rendering of the
        next object is started. This is to avoid incomplete
        object rendering.

        Normally, application will just call GFX_GOL_ObjectListDraw()
        to allow the Graphics Library to manage all object rendering.
        See GFX_GOL_ObjectListDraw() for more information on object rendering.

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_EditBoxDraw(void *pObject)
{
    typedef enum
    {
        DRAW_EDITBOX_START, 
        DRAW_EDITBOX_PANEL, 
        DRAW_EDITBOX_PREPARE_TEXT, 
        DRAW_EDITBOX_TEXT, 
        DRAW_EDITBOX_CARET, 
    } DRAW_EDITBOX_STATES;

    static DRAW_EDITBOX_STATES  state = DRAW_EDITBOX_START;
    static GFX_COLOR            tempColor;
    GFX_GOL_EDITBOX             *pEb = (GFX_GOL_EDITBOX *)pObject;
    GFX_PREEMPTION_LEVEL        preemptionLevel =
                                GFX_GOL_PreemptionLevelGet(pEb->hdr.gfxIndex);
    uint16_t                    cursorX; 
    uint16_t                    cursorY; 
    uint16_t                    cursorWidth;

    while(1)
    {
        if (GFX_RenderStatusGet(pEb->hdr.gfxIndex) == GFX_STATUS_BUSY_BIT)
            return (GFX_STATUS_FAILURE);

        switch(state)
        {
    
            case DRAW_EDITBOX_START:
                
#ifdef GFX_LIB_CFG_USE_BISTABLE_DISPLAY_GOL_AUTO_REFRESH
                GFX_DRIVER_SetupDrawUpdate( pEb->hdr.left,
                                            pEb->hdr.top,
                                            pEb->hdr.right,
                                            pEb->hdr.bottom);
#endif
    
              	if(GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_HIDE_STATE))
                {

                    // Hide the object (remove from screen)
                    if (GFX_GOL_ObjectHideDraw(pEb->hdr.gfxIndex, &(pEb->hdr))
                            != GFX_STATUS_SUCCESS)
                        return (GFX_STATUS_FAILURE);

#ifdef GFX_LIB_CFG_USE_BISTABLE_DISPLAY_GOL_AUTO_REFRESH
                    GFX_DRIVER_CompleteDrawUpdate(  pEb->hdr.left,
                                                    pEb->hdr.top,
                                                    pEb->hdr.right,
                                                    pEb->hdr.bottom);
#endif
                    return (GFX_STATUS_SUCCESS);
                }
    
                if(GFX_GOL_ObjectStateGet(pEb,GFX_GOL_EDITBOX_DISABLED_STATE))
                {
                    tempColor = pEb->hdr.pGolScheme->ColorDisabled;
    	        }
                else
                {
                    tempColor = pEb->hdr.pGolScheme->Color0;
                }
    
                if(GFX_GOL_ObjectStateGet(pEb,GFX_GOL_EDITBOX_DRAW_STATE))
                {
                    // set up the background
                    GFX_GOL_PanelBackgroundSet(pEb->hdr.gfxIndex, &pEb->hdr);

                    // set panel parameters
                    GFX_GOL_PanelParameterSet
                    (   pEb->hdr.gfxIndex,
                        pEb->hdr.left,
                        pEb->hdr.top,
                        pEb->hdr.right,
                        pEb->hdr.bottom,
                        0,
                        tempColor,
                        pEb->hdr.pGolScheme->EmbossDkColor,
                        pEb->hdr.pGolScheme->EmbossLtColor,
                        NULL,
                        pEb->hdr.pGolScheme->fillStyle,
                        pEb->hdr.pGolScheme->EmbossSize
                    );
    
                    state = DRAW_EDITBOX_PANEL;
                    // no break here since it will always go
                    // to the DRAW_EDITBOX_PANEL state
                }
                else
                {
                    state = DRAW_EDITBOX_PREPARE_TEXT;
                    break;
                }

                if( GFX_PREEMPTION_LEVEL_2 == preemptionLevel )
                {
                    return GFX_STATUS_FAILURE;
                }
                
            case DRAW_EDITBOX_PANEL:

                if(GFX_GOL_PanelDraw(pEb->hdr.gfxIndex) != GFX_STATUS_SUCCESS)
		{
                    return (GFX_STATUS_FAILURE);
                }
                state = DRAW_EDITBOX_PREPARE_TEXT;
                // no break here since it will always go to
                // the DRAW_EDITBOX_PREPARE_TEXT state

                if( GFX_PREEMPTION_LEVEL_2 == preemptionLevel )
                {
                    return GFX_STATUS_FAILURE;
                }
                
            case DRAW_EDITBOX_PREPARE_TEXT:
    
    	        GFX_FontSet(pEb->hdr.gfxIndex, pEb->hdr.pGolScheme->pFont);
    
                if(GFX_GOL_ObjectStateGet(pEb,GFX_GOL_EDITBOX_DISABLED_STATE))
                {
                    GFX_ColorSet( pEb->hdr.gfxIndex,
                                  pEb->hdr.pGolScheme->TextColorDisabled);
                }
                else
                {
                    GFX_ColorSet( pEb->hdr.gfxIndex,
                                  pEb->hdr.pGolScheme->TextColor0);
                }
  
                state = DRAW_EDITBOX_TEXT;
    		    
    		// no break here since it will always go to
                // the DRAW_EDITBOX_TEXT state

                if( GFX_PREEMPTION_LEVEL_2 == preemptionLevel )
                {
                    return GFX_STATUS_FAILURE;
                }
                
            case DRAW_EDITBOX_TEXT:

                // render the text
                if (GFX_TextStringBoxDraw(pEb->hdr.gfxIndex,
                    pEb->hdr.left + pEb->hdr.pGolScheme->EmbossSize,
                    pEb->hdr.top  + pEb->hdr.pGolScheme->EmbossSize,
                    pEb->hdr.right - pEb->hdr.left -
                        (pEb->hdr.pGolScheme->EmbossSize << 1),
                    pEb->hdr.bottom - pEb->hdr.top -
                        (pEb->hdr.pGolScheme->EmbossSize << 1),
                    pEb->pText,
                    0,
                    pEb->alignment) != GFX_STATUS_SUCCESS)
                {
                  return (GFX_STATUS_FAILURE);
                };
       			
                // draw the caret if required
                if(!GFX_GOL_ObjectStateGet(
                        pEb,
                        GFX_GOL_EDITBOX_DISABLED_STATE))
                {
    	            if(    (GFX_GOL_ObjectStateGet(
                                pEb,
                                GFX_GOL_EDITBOX_FOCUSED_STATE) &&
                            GFX_GOL_ObjectStateGet(
                                pEb,
                                GFX_GOL_EDITBOX_DRAW_CARET_STATE)
                           ) ||
                           (GFX_GOL_ObjectStateGet(
                                pEb,
                                GFX_GOL_EDITBOX_ENABLE_CARET_STATE)
                            )
                      )
                    {
                        if( GFX_GOL_ObjectStateGet ( pEb, 
                                GFX_GOL_EDITBOX_ENABLE_BAR_CARET_STATE ) )
                        {
                            GFX_TextCursorTypeSet( pEb->hdr.gfxIndex,
                                               GFX_TEXT_CURSOR_TYPE_BAR );
                        }
                        else if( GFX_GOL_ObjectStateGet ( pEb, 
                                GFX_GOL_EDITBOX_ENABLE_BLOCK_CARET_STATE ) )
                        {
                            GFX_TextCursorTypeSet( pEb->hdr.gfxIndex,
                                               GFX_TEXT_CURSOR_TYPE_BLOCK );
                        }
                        else if( GFX_GOL_ObjectStateGet ( pEb, 
                                GFX_GOL_EDITBOX_ENABLE_UNDERSCORE_CARET_STATE ) )
                        {
                            GFX_TextCursorTypeSet( pEb->hdr.gfxIndex,
                                               GFX_TEXT_CURSOR_TYPE_UNDERSCORE );
                        }
                        else 
                        {
                            GFX_TextCursorTypeSet( pEb->hdr.gfxIndex,
                                               GFX_TEXT_CURSOR_TYPE_NONE );
                        }
                                        
                        GFX_ColorSet( pEb->hdr.gfxIndex,
                                      pEb->hdr.pGolScheme->TextColor0);
                    }
                    else
                    {
                        GFX_ColorSet( pEb->hdr.gfxIndex,
                                      pEb->hdr.pGolScheme->Color0);
                    }
                    state = DRAW_EDITBOX_CARET;

                    // no break here since it will always go to
                    // the DRAW_EDITBOX_CARET state
                }
                else
                {
                    state = DRAW_EDITBOX_START;
#ifdef GFX_LIB_CFG_USE_BISTABLE_DISPLAY_GOL_AUTO_REFRESH
                    GFX_DRIVER_CompleteDrawUpdate(  pEb->hdr.left,
                                                    pEb->hdr.top,
                                                    pEb->hdr.right,
                                                    pEb->hdr.bottom);
#endif
                    return (GFX_STATUS_SUCCESS);
                }

                if( GFX_PREEMPTION_LEVEL_2 == preemptionLevel )
                {
                    return GFX_STATUS_FAILURE;
                }
   
            case DRAW_EDITBOX_CARET:
                
                cursorWidth = GFX_TextCursorWidthGet(pEb->hdr.gfxIndex);
                
                if( pEb->alignment == GFX_ALIGN_HCENTER )
                {
                    cursorX = ( pEb->hdr.left + pEb->hdr.right - 
                                GFX_TextStringWidthGet( pEb->pText, 
                                GFX_FontGet( pEb->hdr.gfxIndex )) ) >> 1;
                
                } else if ( pEb->alignment == GFX_ALIGN_RIGHT )
                {
                    cursorX = pEb->hdr.right - pEb->hdr.pGolScheme->EmbossSize -
                              GFX_TextStringWidthGet( pEb->pText, 
                              GFX_FontGet( pEb->hdr.gfxIndex ));
                }
                else
                {
                    cursorX = pEb->hdr.left + pEb->hdr.pGolScheme->EmbossSize; 
                }
                
                cursorX += pEb->cursorPosition * cursorWidth;
                cursorY = GFX_TextCursorPositionYGet(pEb->hdr.gfxIndex);
                        
                if( ( cursorX + cursorWidth ) <= 
                    ( pEb->hdr.right - pEb->hdr.pGolScheme->EmbossSize  ) &&
                     cursorX >= ( pEb->hdr.left + pEb->hdr.pGolScheme->EmbossSize ))
                {    
                    // draw the caret if required
                    if(!GFX_TextCursorDraw( pEb->hdr.gfxIndex,
                                            cursorX,
                                            cursorY,
                                            cursorWidth,
                                            pEb->textHeight ) )
                    {
                        return (GFX_STATUS_FAILURE);
                    }
                }
                
                state = DRAW_EDITBOX_START;

#ifdef GFX_LIB_CFG_USE_BISTABLE_DISPLAY_GOL_AUTO_REFRESH
                GFX_DRIVER_CompleteDrawUpdate(  pEb->hdr.left,
                                                pEb->hdr.top,
                                                pEb->hdr.right,
                                                pEb->hdr.bottom);
#endif
                return (GFX_STATUS_SUCCESS);
        } // switch()
        
    }//  while(1)

}

