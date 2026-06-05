#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class FontManager
{
  public:
    FontManager() = default;
    TTF_Font *loadFont(const std::string &path, int size);
    TTF_Font *getFont(const std::string &path, int size) const;

    SDL_Texture *loadTextTexture(const std::string &key, const std::string &text,
                                TTF_Font *font, const SDL_Color &color,
                                SDL_Renderer *renderer);

    SDL_Texture* getTextTexture(const std::string& key) const;
    void clearFonts();
    void clearTextures();
    std::unordered_map<std::string, TTF_Font*> getFonts() const;
    std::unordered_map<std::string, SDL_Texture*> getTextTextures() const;


  private:
    std::unordered_map<std::string, TTF_Font *> m_fonts;
    std::unordered_map<std::string, SDL_Texture*> m_fontTextures;
};