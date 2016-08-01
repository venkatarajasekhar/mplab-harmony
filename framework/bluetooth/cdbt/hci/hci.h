/*******************************************************************************
 Microchip Bluetooth Stack - Host Controller Interface

  Company:
    Searan LLC.

  File Name:
    hci.h

  Summary:
    Bluetooth API Library interface to the HCI Functions.

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

#ifndef __HCI_H
#define __HCI_H

#include "bluetooth/cdbt/utils/packet.h"

// Enable device specific code for TI BRF6150 module
//#define CDBT_TI_BRF6150

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
// DOM-IGNORE-END

#define HCI_CONFIG_ENABLE_AUTHENTICATION    0x01
#define HCI_CONFIG_ENABLE_ENCRYPTION        0x02
#define HCI_CONFIG_BECOME_MASTER            0x04

#define HCI_OPCODE(ogf, ocf)	(((int)ogf << 10) | ((int)ocf & 0x3ff))

#define OGF_LINK_CONTROL	0x01
#define OGF_LINK_POLICY		0x02
#define OGF_CTRL_BASEBAND	0x03
#define OGF_INFORMATION		0x04
#define OGF_STATUS			0x05
#define OGF_TESTING			0x06
#define OGF_LE				0x08
#define OGF_VENDOR			0x3F

// Link control commands
#define HCI_INQUIRY									HCI_OPCODE(OGF_LINK_CONTROL, 0x0001)
#define HCI_INQUIRY_CANCEL							HCI_OPCODE(OGF_LINK_CONTROL, 0x0002)
#define HCI_PERIODIC_INQUIRY_MODE					HCI_OPCODE(OGF_LINK_CONTROL, 0x0003)
#define HCI_EXIT_PERIODIC_INQUIRY_MODE				HCI_OPCODE(OGF_LINK_CONTROL, 0x0004)
#define HCI_CREATE_CONNECTION						HCI_OPCODE(OGF_LINK_CONTROL, 0x0005)
#define HCI_DISCONNECT								HCI_OPCODE(OGF_LINK_CONTROL, 0x0006)
#define HCI_CREATE_CONNECTION_CANCEL				HCI_OPCODE(OGF_LINK_CONTROL, 0x0008)
#define HCI_ACCEPT_CONNECTION_REQUEST				HCI_OPCODE(OGF_LINK_CONTROL, 0x0009)
#define HCI_REJECT_CONNECTION_REQUEST				HCI_OPCODE(OGF_LINK_CONTROL, 0x000A)
#define HCI_LINK_KEY_REQUEST_REPLY					HCI_OPCODE(OGF_LINK_CONTROL, 0x000B)
#define HCI_LINK_KEY_REQUEST_NEGATIVE_REPLY			HCI_OPCODE(OGF_LINK_CONTROL, 0x000C)
#define HCI_PIN_CODE_REQUEST_REPLY					HCI_OPCODE(OGF_LINK_CONTROL, 0x000D)
#define HCI_PIN_CODE_REQUEST_NEGATIVE_REPLY			HCI_OPCODE(OGF_LINK_CONTROL, 0x000E)
#define HCI_CHANGE_CONNECTION_PACKET_TYPE			HCI_OPCODE(OGF_LINK_CONTROL, 0x000F)
#define HCI_AUTHENTICATION_REQUESTED				HCI_OPCODE(OGF_LINK_CONTROL, 0x0011)
#define HCI_SET_CONNECTION_ENCRYPTION				HCI_OPCODE(OGF_LINK_CONTROL, 0x0013)
#define HCI_CHANGE_CONNECTION_LINK_KEY				HCI_OPCODE(OGF_LINK_CONTROL, 0x0015)
#define HCI_MASTER_LINK_KEY							HCI_OPCODE(OGF_LINK_CONTROL, 0x0017)
#define HCI_REMOTE_NAME_REQUEST						HCI_OPCODE(OGF_LINK_CONTROL, 0x0019)
#define HCI_REMOTE_NAME_REQUEST_CANCEL				HCI_OPCODE(OGF_LINK_CONTROL, 0x001A)
#define HCI_READ_REMOTE_SUPPORTED_FEATURES			HCI_OPCODE(OGF_LINK_CONTROL, 0x001B)
#define HCI_READ_REMOTE_EXTENDED_FEATURES			HCI_OPCODE(OGF_LINK_CONTROL, 0x001C)
#define HCI_READ_REMOTE_VERSION_INFORMATION			HCI_OPCODE(OGF_LINK_CONTROL, 0x001D)
#define HCI_READ_CLOCK_OFFSET						HCI_OPCODE(OGF_LINK_CONTROL, 0x001F)
#define HCI_READ_LMP_HANDLE							HCI_OPCODE(OGF_LINK_CONTROL, 0x0020)
#define HCI_SETUP_SYNCHRONOUS_CONNECTION			HCI_OPCODE(OGF_LINK_CONTROL, 0x0028)
#define HCI_ACCEPT_SYNCH_CONNECTION_REQUEST			HCI_OPCODE(OGF_LINK_CONTROL, 0x0029)
#define HCI_REJECT_SYNCH_CONNECTION_REQUEST			HCI_OPCODE(OGF_LINK_CONTROL, 0x002A)
#define HCI_IO_CAPABILITY_REQUEST_REPLY				HCI_OPCODE(OGF_LINK_CONTROL, 0x002B)
#define HCI_USER_CONFIRMATION_REQUEST_REPLY			HCI_OPCODE(OGF_LINK_CONTROL, 0x002C)
#define HCI_USER_CONFIRMATION_REQ_NEGATIVE_REPLY	HCI_OPCODE(OGF_LINK_CONTROL, 0x002D)
#define HCI_USER_PASSKEY_REQUEST_REPLY				HCI_OPCODE(OGF_LINK_CONTROL, 0x002E)
#define HCI_USER_PASSKEY_REQUEST_NEGATIVE_REPLY		HCI_OPCODE(OGF_LINK_CONTROL, 0x002F)
#define HCI_REMOTE_OOB_DATA_REQUEST_REPLY			HCI_OPCODE(OGF_LINK_CONTROL, 0x0030)
#define HCI_REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY	HCI_OPCODE(OGF_LINK_CONTROL, 0x0033)
#define HCI_IO_CAPABILITY_REQUEST_NEGATIVE_REPLY	HCI_OPCODE(OGF_LINK_CONTROL, 0x0034)

// Link policy commands

#define HCI_HOLD_MODE								HCI_OPCODE(OGF_LINK_POLICY, 0x0001)
#define HCI_SNIFF_MODE								HCI_OPCODE(OGF_LINK_POLICY, 0x0003)
#define HCI_EXIT_SNIFF_MODE							HCI_OPCODE(OGF_LINK_POLICY, 0x0004)
#define HCI_PARK_STATE								HCI_OPCODE(OGF_LINK_POLICY, 0x0005)
#define HCI_EXIT_PARK_STATE							HCI_OPCODE(OGF_LINK_POLICY, 0x0006)
#define HCI_QOS_SETUP								HCI_OPCODE(OGF_LINK_POLICY, 0x0007)
#define HCI_ROLE_DISCOVERY							HCI_OPCODE(OGF_LINK_POLICY, 0x0009)
#define HCI_SWITCH_ROLE								HCI_OPCODE(OGF_LINK_POLICY, 0x000B)
#define HCI_READ_LINK_POLICY_SETTINGS				HCI_OPCODE(OGF_LINK_POLICY, 0x000C)
#define HCI_WRITE_LINK_POLICY_SETTINGS				HCI_OPCODE(OGF_LINK_POLICY, 0x000D)
#define HCI_READ_DEFAULT_POLICY_SETTINGS			HCI_OPCODE(OGF_LINK_POLICY, 0x000E)
#define HCI_WRITE_DEFAULT_POLICY_SETTINGS			HCI_OPCODE(OGF_LINK_POLICY, 0x000F)
#define HCI_FLOW_SPECIFICATION						HCI_OPCODE(OGF_LINK_POLICY, 0x0010)
#define HCI_SNIFF_SUBRATING							HCI_OPCODE(OGF_LINK_POLICY, 0x0011)

// Controller & Baseband commands

#define HCI_SET_EVENT_MASK							HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0001)
#define HCI_RESET									HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0003)
#define HCI_SET_EVENT_FILTER						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0005)
#define HCI_FLUSH									HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0008)
#define HCI_READ_PIN_TYPE							HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0009)
#define HCI_WRITE_PIN_TYPE							HCI_OPCODE(OGF_CTRL_BASEBAND, 0x000A)
#define HCI_CREATE_NEW_UNIT_KEY						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x000B)
#define HCI_READ_STORED_LINK_KEY					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x000D)
#define HCI_WRITE_STORED_LINK_KEY					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0011)
#define HCI_DELETE_STORED_LINK_KEY					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0012)
#define HCI_WRITE_LOCAL_NAME						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0013)
#define HCI_READ_LOCAL_NAME							HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0014)
#define HCI_READ_CONNECTION_ACCEPT_TIMEOUT			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0015)
#define HCI_WRITE_CONNECTION_ACCEPT_TIMEOUT			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0016)
#define HCI_READ_PAGE_TIMEOUT						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0017)
#define HCI_WRITE_PAGE_TIMEOUT						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0018)
#define HCI_READ_SCAN_ENABLE						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0019)
#define HCI_WRITE_SCAN_ENABLE						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x001A)
#define HCI_READ_PAGE_SCAN_ACTIVITY					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x001B)
#define HCI_WRITE_PAGE_SCAN_ACTIVITY				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x001C)
#define HCI_READ_INQUIRY_SCAN_ACTIVITY				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x001D)
#define HCI_WRITE_INQUIRY_SCAN_ACTIVITY				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x001E)
#define HCI_READ_AUTHENTICATION_ENABLE				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x001F)
#define HCI_WRITE_AUTHENTICATION_ENABLE				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0020)
#define HCI_READ_ENCRYPTION_MODE					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0021)
#define HCI_WRITE_ENCRYPTION_MODE					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0022)
#define HCI_READ_CLASS_OF_DEVICE					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0023)
#define HCI_WRITE_CLASS_OF_DEVICE					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0024)
#define HCI_READ_VOICE_SETTING						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0025)
#define HCI_WRITE_VOICE_SETTING						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0026)
#define HCI_READ_AUTOMATIC_FLASH_TIMEOUT			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0027)
#define HCI_WRITE_AUTOMATIC_FLASH_TIMEOUT			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0028)
#define HCI_READ_NUM_BROADCST_RETR					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0029)
#define HCI_WRITE_NUM_BROADCST_RETR					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x002A)
#define HCI_READ_HOLD_MODE_ACTIVITY					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x002B)
#define HCI_WRITE_HOLD_MODE_ACTIVITY				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x002C)
#define HCI_READ_TRANSMIT_POWER_LEVEL				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x002D)
#define HCI_READ_SYNC_FLOW_CONTROL_ENABLE			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x002E)
#define HCI_WRITE_SYNC_FLOW_CONTROL_ENABLE			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x002F)
#define HCI_SET_CTRL_TO_HOST_FLOW_CONTROL			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0031)
#define HCI_HOST_BUFFER_SIZE						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0033)
#define HCI_HOST_NUM_OF_COMPLETED_PACKETS			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0035)
#define HCI_READ_LINK_SUPERVISION_TIMEOUT			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0036)
#define HCI_WRITE_LINK_SUPERVISION_TIMEOUT			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0037)
#define HCI_READ_NUM_OF_SUPPORTED_IAC				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0038)
#define HCI_READ_CURRENT_IAC_LAP					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0039)
#define HCI_WRITE_CURRENT_IAC_LAP					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x003A)
#define HCI_READ_PAGE_SCAN_PERIOD_MODE				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x003B)
#define HCI_WRITE_PAGE_SCAN_PERIOD_MODE				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x003C)
#define HCI_SET_AFH_HOST_CHANNEL_CLASSIFICATION		HCI_OPCODE(OGF_CTRL_BASEBAND, 0x003F)
#define HCI_READ_INQUIRY_SCAN_TYPE					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0042)
#define HCI_WRITE_INQUIRY_SCAN_TYPE					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0043)
#define HCI_READ_INQUIRY_MODE						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0044)
#define HCI_WRITE_INQUIRY_MODE						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0045)
#define HCI_READ_PAGE_SCAN_TYPE						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0046)
#define HCI_WRITE_PAGE_SCAN_TYPE					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0047)
#define HCI_READ_AFH_CHANNEL_ASSESSMENT_MODE		HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0048)
#define HCI_WRITE_AFH_CHANNEL_ASSESSMENT_MODE		HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0049)
#define HCI_READ_EXTENDED_INQUIRY_RESPONSE			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0051)
#define HCI_WRITE_EXTENDED_INQUIRY_RESPONSE			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0052)
#define HCI_READ_REFRESH_ENCRYPTION_KEY				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0053)
#define HCI_READ_SIMPLE_PAIRING_MODE				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0055)
#define HCI_WRITE_SIMPLE_PAIRING_MODE				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0056)
#define HCI_READ_LOCAL_OOB_DATA						HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0057)
#define HCI_READ_INQUIRY_RESPONSE_TX_POWER_LEVEL	HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0058)
#define HCI_WRITE_INQUIRY_TX_POWER_LEVEL			HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0059)
#define HCI_READ_DEFAULT_ERRONEOUS_DATA_REPORTING	HCI_OPCODE(OGF_CTRL_BASEBAND, 0x005A)
#define HCI_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING	HCI_OPCODE(OGF_CTRL_BASEBAND, 0x005B)
#define HCI_ENHANCED_FLUSH							HCI_OPCODE(OGF_CTRL_BASEBAND, 0x005F)
#define HCI_SEND_KEY_PRESS_NOTIFICATION				HCI_OPCODE(OGF_CTRL_BASEBAND, 0x0060)
#define HCI_READ_LE_HOST_SUPPORT					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x006C)
#define HCI_WRITE_LE_HOST_SUPPORT					HCI_OPCODE(OGF_CTRL_BASEBAND, 0x006D)

// Informational Parameters

#define HCI_READ_LOCAL_VERSION_INFORMATION			HCI_OPCODE(OGF_INFORMATION, 0x0001)
#define HCI_READ_LOCAL_SUPPORTED_COMMANDS			HCI_OPCODE(OGF_INFORMATION, 0x0002)
#define HCI_READ_LOCAL_SUPPORTED_FEATURES			HCI_OPCODE(OGF_INFORMATION, 0x0003)
#define HCI_READ_LOCAL_EXTENDED_FEATURES			HCI_OPCODE(OGF_INFORMATION, 0x0004)
#define HCI_READ_BUFFER_SIZE						HCI_OPCODE(OGF_INFORMATION, 0x0005)
#define HCI_READ_BD_ADDR							HCI_OPCODE(OGF_INFORMATION, 0x0009)

// Status Parameters

#define HCI_READ_FAILED_CONTACT_COUNTER				HCI_OPCODE(OGF_STATUS, 0x0001)
#define HCI_RESET_FAILED_CONTACT_COUNTER			HCI_OPCODE(OGF_STATUS, 0x0002)
#define HCI_READ_LINK_QUALITY						HCI_OPCODE(OGF_STATUS, 0x0003)
#define HCI_READ_RSSI								HCI_OPCODE(OGF_STATUS, 0x0005)
#define HCI_READ_AFH_CHANNEL_MAP					HCI_OPCODE(OGF_STATUS, 0x0006)
#define HCI_READ_CLOCK_COMMAND						HCI_OPCODE(OGF_STATUS, 0x0007)

// Testing Commands

#define HCI_READ_LOOPBACK_MODE						HCI_OPCODE(OGF_TESTING, 0x0001)
#define HCI_WRITE_LOOPBACK_MODE						HCI_OPCODE(OGF_TESTING, 0x0002)
#define HCI_ENABLE_DEVICE_UNDER_TEST_MODE			HCI_OPCODE(OGF_TESTING, 0x0003)
#define HCI_WRITE_SIMPLE_PAIRING_DEBUG_MODE			HCI_OPCODE(OGF_TESTING, 0x0004)

// LE controller commands

#define HCI_LE_SET_EVENT_MASK						HCI_OPCODE(OGF_LE, 0x0001)
#define HCI_LE_READ_BUFFER_SIZE						HCI_OPCODE(OGF_LE, 0x0002)
#define HCI_LE_READ_LOCAL_SUPPORTED_FEATURES		HCI_OPCODE(OGF_LE, 0x0003)
#define HCI_LE_SET_RANDOM_ADDRESS					HCI_OPCODE(OGF_LE, 0x0005)
#define HCI_LE_SET_ADVERTISING_PARAMETERS			HCI_OPCODE(OGF_LE, 0x0006)
#define HCI_LE_READ_ADVERTISING_CHANNEL_TX_POWER	HCI_OPCODE(OGF_LE, 0x0007)
#define HCI_LE_SET_ADVERTISING_DATA					HCI_OPCODE(OGF_LE, 0x0008)
#define HCI_LE_SET_SCAN_RESPONSE_DATA				HCI_OPCODE(OGF_LE, 0x0009)
#define HCI_LE_SET_ADVERTISE_ENABLE					HCI_OPCODE(OGF_LE, 0x000A)
#define HCI_LE_SET_SCAN_PARAMETERS					HCI_OPCODE(OGF_LE, 0x000B)
#define HCI_LE_SET_SCAN_ENABLE						HCI_OPCODE(OGF_LE, 0x000C)
#define HCI_LE_CREATE_CONNECTION					HCI_OPCODE(OGF_LE, 0x000D)
#define HCI_LE_CREATE_CONNECTION_CANCEL				HCI_OPCODE(OGF_LE, 0x000E)
#define HCI_LE_READ_WHITE_LIST_SIZE					HCI_OPCODE(OGF_LE, 0x000F)
#define HCI_LE_CLEAR_WHITE_LIST						HCI_OPCODE(OGF_LE, 0x0010)
#define HCI_LE_ADD_DEVICE_TO_WHITE_LIST				HCI_OPCODE(OGF_LE, 0x0011)
#define HCI_LE_REMOVE_DEVICE_FROM_WHITE_LIST		HCI_OPCODE(OGF_LE, 0x0012)
#define HCI_LE_CONNECTION_UPDATE					HCI_OPCODE(OGF_LE, 0x0013)
#define HCI_LE_SET_HOST_CHANNEL_CLASSIFICATION		HCI_OPCODE(OGF_LE, 0x0014)
#define HCI_LE_READ_CHANNEL_MAP						HCI_OPCODE(OGF_LE, 0x0015)
#define HCI_LE_READ_REMOTE_USED_FEATURES			HCI_OPCODE(OGF_LE, 0x0016)
#define HCI_LE_ENCRYPT								HCI_OPCODE(OGF_LE, 0x0017)
#define HCI_LE_RAND									HCI_OPCODE(OGF_LE, 0x0018)
#define HCI_LE_START_ENCRYPTION						HCI_OPCODE(OGF_LE, 0x0019)
#define HCI_LE_LONG_TERM_KEY_REQUEST_REPLY			HCI_OPCODE(OGF_LE, 0x001A)
#define HCI_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY	HCI_OPCODE(OGF_LE, 0x001B)
#define HCI_LE_READ_SUPPORTED_STATES				HCI_OPCODE(OGF_LE, 0x001C)
#define HCI_LE_RECEIVE_TEST							HCI_OPCODE(OGF_LE, 0x001D)
#define HCI_LE_TRANSMITTER_TEST						HCI_OPCODE(OGF_LE, 0x001E)
#define HCI_LE_TEST_END								HCI_OPCODE(OGF_LE, 0x001F)

// Events

#define HCI_EVT_INQUIRY_COMPLETE				0x01
#define HCI_EVT_INQUIRY_RESULT					0x02
#define HCI_EVT_CONNECTION_COMPLETE				0x03
#define HCI_EVT_CONNECTION_REQUEST				0x04
#define HCI_EVT_DISCONNECTION_COMPLETE			0x05
#define HCI_EVT_AUTHENTICATION_COMPLETE			0x06
#define HCI_EVT_REMOTE_NAME_REQUEST_COMPLETE	0x07
#define HCI_EVT_ENCRYPTION_CHANGE				0x08
#define HCI_EVT_CHANGE_CONN_LINK_COMPLETE		0x09
#define HCI_EVT_MASTER_LINK_KEY_COMPLETE		0x0A
#define HCI_EVT_READ_RMT_SUP_FEATURES_COMP		0x0B
#define HCI_EVT_READ_RMT_VERSION_INFO_COMP		0x0C
#define HCI_EVT_QOS_SETUP_COMPLETE				0x0D
#define HCI_EVT_COMMAND_COMPLETE				0x0E
#define HCI_EVT_COMMAND_STATUS					0x0F
#define HCI_EVT_HARDWARE_ERROR					0x10
#define HCI_EVT_FLUSH_OCCURED					0x11
#define HCI_EVT_ROLE_CHANGE						0x12
#define HCI_EVT_NUM_OF_COMPLETED_PACKETS		0x13
#define HCI_EVT_MODE_CHANGE						0x14
#define HCI_EVT_RETURN_LINK_KEYS				0x15
#define HCI_EVT_PIN_CODE_REQUEST				0x16
#define HCI_EVT_LINK_KEY_REQUEST				0x17
#define HCI_EVT_LINK_KEY_NOTIFICATION			0x18
#define HCI_EVT_LOOPBACK_COMMAND				0x19
#define HCI_EVT_DATA_BUFFER_OVERFLOW			0x1A
#define HCI_EVT_MAX_SLOTS_CHANGE				0x1B
#define HCI_EVT_READ_CLOCK_OFFSET_COMPLETE		0x1C
#define HCI_EVT_CONN_PACKET_TYPE_CHANGED		0x1D
#define HCI_EVT_QOS_VIOLATION					0x1E
#define HCI_EVT_PAGE_SCAN_REPET_MODE_CHANGE		0x20
#define HCI_EVT_FLOW_SPECIFICATION_COMPLETE		0x21
#define HCI_EVT_INQUIRY_RESULT_WITH_RSSI		0x22
#define HCI_EVT_READ_RMT_EXT_FEATURES_COMP		0x23
#define HCI_EVT_SYNCH_CONNECTION_COMPLETE		0x2C
#define HCI_EVT_SYNCH_CONNECTION_CHANGED		0x2D
#define HCI_EVT_SNIFF_SUBRATING					0x2E
#define HCI_EVT_EXTENDED_INQUIRY_RESULT			0x2F
#define HCI_EVT_ENCRYPTION_KEY_REFRESH_COMPLETE	0x30
#define HCI_EVT_IO_CAPABILITY_REQUEST			0x31
#define HCI_EVT_IO_CAPABILITY_RESPONSE			0x32
#define HCI_EVT_USER_CONFIRMATION_REQUEST		0x33
#define HCI_EVT_USER_PASSKEY_REQUEST			0x34
#define HCI_EVT_REMOTE_OOB_DATA_REQUEST			0x35
#define HCI_EVT_SIMPLE_PAIRING_COMPLETE			0x36
#define HCI_EVT_LINK_SUPERVISION_TO_CHANGED		0x38
#define HCI_EVT_ENHANCED_FLUSH_COMPLETE			0x39
#define HCI_EVT_USER_PASSKEY_NOTIFICATION		0x3B
#define HCI_EVT_KEYPRESS_NOTIFICATION			0x3C
#define HCI_EVT_RMT_HOST_SUPP_FEATURES_NTF		0x3D
#define HCI_EVT_LE_META_EVENT					0x3E
#define HCI_EVT_LAST							HCI_EVT_LE_META_EVENT
#define HCI_EVT_FIRST							HCI_EVT_INQUIRY_COMPLETE

// Used in bt_hci_ctrl_register_event_listener
// to indicate that the listener is called
// for all HCI events (excluding dotstack internal ones)
#define HCI_EVT_ALL_HCI_EVENTS                  0xffff

// dotstack internal events
#define HCI_EVT_CMD_SEND_STARTED                0xff00
#define HCI_EVT_CMD_SEND_FINISHED               0xff01
#define HCI_EVT_LINK_IS_IDLE                    0xff02
#define HCI_EVT_LINK_IS_BUSY                    0xff03

#define HCI_EVT_COMMAND_COMPLETE_PARAM_LEN	3

#define HCI_CMD_STATUS_PENDING				0
#define HCI_CMD_STATUS_WAITING_RESPONSE		1
#define HCI_CMD_STATUS_BEING_SENT			2

#define HCI_DATA_STATUS_PENDING				0
#define HCI_DATA_STATUS_BEING_SENT			2

#define HCI_PARAM_TYPE_BYTE				0
#define HCI_PARAM_TYPE_INT				1
#define HCI_PARAM_TYPE_LONG				2
#define HCI_PARAM_TYPE_BD_ADDR			4
#define HCI_PARAM_TYPE_HANDLE			5
#define HCI_PARAM_TYPE_DEV_CLASS		6
#define HCI_PARAM_TYPE_STRING			7

#define HCI_PARAM_LEN_BYTE				1
#define HCI_PARAM_LEN_INT				2
#define HCI_PARAM_LEN_LONG				4
#define HCI_PARAM_LEN_BD_ADDR			6
#define HCI_PARAM_LEN_HANDLE			4
#define HCI_PARAM_LEN_DEV_CLASS			3


#define HCI_PACKET_BOUNDARY_FIRST_NO_AUTO_FLUSH	0x0
#define HCI_PACKET_BOUNDARY_CONTINUE			0x1
#define HCI_PACKET_BOUNDARY_FIRST				0x2
#define HCI_PACKET_BOUNDARY_FIRST_AUTO_FLUSH	0x2
#define HCI_PACKET_BOUNDARY_RESERVED2			0x3

#define HCI_H2C_BROADCAST_NO_BROADCATS		0x0
#define HCI_H2C_BROADCAST_ACTIVE_SLAVE		0x1
#define HCI_H2C_BROADCAST_PARCKED_SLAVE		0x2
#define HCI_H2C_BROADCAST_RESERVED			0x3

#define HCI_C2H_BROADCAST_P2P					0x0
#define HCI_C2H_BROADCAST_NOT_PARCKED_SLAVE		0x1
#define HCI_C2H_BROADCAST_PARCKED_SLAVE			0x2
#define HCI_C2H_BROADCAST_RESERVED				0x3

#define HCI_CMD_HEADER_LEN		    3
#ifndef HCI_MAX_PARAM_LEN
#define HCI_MAX_PARAM_LEN		    248
#endif
#define HCI_MAX_EVENT_PARAM_LEN		255

#define HCI_WRITE_LOCAL_NAME_PARAM_LEN	248
#define HCI_WRITE_EXTENDED_INQUIRY_RESPONSE_PARAM_LEN	241

#define HCI_LE_MAX_AD_LEN    31

#define HCI_ACL_DATA_HEADER_LEN	4

#define HCI_SCO_DATA_HEADER_LEN	3
#define HCI_SCO_MAX_DATA_LEN	255

#define HCI_PACKET_TYPE_NONE			0x00
#define HCI_PACKET_TYPE_COMMAND			0x01
#define HCI_PACKET_TYPE_ACL_DATA		0x02
#define HCI_PACKET_TYPE_SCO_DATA		0x03
#define HCI_PACKET_TYPE_EVENT			0x04

#define HCI_PAGE_SCAN_REPETITION_MODE_R0	0x00
#define HCI_PAGE_SCAN_REPETITION_MODE_R1	0x01
#define HCI_PAGE_SCAN_REPETITION_MODE_R2	0x02

#define HCI_ROLE_SWITCH_DISALLOW	0x00
#define HCI_ROLE_SWITCH_ALLOW		0x01

#define HCI_ENCRYPTION_OFF			0x00
#define HCI_ENCRYPTION_ON			0x01

#define HCI_DISCOVERABLE			0x01
#define HCI_CONNECTABLE				0x02

#define HCI_MAX_PIN_LENGTH	8

#define HCI_LINK_KEY_LEN				16
#define HCI_LINK_KEY_TYPE_COMBINATION	0x00
#define HCI_LINK_KEY_TYPE_LOCAL_UNIT	0x01
#define HCI_LINK_KEY_TYPE_REMOTE_UNIT	0x02

#define HCI_BB_PACKET_TYPE_NO_2_DH1		0x0002
#define HCI_BB_PACKET_TYPE_NO_3_DH1		0x0004
#define HCI_BB_PACKET_TYPE_DM1			0x0008
#define HCI_BB_PACKET_TYPE_DH1			0x0010
#define HCI_BB_PACKET_TYPE_NO_2_DH3		0x0100
#define HCI_BB_PACKET_TYPE_NO_3_DH3		0x0200
#define HCI_BB_PACKET_TYPE_DM3			0x0400
#define HCI_BB_PACKET_TYPE_DH3			0x0800
#define HCI_BB_PACKET_TYPE_NO_2_DH5		0x1000
#define HCI_BB_PACKET_TYPE_NO_3_DH5		0x2000
#define HCI_BB_PACKET_TYPE_DM5			0x4000
#define HCI_BB_PACKET_TYPE_DH5			0x8000

#define HCI_POWER_MODE_ACTIVE	0
#define HCI_POWER_MODE_HOLD		1
#define HCI_POWER_MODE_SNIFF	2
#define HCI_POWER_MODE_PARK		3

#define HCI_SCO_TX_BANDWIDTH_DONTCARE	0xFFFFFFFF
#define HCI_SCO_RX_BANDWIDTH_DONTCARE	0xFFFFFFFF
#define HCI_SCO_MAX_LATENCY_DONTCARE	0xFFFF

#define HCI_SCO_CONTENT_FORMAT_INPUT_CODING_LINEAR			0
#define HCI_SCO_CONTENT_FORMAT_INPUT_CODING_N_LAW			0x100
#define HCI_SCO_CONTENT_FORMAT_INPUT_CODING_A_LAW			0x200
#define HCI_SCO_CONTENT_FORMAT_INPUT_FORMAT_1_COMPLEMENT	0
#define HCI_SCO_CONTENT_FORMAT_INPUT_FORMAT_2_COMPLEMENT	0x040
#define HCI_SCO_CONTENT_FORMAT_INPUT_FORMAT_SIGN_MAGNITUDE	0x080
#define HCI_SCO_CONTENT_FORMAT_INPUT_FORMAT_UNSIGNED		0x0C0
#define HCI_SCO_CONTENT_FORMAT_INPUT_SAMPLE_SIZE_8			0x0
#define HCI_SCO_CONTENT_FORMAT_INPUT_SAMPLE_SIZE_16			0x020
#define HCI_SCO_CONTENT_FORMAT_AIR_CODING_CSVD				0x0
#define HCI_SCO_CONTENT_FORMAT_AIR_CODING_N_LAW				0x1
#define HCI_SCO_CONTENT_FORMAT_AIR_CODING_A_LAW				0x2
#define HCI_SCO_CONTENT_FORMAT_AIR_CODING_TRANSPARENT		0x3

#define HCI_SCO_RTX_EFFORT_NO_RETRANSMISSION			0x0
#define HCI_SCO_RTX_EFFORT_OPTIMIZE_POWER_CONSUMPTION	0x1
#define HCI_SCO_RTX_EFFORT_OPTIMIZE_LINK_QUALITY		0x2
#define HCI_SCO_RTX_EFFORT_DONTCARE						0xFF

#define HCI_SCO_PACKET_TYPE_HV1         0x0001
#define HCI_SCO_PACKET_TYPE_HV2         0x0002
#define HCI_SCO_PACKET_TYPE_HV3         0x0004
#define HCI_SCO_PACKET_TYPE_EV3         0x0008
#define HCI_SCO_PACKET_TYPE_EV4         0x0010
#define HCI_SCO_PACKET_TYPE_EV5         0x0020
#define HCI_SCO_PACKET_TYPE_NO_2_EV3    0x0040
#define HCI_SCO_PACKET_TYPE_NO_3_EV3    0x0080
#define HCI_SCO_PACKET_TYPE_NO_2_EV5    0x0100
#define HCI_SCO_PACKET_TYPE_NO_3_EV5    0x0200


#define HCI_SCO_PACKET_TYPE_ALL	0xFFFF
	
#define HCI_LINK_POLICY_ENABLE_ROLE_SWITCH    0x0001
#define HCI_LINK_POLICY_ENABLE_HOLD_MODE      0x0002
#define HCI_LINK_POLICY_ENABLE_SNIFF_MODE     0x0004
#define HCI_LINK_POLICY_ENABLE_PARK_STATE     0x0008
#define HCI_LINK_POLICY_ENABLE_ALL            0x000F

#define HCI_INQUIRY_MODE_STANDARD	0
#define HCI_INQUIRY_MODE_WITH_RSSI	1
#define HCI_INQUIRY_MODE_EXTENDED	2

#define HCI_CONTROLLER	_phci_ctrl

// Flags for HCI_READ_SCAN_ENABLE/HCI_WRITE_SCAN_ENABLE
#define HCI_SCAN_INQUIRY  0x01
#define HCI_SCAN_PAGE     0x02

#define HCI_SEND_DATA_STATUS_SUCCESS        0
#define HCI_SEND_DATA_STATUS_INTERRUPTED    1

// Default value for acl_config parameter of bt_hci_connect()
#define HCI_DEFAULT_ACL_CONFIG              0

#define HCI_DISCOVERABLE_MODE_GENERAL       0
#define HCI_DISCOVERABLE_MODE_LIMITED       1

struct _bt_hci_ctrl_state_s;
struct _bt_hci_command_s;
struct _bt_hci_event_s;
struct _bt_hci_data_s;

typedef bt_int bt_hci_hconn_t, *bt_hci_hconn_p;

typedef struct _bt_hci_conn_state_s bt_hci_conn_state_t, *bt_hci_conn_state_p;

typedef struct _hci_param {
	bt_int type;
	bt_int param_len;
	union {
		bt_byte b;
		bt_int  i;
		bt_long l;
		bt_bdaddr_t bdaddr;
		bt_hci_hconn_t h;
		bt_long dc;
		char *ps;
	} data;
} bt_hci_param_t, *bt_hci_param_p;

typedef void (*bt_hci_cmd_callback_fp) (bt_int, struct _bt_hci_command_s*, struct _bt_hci_event_s*);
typedef void (*bt_hci_event_listener_fp)(bt_int evcode, void* evt_params, void* cb_param);

typedef struct _bt_hci_command_s 
{
	struct _bt_hci_command_s* next_cmd;
	bt_int opcode;
	bt_int params_len;
	bt_byte* params;
	bt_hci_cmd_callback_fp callback;
	void* callback_param;
#ifdef _DEBUG
	bt_int packetNum;
#endif
} bt_hci_command_t, *bt_hci_command_p;

typedef struct _bt_hci_event_s 
{
	bt_int evcode;
	bt_int params_len;
	bt_byte* params;
} bt_hci_event_t, *bt_hci_event_p;

typedef void (*bt_hci_data_callback_fp)(bt_byte status, struct _bt_hci_data_s*);

typedef struct _bt_hci_data_s 
{
	struct _bt_hci_data_s* next_data;
	bt_hci_hconn_t hconn;
	bt_uint data_len;
	bt_byte_p pdata;
	bt_uint pos;
	bt_byte link_type;
	bt_hci_data_callback_fp callback;
	void *param;
#ifdef _DEBUG
	bt_int packetNum;
#endif
} bt_hci_data_t, *bt_hci_data_p;

typedef struct _bt_hci_inquiry_response_t
{
	bt_bdaddr_t bdaddr;
	bt_byte pg_scan_rpt_mode;
	bt_byte pg_scan_period_mode;
	bt_long cod;
	bt_int clock_offset;
	bt_byte rssi;
	bt_byte* eir;
	bt_byte eir_len;
} bt_hci_inquiry_response_t;

/**
* Summary:  Allocate and initialize an HCI command structure.
*
*/
bt_hci_command_p bt_hci_alloc_command(bt_int opcode, bt_hci_cmd_callback_fp callback);


