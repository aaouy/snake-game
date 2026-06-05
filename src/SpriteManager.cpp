#include "SpriteManager.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

SDL_Texture* SpriteManager::loadSpriteTexture(const std::string &path, SDL_Renderer *renderer)
{
  if (m_spriteTextures.count(path))
      SDL_DestroyTexture(m_spriteTextures[path]);
  m_spriteTextures[path] = IMG_LoadTexture(renderer, path.c_str());
  return m_spriteTextures[path];
}

SDL_Texture* SpriteManager::getSpriteTexture(const std::string &path) const
{
  return m_spriteTextures.at(path);
}

void SpriteManager::clearTextures()
{
  for (const auto &pair : m_spriteTextures)
      SDL_DestroyTexture(pair.second);
  m_spriteTextures.clear();
}

std::unordered_map<std::string, SDL_Texture*> SpriteManager::getTextures() const
{
  return m_spriteTextures;
}