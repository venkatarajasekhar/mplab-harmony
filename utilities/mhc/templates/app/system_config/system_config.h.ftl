<#include "/utilities/mhc/templates/freemarker_functions.ftl">
<#include "/bsp/templates/bsp_freemarker_functions.ftl">
<@mhc_expand_list_named name="LIST_APP_FREEMARKER_MACROS"/>
/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version ${CONFIG_MPLAB_HARMONY_VERSION_STRING}
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/
<#if LIST_SYSTEM_CONFIG_H_GLOBAL_INCLUDES?has_content>
<@mhc_expand_list list=LIST_SYSTEM_CONFIG_H_GLOBAL_INCLUDES/>
</#if>
<#if CONFIG_USE_BSP == true>
#include "bsp.h"
</#if>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
<#if LIST_SYSTEM_CONFIG_H_SYSTEM_SERVICE_CONFIGURATION?has_content>
<@mhc_expand_list list=LIST_SYSTEM_CONFIG_H_SYSTEM_SERVICE_CONFIGURATION/>
</#if>
<#if CONFIG_USE_SYS_COMMON == true>
<#include "/framework/system/common/templates/sys_common.h.ftl">
</#if>
<#if CONFIG_USE_SYS_CLK == true>
<#include "/framework/system/clk/templates/sys_clk.h.ftl">
</#if>
<#if CONFIG_USE_SYS_MEMORY == true>
<#include "/framework/system/memory/templates/sys_memory.h.ftl">
</#if>
<#if CONFIG_USE_SYS_INT == true>
<#include "/framework/system/int/config/sys_int.h.ftl">
</#if>
<#if CONFIG_USE_SYS_PORTS == true>
<#include "/framework/system/ports/config/sys_ports.h.ftl">
</#if>
<#if CONFIG_USE_DRV_CTR == true>
<#include "/framework/driver/ctr/templates/drv_ctr.h.ftl">
</#if>
<#if CONFIG_USE_SYS_TMR == true>
<#include "/framework/system/tmr/config/sys_tmr.h.ftl">
</#if>
<#if CONFIG_USE_DRV_PTG == true>
<#include "/framework/driver/ptg/templates/drv_ptg.h.ftl">
</#if>
<#if CONFIG_USE_SYS_DMA == true>
<#include "/framework/system/dma/templates/sys_dma.h.ftl">
</#if>
<#include "/framework/system/console/templates/sys_console.h.ftl">
<#if CONFIG_USE_SYS_MSG == true>
<#include "/framework/system/msg/config/sys_msg.h.ftl">
</#if>
<#if CONFIG_USE_SYS_DEBUG == true>
<#include "/framework/system/debug/config/sys_debug.h.ftl">
</#if>
<#include "/framework/system/command/config/sys_command.h.ftl">
<#if CONFIG_USE_SYS_WDT == true>
<#include "/framework/system/wdt/config/sys_wdt.h.ftl">
</#if>
<#if CONFIG_USE_SYS_FS == true>
<#include "/framework/system/fs/templates/sys_fs.h.ftl">
</#if>
<#if CONFIG_USE_SYS_RANDOM == true>
<#include "/framework/system/random/config/sys_random.h.ftl">
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
<#if LIST_SYSTEM_CONFIG_H_DRIVER_CONFIGURATION?has_content>
<@mhc_expand_list list=LIST_SYSTEM_CONFIG_H_DRIVER_CONFIGURATION/>
</#if>
<#if CONFIG_USE_DRV_CTR == true>
<#include "/framework/driver/ctr/templates/drv_ctr.h.ftl">
</#if>
<#if CONFIG_USE_DRV_TMR == true>
<#include "/framework/driver/tmr/templates/drv_tmr.h.ftl">
</#if>
<#if CONFIG_USE_DRV_USART == true>
<#include "/framework/driver/usart/templates/drv_usart.h.ftl">
</#if>
<#if CONFIG_USE_DRV_I2C == true>
<#include "/framework/driver/i2c/templates/drv_i2c.h.ftl">
</#if>
<#if CONFIG_USE_DRV_NVM == true>
<#include "/framework/driver/nvm/config/drv_nvm.h.ftl">
</#if>
<#if CONFIG_USE_DRV_GFX_GLCD == true>
<#include "/framework/driver/gfx/controller/glcd/config/drv_gfx_glcd_config.h.ftl">
</#if>
<#if CONFIG_USE_DRV_GFX_LCC == true>
<#include "/framework/driver/gfx/controller/lcc/config/drv_gfx_lcc_config.h.ftl">
</#if>
<#if CONFIG_USE_DRV_GFX_SSD1926 == true>
<#include "/framework/driver/gfx/controller/ssd1926/config/drv_gfx_ssd1926_config.h.ftl">
</#if>
<#if CONFIG_USE_DRV_GFX_S1D13517 == true>
<#include "/framework/driver/gfx/controller/s1d13517/config/drv_gfx_s1d13517_config.h.ftl">
</#if>
<#if CONFIG_USE_DRV_GFX_OTM2201A == true>
<#include "/framework/driver/gfx/controller/otm2201a/config/drv_gfx_otm2201a_config.h.ftl">
</#if>
<#if CONFIG_USE_GFX_TRULY_7_800X480 == true || CONFIG_USE_GFX_TRULY_7_800X480 == true
    || CONFIG_USE_GFX_TRULY_57_640X480 == true || CONFIG_USE_GFX_TRULY_32_240X320 == true
    || CONFIG_USE_GFX_POWERTIP_43_480X272 == true || CONFIG_USE_GFX_NEWHAVEN_50_800X480_PCAP == true
    || CONFIG_USE_GFX_NEWHAVEN_43_480X272_PCAP == true || CONFIG_USE_GFX_CRYSTAL_2_172x220 == true
    || CONFIG_USE_GFX_LTS_43_480X272_RTP == true>
