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

bool Sound::playSound(FMOD::Sound *sound) {
    this->result= system->playSound(sound, 0, false, &channel);
    ERRCHECK(this->result);

    int channelPlaying;
    system->getChannelsPlaying(&channelPlaying);
    if (!channelPlaying)
    {
        return true;
    }
    // Set the volume to the value incremented by VOLUME_CHANGE_VALUE clamped between 0 and 1
    channel->setVolume(Common_Clamp(0, volume, 1));

    return true;
}

bool Sound::setLoopOn() {
    this->result = channel->setMode(FMOD_LOOP_NORMAL);
    ERRCHECK(this->result);
    return true;
}

bool Sound::setLoopOff() {
    this->result = channel->setMode(FMOD_LOOP_OFF);
    ERRCHECK(this->result);
    return true;
}

bool Sound::stop() {
    this->result = channel->stop();
    ERRCHECK(this->result);
    return true;
}

bool Sound::changeVolume(float value) {
    
    int channelPlaying;
    system->getChannelsPlaying(&channelPlaying);
    if (!channelPlaying)
    {
        return true;
    }
    float currentVolume;
    // Get current volume of the active channel (there should be just one channel)
    channel->getVolume(&currentVolume);
    // Set the volume to the value incremented by VOLUME_CHANGE_VALUE clamped between 0 and 1
    this->result = channel->setVolume(Common_Clamp(0, (currentVolume + value), 1));
    channel->getVolume(&currentVolume);
    volume = currentVolume;
    ERRCHECK(this->result);
    return true;
}