/**
* Summary:  Free HCI command.
*
*/
void bt_hci_free_command(bt_hci_command_p cmd);


/**
* Summary:  Allocate and initialize an HCI command structure for a canned (pre-formatted) command.
*
*/
bt_hci_command_p bt_hci_alloc_canned_command(const bt_byte* canned_command, bt_hci_cmd_callback_fp callback);


/**
* Summary:  Add byte parameter to an HCI command
*
*/
bt_bool bt_hci_add_param_byte(bt_hci_command_p pcmd, bt_byte value);

/**
* Summary:  Add int parameter to an HCI command
*
*/
bt_bool bt_hci_add_param_int(bt_hci_command_p pcmd, bt_int value);

/**
* Summary:  Add long parameter to an HCI command
*
*/
bt_bool bt_hci_add_param_long(bt_hci_command_p pcmd, bt_long value);

#define bt_hci_add_param_uint(cmd, value)  bt_hci_add_param_int(cmd, (bt_int)(value))

#define bt_hci_add_param_ulong(cmd, value) bt_hci_add_param_long(cmd, (bt_long)(value))

/**
* Summary:  Add connection handle parameter to an HCI command
*
*/
#define bt_hci_add_param_hconn(pcmd, value)	\
	bt_hci_add_param_int(pcmd, value)

