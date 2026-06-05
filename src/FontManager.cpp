#include "FontManager.hpp"
#include <SDL3/SDL.h>

TTF_Font* FontManager::loadFont(const std::string &path, int size)
{
	const std::string fontPath = path + ":" + std::to_string(size);
	m_fonts[fontPath] = TTF_OpenFont(path.c_str(), size);
	return m_fonts[fontPath];
}
TTF_Font* FontManager::getFont(const std::string &path, int size) const
{
  const std::string fontPath = path + ":" + std::to_string(size);
  return m_fonts.at(fontPath);
}

SDL_Texture* FontManager::loadTextTexture(const std::string &key, const std::string &text,
    TTF_Font *font, const SDL_Color &color, SDL_Renderer *renderer)
{  
  if (m_fontTextures.count(key))
    SDL_DestroyTexture(m_fontTextures[key]);

  SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);
  m_fontTextures[key] = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  return m_fontTextures[key];
}

SDL_Texture* FontManager::getTextTexture(const std::string& key) const
{
  return m_fontTextures.at(key);
}

void FontManager::clearFonts()
{
  for (const auto &pair : m_fonts)
    TTF_CloseFont(pair.second);
  m_fonts.clear();  
}

void FontManager::clearTextures()
{
  for (const auto &pair : m_fontTextures)
    SDL_DestroyTexture(pair.second);
  m_fontTextures.clear(); 
}

std::unordered_map<std::string, TTF_Font*> FontManager::getFonts() const
{
  return m_fonts;
}

std::unordered_map<std::string, SDL_Texture*> FontManager::getTextTextures() const
{
  return m_fontTextures;
}