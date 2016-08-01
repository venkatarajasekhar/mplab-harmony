/*******************************************************************************
 Microchip Bluetooth Stack - Serial Data Protocol

  Company:
    Searan LLC.

  File Name:
    sdp_utils.h

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

#ifndef __SDP_UTILS_H  // Guards against multiple inclusion
#define __SDP_UTILS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END
bt_bool _sdp_write_data_element(bt_sdp_data_element_cp pde, bt_byte_p buffer, bt_int len, bt_int_p poffset);
bt_bool _sdp_read_de_header(bt_byte_cp buffer, bt_int len, bt_int_p poffset, bt_byte_p pde_type, bt_byte_p pde_size_index, bt_ulong_p pde_data_len);
bt_ulong _sdp_get_de_data_len(bt_sdp_data_element_cp pde);
bt_ulong _sdp_get_de_hdr_len(bt_sdp_data_element_cp pde);

void bt_sdp_de_to_uuid(bt_sdp_data_element_cp pde, bt_uuid_p puuid);

#ifdef __cplusplus
}
#endif

#endif // _SDP_UTILS_H
