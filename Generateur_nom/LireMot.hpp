
#include "wincompat.h"
#include <fmod.hpp>
#include <fmod_errors.h>


class LireMot
{
    public:
        LireMot(int wave, int spc=100, int ltr=10)
        {
            WaveType = wave;
            result = FMOD::System_Create(&system);
            ERRCHECK(result);
            unsigned int version;
            result = system->getVersion(&version);
            ERRCHECK(result);

            if (version < FMOD_VERSION)
            {
                printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
                exit(0);
            }

            result = system->init(32, FMOD_INIT_NORMAL, 0);
            ERRCHECK(result);

            result = system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp);
            ERRCHECK(result);
            result = dsp->setParameter(FMOD_DSP_OSCILLATOR_RATE, 440.0f);
            ERRCHECK(result);

            result = system->playDSP(FMOD_CHANNEL_REUSE, dsp, true, &channel);

            channel->setVolume(1.0f);
            result = dsp->setParameter(FMOD_DSP_OSCILLATOR_TYPE, WaveType);
            channel->setPan(0.0);
            ERRCHECK(result);

            LetterTime=ltr;
            SpaceTime=spc;
        };

        void ReadWord(const char* Word)
        {
            if (Word != NULL)
            {
                 channel->setPaused(false);
                 int i=0;
                 while (Word[i] != '\0')
                 {
                     int freq=2500;
                     switch (Word[i])
                     {
                        case ' ':
                            channel->setPaused(true);
                            Sleep(SpaceTime);
                            freq=0;
                        break;
                        default:
                            channel->setPaused(false);
                            freq+= Word[i]*Word[i]*7;
                     }
                    channel->setFrequency(freq);
                    printf("%c",Word[i]);
                    Sleep(LetterTime);
                    ++i;
                 }
                 printf("\n");
                 channel->setPaused(true);
                 Sleep(SpaceTime);
            }
        };

        ~LireMot()
        {
            result = dsp->release();
            ERRCHECK(result);
            result = system->close();
            ERRCHECK(result);
            result = system->release();
            ERRCHECK(result);
        };

    private :
        int WaveType;
        FMOD::System    *system;
        FMOD::Channel   *channel;
        FMOD::DSP       *dsp;
        FMOD_RESULT      result;
        int SpaceTime,LetterTime;

        void ERRCHECK(FMOD_RESULT result)
        {
            if (result != FMOD_OK)
            {
                printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
                exit(-1);
            }
        };
};
