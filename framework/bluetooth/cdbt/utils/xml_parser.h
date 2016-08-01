/*******************************************************************************
 Microchip Bluetooth Stack - Utilities

  Company:
    Searan LLC.

  File Name:
    xml_parser.h

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

#ifndef __UTILS_XML_PARSER_H  // Guards against multiple inclusion
#define __UTILS_XML_PARSER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END


#define XML_PARSER_STATE_WAIT_TAG_NAME		0
#define XML_PARSER_STATE_READ_TAG_NAME		1
#define XML_PARSER_STATE_WAIT_TAG_CLOSE		2
#define XML_PARSER_STATE_SKIP_TAG			3
#define XML_PARSER_STATE_WAIT_ATTR_NAME		4
#define XML_PARSER_STATE_READ_ATTR_NAME		5
#define XML_PARSER_STATE_WAIT_ATTR_VALUE	6
#define XML_PARSER_STATE_READ_TAG_VALUE		7
#define XML_PARSER_STATE_READ_ATTR_VALUE	8
#define XML_PARSER_STATE_SKIP_ATTR			9
#define XML_PARSER_STATE_SKIP_PROC_INST		10
#define XML_PARSER_STATE_SKIP_COMMENTS		11

#define XML_EVT_TAG_STARTED			0
#define XML_EVT_TAG_ENDED			1
#define XML_EVT_ATTR_NAME			2
#define XML_EVT_ATTR_VALUE			3


#define XML_BUFFER_LEN	30

struct _bt_xml_parser_t;

typedef void (*bt_xml_parser_callback_pf)(struct _bt_xml_parser_t* parser, bt_byte evt, void* evt_param, void* callback_param);


typedef struct _bt_xml_evt_tag_started_t
{
	bt_byte* name;
	bt_byte len;
} bt_xml_evt_tag_started_t;

typedef struct _bt_xml_evt_attribute_t
{
	bt_byte* name;
	bt_byte len;
} bt_xml_evt_attribute_t;

typedef struct _bt_xml_evt_attribute_value_t
{
	bt_byte* value;
	bt_byte len;
} bt_xml_evt_attribute_value_t;

typedef struct _bt_xml_parser_t
{
	bt_byte state;
	bt_byte buffer[XML_BUFFER_LEN];
	bt_byte write_pos;
	bt_byte prev_c;
	bt_byte quote_c;

	bt_xml_parser_callback_pf callback;
	void* callback_param;
} bt_xml_parser_t;

void bt_xml_parse_fragment(bt_xml_parser_t* parser, bt_byte_cp data, bt_uint len);

void bt_xml_parser_reset(bt_xml_parser_t* parser);

#ifdef __cplusplus
}
#endif

#endif // __UTILS_XML_PARSER_H
