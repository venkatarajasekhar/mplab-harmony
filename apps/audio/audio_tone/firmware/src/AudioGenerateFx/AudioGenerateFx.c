//******************************************************************************
// AudioGenerateFx.c file
//
// AUDIO SIGNAL GENERATION - Fixed Point 16 Bit (Q1d15)
// 
// Programmable tone generation API, i.e. prompt tone/silence/ramp sequences 
// 
//
//     //Audio generate 
//     AudioGenerateInit(AUDIO_GENERATE * ag, AUDIO_GEN_TYPE type, 
//                       AUDIO_GEN_PARAM  param)
//
//     //Get F<min,max> frequency generation values
//     int32_t AudioGenerateFminHz(AUDIO_GENERATE * ag)
//     int32_t AudioGenerateFmaxHz(AUDIO_GENERATE * ag)
//
//     //<Get,Set> the current frequency being generated
//     void AudioGenerateFrequencySet(AUDIO_GENERATE * ag, 
//     int32_t AudioGenerateFrequencyGet(AUDIO_GENERATE * ag)
//
//     //Scale the output value by a power of 2 (NOTE: Not implemented)
//     void AudioGenerateSetAmpExp(AUDIO_GENERATE * ag, uint16_t ampExpFS)
//
//     //Audio generation
//     //--Can generate signals of unlimited length to the output buffer queue
//     //-->Call with new buffers 
//     BOOL AudioGenerateFx(AUDIO_GENERATE * ag, AUDIO_PLAY_BUFFER * audioBuffer); 
//
// FIXED POINT DSP LIBRARY
// 
// --> Intrinsics and Conversions using following
// 
// (x) FxTypes     - Formats for fractional floating and fixed value types
// (x) FxConvert   - Defines to convert mathematical constants between different
//                   FxTypes and standard types
// (x) FxConverVar - inlines to convert variable values between different FxTypes
//                   and standard types.
// (x) FxFract     - Basic fractional math (saturated values). Implemenation should map to 
//                   intrinsics operations for MX and MZ MIPS architectures
// 
// --> Basic Math using intrinsics and conversions
// 
// FxMath - 
// (X) 1) Functions: sin, cos, sqrt, square ...
//     2) Matrix math
// 
// --> DSP using basic math, intrinsics and conversions 
// FxDSP - Signal processing components:
// (X) 1) AudioSignalGeneration 
// (X) 2) Fade-Out/In  (See EffectFade class above) 
// (X) 3) Exponential averaging
//     4) Filter structures
// 
//******************************************************************************

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.
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

#include <math.h>
#include <string.h>

#include "AudioGenerateFx.h"
//#include "FxMath.h"
#include "libq_C.h"
#include "app_config.h"

//******************************************************************************
//Global Objects
//******************************************************************************

#define MAXSAMPLESPERCYCLE 0x0A00 
#define MINSAMPLESPERCYCLE 0x0004
 
//AUDIO_GENERATE object 
//--Can be used directly in app, when AUDIO_SEQUENCE_GENERATE is not using it.
extern AUDIO_GENERATE ag; 

//******************************************************************************
// AudioSequenceGenerateFx/AudioGenerateFx Class functions
//******************************************************************************