/**
* Summary:  Add BD address parameter to an HCI command
*
*/
bt_bool bt_hci_add_param_bdaddr(bt_hci_command_p pcmd, const bt_bdaddr_t* pbdaddr);

/**
* Summary:  Add string parameter to an HCI command
*
*/
bt_bool bt_hci_add_param_string(bt_hci_command_p pcmd, const char *ps, bt_int len);

/**
* Summary:  Add class of device parameter to an HCI command
*
*/
bt_bool bt_hci_add_param_cod(bt_hci_command_p pcmd, bt_long value);


#define bt_hci_add_param_lap(cmd, lap)  bt_hci_add_param_cod(cmd, lap)

/**
* Summary:  Add link key parameter to an HCI command
*
*/
bt_bool bt_hci_add_param_linkkey(bt_hci_command_p pcmd, const bt_linkkey_t* linkkey);

bt_bool bt_hci_get_param(bt_hci_command_p pcm, bt_hci_param_p pparam, bt_int_p poffset);

/**
* Summary:  Get byte parameter from HCI command
*
*/
bt_bool bt_hci_get_param_byte(bt_hci_command_p pcmd, bt_byte* pvalue, bt_int* offset);

/**
* Summary:  Get int parameter from HCI command
*
*/
bt_bool bt_hci_get_param_int(bt_hci_command_p pcmd, bt_int* pvalue, bt_int* poffset);