<#include "/framework/driver/gfx/display/templates/drv_gfx_display.h.ftl">
</#if>
<#if CONFIG_USE_DRV_PMP == true>
<#include "/framework/driver/pmp/config/drv_pmp.h.ftl">
</#if>
<#if CONFIG_USE_DRV_I2S == true>
<#include "/framework/driver/i2s/templates/drv_i2s.h.ftl">
</#if>
<#if CONFIG_USE_DRV_CODEC_AK4953 == true>
<#include "/framework/driver/codec/ak4953/templates/drv_ak4953.h.ftl">
</#if>
<#if CONFIG_USE_DRV_CODEC_AK4384 == true>
<#include "/framework/driver/codec/ak4384/templates/drv_ak4384.h.ftl">
</#if>
<#if CONFIG_USE_DRV_CODEC_AK4642 == true>
<#include "/framework/driver/codec/ak4642/templates/drv_ak4642.h.ftl">
</#if>
<#if CONFIG_USE_DRV_CODEC_AK7755 == true>
<#include "/framework/driver/codec/ak7755/templates/drv_ak7755.h.ftl">
</#if>
<#if CONFIG_USE_DRV_SDCARD == true>
<#include "/framework/driver/sdcard/config/drv_sdcard.h.ftl">
</#if>
<#if CONFIG_USE_DRV_SDHC == true>
<#include "/framework/driver/sdhc/templates/drv_sdhc.h.ftl">
</#if>
<#if CONFIG_DRV_SPI_USE_DRIVER == true>
<#include "/framework/driver/spi/config/drv_spi.h.ftl">
</#if>
<#if CONFIG_USE_DRV_WIFI == true>
<#include "/framework/driver/wifi/templates/drv_wifi.h.ftl">
</#if>
<#if CONFIG_USE_DRV_TOUCH_AR1021 == true>
<#include "/framework/driver/touch/ar1021/config/drv_ar1021.h.ftl">
</#if>
<#if CONFIG_USE_DRV_TOUCH_ADC10BIT == true>
<#include "/framework/driver/touch/adc10bit/config/drv_adc10bit.h.ftl">
</#if>
<#if CONFIG_USE_DRV_TOUCH_MTCH6301 == true>
<#include "/framework/driver/touch/mtch6301/config/drv_mtch6301.h.ftl">
</#if>
<#if CONFIG_USE_DRV_OVM7690 == true>
<#include "/framework/driver/camera/ovm7690/config/drv_ovm7690.h.ftl">
</#if>
<#if CONFIG_USE_DRV_SST25VF020B == true>
<#include "/framework/driver/spi_flash/sst25vf020b/templates/drv_sst25vf020b.h.ftl">
</#if>
<#if CONFIG_USE_DRV_SST25VF016B == true>
<#include "/framework/driver/spi_flash/sst25vf016b/templates/drv_sst25vf016b.h.ftl">
</#if>
<#if CONFIG_USE_DRV_SST25VF064C == true>
<#include "/framework/driver/spi_flash/sst25vf064c/templates/drv_sst25vf064c.h.ftl">
</#if>
<#if CONFIG_USE_DRV_IPF == true>
<#include "/framework/driver/spi_flash/pic32wk_ipf/templates/drv_ipf.h.ftl">
</#if>
<#if CONFIG_DRV_ENCX24J600_USE_DRIVER == true>
<#include "/framework/driver/encx24j600/config/drv_encx24j600.h.ftl">
</#if>
<#if CONFIG_DRV_ENC28J60_USE_DRIVER == true>
<#include "/framework/driver/enc28j60/config/drv_enc28j60.h.ftl">
</#if>
<#if CONFIG_USE_DRV_SAMPLE == true>
<#include "/framework/driver/sample/templates/system_config.h.ftl">
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************
<#if LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION?has_content>
<@mhc_expand_list list=LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION/>
</#if>
<#if CONFIG_USE_BOOTLOADER_LIBRARY == true><#if CONFIG_CUSTOM_BOOTLOADER_PROGRAM_SPACE == false>
<#include "/framework/bootloader/templates/bootloader_config.h.ftl">
</#if></#if>
<#if CONFIG_USE_GFX_STACK == true>
<#include "/framework/gfx/config/gfx.h.ftl">
</#if>
<#if CONFIG_USE_IMAGE_DECODER == true>
<#include "/framework/decoder/templates/gfx_decoders.h.ftl">
</#if>
<#if CONFIG_USE_SEGGER_EMWIN == true>
<#include "/third_party/gfx/emwin/templates/system_config.h.ftl">
<#if CONFIG_SEGGER_EMWIN_GUI_WRAPPER == true>
<#include "/third_party/gfx/emwin/gui/templates/system_config.h.ftl">
</#if>
</#if>
<#if CONFIG_USE_CRYPTO_LIB == true>
<#include "/framework/crypto/config/crypto.h.ftl">
</#if>
<#if CONFIG_USE_USB_STACK == true>
<#include "/framework/usb/templates/system_config.h.common.ftl">
</#if>
<#if CONFIG_USE_TCPIP_STACK == true>
<#include "/framework/tcpip/config/tcpip_stack.h.ftl">
</#if>
<#if CONFIG_USE_OSAL == true>
<#include "/framework/osal/config/osal.ftl">
</#if>
<#if CONFIG_USE_SAMPLE_MODULE == true>
<#include "/framework/sample/templates/system_config.h.ftl">
</#if>
<#if CONFIG_USE_TEST_HARNESS == true>
<#include "/framework/test/templates/system_config.h.ftl">
</#if>
<#include "/framework/net/templates/system_config.h.ftl">
<#include "/bsp/templates/bsp_config.h.ftl">


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

