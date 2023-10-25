#pragma once
#include "fmod.hpp"
#include "common.h"
#include <list>

class Sound {
public:
	/**
	* @brief Default constructor, initialize the parameters
	*/
	Sound();

	/**
	 * @brief Initializes the sound system.
	 *
	 * @return Boolean value indicating the success of the initialization.
	 */
	bool init();
	/**
	 * @brief Releases the resources used by the Sound system.
	 *
	 * @return Boolean value indicating the success of the release operation.
	 */
	bool release();
	/**
	 * @brief Updates the Sound system.
	 *
	 * @return Boolean value indicating the success of the update operation.
	 */
	bool update();

	bool playSound(FMOD::Sound *sound);

	FMOD::System* system;
	FMOD_RESULT result;
	FMOD::Channel* channel = 0;
	FMOD::Sound* s1;
	FMOD::Sound* s2;
	FMOD::Sound* s3;
	void* extradriverdata = 0;
};