/*********************************************************************
*                 SEGGER Microcontroller Systems LLC                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2016  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.36 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to Microchip Technology Inc. for the
purposes  of  creating  libraries  for  16 -bit  PIC microcontrollers,
32-bit  PIC  microntrollers,  dsPIC  digital  signal  controllers  and
microcontrollers   with   part   name   prefix   "PIC16"  and  "PIC18"
commercialized and distributed by Microchip Technology Inc. as part of
the  MPLAB  Integrated  Development  Environment  under  the terms and
conditions  of  an  End  User  License  Agreement  supplied  with  the
libraries. Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
----------------------------------------------------------------------
File        : TEXT.h
Purpose     : TEXT include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef TEXT_PRIVATE_H
#define TEXT_PRIVATE_H

#include "TEXT.h"
#include "GUI_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  const GUI_FONT * pFont;
  GUI_COLOR TextColor;
  GUI_COLOR BkColor;
  GUI_WRAPMODE WrapMode;
} TEXT_PROPS;

typedef struct {
  WIDGET Widget;
  TEXT_PROPS Props;
  WM_HMEM hpText;
  I16 Align;
} TEXT_OBJ;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define TEXT_INIT_ID(p) p->Widget.DebugId = TEXT_ID
#else
  #define TEXT_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  TEXT_OBJ * TEXT_LockH(TEXT_Handle h);
  #define TEXT_LOCK_H(h)   TEXT_LockH(h)
#else
  #define TEXT_LOCK_H(h)   (TEXT_OBJ *)GUI_LOCK_H(h)
#endif

/*********************************************************************
*
*       Module internal data
*
**********************************************************************
*/
extern TEXT_PROPS TEXT__DefaultProps;

#endif   /* if GUI_WINSUPPORT */
#endif   /* TEXT_PRIVATE_H */