//******************************************************************************
//
// AudioGenerateInit()
//
// Description:
//    Initialize for Audio Generation.
//
// NOTE: 1) Buffer provided in for each AudioGenerateFx() call.
//       2) A timeDelSec < 0 -> inf time (durationSamples = -1)
//          TODO: repeat the cycle
//
//******************************************************************************
void AudioGenerateInit(AUDIO_GENERATE * ag, 
                       AUDIO_GEN_TYPE   type, 
                       AUDIO_GEN_PARAM  param)
{
    ag->audioBuffer     = NULL;  //Buffer set with first generate call
    ag->type            = type;
    ag->param           = param;

    //Setup the signal generation parameters
    ag->audioSampleCnt  = 0; //Current sample
    //ag->ampExpFS        = param.ampExpFS;

    ag->sampleTimeSec = 1/ag->param.sampleRate;

    if (ag->param.timeDeltaMs < 0) 
    {
        ag->durationSamples = -1; //inf
        ag->infDuration = TRUE;
    }
    else
    {
        ag->durationSamples = (int32_t) 
                floor((param.sampleRate*param.timeDeltaMs*1e-3) + .5);
        ag->infDuration = FALSE;
    }

    //Maximum/Minimum/Initial Frequency
    //FIX: To overcome Harmony Driver Mutex Problem. Lower frequencies
    //     appear to cause an undefined call to a mutex service routine
    //     in the driver. CAL
    int32_t f0MinHz = ag->param.sampleRate/(AUDIO_PLAY_BUFFER_SIZE/2);
    f0MinHz = 50;

    int32_t f0MaxHz = ag->param.sampleRate/8;  //4 samples per cycle
    ag->fMinHz = f0MinHz;
    ag->fMaxHz = f0MaxHz;
    if (ag->param.fHz1 < f0MinHz) ag->param.fHz1 = f0MinHz;
    if (ag->param.fHz1 > f0MaxHz) ag->param.fHz1 = f0MaxHz;
    if (ag->param.fHz2 < f0MinHz) ag->param.fHz2 = f0MinHz;
    if (ag->param.fHz2 > f0MaxHz) ag->param.fHz2 = f0MaxHz;

    ag->fHz = ag->param.fHz1;
    ag->f0Hz = ag->param.fHz1; //Initial frequency

    double samPerCyc = ag->param.sampleRate/ag->fHz;
    ag->samplesPerCycle = (int32_t) floor(samPerCyc + .5);

    //#cycles that fit in buffer
    ag->cyclesPerBuffer = (int32_t) floor(AUDIO_PLAY_BUFFER_SIZE/samPerCyc);

    if (ag->type == AUDIO_GEN_CHIRP)
    {
        if (ag->durationSamples > 10*ag->samplesPerCycle ) //So I can see it.
        {
            ag->deltaHz   = (double) (ag->param.fHz2 - ag->param.fHz1);
	         ag->deltaHzPerSample =  ag->deltaHz/ag->durationSamples;

            ag->cycleDurationFrac = samPerCyc/ag->durationSamples;

            //Linear Chirp
            ag->chirpDelHzPerCycle = (int32_t) floor(ag->cycleDurationFrac*ag->deltaHz);

            ag->chirpDelHzPerBuffer = (int32_t) 
                      floor(ag->cyclesPerBuffer * ag->cycleDurationFrac * ag->deltaHz); 
	}
        else
        {
            //Generate as AUDIO_GEN_TONE
            ag->chirpDelHzPerCycle = 0;
            ag->chirpDelHzPerBuffer = 0;
        }
    }

} //End AudioGenerateInit()


int32_t AudioGenerateFminHz(AUDIO_GENERATE * ag)
{
    return ag->fMinHz;
}

int32_t AudioGenerateFmaxHz(AUDIO_GENERATE * ag)
{
    return ag->fMaxHz;
}

//******************************************************************************
//  APP_audioGenSetFrequency() - 
//
//  Change the current tone frequency setting and the nextTone setting value.
//
//  NOTE: 1) Frequency set in real-time by the +/- increment buttons. 
//        2) Used only when in tone mode and with on of the frequency parameter 
//           selects.   
//
//******************************************************************************
void AudioGenerateFrequencySet(AUDIO_GENERATE * ag, 
                               uint32_t freq)
{
   if (freq < ag->fMinHz) freq = ag->fMinHz;
   if (freq > ag->fMaxHz) freq = ag->fMaxHz;

   ag->fHz = freq;

   double samPerCyc = ag->param.sampleRate/ag->fHz;
   ag->samplesPerCycle = (int32_t) floor(samPerCyc + .5);
   ag->cyclesPerBuffer = (int32_t) floor(AUDIO_PLAY_BUFFER_SIZE/samPerCyc);
}

//******************************************************************************
//  APP_audioGenSetFrequency() - Change the tone type, without changing
//                                  any other parameter.
//
//  NOTE: Used by buttons to change the audio generator frequency output.
//
//******************************************************************************
int32_t AudioGenerateFrequencyGet(AUDIO_GENERATE * ag)
{
    return ag->fHz;
}


//******************************************************************************
// AudioGenerateSetAmpExp()
//******************************************************************************
//void AudioGenerateSetAmpExp(AUDIO_GENERATE * ag, uint16_t ampExpFS)
//{
//   ag->ampExpFS = ampExpFS;
//}

