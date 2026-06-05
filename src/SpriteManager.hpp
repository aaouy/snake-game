#pragma once

#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>

class SpriteManager
{
  public: 
    SpriteManager() = default;
    SDL_Texture* loadSpriteTexture(const std::string &path, SDL_Renderer *renderer);
    SDL_Texture* getSpriteTexture(const std::string &path) const;
    void clearTextures();
    std::unordered_map<std::string, SDL_Texture*> getTextures() const;
  
  private:
    std::unordered_map<std::string, SDL_Texture*> m_spriteTextures;
};