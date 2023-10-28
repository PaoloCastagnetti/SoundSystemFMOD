#include "pch.h"
#include "framework.h"
#include "StaticSoundLib.h"
#include <iostream>

//Library functions implementations

Sound::Sound() {
	this->s1 = nullptr;
	this->s2 = nullptr;
	this->s3 = nullptr;
	this->system = nullptr;
	this->result = FMOD_OK;
}

bool Sound::init() {

	// Initialize Common with the extradriverdata
	Common_Init(&extradriverdata);

	//Create a System object and initialize
	this->result = FMOD::System_Create(&system);
	ERRCHECK(this->result);

	// Initialize the system with the specified settings
	this->result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ERRCHECK(this->result);

	// Load the sound files for 'drumloop.wav', 'jaguar.wav', and 'swish.wav'
	this->result = system->createSound(Common_MediaPath("drumloop.wav"), FMOD_LOOP_OFF, 0, &s1);
	ERRCHECK(this->result);

	this->result = system->createSound(Common_MediaPath("jaguar.wav"), FMOD_LOOP_OFF, 0, &s2);
	ERRCHECK(this->result);

	this->result = system->createSound(Common_MediaPath("swish.wav"), FMOD_LOOP_OFF, 0, &s3);
	ERRCHECK(this->result);

	// Initialization of the main channel group
	FMOD::ChannelGroup* tmpChannelGroup;
	this->result = system->createChannelGroup("main", &tmpChannelGroup);
	ERRCHECK(this->result);

	// Set the volume to 0.5
	tmpChannelGroup->setVolume(volume);

	// Add it to the vector of channel group
	channelGroupVector.push_back(tmpChannelGroup);

	// Add the pan value to the vector
	panValues.push_back(0);

	// Initialization of the side channel group
	this->result = system->createChannelGroup("side", &tmpChannelGroup);
	ERRCHECK(this->result);

	// Set the volume to 0.5
	tmpChannelGroup->setVolume(volume);
	
	// Add it to the vector of channel group
	channelGroupVector.push_back(tmpChannelGroup);
	// Add the pan value to the vector
	panValues.push_back(0);

	// Set the current channel group to the main channel group
	channelGroup = channelGroupVector[0];

	// Set the channel group of the current channel to the one just created
	//this->result = channel->setChannelGroup(channelGroup);
	//ERRCHECK(this->result);

	// Return true to indicate successful initialization
	return true;
}

bool Sound::release() {
	// Release the resources for s1, s2, and s3
	this->result = s1->release();
	ERRCHECK(this->result);
	this->result = s2->release();
	ERRCHECK(this->result);
	this->result = s3->release();
	ERRCHECK(this->result);

	// Release the channel group
	this->result = channelGroup->release();
	ERRCHECK(this->result);

	// Close the system and release its resources
	this->result = system->close();
	ERRCHECK(this->result);
	this->result = system->release();
	ERRCHECK(this->result);

	// Return true to indicate successful release
	return true;
}

bool Sound::update() {
	// Update the system
	this->result = system->update();
	ERRCHECK(this->result);

	// Return true to indicate successful update
	return true;
}

bool Sound::playSound(FMOD::Sound* sound) {
	int channelsplaying = 0;
	system->getChannelsPlaying(&channelsplaying, NULL);

	//if (channelsplaying == 0) {
		this->result = system->playSound(sound, channelGroup, false, &channel);
		ERRCHECK(this->result);
		//loadSoundInfo();
	//}
	return true;
}

bool Sound::setLoopOn() {
	int channelsplaying = 0;
	system->getChannelsPlaying(&channelsplaying, NULL);
	if (channelsplaying != 0) {
		int numChannels;
		channelGroup->getNumChannels(&numChannels);
		for (int i = 0; i < numChannels; i++)
		{
			FMOD::Channel *tmpChannel;
			channelGroup->getChannel(i, &tmpChannel);
			this->result = tmpChannel->setMode(FMOD_LOOP_NORMAL);
			ERRCHECK(this->result);
		}

		
	}
	return true;
}

bool Sound::setLoopOff() {
	int channelsplaying = 0;
	system->getChannelsPlaying(&channelsplaying, NULL);
	if (channelsplaying != 0) {
		int numChannels;
		channelGroup->getNumChannels(&numChannels);
		for (int i = 0; i < numChannels; i++)
		{
			FMOD::Channel* tmpChannel;
			channelGroup->getChannel(i, &tmpChannel);
			this->result = tmpChannel->setMode(FMOD_LOOP_OFF);
			ERRCHECK(this->result);
		}
	}
	return true;
}

bool Sound::stop() {
	int channelsplaying = 0;
	system->getChannelsPlaying(&channelsplaying, NULL);
	if (channelsplaying != 0) {
		this->result = channelGroup->stop();
		ERRCHECK(this->result);
	}
	return true;
}

bool Sound::changeVolume(float value) {

	int channelPlaying;
	system->getChannelsPlaying(&channelPlaying);
	volume = Common_Clamp(0, (volume + value), 1);
	float nearest = roundf(volume * 10) / 10;
	volume = nearest;
	// Set the volume to the incremented value
	this->result = channelGroup->setVolume(volume);
	ERRCHECK(this->result);

	return true;
}

float Sound::getVolume() {
	return volume;
}

bool Sound::setPause() {
	int channelsplaying = 0;
	system->getChannelsPlaying(&channelsplaying, NULL);
	if (channelsplaying != 0) {
		bool paused;
		channelGroup->getPaused(&paused);
		this->result = channelGroup->setPaused(!paused);
		ERRCHECK(this->result);
	}
	return true;
}

bool Sound::changePan(float value) {
	int channelPlaying;
	system->getChannelsPlaying(&channelPlaying);

	// Update the pan by adding the value and clamping it between -1 and 1
	pan = Common_Clamp(-1, (pan + value), 1);
	float nearest = roundf(pan * 10) / 10;
	pan = nearest;
	this->result = channelGroup->setPan(pan);
	ERRCHECK(this->result);
	// Set the pan of the channel to the pan calculated before
	//this->result = channel->setPan(pan);
	//ERRCHECK(this->result);
	return true;
}

float Sound::getPan() {
	return pan;
}

void Sound::loadSoundInfo() {
	int channelPlaying;
	system->getChannelsPlaying(&channelPlaying);
	if (!channelPlaying)
	{
		return;
	}
	// Set the volume to the value saved
	channelGroup->setVolume(Common_Clamp(0, volume, 1));

	// Set the pan to the value saved
	channelGroup->setPan(pan);
}

void Sound::changeChannelGroup() {

	// Save the current pan value
	panValues[channelGroupIndex] = pan;

	// Check if the current channel group selected is the last one
	if (channelGroupIndex == channelGroupVector.size() - 1)
	{
		// Set it to 0 to get the first
		channelGroupIndex = 0;
	}
	else
	{
		// Increment it to get the next one
		channelGroupIndex++;
	}

	// Change the current channel group
	channelGroup = channelGroupVector[channelGroupIndex];

	// Update the values volume
	channelGroup->getVolume(&volume);

	// Set the pan value
	pan = panValues[channelGroupIndex];
	channelGroup->setPan(pan);
}