//******************************************************************************
//  AudioGenerateFx(AUDIO_PLAY_BUFFER * buffer, type) 
//
//  Description: 
//    Fill the playback buffer with current generated audio values.
//    A single type audio is generate through to multiple calls to
//    multiple buffers as provided.
//
//  Arguments:
//
//    [in] AUDIO_GENERATE * ag - Object to maintain generation state: 
//              AUDIO_PLAY_BUFFER * audioBuffer;
//              AUDIO_GEN_PARAM  param;
//                  AUDIO_GEN_TYPE type;
//                      AUDIO_GEN_SILENCE,
//                      AUDIO_GEN_TONE,
//                      AUDIO_GEN_CHIRP,
//                      AUDIO_GEN_UWN,
//                      AUDIO_GEN_GWN,
//                      AUDIO_GEN_PINK,
//                  uint8_t        amplitude;
//                  uint16_t       fHz1; //tone or chirp1
//                  uint16_t       fHz2; //chirp2
//                  int16_t        rateHzPerSec; //chirp  
//                  uint32_t       sigma; //noise sigma (Full Scale is 1)
//              int32_t          audioSampleCnt;      //Current sample
//              int32_t          sampleRate;          //Signal generatio sample rate
//              int32_t          chirpCurrFreqHz;     //Current chirp frequency
//              int32_t          chirpDelHzPerSample; //Chirp Freq Change param 
//    [in] AUDIO_PLAY_BUFFER * audioBuffer - audio buffer struct with:
//              uint32_t dataLen;    //#actually generated data
//              uint32_t dataLenMax; //Size of allocated data buffer
//              int16_t  data*       //A single buffer in the playback queu
//
//  Globals Used:
//
//  Returns:
//    
//    BOOL audioEnd -  generation completed status 
//
//******************************************************************************
BOOL AudioGenerateFx(AUDIO_GENERATE * ag, AUDIO_PLAY_BUFFER * audioBuffer) 
{

    //TEST VALUE: Test compiler intialization constants
    static const int addrIncr = sizeof(APP_TONE_TYPE); 
    int   i;
    BOOL  retVal      = FALSE;
    APP_DATA_TYPE *  buffer     = audioBuffer->data;  

    i=addrIncr;

    //int32_t  durationSamples = ag->durationSamples;

    //uint16_t  ampExp      = ag->param.ampExpFS;  //Amplitude shift

    //uint16_t fHz1         = ag->param.fHz1;      //tone or chirp1
    //uint16_t fhz2         = ag->param.fHz2;      //chirp2
    //uint32_t sigma               = ag->param.sigma; 

    //int32_t  sampleRate = ag->param.sampleRate;
    
    BOOL     infDuration = ag->infDuration;

    audioBuffer->dataLen = 0;

    AUDIO_GEN_TYPE type;
    type = ag->type;

    if (ag->type == AUDIO_GEN_CHIRP)
    {
        if (infDuration) type = AUDIO_GEN_TONE;
    }

    switch (type)
    {
        case AUDIO_GEN_SILENCE:
        {
            for (i = 0; (i < audioBuffer->dataLenMax/2); i++)
            {
                //int32_t sampleRate = ag->param.sampleRate;
                if ((ag->audioSampleCnt < ag->durationSamples) ||
                    infDuration)
                {
                    buffer[2*i]     = (APP_DATA_TYPE) 0; 
                    buffer[2*i + 1] = (APP_DATA_TYPE) 0;

                    audioBuffer->dataLen += 2; //2 samples per sampleTime
                    ag->audioSampleCnt++;
                }
                else
                {
                    retVal = TRUE; //End of generate
                }
            }
        } //End Case AUDIO_GEN_SILENCE
        break;

        case AUDIO_GEN_TONE:
        {
           //Fill with 1 cycle of stereo prompt data
            for (i = 0; (i < ag->samplesPerCycle); i++) //Sample
            {
                //int32_t sampleRate = ag->param.sampleRate;
                if ((ag->audioSampleCnt < ag->durationSamples) ||
                    infDuration)
                {
                    // FrssSin_AngT5() 
                    // Arguments:
                    //   FxPnt16 angleQ10d6
                    //     [in] The angle in degrees for which the sine is computed
                    //
                    // Return Value:
                    //   Fract16.  sinQ1d15, the value of the computed sine.
                    //
                    // NOTE: Amplitude is Q1.15 number.  
                    //       Thus Q1.15 * Q1.15 * 2^15 -> Q1.31; which is then rounded 
                    //       to Q1.15.
                    //
                    // TODO: Use DDS techniques to modulate the chirp:  
                    //       1) Counter. 2) sin table. 3) Interpolation output
                    //       modulated through counter value, allowing sample
                    //       time modulation of the chirp frequency. Using cycle
                    //       time frequency modulation.  CAL 
                    //       
                    //**********************************************************************
                    q15 angleQ10d6;
                    int32_t sinValueQ1d15;
                    //int32_t sinValueQ10d22;
                    angleQ10d6 = Fl2FxPnt(360.0*((float)i/ag->samplesPerCycle), 6);

                    //sinValueQ1d15 = (int32_t) FrssSin_AngT5(angleQ10d6);
                    sinValueQ1d15  = libq_q1d15_Sin_q10d6(angleQ10d6);

                    buffer[2*i]     = (APP_DATA_TYPE) sinValueQ1d15;  //lCh 
                    buffer[2*i + 1] = (APP_DATA_TYPE) sinValueQ1d15;  //rCh
                 
                    audioBuffer->dataLen += 2; //2 samples per sampleTime
                    ag->audioSampleCnt++;

                }  //End AUDIO_GEN_TONE Duration
                else
                {
                    retVal = TRUE; //End of generate
                    break;
                }

            }  //End AUDIO_GEN_TONE Loop
            audioBuffer->dataLen = ag->samplesPerCycle*2;

        } //End AUDIO_GEN_TONE Case
        break;

        case AUDIO_GEN_CHIRP:
        {
            //Generate 1 cycle of chirp
            for (i = 0; (i < ag->samplesPerCycle); i++)
            {
                //int32_t sampleRate = ag->param.sampleRate;
                if ((ag->audioSampleCnt < ag->durationSamples) ||
                    infDuration)
                {
                    q15 angleQ10d6;
                    int32_t sinValueQ1d15;
                    //int32_t sinValueQ10d22;
                    angleQ10d6 = Fl2FxPnt(360.0*((float)i/ag->samplesPerCycle), 6);

                    //sinValueQ1d15 = (int32_t) FrssSin_AngT5(angleQ10d6);
                    sinValueQ1d15 = 
                            (int32_t) libq_q1d15_Sin_q10d6(angleQ10d6);

                    //sinValueQ10d22 = sinValueQ1d15 << 7;
                    //sinValueQ10d22 = sinValueQ10d22 *5/8; //Scaling factor

                    //temp =  (APP_DATA_TYPE) (sinValue >> ampExpFS);

                    buffer[2*i]     = (APP_DATA_TYPE) sinValueQ1d15; 
                    buffer[2*i + 1] = (APP_DATA_TYPE) sinValueQ1d15;
     
                    audioBuffer->dataLen += 2; //2 samples per sampleTime
                    ag->audioSampleCnt++;
                }
                else
                {
                    retVal = TRUE; //End of generate4
		    asm("nop");
                    break;
                }
            }

            //Instantaneous Frequency of next cycle
            //ag->fHz += ag->chirpDelHzPerCycle;
            ag->fHz = ag-> f0Hz + 
                      (int32_t) (ag->deltaHzPerSample*ag->audioSampleCnt);
            double samPerCyc = ag->param.sampleRate/ag->fHz;
            ag->samplesPerCycle = (int32_t) floor(samPerCyc + .5);

            if (ag->samplesPerCycle < 8) 
	    {
                return TRUE;
		asm("nop");
	        break;
	    }

            //Delta fHz values using cycle fraction
            ag->cycleDurationFrac = samPerCyc/ag->durationSamples;
            ag->cyclesPerBuffer = (int32_t) floor(AUDIO_PLAY_BUFFER_SIZE/samPerCyc);
            ag->chirpDelHzPerCycle = (int32_t) floor(ag->cycleDurationFrac*ag->deltaHz);
            ag->chirpDelHzPerBuffer = (int32_t) 
                      floor(ag->cyclesPerBuffer * ag->cycleDurationFrac * ag->deltaHz); 

        } //End Case AUDIO_GEN_CHIRP
        break;

        case AUDIO_GEN_UWN:
        case AUDIO_GEN_GWN:
        case AUDIO_GEN_PINK:
        {
           //TODO: Implement Noise
            retVal = TRUE; //Don't Generate
        }
        break;

        default: break;
        
    } //End Switch(Audio Interval Type)

    return retVal;

} //End AudioGenerateFx()

