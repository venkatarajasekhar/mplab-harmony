/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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


#include "app.h"
#include "decoder.h"

static APP_AUDIOPLAYER APP_MAKE_BUFFER_DMA_READY appData;
static uint8_t audioInput[DECODER_MAX_INPUT_BUFFER_SIZE];
static APP_RUNDCPT  appRunDcpt;
volatile bool   playerPlay = false;
uint16_t        playerDiskDataSize=0;

uint32_t        playerFileStreamStart = 0;
bool            playerStreaming;
static uint16_t playerBitrate;

uint32_t        playerFileInitialAdvanceStep;
uint32_t        playerFileAdvanceStep;
uint32_t        playerFileAdvanceMaxStep;

static bool     playerMoveToEnd;
static uint16_t playerTrackTotalTime;
static uint16_t playerTrackPlayTime;
static int      count1s = 1;
static char currentLFN[255];
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************



static bool isOutputBufferFull(){
    int i;
    for(i = 0; i < AUDIO_QUEUEBUFFER_NUMBER; i++)
    {
        if(!appData.audioBuffer[i].decoded)
            return false;
    }
    return true;
}

static bool noOutputBufferInUse()
{
    int i;
    for(i = 0; i < AUDIO_QUEUEBUFFER_NUMBER;i++)
    {
        if(appData.audioBuffer[i].inUse)
            return false;
    }
    return true;
}

static bool allBufferCompleted(){
    int i;
    for(i = 0; i < AUDIO_QUEUEBUFFER_NUMBER; i++)
    {
        if(appData.audioBuffer[i].writeHandler != DRV_CODEC_BUFFER_HANDLE_INVALID)
            return false;
    }
    return true;
}

/************************Application Data Setter & Getter**********************/
bool APP_GetSpiAudioMode(){
    return appRunDcpt.bStereoMode;
}
void APP_SetSpiAudioMode(bool mode){
    appRunDcpt.bStereoMode = mode;
}
void APP_SetReadBytesInAppData(int32_t val){
    appData.readBytes = val;
}

int32_t APP_GetReadBytesInAppData(){
    return appData.readBytes;
}

void APP_SetReadFlagInAppData(bool b){
    appData.readbyte_flag = b;
}
void APP_SetReadBytesReadFlag(int32_t val, bool b){
    if(val >= 0)
        appData.readBytes = val;
    appData.readbyte_flag = b;
}
APP_AUDIOPLAYER* APP_GetAppDataInstance()
{
    return &appData;
}

void APP_SetPlayerTrackTotalTime(uint16_t totalTimeParam){
    playerTrackTotalTime = totalTimeParam;
}
void APP_SetPlayerPlay(bool playerPlayParam){
    playerPlay = playerPlayParam;
}
void APP_ResetPlayerFileAdvanceStep()
{
    playerFileAdvanceStep = playerFileInitialAdvanceStep;
}


