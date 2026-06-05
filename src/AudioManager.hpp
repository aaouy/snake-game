#pragma once

#include <iostream>
#include <SDL3_mixer/SDL_mixer.h>

class AudioManager
{
	public:
		AudioManager();
		~AudioManager() = default;
		MIX_Audio *loadAudio(const std::string &path, const std::string &name);
		void playAudio(const std::string &name, int audioStartTime = 0,
							int audioEndTime = -1);
		void clearSounds();
		MIX_Mixer* getMixer() const;
		MIX_Track* getTrack() const;
		MIX_Audio* getCurrentAudio() const;
		std::unordered_map<std::string, MIX_Audio*> getSounds() const;
	
	private:
		MIX_Mixer *m_mixer{};
		MIX_Track *m_track{};
		std::unordered_map<std::string, MIX_Audio *> m_sounds;
};