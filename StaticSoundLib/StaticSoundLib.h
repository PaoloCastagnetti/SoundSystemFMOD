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
	bool playSound(FMOD::Sound* sound);

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

	/**
	* @brief Changes the volume by the passed amount.
	*
	* @param The value to add to the volume
	*
	* @return Boolean value indicating the success of the change volume operation.
	*/
	bool changeVolume(float value);

	/**
	* @brief Returns the volume
	*
	* @return Floating value indicating the volume.
	*/
	float getVolume();

	/**
	* @brief Returns the pan
	*
	* @return Floating value indicating the pan.
	*/
	float getPan();

	/**
	* @brief Pause or unpause the sound
	*
	* @return Boolean value indicating whether to pause or unpause the sound
	*/
	bool setPause();

	/**
	* @brief Changes the pan by the passed amount
	*
	* @param The value to add to the pan
	*
	* @return Boolean value indicating the success of the change pan operation.
	*/
	bool changePan(float value);

	/**
	* @brief Load the volume and the pan into the channel that is currently playing.
	* This function is called just after the play sound to correctly play the sound with the volume and pan loaded
	*/
	void loadSoundInfo();

	FMOD::System* system;
	FMOD_RESULT result;
	FMOD::Channel* channel = 0;
	FMOD::ChannelGroup* channelGroup;
	FMOD::Sound* s1;
	FMOD::Sound* s2;
	FMOD::Sound* s3;
	void* extradriverdata = 0;

private:
	float volume = 0.5f;
	float pan = 0.0f;

};