void APP_handlePeriodicTimerSignal(uintptr_t context, uint32_t alarmCount)
{
    if (mRepeatButton != INVALID_BUTTON)
    {
        // make sure this button is still pressed
        if(APP_ButtonGetState(mRepeatButton) == BSP_SWITCH_STATE_PRESSED){
            if(mRepeatCount+1 != 0)
            {
                mRepeatCount++;
            }
            APP_OnButtonEvent(mRepeatButton,true,mRepeatCount);
        }
    }
    
    // Display play time
    if(appData.currentStreamType == APP_STREAM_AAC || appData.currentStreamType == APP_STREAM_WMA || appData.currentStreamType == APP_STREAM_FLAC)
    {
        if(playerPlay && playerStreaming)
        {
            if(count1s == 10)
            {
                count1s = 1;
                APP_PlayerEventHandler ( PLAYER_EVENT_TRACK_PLAY_TIME, playerTrackPlayTime+1 );
            }else
                count1s++;
        }
    }
    
//    if(appData.playerState == APP_STATE_RUNNING){
//        if(nextTrackDebug==30) // 3 sec
//        {
//            if(autoNext){
//                
//            
//           
//            appData.pressCMD = PLAYER_CMD_NEXT_FILE;
//            nextTrackDebug = 0;
//            }
//        }
//        
//        nextTrackDebug++;
//      
//    }
    
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

void APP_PeriodicTimerInit(){
/* Open the repeat timer driver */
    if (SYS_STATUS_READY == DRV_TMR_Status(sysObj.drvTmr2))
    {
        appData.repeatTmrHandle = DRV_TMR_Open (DRV_TMR_INDEX_2,
                    DRV_IO_INTENT_EXCLUSIVE);
        if(DRV_HANDLE_INVALID == appData.repeatTmrHandle ||
                (DRV_HANDLE) NULL == appData.repeatTmrHandle)
        {
//            SYS_DEBUG(0, "Timer DRV_TMR_Open Error");
        }
        else
        {
            
            DRV_TMR_Alarm32BitRegister (appData.repeatTmrHandle,
                    APP_REPEAT_TIMER_PERIOD, true,
                    (uintptr_t)0, &APP_handlePeriodicTimerSignal);
            DRV_TMR_Start (appData.repeatTmrHandle);
        }
    }
    else
    {
//        SYS_DEBUG(0, "Timer Driver Not Ready");
    }
}

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Initialize(void)
{
    /* Initialize the Application */
    APP_PlayerInitialize();
    AUDIO_CODEC_Initialize();
    
    APP_ButtonInit();
    APP_PeriodicTimerInit();
}

void APP_PeriodicTimer_Task(){
    
    APP_PlayerCommand(appData.pressCMD);
    appData.pressCMD = PLAYER_CMD_NONE;
}

void APP_Tasks(void)
{
   /* Maintain the application's state machine. */
    APP_PlayerTasks();
    APP_ButtonTask();
    APP_PeriodicTimer_Task();
}

void resetBuffers()
{
    int i = 0;
    for(i=0; i < AUDIO_QUEUEBUFFER_NUMBER; i++)
    {
        appData.audioBuffer[i].inUse = false;
        appData.audioBuffer[i].decoded = false;
        appData.readIdx = 0;
        appData.writeIdx = 0;
    }
}

void APP_PlayerInitialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_OPEN_HOST_LAYER;
    appData.playerState = APP_STATE_WAITING;
    appData.fileHandle = SYS_FS_HANDLE_INVALID;
    appData.fileStatus.lfname = currentLFN;
    appData.fileStatus.lfsize = FAT_FS_MAX_LFN;
    appData.nextTrack = true;
    appData.updatePlaytimeFunc = NULL;

    appData.readBytes = 0;
    appData.current_filesize = 0;
    appData.pressCMD = PLAYER_CMD_NONE;
    
    resetBuffers();

    // Configure Available Decoders
    appData.MP3_decoder_enabled     = isMP3decoder_enabled();
    if(appData.MP3_decoder_enabled){
        MP3_RegisterDecoderEventHandlerCallback(DECODER_EventHandler);
    }
    appData.AAC_decoder_enabled     = isAACdecoder_enabled();
    if(appData.AAC_decoder_enabled){
        AAC_RegisterDecoderEventHandlerCallback(APP_SetReadBytesInAppData);
    }
    appData.WMA_decoder_enabled     = isWMAdecoder_enabled();
    if(appData.WMA_decoder_enabled){
        WMA_RegisterAppCallback(APP_SetReadBytesReadFlag, APP_GetReadBytesInAppData);
    }
    appData.WAV_decoder_enabled     = isWAVdecoder_enabled();
    appData.SPEEX_decoder_enabled   = isSPEEXdecoder_enabled();
    appData.ADPCM_decoder_enabled   = isADPCMdecoder_enabled();
    appData.OPUS_decoder_enabled    = isOPUSdecoder_enabled();
    
    
    appRunDcpt.bStereoMode = (SPI_AUDIO_TRANSMIT_MODE_IDX0==SPI_AUDIO_TRANSMIT_STEREO)?true:false;
    
    DISK_Initialize();
    APP_PlayerReinit();
}

uint8_t APP_GetNextIdxInOutputBuffer(uint8_t idx)
{
    return (uint8_t)((idx+1) % AUDIO_QUEUEBUFFER_NUMBER);
}

static bool APP_FillAllOutputBuffer()
{
    
    int8_t *outputptr = NULL;

    while( !isOutputBufferFull())
    {
        outputptr = appData.audioBuffer[appData.writeIdx].buffer;
        if(APP_PlayerFillDiskBuffer (audioInput)==true)
        {
            if(APP_PlayerDecode (audioInput, (int16_t*)outputptr)==true)
            {
                if(appData.playerDecodeDataSize != 0)
                {
                    appData.audioBuffer[appData.writeIdx].decoded = true;
                    
                    appData.audioBuffer[appData.writeIdx].bufferSize = appData.playerDecodeDataSize;
                    
                    appData.writeIdx = APP_GetNextIdxInOutputBuffer(appData.writeIdx);

                    appData.playerDecodeDataSize = 0;
                }else{
                    
                    return false;
                }
                appData.playerState = APP_STATE_RUNNING;

            }
            else
             {
                 appData.nextTrack = true;
                 appData.playerState = APP_STATE_TRACK_CHANGE;
                 return false;
             }

        }
        else
        {
            appData.nextTrack = true;
            appData.playerState = APP_STATE_TRACK_CHANGE;
            return false;
        }
    }

    
    playerStreaming = true;
    if(noOutputBufferInUse())
    {
        if( Audio_Codec_Addbuffer(appData.audioBuffer[appData.readIdx].buffer, appData.audioBuffer[appData.readIdx].bufferSize))
        {
            appData.audioBuffer[appData.readIdx].writeHandler = CodecData.codecClient.writeBufHandle;
            appData.audioBuffer[appData.readIdx].inUse = true;
            appData.readIdx = APP_GetNextIdxInOutputBuffer(appData.readIdx); 
        }
        
        
    }
    
    return true;
}

