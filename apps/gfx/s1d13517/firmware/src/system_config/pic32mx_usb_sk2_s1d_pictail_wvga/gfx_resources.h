/*****************************************************************************
  AUTO-GENERATED CODE:  Graphics Resource Converter version: 4.00.39 BETA

  Company:
      Microchip Technology, Inc.
 
  File Name:
     gfx_resources.h
 
  Summary:
      This file is generated by the Microchip's Graphics Resource Converter.
  Description:
      This file is generated by the Graphics Resource Converter containing
      resources such as images and fonts that can be used by Microchip's
      Graphics Library, which is part of the MLA.
 *****************************************************************************/

// DOM-IGNORE-BEGIN
/*****************************************************************************
  Software License Agreement

  Copyright(c) 2013 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller that is integrated into your product or third party
  product (pursuant to the sublicense terms in the accompanying license
  agreement).
 
  You should refer to the license agreement accompanying this Software
  for additional information regarding your rights and obligations.
 
  SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
  OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
  PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
  OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
  BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
  DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
  INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
  CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
  OR OTHER SIMILAR COSTS.
 *****************************************************************************/
// DOM-IGNORE-END

#ifndef GFX_RESOURCES_H_FILE
#define GFX_RESOURCES_H_FILE
/*****************************************************************************
 * SECTION:  Includes
 *****************************************************************************/
#include <gfx/gfx.h>
#include <stdint.h>

/*****************************************************************************
 * SECTION:  Graphics Library Firmware Check
 *****************************************************************************/
#if(GRAPHICS_LIBRARY_VERSION != 0x0400)
#warning "It is suggested to use Graphics Library version 4.00 with this version of GRC."
#endif

/*****************************************************************************
 * SECTION:  Graphics Bitmap Padding Check
 *****************************************************************************/
#ifdef GFX_CONFIG_IMAGE_PADDING_DISABLE
#error These bitmap resources have been converted with padding of the horizontal lines, but GFX_CONFIG_IMAGE_PADDING_DISABLE is defined in system_config.h.
#endif


/*****************************************************************************
 * SECTION: Graphics Configuration
 * Overview:    This defines the size of the buffer used by font functions
 *              to retrieve font data from the external memory. The buffer
 *              size can be increased to accommodate large font sizes.
 *              The user must be aware of the expected glyph sizes of the 
 *              characters stored in the font table. 
 *              To modify the size used, declare this macro in the 
 *              GraphicsConfig.h file with the desired size.
 *
 * #define GFX_EXTERNAL_FONT_RASTER_BUFFER_SIZE     (576)
 *****************************************************************************/

/*****************************************************************************
 * This is an error check for the color depth
 *****************************************************************************/
#if (COLOR_DEPTH > 16)
#error "Color Depth needs to be 16 to correctly use these resources"
#endif



/*****************************************************************************
 * SECTION:  BITMAPS
 *****************************************************************************/

/*********************************
 * Bitmap Structure
 * Label: harmony
 * Description:  480x272 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR harmony;
#define harmony_WIDTH     (480)
#define harmony_HEIGHT    (272)
#define harmony_SIZE      (261126)
/*********************************
 * Bitmap Structure
 * Label: file_browser
 * Description:  50x50 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR file_browser;
#define file_browser_WIDTH     (50)
#define file_browser_HEIGHT    (50)
#define file_browser_SIZE      (5006)
/*********************************
 * Bitmap Structure
 * Label: appointment_new
 * Description:  48x48 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR appointment_new;
#define appointment_new_WIDTH     (48)
#define appointment_new_HEIGHT    (48)
#define appointment_new_SIZE      (4614)
/*********************************
 * Bitmap Structure
 * Label: list_add
 * Description:  48x48 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR list_add;
#define list_add_WIDTH     (48)
#define list_add_HEIGHT    (48)
#define list_add_SIZE      (4614)
/*********************************
 * Bitmap Structure
 * Label: list_remove
 * Description:  48x48 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR list_remove;
#define list_remove_WIDTH     (48)
#define list_remove_HEIGHT    (48)
#define list_remove_SIZE      (4614)
/*********************************
 * Bitmap Structure
 * Label: House
 * Description:  380x366 pixels, 4-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR House;
#define House_WIDTH     (380)
#define House_HEIGHT    (366)
#define House_SIZE      (69578)
/*********************************
 * Bitmap Structure
 * Label: help_faq
 * Description:  48x48 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR help_faq;
#define help_faq_WIDTH     (48)
#define help_faq_HEIGHT    (48)
#define help_faq_SIZE      (4614)
/*****************************************************************************
 * SECTION:  Fonts
 *****************************************************************************/

/*********************************
 * TTF Font File Structure
 * Label: Arial
 * Description:  Height: 22 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const GFX_RESOURCE_HDR Arial;
#define Arial_SIZE    (4084)
/*********************************
 * TTF Font File Structure
 * Label: Arial30
 * Description:  Height: 35 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const GFX_RESOURCE_HDR Arial30;
#define Arial30_SIZE    (9177)
/*********************************
 * TTF Font File Structure
 * Label: Arial60
 * Description:  Height: 70 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const GFX_RESOURCE_HDR Arial60;
#define Arial60_SIZE    (31574)
#endif

