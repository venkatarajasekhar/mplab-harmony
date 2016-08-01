/*********************************************************************
 * File Name: http_print.c
 *
 * Provides callback headers and resolution for user's custom
 * HTTP Application.
 * 
 * This file is automatically generated by the MPFS Utility
 * ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR
 *
 * Software License Agreement
 *
 * Copyright (C) 2012 Microchip Technology Inc.  All rights
 * reserved.
 * Microchip licenses to you the right to use, modify, copy, and distribute
 * software only embedded on a Microchip microcontroller or digital signal 
 * controller that is integrated into your product or third party product
 * (pursuant to the sublicense terms in the accompanying license agreement)

 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/

#include "tcpip/tcpip.h"

void TCPIP_HTTP_Print(HTTP_CONN_HANDLE connHandle,uint32_t callbackID);
void TCPIP_HTTP_Print_ssid(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_currPrivacy(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_currWLAN(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_ipaddr(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_fwver(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_led(HTTP_CONN_HANDLE connHandle,uint16_t);
void TCPIP_HTTP_Print_nextSSID(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_prevSSID(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_prevWLAN(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_nextWLAN(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_scan(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_bssCount(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_valid(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_name(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_privacy(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_wlan(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_strength(HTTP_CONN_HANDLE connHandle);
void TCPIP_HTTP_Print_btn(HTTP_CONN_HANDLE connHandle,uint16_t);

void TCPIP_HTTP_Print(HTTP_CONN_HANDLE connHandle,uint32_t callbackID)
{
    TCP_SOCKET sktHTTP; 
    switch(callbackID)
    {
        case 0x00000000:
			TCPIP_HTTP_FileInclude(connHandle,(const uint8_t*)"header.inc");
			break;
        case 0x00000001:
			TCPIP_HTTP_FileInclude(connHandle,(const uint8_t*)"footer.inc");
			break;
        case 0x00000002:
			TCPIP_HTTP_Print_ssid(connHandle);
			break;
        case 0x00000003:
			TCPIP_HTTP_Print_currPrivacy(connHandle);
			break;
        case 0x00000004:
			TCPIP_HTTP_Print_currWLAN(connHandle);
			break;
        case 0x00000005:
			TCPIP_HTTP_Print_ipaddr(connHandle);
			break;
        case 0x00000006:
			TCPIP_HTTP_Print_fwver(connHandle);
			break;
        case 0x00000007:
			TCPIP_HTTP_Print_led(connHandle,0);
			break;
        case 0x00000008:
			TCPIP_HTTP_Print_nextSSID(connHandle);
			break;
        case 0x00000009:
			TCPIP_HTTP_Print_prevSSID(connHandle);
			break;
        case 0x0000000a:
			TCPIP_HTTP_Print_prevWLAN(connHandle);
			break;
        case 0x0000000b:
			TCPIP_HTTP_Print_nextWLAN(connHandle);
			break;
        case 0x0000000c:
			TCPIP_HTTP_Print_scan(connHandle);
			break;
        case 0x0000000d:
			TCPIP_HTTP_Print_bssCount(connHandle);
			break;
        case 0x0000000e:
			TCPIP_HTTP_Print_valid(connHandle);
			break;
        case 0x0000000f:
			TCPIP_HTTP_Print_name(connHandle);
			break;
        case 0x00000010:
			TCPIP_HTTP_Print_privacy(connHandle);
			break;
        case 0x00000011:
			TCPIP_HTTP_Print_wlan(connHandle);
			break;
        case 0x00000012:
			TCPIP_HTTP_Print_strength(connHandle);
			break;
        case 0x00000013:
			TCPIP_HTTP_Print_led(connHandle,1);
			break;
        case 0x00000014:
			TCPIP_HTTP_Print_led(connHandle,2);
			break;
        case 0x00000015:
			TCPIP_HTTP_Print_btn(connHandle,0);
			break;
        default:
            // Output notification for undefined values
            sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
            TCPIP_TCP_ArrayPut(sktHTTP, (const uint8_t *)"!DEF", 4);
    }
    return;
}

void TCPIP_HTTP_Print_myVariable(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_TCP_Put(sktHTTP, '~');
    return;
}