/*  Since each decoder has different compression rates and different calculation for file size (size of valid audio data)
 *  number of bytes in FastForward step calculation is delegate to each decoder.
 */
void APP_PlayerUpdatePlayTime(){
    if(appData.updatePlaytimeFunc != NULL)
    {
        APP_PlayerEventHandler ( PLAYER_EVENT_TRACK_PLAY_TIME, appData.updatePlaytimeFunc());
    }
}

void APP_PlayerTasks(void)
{
    
    bool ret = true;
    
    DISK_Tasks();
    
    switch (appData.playerState)
    {
        case APP_STATE_CODEC_OPEN:
            if(Audio_Codec_Open() == true)
            {
                Audio_Codec_SetBufferHandler();
                Audio_Codec_SetCommandCallback();
                appData.playerState = APP_STATE_WAITING;
            }
            break;
            
        case APP_STATE_NO_MEDIA:
            BSP_LEDToggle(APP_USB_LED_1);
            BSP_LEDToggle(APP_USB_LED_2);
            BSP_LEDToggle(APP_USB_LED_3);
            break;

        case APP_STATE_NO_FILE:
        case APP_STATE_WAITING:
            break;
        case APP_STATE_SCANNING:
            BSP_LEDToggle(APP_USB_LED_1);
            BSP_LEDToggle(APP_USB_LED_2);
            BSP_LEDToggle(APP_USB_LED_3);

//            APP_PlayerEventHandler ( PLAYER_EVENT_SCANNING_FOUND, DISK_GetTotalFiles ());

            break;

        case APP_STATE_RUNNING:
            
            if (( playerPlay == true ) || ( playerStreaming == false ))
            {
                ret = APP_FillAllOutputBuffer();
            }
            if( ret && (appData.currentStreamType == APP_STREAM_WAV || appData.currentStreamType == APP_STREAM_MP3)){
                APP_PlayerUpdatePlayTime();
            } 
            break;

        case APP_STATE_TRACK_CHANGE:
    
            playerTrackPlayTime = 0;
            // Flush all decoded audio buffers to codec
            int i;
            for(i=0;i<AUDIO_QUEUEBUFFER_NUMBER;i++)
            {
                if( !appData.audioBuffer[i].inUse && appData.audioBuffer[i].decoded )
                {
                   if(Audio_Codec_Addbuffer(appData.audioBuffer[i].buffer, appData.audioBuffer[i].bufferSize))
                   {
                      appData.audioBuffer[i].writeHandler = CodecData.codecClient.writeBufHandle;
                      appData.audioBuffer[i].inUse = true;
                   }

                }
            }
             // Goto next state, wait for all previous buffers complete.
             appData.playerState = APP_WAIT_BUFFERS_COMPLETED;
             break;

         case APP_SEND_AUDIO_DATA:
            break;

        case APP_STATE_HALT:
            break;
        case APP_WAIT_BUFFERS_COMPLETED:
            // wait the buffers in I2S are all played
            if(allBufferCompleted())
            {
                if(appData.nextTrack)
                {
                    APP_PlayerCommand(PLAYER_CMD_NEXT_FILE);
                }else{
                    appData.nextTrack = true;
                    APP_PlayerCommand(PLAYER_CMD_PREV_FILE);
                }
            }
            break;
            
        default:
            break;
    }
}