/**
* Summary:  Get long parameter from HCI command
*
*/
bt_bool bt_hci_get_param_long(bt_hci_command_p pcmd, bt_long* pvalue, bt_int* poffset);

/**
* Summary:  Get connection handle parameter from HCI command
*
*/
#define bt_hci_get_param_hconn(pcmd, pvalue, poffset)  bt_hci_get_param_int(pcmd, pvalue, poffset)

/**
* Summary:  Get BD address parameter from HCI command
*
*/
bt_bool bt_hci_get_param_bdaddr(bt_hci_command_p pcm, bt_bdaddr_p pvalue, bt_int_p poffset);

/**
* Summary:  Get link key parameter from HCI command
*
*/
bt_bool bt_hci_get_param_linkkey(bt_hci_command_p pcmd, bt_byte_p pvalue, bt_int_p poffset);

/**
* Summary:  Get byte parameter from HCI event
*
*/
bt_bool bt_hci_get_evt_param_byte(bt_hci_event_p pevt, bt_byte* pvalue, bt_int* poffset);

/**
* Summary:  Get int parameter from HCI event
*
*/
bt_bool bt_hci_get_evt_param_int(bt_hci_event_p pevt, bt_int* pvalue, bt_int* poffset);

#ifdef BT_DO_NOT_USE_TYPE_CAST_MACROS
	bt_bool bt_hci_get_evt_param_uint(bt_hci_event_p pevt, bt_uint* pvalue, bt_int* poffset);
