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

	/**
	 * @brief Plays the provided FMOD sound using the Sound System.
	 *
	 * @param sound Pointer to the FMOD Sound object to be played.
	 * @return Boolean value indicating the success of playing the sound.
	 */
	bool playSound(FMOD::Sound *sound);

	/**
	 * @brief Sets the looping mode for the currently playing sound to continuous looping.
	 *
	 * @return Boolean value indicating the success of setting the looping mode.
	 */
	bool setLoopOn();

	/**
	 * @brief Disables the looping mode for the currently playing sound.
	 *
	 * @return Boolean value indicating the success of disabling the looping mode.
	 */
	bool setLoopOff();

	/**
	 * @brief Stops the currently playing sound.
	 *
	 * @return Boolean value indicating the success of stopping the sound.
	 */
	bool stop();

	FMOD::System* system;
	FMOD_RESULT result;
	FMOD::Channel* channel = 0;
	FMOD::Sound* s1;
	FMOD::Sound* s2;
	FMOD::Sound* s3;
	void* extradriverdata = 0;
};