/*****************************************************************************
  AUTO-GENERATED CODE:  Graphics Resource Converter version: 4.00.39 BETA

  Company:
      Microchip Technology, Inc.
 
  File Name:
     gfx_resources_int.h
 
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

#ifndef GFX_RESOURCES_INT_H_FILE
#define GFX_RESOURCES_INT_H_FILE
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
 * #define GFX_EXTERNAL_FONT_RASTER_BUFFER_SIZE     (215)
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
 * Label: cog
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR cog;
#define cog_WIDTH     (120)
#define cog_HEIGHT    (120)
#define cog_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: cog_outline
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR cog_outline;
#define cog_outline_WIDTH     (120)
#define cog_outline_HEIGHT    (120)
#define cog_outline_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: layers_image
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR layers_image;
#define layers_image_WIDTH     (120)
#define layers_image_HEIGHT    (120)
#define layers_image_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: layers_image_outline
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR layers_image_outline;
#define layers_image_outline_WIDTH     (120)
#define layers_image_outline_HEIGHT    (120)
#define layers_image_outline_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: location_pin
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR location_pin;
#define location_pin_WIDTH     (120)
#define location_pin_HEIGHT    (120)
#define location_pin_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: location_pin_outline
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR location_pin_outline;
#define location_pin_outline_WIDTH     (120)
#define location_pin_outline_HEIGHT    (120)
#define location_pin_outline_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: script_invert
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR script_invert;
#define script_invert_WIDTH     (120)
#define script_invert_HEIGHT    (120)
#define script_invert_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: script_outline
 * Description:  120x120 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR script_outline;
#define script_outline_WIDTH     (120)
#define script_outline_HEIGHT    (120)
#define script_outline_SIZE      (1810)
/*********************************
 * Bitmap Structure
 * Label: home_outline
 * Description:  90x90 pixels, 1-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR home_outline;
#define home_outline_WIDTH     (90)
#define home_outline_HEIGHT    (90)
#define home_outline_SIZE      (1090)
/*********************************
 * Bitmap Structure
 * Label: ct_FeatureList
 * Description:  547x350 pixels, 4-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR ct_FeatureList;
#define ct_FeatureList_WIDTH     (547)
#define ct_FeatureList_HEIGHT    (350)
#define ct_FeatureList_SIZE      (95938)
/*********************************
 * Bitmap Structure
 * Label: cs_FeatureList
 * Description:  562x350 pixels, 4-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR cs_FeatureList;
#define cs_FeatureList_WIDTH     (562)
#define cs_FeatureList_HEIGHT    (350)
#define cs_FeatureList_SIZE      (98388)
/*********************************
 * Bitmap Structure
 * Label: cs_SlideShowInstructions
 * Description:  686x310 pixels, 4-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR cs_SlideShowInstructions;
#define cs_SlideShowInstructions_WIDTH     (686)
#define cs_SlideShowInstructions_HEIGHT    (310)
#define cs_SlideShowInstructions_SIZE      (106368)
/*********************************
 * Bitmap Structure
 * Label: ct_SlideShowInstructions
 * Description:  686x311 pixels, 4-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR ct_SlideShowInstructions;
#define ct_SlideShowInstructions_WIDTH     (686)
#define ct_SlideShowInstructions_HEIGHT    (311)
#define ct_SlideShowInstructions_SIZE      (106711)
/*********************************
 * Bitmap Structure
 * Label: RoundHomeButton
 * Description:  128x127 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR RoundHomeButton;
#define RoundHomeButton_WIDTH     (128)
#define RoundHomeButton_HEIGHT    (127)
#define RoundHomeButton_SIZE      (32518)
/*********************************
 * Bitmap Structure
 * Label: RoundHomeButton_Outline
 * Description:  128x127 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR RoundHomeButton_Outline;
#define RoundHomeButton_Outline_WIDTH     (128)
#define RoundHomeButton_Outline_HEIGHT    (127)
#define RoundHomeButton_Outline_SIZE      (32518)
/*********************************
 * Bitmap Structure
 * Label: NewHarmonyLogo_Small
 * Description:  172x120 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR NewHarmonyLogo_Small;
#define NewHarmonyLogo_Small_WIDTH     (172)
#define NewHarmonyLogo_Small_HEIGHT    (120)
#define NewHarmonyLogo_Small_SIZE      (41286)
/*********************************
 * Bitmap Structure
 * Label: microchipLogo_small
 * Description:  220x120 pixels, 16-bits per pixel
 ***********************************/
extern const GFX_RESOURCE_HDR microchipLogo_small;
#define microchipLogo_small_WIDTH     (220)
#define microchipLogo_small_HEIGHT    (120)
#define microchipLogo_small_SIZE      (52806)
/*****************************************************************************
 * SECTION:  JPEGS
 *****************************************************************************/

