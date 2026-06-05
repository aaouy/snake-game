#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager()
{
    MIX_Init();
    m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!m_mixer) { SDL_Log("Mixer failed: %s", SDL_GetError()); return; }
    m_track = MIX_CreateTrack(m_mixer);
}

AudioManager::~AudioManager()
{
  MIX_Quit();
}

MIX_Audio* AudioManager::loadAudio(const std::string &path, const std::string &name)
{
  MIX_Audio *audio{MIX_LoadAudio(m_mixer, path.c_str(), true)};
  m_sounds[name] = audio;
  return audio; 
}

void AudioManager::playAudio(const std::string &name, int audioStartTime, int audioEndTime)
{
  MIX_SetTrackAudio(m_track, m_sounds[name]);
  SDL_PropertiesID properties{SDL_CreateProperties()};

  SDL_SetNumberProperty(properties, MIX_PROP_PLAY_START_MILLISECOND_NUMBER,
                          audioStartTime);
  SDL_SetNumberProperty(properties, MIX_PROP_PLAY_MAX_MILLISECONDS_NUMBER,
                          audioEndTime);
  MIX_PlayTrack(m_track, properties);
  SDL_DestroyProperties(properties);

}

void AudioManager::clearSounds()
{
  for (const auto &pair : m_sounds)
    MIX_DestroyAudio(pair.second);
  m_sounds.clear();
}

MIX_Mixer *AudioManager::getMixer() const
{
  return m_mixer;
}

MIX_Track*AudioManager::getTrack() const
{
  return m_track;
}

std::unordered_map<std::string, MIX_Audio*> AudioManager::getSounds() const
{
  return m_sounds;
}

MIX_Audio* AudioManager::getCurrentAudio() const
{
    return MIX_GetTrackAudio(m_track);
}