<#include "/bsp/templates/bsp_pins_config.h.ftl">

<#if CONFIG_USE_APP_CONFIG?has_content>
<#if CONFIG_USE_APP_CONFIG == true>
<#if LIST_SYSTEM_CONFIG_H_APPLICATION_CONFIGURATION?has_content>
<@mhc_expand_list list=LIST_SYSTEM_CONFIG_H_APPLICATION_CONFIGURATION/>
</#if>
<#include "${CONFIG_APP_DIRECTORY}/firmware/templates/system_config.h.ftl">
</#if>
</#if>
<#if CONFIG_USE_BLUETOOTH_LIBRARIES == true>
<#include "/framework/bluetooth/templates/bt_config.h.ftl">
</#if>
<#if CONFIG_USE_DECODER == true>
<#include "/framework/decoder/templates/audio_decoders.h.ftl">
</#if>
<#if CONFIG_APP_NAME_0?has_content>
<#assign HCONFIG_APP_INSTANCE=0>
<#assign APP_NAME = CONFIG_APP_NAME_0>

/*** Application Instance 0 Configuration ***/
<@mhc_expand_list_named name="LIST_APP0_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_1?has_content>
<#assign HCONFIG_APP_INSTANCE=1>
<#assign APP_NAME = CONFIG_APP_NAME_1>

/*** Application Instance 1 Configuration ***/
<@mhc_expand_list_named name="LIST_APP1_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_2?has_content>
<#assign HCONFIG_APP_INSTANCE=2>
<#assign APP_NAME = CONFIG_APP_NAME_2>

/*** Application Instance 2 Configuration ***/
<@mhc_expand_list_named name="LIST_APP2_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_3?has_content>
<#assign HCONFIG_APP_INSTANCE=3>
<#assign APP_NAME = CONFIG_APP_NAME_3>

/*** Application Instance 3 Configuration ***/
<@mhc_expand_list_named name="LIST_APP3_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_4?has_content>
<#assign HCONFIG_APP_INSTANCE=4>
<#assign APP_NAME = CONFIG_APP_NAME_4>

/*** Application Instance 4 Configuration ***/
<@mhc_expand_list_named name="LIST_APP4_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_5?has_content>
<#assign HCONFIG_APP_INSTANCE=5>
<#assign APP_NAME = CONFIG_APP_NAME_5>

/*** Application Instance 5 Configuration ***/
<@mhc_expand_list_named name="LIST_APP5_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_6?has_content>
<#assign HCONFIG_APP_INSTANCE=6>
<#assign APP_NAME = CONFIG_APP_NAME_6>

/*** Application Instance 6 Configuration ***/
<@mhc_expand_list_named name="LIST_APP6_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_7?has_content>
<#assign HCONFIG_APP_INSTANCE=7>
<#assign APP_NAME = CONFIG_APP_NAME_7>

/*** Application Instance 7 Configuration ***/
<@mhc_expand_list_named name="LIST_APP7_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_8?has_content>
<#assign HCONFIG_APP_INSTANCE=8>
<#assign APP_NAME = CONFIG_APP_NAME_8>

/*** Application Instance 8 Configuration ***/
<@mhc_expand_list_named name="LIST_APP8_H_CONSTANTS"/>
</#if>
<#if CONFIG_APP_NAME_9?has_content>
<#assign HCONFIG_APP_INSTANCE=9>
<#assign APP_NAME = CONFIG_APP_NAME_9>

/*** Application Instance 9 Configuration ***/
<@mhc_expand_list_named name="LIST_APP9_H_CONSTANTS"/>
</#if>

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/

