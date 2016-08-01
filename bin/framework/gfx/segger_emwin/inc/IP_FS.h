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

** emWin V5.34 - Graphical user interface for embedded applications **
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
Licensing information

Licensor:                 SEGGER Microcontroller Systems LLC
Licensed to:              Microchip Technology Inc., 2355 W Chandler Blvd., Chandler, AZ 85224, US
Licensed SEGGER software: emWin
License number:           GUI-00614
License model:            CPU Object Code License, dated Sept. 8, 2015
Licensed product:         Any
Licensed platform:        PIC24, PIC32, dsPIC, PIC16, PIC18 / MPLAB X Integrated Development Evironment, XC16 C Compiler, XC32 C/C++ Compiler
Licensed number of seats: -
----------------------------------------------------------------------
File        : IP_FS.h
Purpose     : File system abstraction layer
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file !
*/

#ifndef  IP_FS_H
#define  IP_FS_H

#include "SEGGER.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Functions
*
**********************************************************************
*/

typedef struct {
  //
  // Read only file operations. These have to be present on ANY file system, even the simplest one.
  //
  void * (*pfOpenFile)             (const char *sFilename);
  int    (*pfCloseFile)            (void *hFile);
  int    (*pfReadAt)               (void *hFile, void *pBuffer, U32 Pos, U32 NumBytes);
  long   (*pfGetLen)               (void *hFile);
  //
  // Directory query operations.
  //
  void   (*pfForEachDirEntry)      (void *pContext, const char *sDir, void (*pf)(void *pContext, void *pFileEntry));
  void   (*pfGetDirEntryFileName)  (void *pFileEntry, char *sFileName, U32 SizeOfBuffer);
  U32    (*pfGetDirEntryFileSize)  (void *pFileEntry, U32 *pFileSizeHigh);
  U32    (*pfGetDirEntryFileTime)  (void *pFileEntry);
  int    (*pfGetDirEntryAttributes)(void *pFileEntry);
  //
  // Write file operations.
  //
  void * (*pfCreate)               (const char *sFileName);
  void * (*pfDeleteFile)           (const char *sFilename);
  int    (*pfRenameFile)           (const char *sOldFilename, const char *sNewFilename);
  int    (*pfWriteAt)              (void *hFile, void *pBuffer, U32 Pos, U32 NumBytes);
  //
  // Additional directory operations
  //
  int    (*pfMKDir)                (const char *sDirName);
  int    (*pfRMDir)                (const char *sDirName);
  //
  // Additional operations
  //
  int    (*pfIsFolder)             (const char *sPath);
  int    (*pfMove)                 (const char *sOldFilename, const char *sNewFilename);
} IP_FS_API;

extern const IP_FS_API IP_FS_ReadOnly;   // Read-only file system, typically located in flash memory
extern const IP_FS_API IP_FS_Win32;      // File system interface for Win32
extern const IP_FS_API IP_FS_FS;         // target file system (emFile)

//
// Function for setting the base dir
//
void IP_FS_WIN32_SetBaseDir(const char * sBaseDir);

#if defined(__cplusplus)
  }
#endif


#endif   /* Avoid multiple inclusion */

/*************************** End of file ****************************/




