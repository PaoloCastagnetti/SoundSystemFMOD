#pragma once
#include "fmod.hpp"
#include "common.h"

class Sound {
public:
	float getVolume();
private:
	float volume;
};