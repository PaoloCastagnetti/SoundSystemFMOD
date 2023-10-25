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
}

bool Sound::init() {

    //Create a System object and initialize
    this->result = FMOD::System_Create(&system);
    ERRCHECK(this->result);

    // Initialize the system with the specified settings
    this->result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    ERRCHECK(this->result);

    // Load the sound files for 'drumloop.wav', 'jaguar.wav', and 'swish.wav'
    this->result = system->createSound(Common_MediaPath("drumloop.wav"), FMOD_DEFAULT, 0, &s1);
    ERRCHECK(this->result);

    this->result = system->createSound(Common_MediaPath("jaguar.wav"), FMOD_DEFAULT, 0, &s2);
    ERRCHECK(this->result);

    this->result = system->createSound(Common_MediaPath("swish.wav"), FMOD_DEFAULT, 0, &s3);
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
    result = system->update();
    ERRCHECK(result);

    // Return true to indicate successful update
    return true;
}

bool Sound::playSound(FMOD::Sound *sound) {
    //Example code
    this->result= system->playSound(sound, 0, false, &channel);
    ERRCHECK(result);
    
    return true;
}
