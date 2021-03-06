/*****************************************************************************
  AUTO-GENERATED CODE:  Graphics Resource Converter version: 4.00.39 BETA

  Company:
      Microchip Technology, Inc.
 
  File Name:
     gfx_resources_ext.h
 
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

#ifndef GFX_RESOURCES_EXT_H_FILE
#define GFX_RESOURCES_EXT_H_FILE
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
 * This is an error check for the color depth
 *****************************************************************************/
#if (COLOR_DEPTH > 16)
#error "Color Depth needs to be 16 to correctly use these resources"
#endif


/*****************************************************************************
 * This is a unique marker to verify the external memory data
 * The marker is a total of 8 bytes in length starting at the location GRC_CRC32_EXTERNAL_ADDR.
 * The first four bytes, starting at GRC_CRC32_EXTERNAL_ADDR, will always equal 'M', 'C', 'H', 'P'.
 * The next four byte is the generated 32-bit CRC.  The application can compare the value read from the
 * external memory to the value of GRC_CRC32_EXTERNAL_MARKER to verify that the data is valid.
 *****************************************************************************/
#define GRC_CRC32_EXTERNAL_MARKER 0x3B4D1AB5ul
#define GRC_CRC32_EXTERNAL_ADDR 0x00214AA0ul

/*****************************************************************************
 * SECTION:  BITMAPS
 *****************************************************************************/

/*********************************
 * Bitmap Structure
 * Label: AutumnGass
 * Description:  480x288 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR AutumnGass;
#define AutumnGass_WIDTH     (480)
#define AutumnGass_HEIGHT    (288)
#define AutumnGass_SIZE      (276486)
/*********************************
 * Bitmap Structure
 * Label: ParkTrees
 * Description:  453x272 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR ParkTrees;
#define ParkTrees_WIDTH     (453)
#define ParkTrees_HEIGHT    (272)
#define ParkTrees_SIZE      (246438)
/*********************************
 * Bitmap Structure
 * Label: Wheats
 * Description:  480x288 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR Wheats;
#define Wheats_WIDTH     (480)
#define Wheats_HEIGHT    (288)
#define Wheats_SIZE      (276486)
/*********************************
 * Bitmap Structure
 * Label: FalseCreek
 * Description:  480x288 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR FalseCreek;
#define FalseCreek_WIDTH     (480)
#define FalseCreek_HEIGHT    (288)
#define FalseCreek_SIZE      (276486)
/*********************************
 * Bitmap Structure
 * Label: Fishes
 * Description:  480x288 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR Fishes;
#define Fishes_WIDTH     (480)
#define Fishes_HEIGHT    (288)
#define Fishes_SIZE      (276486)
/*********************************
 * Bitmap Structure
 * Label: ColorPalette
 * Description:  480x288 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR ColorPalette;
#define ColorPalette_WIDTH     (480)
#define ColorPalette_HEIGHT    (288)
#define ColorPalette_SIZE      (276486)
/*********************************
 * Bitmap Structure
 * Label: Sherwood
 * Description:  480x288 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR Sherwood;
#define Sherwood_WIDTH     (480)
#define Sherwood_HEIGHT    (288)
#define Sherwood_SIZE      (276486)
/*********************************
 * Bitmap Structure
 * Label: SnowyHills
 * Description:  480x288 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR SnowyHills;
#define SnowyHills_WIDTH     (480)
#define SnowyHills_HEIGHT    (288)
#define SnowyHills_SIZE      (276486)
#endif

