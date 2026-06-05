#include "AudioManager.hpp"
#include "Specs.hpp"
#include <gtest/gtest.h>
#include <SDL3_mixer/SDL_mixer.h>


class AudioManagerTest : public testing::Test
{
  protected:
    AudioManagerTest()
    {
      MIX_Init();
      m_audioManager.loadAudio(specs::snakeEatingSound, specs::snakeEatingAudioKey);
    }

    ~AudioManagerTest()
    {
      m_audioManager.clearSounds();
      MIX_Quit();
    }

    AudioManager m_audioManager{};
};

TEST_F(AudioManagerTest, MixerCreated)
{
  EXPECT_NE(m_audioManager.getMixer(), nullptr);
}

TEST_F(AudioManagerTest, TrackCreated)
{
  EXPECT_NE(m_audioManager.getTrack(), nullptr);
}

TEST_F(AudioManagerTest, AudioLoaded) 
{
  EXPECT_EQ(m_audioManager.getSounds().size(), 1);
  EXPECT_NE(m_audioManager.getSounds().at(specs::snakeEatingAudioKey), nullptr);

}

TEST_F(AudioManagerTest, AudioPlaying)
{
  m_audioManager.playAudio(specs::snakeEatingAudioKey);
  EXPECT_NE(m_audioManager.getCurrentAudio(), nullptr);

}

TEST_F(AudioManagerTest, SoundsDestroyed)
{
  m_audioManager.clearSounds();
  EXPECT_EQ(m_audioManager.getSounds().size(), 0);
}