#else
	#define bt_hci_get_evt_param_uint(pevt, pvalue, poffset) bt_hci_get_evt_param_int(pevt, (bt_int*)pvalue, poffset)
#endif

/**
* Summary:  Get long parameter from HCI event
*
*/
bt_bool bt_hci_get_evt_param_long(bt_hci_event_p pevt, bt_long* pvalue, bt_int* poffset);

#ifdef BT_DO_NOT_USE_TYPE_CAST_MACROS
	bt_bool bt_hci_get_evt_param_ulong(bt_hci_event_p pevt, bt_ulong* pvalue, bt_int* poffset);
#else
	#define bt_hci_get_evt_param_ulong(pevt, pvalue, poffset) bt_hci_get_evt_param_long(pevt, (bt_long*)pvalue, poffset)
#endif

/**
* Summary:  Get connection handle parameter from HCI event
*
*/
#define bt_hci_get_evt_param_hconn(pevt, pvalue, poffset)	\
	bt_hci_get_evt_param_int(pevt, pvalue, poffset)

/**
* Summary:  Get bd address parameter from HCI event
*
*/
bt_bool bt_hci_get_evt_param_bdaddr(bt_hci_event_p pevt, bt_bdaddr_p pvalue, bt_int_p poffset);

/**
* Summary:  Get class of device parameter from HCI event
*
*/
bt_bool bt_hci_get_evt_param_devclass(bt_hci_event_p pevt, bt_long_p pvalue, bt_int_p poffset);

