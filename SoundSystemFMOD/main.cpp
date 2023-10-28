#include "StaticSoundLib.h"
#include <iostream>
#include <algorithm>
#include <string>

#define VOLUME_CHANGE_VALUE 0.1
#define PAN_CHANGE_VALUE 0.1


int FMOD_Main() {   
	//Sound system creation
	Sound *System = new Sound();

	//System init
	System->init();

	//System loop
	do {
		Common_Update();

        // Button 1
		if (Common_BtnPress(BTN_ACTION1)) {
            //Common_Draw("Banana");
            if (!System->playSound(System->s1)) return 0;
		}

        // Button 2
		if (Common_BtnPress(BTN_ACTION2)) {
            //Common_Draw("Banana");
            if (!System->playSound(System->s2)) return 0;
		}

        // Button 3
		if (Common_BtnPress(BTN_ACTION3)) {
            //Common_Draw("Banana");
            if (!System->playSound(System->s3)) return 0;
		}

        // Button +
        if (Common_BtnPress(BTN_PLUS)) {
            //Common_Draw("Banana plus");
            if (!System->changeVolume(VOLUME_CHANGE_VALUE)) return 0;
        }

        // Button -
        if (Common_BtnPress(BTN_MINUS)) {
            //Common_Draw("Banana minus");
            if (!System->changeVolume(-VOLUME_CHANGE_VALUE)) return 0;
        }

        // Button m
        if (Common_BtnPress(BTN_PAN_UP)) {
            if (!System->changePan(PAN_CHANGE_VALUE)) return 0;
        }

        // Button n
        if (Common_BtnPress(BTN_PAN_DOWN)) {
            //Common_Draw("Banana minus");
            if (!System->changePan(-PAN_CHANGE_VALUE)) return 0;
        }

        // Button volumeString
        if (Common_BtnPress(BTN_STOP)) {
            //Common_Draw("Banana stop");
            if (!System->stop()) return 0;
        }

        // Button p
        if (Common_BtnPress(BTN_PAUSE)) {
            //Common_Draw("Banana pause");
            if(!System->setPause()) return 0;
        }

        //button l
        if (Common_BtnPress(BTN_LOOP_ON)) {
            //Common_Draw("Banana loop on");
            if(!System->setLoopOn()) return 0;
        }

        //button k
        if (Common_BtnPress(BTN_LOOP_OFF)) {
            //Common_Draw("Banana loop off");
            if (!System->setLoopOff()) return 0;
        }

        //button g
        if (Common_BtnPress(BTN_CHANGE_CHANNEL_GROUP)) {
            //Common_Draw("Banana change channel group");
            System->changeChannelGroup();
        }

		if (!System->update()) return 0;
        
        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            bool         playing = 0;
            bool         paused = 0;
            int          channelsplaying = 0;

            if (System->channel)
            {
                FMOD::Sound* currentsound = 0;

                System->result = System->channel->isPlaying(&playing);
                if ((System->result != FMOD_OK) && (System->result != FMOD_ERR_INVALID_HANDLE) && (System->result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(System->result);
                }

                System->result = System->channel->getPaused(&paused);
                if ((System->result != FMOD_OK) && (System->result != FMOD_ERR_INVALID_HANDLE) && (System->result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(System->result);
                }

                System->result = System->channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                if ((System->result != FMOD_OK) && (System->result != FMOD_ERR_INVALID_HANDLE) && (System->result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(System->result);
                }

                System->channel->getCurrentSound(&currentsound);
                if (currentsound)
                {
                    System->result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                    if ((System->result != FMOD_OK) && (System->result != FMOD_ERR_INVALID_HANDLE) && (System->result != FMOD_ERR_CHANNEL_STOLEN))
                    {
                        ERRCHECK(System->result);
                    }
                }
            }

            System->system->getChannelsPlaying(&channelsplaying, NULL);

            Common_Draw("==================================================");
            Common_Draw("Sound System FMOD - Sound programming Exam");
            Common_Draw("Bertini Luca, Castagnetti Paolo, Guardini Matteo");
            Common_Draw("==================================================");
            Common_Draw("");
            Common_Draw("%s) To play a mono sound (drumloop)", Common_BtnStr(BTN_ACTION1));
            Common_Draw("%s) To play a mono sound (jaguar)", Common_BtnStr(BTN_ACTION2));
            Common_Draw("%s) To play a stereo sound (swish)", Common_BtnStr(BTN_ACTION3));
            Common_Draw("%s) To put the sound in loop", Common_BtnStr(BTN_LOOP_ON));
            Common_Draw("%s) To remove the loop", Common_BtnStr(BTN_LOOP_OFF));
            Common_Draw("%s) To stop the sound", Common_BtnStr(BTN_STOP));
            Common_Draw("%s) To pause/resume the sound", Common_BtnStr(BTN_PAUSE));
            Common_Draw("%s) To put the pan right", Common_BtnStr(BTN_PAN_UP));
            Common_Draw("%s) To put the pan left", Common_BtnStr(BTN_PAN_DOWN));
            Common_Draw("%s) To increse the volume", Common_BtnStr(BTN_PLUS));
            Common_Draw("%s) To decrese the volume", Common_BtnStr(BTN_MINUS));
            Common_Draw("%s) To quit", Common_BtnStr(BTN_QUIT));
            Common_Draw("");
            std::string volumeString = "";
            for (float i = 0; i < 1; i+= 0.1)
            {
                if (i < System->getVolume())
                {
                    volumeString += "X";
                }
                else
                {
                    volumeString += ".";
                }
            }
            Common_Draw("Volume: [%s]", volumeString.c_str());
            Common_Draw("");
            std::string panString = "";
            for (float i = -1; i < 1.1; i += 0.1)
            {
                float nearest = roundf(i * 10) / 10;
                if (nearest == System->getPan())
                {
                    panString += "O";
                }
                else if (nearest == 0)
                {
                    panString += "|";
                }
                else {
                    panString += ".";
                }
            }
            Common_Draw("Current Pan: [%s]", panString.c_str());
            
            Common_Draw("Time %02d:%02d:%02d/%02d:%02d:%02d : %s", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
            Common_Draw("Channels Playing %d", channelsplaying);
            char* channelGroupName = new char;
            System->channelGroup->getName(channelGroupName, 5);
            Common_Draw("Current channel group name: %s", channelGroupName);
        }
        
		Common_Sleep(50);
	} while (!Common_BtnPress(BTN_QUIT));

	//System release
	if (!System->release()) return 0;

    Common_Close();

	//Releasing system memory
	delete(System);

	//Close program
	return 0;
}