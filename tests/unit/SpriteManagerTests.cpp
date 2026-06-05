#include <gtest/gtest.h>
#include <iostream>
#include "SpriteManager.hpp"
#include "Specs.hpp"

class SpriteManagerTest : public testing::Test
{
  protected:
    SpriteManagerTest()
    { 
      SDL_Window* window {SDL_CreateWindow(specs::windowName, specs::windowWidth, specs::windowHeight, SDL_WINDOW_RESIZABLE)};
      SDL_Renderer* renderer {SDL_CreateRenderer(window, nullptr)};
      m_spriteManager.loadSpriteTexture(specs::defaultSnakeTexturePath, renderer);
    }

    ~SpriteManagerTest()
    {
      m_spriteManager.clearTextures();
    }

    SpriteManager m_spriteManager{};
};

TEST_F(SpriteManagerTest, TextureLoaded)
{
  EXPECT_EQ(m_spriteManager.getTextures().size(), 1);
  EXPECT_NE(m_spriteManager.getTextures().at(specs::defaultSnakeTexturePath), nullptr);
}

TEST_F(SpriteManagerTest, TexturesCleared)
{
  m_spriteManager.clearTextures();
  EXPECT_EQ(m_spriteManager.getTextures().size(), 0);
}