/**
* Summary:  Get link key parameter from HCI event
*
*/
bt_bool bt_hci_get_evt_param_linkkey(bt_hci_event_p pevt, bt_linkkey_p pvalue, bt_int_p poffset);


/**
 * Summary:  HCI initialization callback.
 * , Functional Group:  hci
 *
 * Description:  This typedef defines a function pointer type for the HCI initailization callback
 * functions. Such a function must be passed to the hci_init() function.
 *
 * Parameters:  success - Specifies whether HCI initialization succeeded or not.
 */
typedef void (*bt_hci_start_callback_fp)(bt_bool success, void* param);


typedef void (*bt_hci_stop_callback_fp)(void* param);


void bt_hci_init(void);

/**
 * Summary:  Initialize HCI layer.
 * , Functional Group:  hci
 *
 * Description:  This function initializes the HCI layer of the stack. Upon completion of initialization
 * the callback function passed in the callback parameter is called.
 *
 * Parameters:  callback - Completion callback. Called when initialization is complete.
 *
 * Returns:
 *         -  TRUE when the function succeeds.
 *         -  FALSE otherwise. The callback function is not called in this case.
 *
 */
bt_bool bt_hci_start(bt_hci_start_callback_fp callback, void* callback_param, bt_byte enable_scan);


void bt_hci_start_no_init(void);