bool APP_PlayerDecode(uint8_t *ptr, int16_t* outputptr)
{
    if(appData.currentStreamType == APP_STREAM_MP3)
    {
        uint16_t read;
        if ( ( appData.playerDecodeDataSize ==0 )&&( playerDiskDataSize != 0 ))
        {
            if ( DECODER_Decode ( ptr, playerDiskDataSize, &read, outputptr, &appData.playerDecodeDataSize ) == true )
            {
                if(appData.playerDecodeDataSize > DECODER_MAX_OUTPUT_BUFFER_SIZE){
                    appData.nextTrack = true;
                    return false;
                } // size of decoded data is larger than output buffer size, skip this audio file.
                if ( read != 0 )
                {
                    memcpy ( ptr, ptr + read,  DECODER_MAX_INPUT_BUFFER_SIZE - read );//MP3_PLAYER_INPUT_BUFFER_SIZE
                    playerDiskDataSize -= read;

                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            appData.nextTrack = true;
            return false;
        }
    }

     else
    {
        uint16_t read;
        if (appData.playerDecodeDataSize == 0)
        {
            if ( DECODER_Decode ( ptr, playerDiskDataSize, &read, outputptr, &appData.playerDecodeDataSize ) == true )
            {
                if(appData.playerDecodeDataSize > DECODER_MAX_OUTPUT_BUFFER_SIZE){
                    appData.nextTrack = true;
                    return false;
                } // size of decoded data is larger than output buffer size, skip this audio file.
                if ( read != 0 )
                {
                    playerDiskDataSize -= read;
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            appData.nextTrack = true;
            return false;

        }
    }

    return true;
}


bool APP_IsSupportedAudioFile(char *name)
{
    int i = 0;
    do
    {
       i++;
    }while(name[i]!= '.' && name[i] != '\0');
    
    if(name[i] == '\0')
        return false;

    if(appData.AAC_decoder_enabled)
    {
        if((name[i+1] == 'a' && name[i+2] == 'a' && name[i+3] == 'c') || (name[i+1] == 'A' && name[i+2] == 'A' && name[i+3] == 'C'))
            return true;
    }
    
    if(appData.MP3_decoder_enabled)
    {
        if((name[i+1] == 'm' && name[i+2] == 'p' && name[i+3] == '3') || (name[i+1] == 'M' && name[i+2] == 'P' && name[i+3] == '3'))
            return true;
    }
    
    if(appData.WMA_decoder_enabled)
    {
        if((name[i+1] == 'w' && name[i+2] == 'm' && name[i+3] == 'a') || (name[i+1] == 'W' && name[i+2] == 'M' && name[i+3] == 'A'))
            return true;
    }
    if(appData.WAV_decoder_enabled){
        if((name[i+1] == 'w' && name[i+2] == 'a' && name[i+3] == 'v') || (name[i+1] == 'W' && name[i+2] == 'A' && name[i+3] == 'V'))
            return true;
    }
    if(appData.OPUS_decoder_enabled){
        if((name[i+1] == 'o' && name[i+2] == 'p' && name[i+3] == 'u') || (name[i+1] == 'O' && name[i+2] == 'P' && name[i+3] == 'U'))
            return true;
    }
    if(appData.SPEEX_decoder_enabled){
        if((name[i+1] == 's' && name[i+2] == 'p' && name[i+3] == 'x') || (name[i+1] == 'S' && name[i+2] == 'P' && name[i+3] == 'X'))
            return true;
    }
    if(appData.ADPCM_decoder_enabled){
        if((name[i+1] == 'p' && name[i+2] == 'c' && name[i+3] == 'm') || (name[i+1] == 'P' && name[i+2] == 'C' && name[i+3] == 'M'))
        {
            return true;
        }
    }
	// Tobe added
/*
    if(appData.FLAC_decoder_enabled) {
        if((name[i+1] == 'f' && name[i+2] == 'l' && name[i+3] == 'a' ) || (name[i+1] == 'F' && name[i+2] == 'L' && name[i+3] == 'A' ))
        {
            Nop();
            return true;
        }
    }   
*/ 
    return false;
}


APP_DECODER_TYPE APP_GetCurrentFileType ( char *ext )
{
    if (( ext[0] == 'M' && ext[1] == 'P' && ext[2] == '3' )||( ext[0] == 'm' && ext[1] == 'p' && ext[2] == '3' ))
    {
        return APP_DECODER_MP3;
    }

    if (( ext[0] == 'W' && ext[1] == 'M' && ext[2] == 'A' )||( ext[0] == 'w' && ext[1] == 'm' && ext[2] == 'a' ))
    {
        return APP_DECODER_WMA;
    }

    if (( ext[0] == 'M' && ext[1] == 'P' && ext[2] == '4' )||( ext[0] == 'm' && ext[1] == 'p' && ext[2] == '4' ))
    {
        return APP_DECODER_AAC;
    }

    if (( ext[0] == 'M' && ext[1] == '4' && ext[2] == 'A' )||( ext[0] == 'm' && ext[1] == '4' && ext[2] == 'a' ))
    {
        return APP_DECODER_AAC;
    }

    if (( ext[0] == 'A' && ext[1] == 'A' && ext[2] == 'C' )||( ext[0] == 'a' && ext[1] == 'a' && ext[2] == 'c' ))
    {
        return APP_DECODER_AAC;
    }

    if (( ext[0] == 'P' && ext[1] == 'C' && ext[2] == 'M' )||( ext[0] == 'p' && ext[1] == 'c' && ext[2] == 'm' ))
    {
        return APP_DECODER_ADPCM;
    }

    if (( ext[0] == 'W' && ext[1] == 'A' && ext[2] == 'V' )||( ext[0] == 'w' && ext[1] == 'a' && ext[2] == 'v' ))
    {
        return APP_DECODER_WAV;
    }
    if(( ext[0] == 'S' && ext[1] == 'P' && ext[2] == 'X' )||( ext[0] == 's' && ext[1] == 'p' && ext[2] == 'x' ))
    {
        return APP_DECODER_SPEEX;
    }
    if(( ext[0] == 'O' && ext[1] == 'P' && ext[2] == 'U')||( ext[0] == 'o' && ext[1] == 'p' && ext[2] == 'u'))
    {
        return APP_DECODER_OPUS;
    }
	// Tobe added
/*
    if(( ext[0] == 'F' && ext[1] == 'L' && ext[2] == 'A')||( ext[0] == 'f' && ext[1] == 'l' && ext[2] == 'a'))
    {
        Nop();
        return APP_DECODER_FLAC;
    }
*/
    return APP_DECODER_UNKNOWN;
}

void APP_PlayerReinit(void)
{
    appData.fileSize = 0;
    appData.playerDecodeDataSize = 0;
    playerTrackPlayTime = 0;
    playerTrackTotalTime = 0;
    playerFileStreamStart = 0;
    playerBitrate = 0;
    playerStreaming = false;
    
    resetBuffers();
    DECODER_Cleanup();
}

void APP_PlayerReset(void)
{
    // can not reset file size here
//    appData.fileSize = 0;
    appData.playerDecodeDataSize = 0;
    playerTrackPlayTime = 0;
    playerTrackTotalTime = 0;
    playerFileStreamStart = 0;
    playerBitrate = 0;
    playerStreaming = false;
    uint8_t i=0;

    resetBuffers();
    DECODER_Cleanup();
     
    do
    {
       i++;
    }while(appData.fileStatus.fname[i]!= '.');
    
    uint8_t decoderType = APP_GetCurrentFileType (&(appData.fileStatus.fname[i+1]));
    DECODER_Initialize (decoderType);
}


bool APP_PlayerFillDiskBuffer(uint8_t *ptr)
{
    bool status;
    status = DISK_FillBuffer(ptr);
    return status;
}

bool APP_PlayerEventHandler ( PLAYER_EVENT event, uint32_t data )
{
    switch ( event )
    {
        case PLAYER_EVENT_DISK_REMOVED:
            //DISPLAY_IdleScreen ();
            
            //DISPLAY_Message ("Please insert USB drive");
            break;

        case PLAYER_EVENT_DISK_INSERTED:
            //DISPLAY_PlaybackScreen ();
            
            //DISPLAY_Message ("USB drive detected");
            break;

        case PLAYER_EVENT_SCANNING_STARTED:
            //DISPLAY_Message ("Scanning...");
            break;

        case PLAYER_EVENT_SCANNING_FOUND:
//            DISPLAY_FilesFound ( data );
            break;

        case PLAYER_EVENT_SCANNING_FINISHED:
          //  DISPLAY_PlaybackScreen ();
//            DISPLAY_TotalDirsFiles ( DISK_GetTotalDirs (), data );
            break;

        case PLAYER_EVENT_NO_FILES_FOUND:
        //    DISPLAY_Message ("No MP3 files found");
            break;

        case PLAYER_EVENT_READY:
            APP_PlayerCommand ( PLAYER_CMD_PLAY );
            break;

        case PLAYER_EVENT_TAG_ARTIST:
           // DISPLAY_SetInfoPage ( DISPLAY_INFO_PAGE_TAG );
          // DISPLAY_Artist ( (CHAR8*) data );
            break;

        case PLAYER_EVENT_TAG_ALBUM:
          //  DISPLAY_SetInfoPage ( DISPLAY_INFO_PAGE_TAG );
          //  DISPLAY_Album ( (CHAR8*) data );
            break;

        case PLAYER_EVENT_TAG_TITLE:
          //  DISPLAY_SetInfoPage ( DISPLAY_INFO_PAGE_TAG );
         //   DISPLAY_Title ( (CHAR8*) data );
            break;

        case PLAYER_EVENT_TRACK_CHANGED:
           // DISPLAY_ClearTagData ();
          //  DISPLAY_CurrentFile ( data );
          //  DISPLAY_SetInfoPage ( DISPLAY_INFO_PAGE_FILE );
           // if ( DISK_GetCurrentFileName ( &str ))
           // {
           //     DISPLAY_FileName ( str );
           // }
           // else
           // {
           //     DISPLAY_FileName ( "Cannot read file name" );
   //         }
//
            break;


        case PLAYER_EVENT_TIME_CHANGED:
           // DISPLAY_PlayTime ( data );
            break;

        case PLAYER_EVENT_SAMPLERATE:
          //  DISPLAY_SampleRate ( data );
            break;

        case PLAYER_EVENT_BITRATE:
           // DISPLAY_BitRate ( data );
            break;

        case PLAYER_EVENT_TRACK_TOTAL_TIME:
            if(playerTrackTotalTime != 0)
            {
                // Advance Step size must be an even number
                
                uint32_t validSize = DECODER_GetCurrentValidAudioSize();
                playerFileInitialAdvanceStep    = PLAYER_ADVANCE_INITIAL_STEP_IN_SECOND * ( validSize / playerTrackTotalTime);
                if(playerFileInitialAdvanceStep & 0x1)
                {
                    playerFileInitialAdvanceStep += 1;
                }
                playerFileAdvanceMaxStep = PLAYER_ADVANCE_STEP_MAX_IN_SECOND * (validSize / playerTrackTotalTime);
                if(playerFileAdvanceMaxStep & 0x1)
                {
                    playerFileAdvanceMaxStep += 1;
                }
                    
                playerFileAdvanceStep = playerFileInitialAdvanceStep;
            }
           // DISPLAY_TotalTime ( data );
            break;

        case PLAYER_EVENT_TRACK_PLAY_TIME:
            if(data != playerTrackPlayTime)
            {
                playerTrackPlayTime = data;
            }
            else 
                return true;
           // DISPLAY_PlayTime ( data );
            break;
        case PLAYER_EVENT_VOLUME_CHANGE:
            return true;
        case PLAYER_EVENT_ERROR_MESSAGE:
            return true;
    }
    
#if defined USE_DISPLAY
    display_tasks(event,  data);
#endif

    return ( true );
}


bool DECODER_EventHandler ( DECODER_EVENT event, uint32_t data )
{
    switch ( event )
    {
        case DECODER_EVENT_TAG_ARTIST:
          APP_PlayerEventHandler ( PLAYER_EVENT_TAG_ARTIST, data );
            return ( true );

        case DECODER_EVENT_TAG_ALBUM:
           APP_PlayerEventHandler ( PLAYER_EVENT_TAG_ALBUM, data );
            return ( true );

        case DECODER_EVENT_TAG_TITLE:
           APP_PlayerEventHandler ( PLAYER_EVENT_TAG_TITLE, data );
            return ( true );

        case DECODER_EVENT_STREAM_START:
//            playerStreaming = true;
            playerFileStreamStart = DISK_GetFilePosition (appData.fileHandle);
            if ( playerMoveToEnd )
            {
                int pos = DISK_GetFileSize (appData.fileHandle) - playerFileAdvanceStep;
                DISK_SetFilePosition (appData.fileHandle,  pos);
                
                playerMoveToEnd = false;
            }
            //MP3 total time and bit rate calculation 
//            if(appData.currentStreamType == APP_STREAM_MP3){
//                uint32_t filesize = DISK_GetFileSize (appData.fileHandle);
//                if (( playerTrackTotalTime == 0 ) && ( playerBitrate != 0 ))
//                {
//                    // playerBitrate in Kb/s, file size in bytes.
//                    // thus, track length = file_size/byterate = (TotalFileSize - MP3HeaderSize)/(playerBitrate*1000/8)
//                    // = ( filesize - playerFileStreamStart ) / 125 / playerBitrate; 
//                    playerTrackTotalTime = ( filesize - playerFileStreamStart ) / 125 / playerBitrate; 
//                }
//                if (( playerBitrate == 0 ) && ( playerTrackTotalTime != 0 ))
//                {
//                    playerBitrate = ( filesize - playerFileStreamStart ) / 125 / playerTrackTotalTime;
//                }
//                APP_PlayerEventHandler ( PLAYER_EVENT_BITRATE, playerBitrate );
//                APP_PlayerEventHandler ( PLAYER_EVENT_TRACK_TOTAL_TIME, playerTrackTotalTime );
            
//            }
            return ( true );

        case DECODER_EVENT_SAMPLERATE:
            Player_SetSamplingRate(data);
            APP_PlayerEventHandler ( PLAYER_EVENT_SAMPLERATE, data );
            return ( true );
        
        case DECODER_EVENT_BITRATE:
            playerBitrate = data;
            APP_PlayerEventHandler ( PLAYER_EVENT_BITRATE, data );
            return ( true );

        case DECODER_EVENT_TRACK_TIME:
            playerTrackTotalTime = data;          
            APP_PlayerEventHandler ( PLAYER_EVENT_TRACK_TOTAL_TIME, playerTrackTotalTime );
            return ( true );

        case DECODER_INITIALIZATION_ERROR:
            // Todo: show error messages
            APP_PlayerCommand(PLAYER_CMD_NEXT_FILE);
            break;
    }
    return ( false );
}

////////////////////////////////////////////////////////////////////////////////
bool APP_PlayerCommand ( PLAYER_COMMAND cmd )
{
    // use 64bits to avoid overflow
    uint64_t posFF;
    int32_t  posRW;
    
    // If there is no audio files, return
    if(appData.playerState == APP_STATE_NO_FILE)
        return true;

    switch ( cmd )
    {
        case PLAYER_CMD_STOP:
            DISK_ReopenTrack ();
            playerPlay = false;
            break;

        case PLAYER_CMD_PLAY:
            playerPlay = true;
            Player_MuteOff();

            break;

        case PLAYER_CMD_PAUSE:
            playerPlay = false;
            Player_MuteOn();
            break;

        case PLAYER_CMD_PLAY_PAUSE:
            if ( playerPlay == false )
            {
                playerPlay = true;
                Player_MuteOff();
            }
            else
            {
                playerPlay = false;
                Player_MuteOn();
            }
            break;

        case PLAYER_CMD_NEXT_FILE:
            appData.nextTrack = true;
            Player_MuteOn();

            DISK_CloseFile(appData.fileHandle);
            appData.playerState = APP_STATE_RUNNING;

            Player_MuteOff();
            DISK_NextTrack ();
            break;

        case PLAYER_CMD_PREV_FILE:
            appData.nextTrack = false;
            Player_MuteOn();

            appData.playerState = APP_STATE_RUNNING;

            if ( playerTrackPlayTime < 5 )
            {
                DISK_CloseFile(appData.fileHandle);
                Player_MuteOff();
//                    DISK_PreviousTrack ();
                DISK_PreviousTrack();
            }
            else
            {
                DISK_CloseFile(appData.fileHandle);
                Player_MuteOff();
                DISK_ReopenTrack ();
            }
            break;


        case PLAYER_CMD_FAST_FORWARD:
            // AAC/WMA doesn't support FF
            if(appData.currentStreamType == APP_STREAM_AAC || appData.currentStreamType == APP_STREAM_WMA )
            {
                break;
            }
            appData.nextTrack = true;
            appData.playerState =  APP_STATE_RUNNING;
            if ( playerStreaming )
            {
                appData.playerDecodeDataSize = 0;
                posFF = (uint32_t)(DISK_GetFilePosition (appData.fileHandle)) + playerFileAdvanceStep;

                if ( posFF < (uint64_t)appData.fileSize)
                {
                    if ( DISK_SetFilePosition ( appData.fileHandle,posFF ) == true )
                    {
                        if(appData.current_filesize > playerFileAdvanceStep)
                        {    
                            appData.current_filesize -= playerFileAdvanceStep;
                        }

                        if(playerFileAdvanceStep < playerFileAdvanceMaxStep)
                        {
                            playerFileAdvanceStep = playerFileAdvanceStep + (playerFileAdvanceStep)/8; // MULTIPLE
                            if(playerFileAdvanceStep & 0x01)
                            {
                                playerFileAdvanceStep += 1;
                            }
                        }
                        else if(playerFileAdvanceStep > playerFileAdvanceMaxStep)
                        {
                            Nop();
                            playerFileAdvanceStep = playerFileAdvanceMaxStep;
                        }
                        break;
                    }
                    else
                    {
                        // set file position fail
                        Nop();
                    }
                }
                else
                {
                    appData.playerState = APP_STATE_TRACK_CHANGE;
                }
            }
            break;

        case PLAYER_CMD_REWIND:
            // AAC/WMA rewind function is not supported
            if(!(appData.currentStreamType == APP_STREAM_MP3 || appData.currentStreamType == APP_STREAM_WAV) )
            {
                break;   
            }
            appData.playerState =  APP_STATE_RUNNING;
            appData.nextTrack = false;
            playerPlay = false;

            {

                appData.playerDecodeDataSize = 0;
                
                posRW = DISK_GetFilePosition (appData.fileHandle) - playerFileAdvanceStep;
                
                if ( posRW > (int32_t)playerFileStreamStart )
                {
                    if ( DISK_SetFilePosition (appData.fileHandle, posRW ) )
                    {
                        appData.current_filesize += playerFileAdvanceStep;
                    }

                    // playerFileAdvanceStep must be an even number due to the wav audio sample size, 1 sample is 2 bytes.
                    playerFileAdvanceStep = playerFileAdvanceStep + (playerFileAdvanceStep)/8; // MULTIPLE
                    if(playerFileAdvanceStep & 0x01)
                        playerFileAdvanceStep += 1;
                    if(playerFileAdvanceStep > playerFileAdvanceMaxStep)
                    {
                        playerFileAdvanceStep = playerFileAdvanceMaxStep;
                    }
                    break;
                }
                else
                {
                    appData.playerState = APP_STATE_TRACK_CHANGE;
                    playerMoveToEnd = true;              
                }
            }
            break;

        case PLAYER_CMD_NONE:
        default:
            break;

    }
    return ( true );
}

////////////////////////////////////////////////////////
bool DISK_EventHandler ( DISK_EVENT event, uint32_t variable,SYS_FS_HANDLE fileHandle)
{
    switch ( event )
    {
        case DISK_EVENT_REMOVED:
        {
            APP_PlayerReinit();
            appData.playerState = APP_STATE_NO_MEDIA;
            APP_PlayerEventHandler ( PLAYER_EVENT_DISK_REMOVED, 0 );
            return ( true );
        }

        case DISK_EVENT_INSERTED:
        {
            appData.playerState = APP_STATE_WAITING;
            APP_PlayerEventHandler ( PLAYER_EVENT_DISK_INSERTED, 0 );
            return ( true );
        }

        case DISK_EVENT_SCANNING_STARTED:
        {
            appData.playerState = APP_STATE_SCANNING;
            APP_PlayerEventHandler ( PLAYER_EVENT_SCANNING_STARTED, 0 );
            return ( true );
        }

        case DISK_EVENT_SCANNING_FINISHED:
        {
            
//            if (( appData.diskTotalFiles > 0 )) //&&(appData.diskTotalDirs>0)
//            {
//               APP_PlayerEventHandler ( PLAYER_EVENT_SCANNING_FINISHED, 0 );
//               
//               DISK_FirstTrack ();
//               appData.playerState = APP_STATE_RUNNING;
//            }
//            else
//            {
//                APP_PlayerEventHandler ( PLAYER_EVENT_NO_FILES_FOUND, 0 );
//                appData.playerState = APP_STATE_HALT;
//            }

            return ( true );
        }

        case DISK_EVENT_TRACK_CHANGED:
        {
            APP_PlayerEventHandler ( PLAYER_EVENT_TRACK_CHANGED, appData.currentSongIdx+1);
            APP_PlayerReset();
            appData.playerState = APP_STATE_RUNNING;

            return ( true );
        }

        case DISK_EVENT_FILE_OPEN_ERROR:
        case DISK_EVENT_END_OF_FILE:
        {
//            Player_MuteOn();
            DISK_CloseFile(appData.fileHandle);
//            Player_MuteOff();
            DISK_NextTrack();
            return ( true );
        }
    }

    return ( false );
}

/******************************************************************************
  Function:
    void USB_Connection_Tasks ( void )

  Remarks:
    See prototype in app.h.
*/
void USB_Connection_Tasks (void)
{
    /* The application task state machine */
    switch(appData.state)
    {
        case APP_STATE_OPEN_HOST_LAYER:
             /* Set the event handler and enable the bus */
            
            SYS_FS_EventHandlerSet(APP_SYSFSEventHandler, (uintptr_t)NULL);
            USB_HOST_EventHandlerSet(APP_USBHostEventHandler, 0);
            // enable, open, bus 0
            USB_HOST_RESULT ret = USB_HOST_BusEnable(0);
            if(ret == USB_HOST_RESULT_FALSE)
                return;
            appData.state = APP_STATE_WAIT_FOR_HOST_ENABLE;
            break;

        case APP_STATE_WAIT_FOR_HOST_ENABLE:

            /* Check if the host operation has been enabled */
            if(USB_HOST_BusIsEnabled(0))
            {
                /* This means host operation is enabled. We can
                 * move on to the next state */
                 appData.state = APP_STATE_WAIT_FOR_DEVICE_ATTACH;
            }
            break;

        case APP_STATE_WAIT_FOR_DEVICE_ATTACH:

            /* Wait for device attach. The state machine will move
             * to the next state when the attach event
             * is received.  */

            break;

        default:
            break;

    }

} //End of APP_Tasks

void APP_SYSFSEventHandler(SYS_FS_EVENT event, void * eventData, uintptr_t context)
{
    switch(event)
    {
        case SYS_FS_EVENT_MOUNT:
            appData.state =  APP_STATE_DEVICE_CONNECTED;
//            appData.playerState = APP_STATE_CODEC_OPEN;
            APP_BSP_LEDOn(APP_USB_LED_1);
            APP_BSP_LEDOff(APP_USB_LED_2);
            APP_BSP_LEDOn(APP_USB_LED_3);
            
            
            break;
            
        case SYS_FS_EVENT_UNMOUNT:
            appData.state = APP_STATE_UNMOUNT_DISK;
            appData.fileHandle = SYS_FS_HANDLE_INVALID; 
            Player_MuteOn();
           
            Audio_Codec_Close();

            appData.state =  APP_STATE_WAIT_FOR_DEVICE_ATTACH;
            appData.playerState = APP_STATE_NO_MEDIA;
            break;
            
        default:
            break;
    }
}

/*******************************************************
 * USB HOST Layer Events - Host Event Handler
 *******************************************************/
USB_HOST_EVENT_RESPONSE APP_USBHostEventHandler (USB_HOST_EVENT event, void * eventData, uintptr_t context)
{
    switch(event)
    {
        case USB_HOST_EVENT_DEVICE_REJECTED_INSUFFICIENT_POWER:
            break;
        case USB_HOST_EVENT_DEVICE_UNSUPPORTED:
            break;
        case USB_HOST_EVENT_HUB_TIER_LEVEL_EXCEEDED:
            break;
        case USB_HOST_EVENT_PORT_OVERCURRENT_DETECTED:
            break;
        default:
            break;
    }
    return (USB_HOST_EVENT_RESPONSE)USB_HOST_EVENT_RESPONSE_NONE;
}
void Player_SetSamplingRate(int data)
{
    if(CodecData.codecClient.handle != DRV_HANDLE_INVALID){
        DRV_CODEC_SamplingRateSet(CodecData.codecClient.handle, data);
        CodecData.codecClient.currentCommand = CODEC_COMMAND_SAMPLING_RATE_SET;
    }
}

void Player_MuteOff()
{
    DRV_CODEC_MuteOff(CodecData.codecClient.handle);
}

void Player_MuteOn()
{
    DRV_CODEC_MuteOn(CodecData.codecClient.handle);
}