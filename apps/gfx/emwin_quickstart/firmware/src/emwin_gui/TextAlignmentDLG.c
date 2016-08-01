/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "system_config.h"
#include "system_definitions.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_BUTTON_0   (GUI_ID_USER + 0x01)
#define ID_TEXT_0   (GUI_ID_USER + 0x02)
#define ID_RADIO_0   (GUI_ID_USER + 0x03)
#define ID_TEXT_1   (GUI_ID_USER + 0x04)
#define ID_TEXT_2   (GUI_ID_USER + 0x05)
#define ID_TEXT_3   (GUI_ID_USER + 0x06)
#define ID_TEXT_4   (GUI_ID_USER + 0x07)
#define ID_TEXT_5   (GUI_ID_USER + 0x08)
#define ID_RADIO_1   (GUI_ID_USER + 0x09)
#define ID_TEXT_6   (GUI_ID_USER + 0x0A)
#define ID_TEXT_7   (GUI_ID_USER + 0x0B)
#define ID_TEXT_8   (GUI_ID_USER + 0x0C)
#define ID_TEXT_9   (GUI_ID_USER + 0x0D)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
static int hAlignment = GUI_TA_HCENTER; 
static int vAlignment = GUI_TA_VCENTER; 
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Text Alignment", ID_FRAMEWIN_0, 0, 0, 480, 272, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "TABack", ID_BUTTON_0, 10, 175, 60, 60, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 180, 75, 120, 20, 0, 0x64, 0 },
  { RADIO_CreateIndirect, "Radio", ID_RADIO_0, 50, 50, 20, 85, 0, 0x1e03, 0 },
  { TEXT_CreateIndirect, "center", ID_TEXT_1, 75, 47, 45, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "left", ID_TEXT_2, 77, 77, 45, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "right", ID_TEXT_3, 77, 109, 45, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "TAInstructions", ID_TEXT_4, 110, 140, 260, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 29, 23, 120, 20, 0, 0x64, 0 },
  { RADIO_CreateIndirect, "Radio", ID_RADIO_1, 390, 50, 21, 86, 0, 0x1e03, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 321, 20, 116, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 344, 47, 38, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 358, 77, 23, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 339, 108, 42, 20, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  int     alignment;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Text Alignment'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetFont(hItem, GUI_FONT_13B_1);
    //
    // Initialization of 'TABack'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "Previous");
    BUTTON_SetFont(hItem, GUI_FONT_13B_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_13B_1);
    TEXT_SetText(hItem, "Alignment");
    //
    // Initialization of 'center'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "center");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'left'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "left");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'right'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetText(hItem, "right");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'TAInstructions'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "Change text alignment by presseing the radio button");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetText(hItem, "Horizontal Alignment");
    TEXT_SetFont(hItem, GUI_FONT_13B_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetText(hItem, "Vertical Alignment");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_13B_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetText(hItem, "center");
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    TEXT_SetText(hItem, "top");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    TEXT_SetText(hItem, "bottom");
    // USER START (Optionally insert additional code for further widget initialization)
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetBkColor(hItem, GUI_LIGHTGRAY);
    TEXT_SetTextAlign(hItem, hAlignment | vAlignment);
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'TABack'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
          emWin_GuiScreenChange(EMWIN_APP_SCREEN_NUMBER_CHURNING);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_RADIO_0: // Notifications sent by 'Radio'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
          hItem     = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
          alignment = RADIO_GetValue(hItem);
          
          switch(alignment)
          {
              case 1:
              {
                  hAlignment = GUI_TA_LEFT ;
                  break;
              }
              
              case 2:
              {
                  hAlignment = GUI_TA_RIGHT;
                  break;
              }
              
              default:
              {
                  hAlignment = GUI_TA_HCENTER;
                  break;
              }
          }
          
          hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
          TEXT_SetTextAlign(hItem, hAlignment | vAlignment );
          
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_RADIO_1: // Notifications sent by 'Radio'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
          hItem     = WM_GetDialogItem(pMsg->hWin, ID_RADIO_1);
          alignment = RADIO_GetValue(hItem);
          
          switch(alignment)
          {
              case 1:
              {
                  vAlignment = GUI_TA_TOP;
                  break;
              }
              
              case 2:
              {
                  vAlignment = GUI_TA_BOTTOM;
                  break;
              }
              
              default:
              {
                  vAlignment = GUI_TA_VCENTER;
                  break;
              }
          }
          
          hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
          TEXT_SetTextAlign(hItem, hAlignment | vAlignment );
          
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateText Alignment
*/
WM_HWIN CreateTextAlignment(void);
WM_HWIN CreateTextAlignment(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