void bt_hci_stop(bt_hci_stop_callback_fp callback, void* callback_param);

/**
 * Summary:  HCI connect callback.
 * , Functional Group:  hci
 *
 * Description:  This typedef defines a type for the callback function that is called when HCI connect operation
 * initiated by a call to hci_init() is complete.
 *
 * Parameters:  status - Operation status. It is 0 if connection was successfully established.
 *   pconn - pointer to a structure representing the established connection.
 *   param - pointer to arbitrary data passed to the hci_connect() function through its param parameter.
 *
 */
typedef void (*bt_hci_connect_callback_fp)(bt_byte status, bt_hci_conn_state_t *pconn, void* param);

typedef void (*bt_hci_disconnect_callback_fp)(bt_byte status, bt_byte reason, bt_hci_conn_state_t *pconn, void* param);

/**
 * Summary:  Connect to a remote device.
 * , Functional Group:  hci
 *
 * Description:  This function tries to establish an HCI connection with a remote device specified by the
 * Bluetooth address dest. Upon completion, the callback function specified by the callback parameter
 * is called.
 *
 * Parameters:  dest - Bluetooth address of the remote device.
 *   packet_type -
 *   role_switch -
 *   acl_config -
 *   callback - Pointer to a callback function that is called when the connect operation completes.
 *   param - Pointer to arbitrary data that is to be passed to the callback function.
 *
 * Returns:
 *         -  TRUE when the function succeeds.
 *         -  FALSE otherwise. The callback function is not called in this case.
 *
 */
bt_bool bt_hci_connect(bt_bdaddr_p dest,
	bt_uint packet_type, bt_byte pg_scan_rpt_mode,
	bt_byte role_switch, bt_uint acl_config,
	bt_hci_connect_callback_fp callback, void* param);

/**
 * Summary:  Listen for incoming connections.
 * , Functional Group:  hci
 *
 * Description:
 *
 */
bt_bool bt_hci_listen(bt_hci_connect_callback_fp cb, void* param);

bt_bool bt_hci_listen_sco(
   bt_ulong tx_bandwidth,
   bt_ulong rcv_bandwidth,
   bt_uint max_latency,
   bt_uint content_format,
   bt_byte retransmission_effort,
   bt_uint packet_type,
   bt_hci_connect_callback_fp cb, void *param);

bt_bool bt_hci_connect_sco(
	bt_hci_conn_state_t* pconn,
	bt_ulong tx_bandwidth,
	bt_ulong rcv_bandwidth,
	bt_uint max_latency,
	bt_uint content_format,
	bt_byte retransmission_effort,
	bt_uint packet_type,
	bt_hci_connect_callback_fp cb, void *param);

/**
 * Summary:  Abort connection
 * , Functional Group:  hci
 *
 */
bt_bool bt_hci_disconnect(bt_hci_conn_state_t *pconn);


typedef void (*bt_hci_inquiry_callback_fp)(bt_byte status, bt_hci_inquiry_response_t* response);

/**
* Summary:  Start inquiry
*
*/
bt_bool bt_hci_find_devices(bt_byte max_responses, bt_byte length, bt_hci_inquiry_callback_fp cb);

bt_bool bt_hci_find_devices_ex(
	bt_byte max_responses, bt_byte length, bt_byte mode,
	bt_hci_inquiry_callback_fp cb);

/**
* Summary:  Stop inquiry
*
*/
bt_bool bt_hci_cancel_find_devices(bt_hci_cmd_callback_fp cb);

typedef void (*bt_hci_request_remote_name_callback_fp)(bt_bdaddr_p pdbaddr, const char* name);

/**
* Summary:  Request remote device's name
*
*/
bt_bool bt_hci_request_remote_name(bt_bdaddr_p pbdaddr, bt_byte pg_scan_rpt_mode, bt_int clock_offset, bt_hci_request_remote_name_callback_fp cb);

/**
* Summary:  Cancel remote device name request
*
*/
bt_bool bt_hci_cancel_request_remote_name(bt_bdaddr_p pbdaddr);

/**
* Summary:  Change local device's role
*
*/
bt_bool bt_hci_role_change_ex(bt_bdaddr_p pbdaddr, bt_byte role, bt_hci_cmd_callback_fp cb, void* cb_param);
#define bt_hci_role_change(pbdaddr, role, cb) bt_hci_role_change_ex(pbdaddr, role, cb, NULL)

bt_bool bt_hci_authenticate_ex(bt_hci_conn_state_t *pconn, bt_hci_cmd_callback_fp cb, void* cb_param);
#define bt_hci_authenticate(pconn, cb)    bt_hci_authenticate_ex(pconn, cb, NULL)

/**
* Summary:  Set connection encryption
*
*/

bt_bool bt_hci_set_encryption_ex(bt_hci_conn_state_t* pconn, bt_byte encryption_enable, bt_hci_cmd_callback_fp cb, void* cb_param);
#define bt_hci_set_encryption(pconn, encryption_enable, cb)    bt_hci_set_encryption_ex(pconn, encryption_enable, cb, NULL)


typedef void (*pf_hci_sleep_callback)(bt_bool status);
typedef void (*pf_hci_wakeup_callback)(bt_bool status);


/**
* Summary:  Put local device to sleep
*
*/
void hci_sleep(pf_hci_sleep_callback cb);

/**
* Summary:  Awaken local device
*
*/
void hci_wakeup(pf_hci_wakeup_callback cb);

/**
* Summary:  Put local device to sniff mode
*
*/
#define bt_hci_sniff_mode(pconn, min_interval, max_interval, attempt_slots, timeout, cb)	\
	bt_hci_sniff_mode_ex(pconn, min_interval, max_interval, attempt_slots, timeout, cb, NULL)

bt_bool bt_hci_sniff_mode_ex(
	bt_hci_conn_state_t *pconn, bt_int min_interval, bt_int max_interval,
	bt_int attempt_slots, bt_int timeout, bt_hci_cmd_callback_fp cb,
	void* cb_param);

/**
* Summary:  Cancel sniff mode
*
*/
#define bt_hci_exit_sniff_mode(pconn, cb)	bt_hci_exit_sniff_mode_ex(pconn, cb, NULL)

bt_bool bt_hci_exit_sniff_mode_ex(bt_hci_conn_state_t *pconn, bt_hci_cmd_callback_fp cb, void* cb_param);

#define bt_hci_sniff_subrating(pconn, max_latency, min_remote_timeout, min_local_timeout, cb)	\
	bt_hci_sniff_subrating_ex(pconn, max_latency, min_remote_timeout, min_local_timeout, cb, NULL)

bt_bool bt_hci_sniff_subrating_ex(
	bt_hci_conn_state_t* pconn,
	bt_uint max_latency, bt_uint min_remote_timeout,
	bt_uint min_local_timeout,
	bt_hci_cmd_callback_fp cb,
	void* cb_param);