/*********************************
 * JPEG Structure
 * Label: ScienceWorldNight
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR ScienceWorldNight;
#define ScienceWorldNight_WIDTH     (800)
#define ScienceWorldNight_HEIGHT    (480)
#define ScienceWorldNight_SIZE      (65734)
/*********************************
 * JPEG Structure
 * Label: EnglishBayFireworks
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR EnglishBayFireworks;
#define EnglishBayFireworks_WIDTH     (800)
#define EnglishBayFireworks_HEIGHT    (480)
#define EnglishBayFireworks_SIZE      (55400)
/*********************************
 * JPEG Structure
 * Label: CoalHarbourDay
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR CoalHarbourDay;
#define CoalHarbourDay_WIDTH     (800)
#define CoalHarbourDay_HEIGHT    (480)
#define CoalHarbourDay_SIZE      (70406)
/*********************************
 * JPEG Structure
 * Label: HomeScreen
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR HomeScreen;
#define HomeScreen_WIDTH     (800)
#define HomeScreen_HEIGHT    (480)
#define HomeScreen_SIZE      (19737)
/*********************************
 * JPEG Structure
 * Label: AutumnGass_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR AutumnGass_JPEG;
#define AutumnGass_JPEG_WIDTH     (800)
#define AutumnGass_JPEG_HEIGHT    (480)
#define AutumnGass_JPEG_SIZE      (98547)
/*********************************
 * JPEG Structure
 * Label: FalseCreek_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR FalseCreek_JPEG;
#define FalseCreek_JPEG_WIDTH     (800)
#define FalseCreek_JPEG_HEIGHT    (480)
#define FalseCreek_JPEG_SIZE      (72465)
/*********************************
 * JPEG Structure
 * Label: BoraBoraSunset_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR BoraBoraSunset_JPEG;
#define BoraBoraSunset_JPEG_WIDTH     (800)
#define BoraBoraSunset_JPEG_HEIGHT    (480)
#define BoraBoraSunset_JPEG_SIZE      (77469)
/*********************************
 * JPEG Structure
 * Label: DowntownVancouver_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR DowntownVancouver_JPEG;
#define DowntownVancouver_JPEG_WIDTH     (800)
#define DowntownVancouver_JPEG_HEIGHT    (480)
#define DowntownVancouver_JPEG_SIZE      (102252)
/*********************************
 * JPEG Structure
 * Label: MacBethChart_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR MacBethChart_JPEG;
#define MacBethChart_JPEG_WIDTH     (800)
#define MacBethChart_JPEG_HEIGHT    (480)
#define MacBethChart_JPEG_SIZE      (21995)
/*********************************
 * JPEG Structure
 * Label: Fishes_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR Fishes_JPEG;
#define Fishes_JPEG_WIDTH     (800)
#define Fishes_JPEG_HEIGHT    (480)
#define Fishes_JPEG_SIZE      (50040)
/*********************************
 * JPEG Structure
 * Label: ParkTrees_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR ParkTrees_JPEG;
#define ParkTrees_JPEG_WIDTH     (800)
#define ParkTrees_JPEG_HEIGHT    (480)
#define ParkTrees_JPEG_SIZE      (128167)
/*********************************
 * JPEG Structure
 * Label: Rockies_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR Rockies_JPEG;
#define Rockies_JPEG_WIDTH     (800)
#define Rockies_JPEG_HEIGHT    (480)
#define Rockies_JPEG_SIZE      (93361)
/*********************************
 * JPEG Structure
 * Label: SnowLeopard_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR SnowLeopard_JPEG;
#define SnowLeopard_JPEG_WIDTH     (800)
#define SnowLeopard_JPEG_HEIGHT    (480)
#define SnowLeopard_JPEG_SIZE      (43854)
/*********************************
 * JPEG Structure
 * Label: SnowyHills_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR SnowyHills_JPEG;
#define SnowyHills_JPEG_WIDTH     (800)
#define SnowyHills_JPEG_HEIGHT    (480)
#define SnowyHills_JPEG_SIZE      (70376)
/*********************************
 * JPEG Structure
 * Label: Splash_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR Splash_JPEG;
#define Splash_JPEG_WIDTH     (800)
#define Splash_JPEG_HEIGHT    (480)
#define Splash_JPEG_SIZE      (29117)
/*********************************
 * JPEG Structure
 * Label: Waterfall_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR Waterfall_JPEG;
#define Waterfall_JPEG_WIDTH     (800)
#define Waterfall_JPEG_HEIGHT    (480)
#define Waterfall_JPEG_SIZE      (70137)
/*********************************
 * JPEG Structure
 * Label: Wheats_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR Wheats_JPEG;
#define Wheats_JPEG_WIDTH     (800)
#define Wheats_JPEG_HEIGHT    (480)
#define Wheats_JPEG_SIZE      (40875)
/*********************************
 * JPEG Structure
 * Label: ColorPalette_JPEG
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR ColorPalette_JPEG;
#define ColorPalette_JPEG_WIDTH     (800)
#define ColorPalette_JPEG_HEIGHT    (480)
#define ColorPalette_JPEG_SIZE      (18709)
/*********************************
 * JPEG Structure
 * Label: NewHarmonyLogo
 * Description:  800x480 pixels
 ***********************************/
extern const GFX_RESOURCE_HDR NewHarmonyLogo;
#define NewHarmonyLogo_WIDTH     (800)
#define NewHarmonyLogo_HEIGHT    (480)
#define NewHarmonyLogo_SIZE      (31318)
/*****************************************************************************
 * SECTION:  Fonts
 *****************************************************************************/

/*********************************
 * TTF Font File Structure
 * Label: VeraMono
 * Description:  Height: 29 pixels, 1 bit per pixel, Range: ' ' to ''
 ***********************************/
extern const GFX_RESOURCE_HDR VeraMono;
#define VeraMono_SIZE    (5960)
/*********************************
 * TTF Font File Structure
 * Label: SimHei36
 * Description:  Height: 42 pixels, 1 bit per pixel, Range: '?' to '?'
 ***********************************/
extern const GFX_RESOURCE_HDR SimHei36;
#define SimHei36_SIZE    (8245)
#endif

