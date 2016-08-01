/*******************************************************************************
  Universal Audio Decoders Demo

  Company:
    Microchip Technology Inc.

  File Name:
    wav.c

  Summary:
   Contains the functional implementation of wav decoder.

  Description:
   This file contains the functional implementation of wav decoder.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
//#include "wav.h"
#include "app.h"


static WAVHEADER wavHeader;
static WAV_DEC   wavDecoder;

int WAV_HdrGetFormat (void)
{
    return wavHeader.format;
}

int WAV_HdrGetNumOfChan(void)
{
    return wavHeader.numOfChan;
}
uint8_t WAV_GetChannels()
{
    return WAV_HdrGetNumOfChan();
}


int WAV_HdrGetSamplesPerSec(void)
{
    return wavHeader.samplesPerSec;
}

int WAV_HdrGetBlockAlign(void)
{
   return wavHeader.blockAlign;
}

int WAV_HdrGetBitsPerSample(void)
{
    return wavHeader.bitsPerSample;
}

int WAV_HdrGetBytesPerSec(void)
{
    return wavHeader.bytesPerSec;
}

int WAV_HdrGetDataLen(void)
{
    return (int) wavHeader.dataLen;
}

unsigned int WAV_HdrGetFileSize(void)
{
    return (unsigned int) wavHeader.extralen;
}

void WAV_Initialize(uint8_t *input)
{
    memcpy(&wavHeader, input, WAV_HEADER_SIZE);

    wavDecoder.decodeStartPos = WAV_HEADER_SIZE;
    wavDecoder.wavSampleRate  = wavHeader.samplesPerSec;
    wavDecoder.wavBitRate     = wavHeader.bytesPerSec*8/1000;
    wavDecoder.wavFileBytes   = wavHeader.extralen;
    wavDecoder.wavDuration    = wavDecoder.wavFileBytes / wavHeader.bytesPerSec;

    DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, wavHeader.samplesPerSec );
    DECODER_EventHandler ( DECODER_EVENT_BITRATE, wavDecoder.wavBitRate );
    DECODER_EventHandler ( DECODER_EVENT_TRACK_TIME, wavDecoder.wavDuration);
}

uint32_t WAV_UpdatePlaytime(){
    uint32_t playtime;

    playtime = (DISK_GetCurrentFilePosition() - WAV_HEADER_SIZE)>>12;
    playtime *= wavDecoder.wavDuration;
    playtime /= wavDecoder.wavFileBytes >> 12;
    return playtime;
}

uint32_t WAV_GetAudioSize(){
    return wavDecoder.wavFileBytes;
}

bool WAV_Decoder(uint8_t *input, uint16_t inSize, uint16_t *read, int16_t *output, uint16_t *written)
{
    memcpy ( output, input, WAV_INPUT_BUFFER_SIZE );

    *read = WAV_INPUT_BUFFER_SIZE;
    *written = WAV_INPUT_BUFFER_SIZE;
    return true;
}

bool isWAVdecoder_enabled(){
    return true;
}