/**
* Summary:  Put local device to park state
*
*/
bt_bool bt_hci_park_state(bt_hci_conn_state_t *pconn, bt_int min_interval, bt_int max_interval, bt_hci_cmd_callback_fp cb);

/**
* Summary:  Exit park state
*
*/
bt_bool bt_hci_exit_park_state(bt_hci_conn_state_t *pconn, bt_hci_cmd_callback_fp cb);

/**
* Summary:  Send a command to local device
*
*/
bt_bool bt_hci_send_cmd(bt_hci_command_p pcmd);

/**
* Summary:  Send data over ACL connection
*
*/
bt_bool bt_hci_send_acl_data(bt_hci_hconn_t h, bt_byte_p pdata, bt_int len, bt_hci_data_callback_fp cb, void *param);


/**
* Summary:  Cancel sending data over ACL connection
*
*/
void bt_hci_cancel_send_acl_data(bt_byte* data);

/**
* Summary:  Send data over SCO connection
*
*/
bt_bool bt_hci_send_sco_data(bt_hci_hconn_t h, bt_byte_p pdata, bt_uint len, bt_hci_data_callback_fp cb, void *param);

/**
* Summary:  Configure inquiry scan activity
*
*/
bt_bool bt_hci_write_inquiry_scan_activity(bt_uint interval, bt_uint window, bt_hci_cmd_callback_fp cb);

/**
* Summary:  Configure inquiry scan type
*
*/
bt_bool bt_hci_write_inquiry_scan_type(bt_byte scanType, bt_hci_cmd_callback_fp cb);

/**
* Summary:  Configure inquiry mode
*
*/
bt_bool bt_hci_write_inquiry_mode(bt_byte scanMode, bt_hci_cmd_callback_fp cb);

typedef void (*bt_hci_read_inquiry_scan_activity_callback_fp)(bt_byte status, bt_uint interval, bt_uint window);
typedef void (*bt_hci_read_inquiry_scan_type_callback_fp)(bt_byte status, bt_byte scanType);
typedef void (*bt_hci_read_inquiry_mode_callback_fp)(bt_byte status, bt_byte mode);

/**
* Summary:  Get current inquiry scan activity configuration
*
*/
bt_bool bt_hci_read_inquiry_scan_activity(bt_hci_read_inquiry_scan_activity_callback_fp cb);

/**
* Summary:  Get current inquiry scan type
*
*/
bt_bool bt_hci_read_inquiry_scan_type(bt_hci_read_inquiry_scan_type_callback_fp cb);

/**
* Summary:  Get current inquiry mode
*
*/
bt_bool bt_hci_read_inquiry_mode(bt_hci_read_inquiry_mode_callback_fp cb);


/**
* Summary:  Configure page scan activity
*
*/
bt_bool bt_hci_write_page_scan_activity(bt_uint interval, bt_uint window, bt_hci_cmd_callback_fp cb);

/**
* Summary:  Configure page timeout
*
*/
bt_bool bt_hci_write_page_timeout(bt_uint timeout, bt_hci_cmd_callback_fp cb);

/**
* Summary:  Configure page scan period mode
*
*/
bt_bool bt_hci_write_page_scan_period_mode(bt_byte mode, bt_hci_cmd_callback_fp cb);

/**
* Summary:  Configure page scan type
*
*/
bt_bool bt_hci_write_page_scan_type(bt_byte scanType, bt_hci_cmd_callback_fp cb);

typedef void (*bt_hci_read_page_scan_activity_callback_fp)(bt_byte status, bt_uint interval, bt_uint window);
typedef void (*bt_hci_read_page_timeout_callback_fp)(bt_byte status, bt_uint timeout);
typedef void (*bt_hci_read_page_scan_period_mode_callback_fp)(bt_byte status, bt_byte mode);
typedef void (*bt_hci_read_page_scan_type_callback_fp)(bt_byte status, bt_byte scanType);

/**
* Summary:  Get current page scan activity configuration
*
*/
bt_bool bt_hci_read_page_scan_activity(bt_hci_read_page_scan_activity_callback_fp cb);

/**
* Summary:  Get current page timeout
*
*/
bt_bool bt_hci_read_page_timeout(bt_hci_read_page_timeout_callback_fp cb);

/**
* Summary:  Get current page scan period mode
*
*/
bt_bool bt_hci_read_page_scan_period_mode(bt_hci_read_page_scan_period_mode_callback_fp cb);

/**
* Summary:  Get current page scan type
*
*/
bt_bool bt_hci_read_page_scan_type(bt_hci_read_page_scan_type_callback_fp cb);

/**
* Summary:  Write local device name
*
*/
bt_bool bt_hci_write_local_name(const char *device_name, bt_hci_cmd_callback_fp cb);

void bt_hci_send_pin_code(bt_bdaddr_p pbdaddr_remote, const char* pincode);

void bt_hci_reject_pin_code(bt_bdaddr_p pbdaddr_remote);

bt_bool bt_hci_send_linkkey(const bt_bdaddr_t* bdaddr_remote, const bt_linkkey_t* link_key, bt_hci_cmd_callback_fp cb);

bt_bool bt_hci_set_scan(
	bt_bool discoverable, bt_ulong discoverable_period, 
	bt_bool connectable, bt_ulong connectable_period, 
	bt_hci_cmd_callback_fp cb);

bt_bool bt_hci_set_scan_ex(
   bt_bool discoverable, bt_ulong discoverable_period, bt_byte discoverable_mode,
   bt_bool connectable, bt_ulong connectable_period, 
   bt_hci_cmd_callback_fp cb);

bt_byte bt_hci_get_last_cmd_status(void);

bt_byte* bt_hci_get_recv_buffer(void);
bt_int bt_hci_get_recv_buffer_len(void);

bt_byte* bt_hci_get_send_buffer(void);
bt_int bt_hci_get_send_buffer_len(void);

bt_bool bt_hci_write_default_link_policy_settings(bt_uint settings, bt_hci_cmd_callback_fp cb);

void bt_hci_set_incoming_connection_role(bt_byte role);

#include "bluetooth/cdbt/utils/buffer.h"
#include "bluetooth/cdbt/utils/bufferutils.h"
#include "bluetooth/cdbt/utils/queue.h"
#include "bluetooth/cdbt/hci/hci_cmd_queue.h"
#include "bluetooth/cdbt/hci/hci_cmd_buffer.h"
#include "bluetooth/cdbt/hci/hci_data_queue.h"
#include "bluetooth/cdbt/hci/hci_data_buffer.h"
#include "bluetooth/cdbt/hci/hci_linkkey_buffer.h"
#include "bluetooth/cdbt/hci/hci_ctrl_state.h"
#include "bluetooth/cdbt/hci/hci_evt_handlers.h"
#include "bluetooth/cdbt/hci/hci_conn_state.h"
#include "bluetooth/cdbt/hci/hci_transport.h"
#include "bluetooth/cdbt/hci/hci_errors.h"
#include "bluetooth/cdbt/hci/hci_eir.h"
#include "bluetooth/cdbt/hci/hci_private.h"

#ifdef __cplusplus
}
#endif

#endif // __HCI_H
