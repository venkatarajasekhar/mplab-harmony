/*******************************************************************************
 Microchip Bluetooth Stack - Serial Data Protocol

  Company:
    Searan LLC.

  File Name:
    sdp_private.h

  Summary:
    Bluetooth API Library interface to the SDP.

  Description:
    This is a portion of the API interface to the Bluetooth stack.  Other header files are
	grouped in the section under the CDBT master directory.  This module describe functions
	and data structures used to start the SDP server and perform SDP queries.

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

#ifndef __SDP_PRIVATE_H  // Guards against multiple inclusion
#define __SDP_PRIVATE_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END
//
// Global variables defined in SDP modules
// -------------------------------------------------------------------
//

// DOM-IGNORE-BEGIN
// In sdp_server.c
extern bt_buffer_mgr_t  _sdp_packet_buffer_mgr;
extern const bt_byte* sdp_db_main2;
extern bt_uint sdp_db_main2_len;

//
// Global variables defined by OEM configuration
// -------------------------------------------------------------------
//
extern bt_buffer_header_t           _sdp_buffer_headers[];
extern bt_byte                      _sdp_buffers[];
extern bt_buffer_header_t           _sdp_packet_buffer_headers[];
extern bt_sdp_packet_t              _sdp_packet_buffers[];
extern const bt_byte                _sdp_max_buffers;
extern const bt_uint                _sdp_max_search_result_len;
extern const bt_uint                _sdp_max_attribute_result_len;
extern bt_sr_handle_t               _sdp_found_sr_lists_buffers[];
extern bt_byte*			            _sdp_found_attr_list_buffers[];
extern bt_sdp_found_attr_list_t     _sdp_found_attr_lists_buffers[];
extern bt_buffer_mgr_t              _sdp_tran_buffer_mgr2;
extern bt_buffer_header_t           _sdp_tran_buffer_headers2[];
extern bt_sdp_transaction_t         _sdp_tran_buffers2[];
extern bt_buffer_mgr_t              _sdp_service_tran_buffer_mgr;
extern bt_buffer_header_t           _sdp_service_tran_buffer_headers[];
extern bt_sdp_service_transaction_t _sdp_service_tran_buffers[];

extern bt_bool             (*_sdp_start_fp)(bt_l2cap_mgr_p l2cap_mgr, const bt_byte* sdp_db, bt_uint sdp_db_len);


#ifdef _DEBUG
extern const bt_uint _ram_size_sdp_buffers;
#endif
// DOM-IGNORE-END
//
// Private types
// -------------------------------------------------------------------
//

typedef struct _bt_sdp_server_data_element_t
{
	bt_byte type;
	bt_uint data_len;
	const bt_byte* data;
} bt_sdp_server_data_element_t;

typedef struct _bt_sdp_server_attribute_t
{
	bt_uint attr_id;
	bt_uint data_len;
	const bt_byte* data;
	bt_sdp_server_data_element_t attr_value;
} bt_sdp_server_attribute_t;

typedef struct _bt_sdp_server_record_t 
{
	bt_sr_handle_t h;
	bt_uint data_len;
	const bt_byte* data;
} bt_sdp_server_record_t;


//
// Private global functions
// -------------------------------------------------------------------
//

// From sdp_utils.c
int sdp_find_service_records2(
	bt_byte_p pparams, bt_int params_len, 
	bt_int offsetInit, bt_byte patternCount,
	bt_sdp_service_transaction_p ptran, bt_int max_handles);
bt_bool sdp_find_attributes(
	bt_sr_handle_p h_list, bt_int h_count, 
	bt_byte_p pparams, bt_int params_len, 
	bt_int offsetInit, bt_byte patternCount,
	bt_sdp_transaction_t* ptran, bt_int max_attrs);

// From sdp_uuid.c
void sdp_uuid16_to_uuid128(bt_uuid16 uuid16, bt_uuid_p puuid);
void sdp_uuid32_to_uuid128(bt_uuid32 uuid32, bt_uuid_p puuid);
bt_int sdp_compare_uuid(bt_uuid_cp puuid1, bt_uuid_cp puuid2);
bt_bool sdp_compare_uuid_de(bt_sdp_data_element_cp pde1, bt_sdp_data_element_cp pde2);

// From sdp_tran_buffer.c
bt_bool _sdp_init_tran_buffers(void);
bt_sdp_transaction_t* _sdp_alloc_tran_buffer(bt_int id);
void _sdp_free_tran_buffer(bt_sdp_transaction_t* ptran);
bt_sdp_transaction_t* _sdp_find_transaction(bt_int id);
bt_sdp_service_transaction_p _sdp_alloc_svc_tran_buffer(bt_int id);
void _sdp_free_svc_tran_buffer(bt_sdp_service_transaction_p ptran);
bt_sdp_service_transaction_p _sdp_find_svc_transaction(bt_int id);

// From sdp_db_utils.c
bt_bool bt_sdp_read_attribute(bt_sdp_server_attribute_t* attr, const bt_byte* buffer, bt_int len, bt_int* offset);


#ifdef __cplusplus
}
#endif

#endif // __SDP_PRIVATE_H

