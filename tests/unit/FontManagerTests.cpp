#include <gtest/gtest.h>
#include "FontManager.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <SDL3/SDL.h>
#include "Specs.hpp"

class FontManagerTest : public testing::Test
{
  protected:
    FontManagerTest()
    {
      TTF_Init();
      m_fontManager.loadFont(specs::defaultFontPath, specs::fontSize);
      TTF_Font* font {m_fontManager.getFont(specs::defaultFontPath, specs::fontSize)};
      m_fontManager.loadTextTexture(specs::gameOverTextTextureKey, specs::gameOverText, font, {0, 0, 0, 0}, m_renderer);
    }
    
    ~FontManagerTest()
    {
      m_fontManager.clearFonts();
      m_fontManager.clearTextures();

      SDL_DestroyWindow(m_window);
      SDL_DestroyRenderer(m_renderer);

      TTF_Quit();
    }

    FontManager m_fontManager{};
    SDL_Window* m_window{SDL_CreateWindow(specs::windowName, specs::windowWidth, specs::windowHeight, SDL_WINDOW_RESIZABLE)};
    SDL_Renderer* m_renderer{SDL_CreateRenderer(m_window, nullptr)};
};

TEST_F(FontManagerTest, FontLoaded)
{
  EXPECT_EQ(m_fontManager.getFonts().size(), 1);
  EXPECT_NE(m_fontManager.getFont(specs::defaultFontPath, specs::fontSize), nullptr);
}

TEST_F(FontManagerTest, TextTextureLoaded)
{
  EXPECT_NE(m_fontManager.getTextTexture(specs::gameOverTextTextureKey), nullptr);
}

TEST_F(FontManagerTest, FontsAndTexturesDestroyed)
{
  m_fontManager.clearTextures();
  m_fontManager.clearFonts();
  EXPECT_EQ(m_fontManager.getFonts().size(), 0);
  EXPECT_EQ(m_fontManager.getTextTextures().size(), 0);
}


