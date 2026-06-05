#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>

class Food
{
  public:
      Food(float w, float h);
      float getX() const;
      float getY() const;
      float getWidth() const;
      float getHeight() const;
      const SDL_Texture* getTexture() const;
      void setX(float x);
      void setY(float y); 
      void setWidth(float w); 
      void setHeight(float h); 
      void setTexture(SDL_Texture* texture);
      void spawn(float xStart, float yStart, float xEnd, float yEnd, float xSkip, float ySkip, std::mt19937& rng);
      void draw(SDL_Renderer* renderer) const;
  
  private:
      SDL_FRect m_boundaries{};
      SDL_Texture* m_texture{};

};
