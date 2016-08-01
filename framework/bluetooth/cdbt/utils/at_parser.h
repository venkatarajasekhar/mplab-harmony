/*******************************************************************************
 Microchip Bluetooth Stack - Utilities

  Company:
    Searan LLC.

  File Name:
    at_parser.h

  Summary:
    Bluetooth API Library interface Utilities.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.

*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
* Source contains proprietary and confidential information of SEARAN LLC.
* May not be used or disclosed to any other party except in accordance
* with a license from SEARAN LLC or Microchip Technology Inc.
* Copyright (c) 2011, 2012 SEARAN LLC. All Rights Reserved.
*
*
*******************************************************************************/
// DOM-IGNORE-END

#ifndef __UTILS_AT_PARSER_H  // Guards against multiple inclusion
#define __UTILS_AT_PARSER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#define AT_EVT_RING          0
#define AT_EVT_OK            1
#define AT_EVT_ERROR         2
#define AT_EVT_CMD_CODE      3
#define AT_EVT_CMD_READ_CODE 4
#define AT_EVT_CMD_PARAM     5
#define AT_EVT_CMD_COMPLETED 6

#define ATCMD_BUFFER_LEN 20

struct _bt_at_parser_t;

typedef void (*bt_at_parser_callback_pf)(struct _bt_at_parser_t* parser, bt_byte evt, void* evt_param, void* callback_param);

typedef struct _bt_at_parser_t
{
	bt_byte state;
	bt_byte buffer[ATCMD_BUFFER_LEN + 1];
	bt_byte write_pos;
	bt_byte param_read_state;
	bt_byte param_read_nesting_level;

	bt_at_parser_callback_pf callback;
	void* callback_param;
} bt_at_parser_t;

void bt_at_parse_fragment(bt_at_parser_t* parser, bt_byte* data, bt_uint len);

void bt_at_parser_reset(bt_at_parser_t* parser);

#ifdef __cplusplus
}
#endif

#endif // __UTILS_AT_PARSER_H
