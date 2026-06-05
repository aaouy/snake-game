#include "Food.hpp"

#include <random>
#include <SDL3_image/SDL_image.h>
#include <iostream>

Food::Food(float w, float h)
  : m_boundaries{0, 0, w, h}
  {}

float Food::getX() const
{
  return m_boundaries.x;
}

float Food::getY() const
{
  return m_boundaries.y;
}

float Food::getWidth() const
{
  return m_boundaries.w;
}

float Food::getHeight() const
{
  return m_boundaries.h;
}

const SDL_Texture* Food::getTexture() const
{
  return m_texture;
}

void Food::setTexture(SDL_Texture* texture)
{
  m_texture = texture;
}

void Food::setX(float x)
{
  m_boundaries.x = x;
}

void Food::setY(float y)
{
  m_boundaries.y = y;
}

void Food::setWidth(float w)
{
  m_boundaries.w = w;
}

void Food::setHeight(float h)
{
  m_boundaries.h = h;
}

void Food::spawn(float xStart, float yStart, float xEnd, float yEnd, float xSkip, float ySkip, std::mt19937& rng)
{
  std::uniform_int_distribution<int> distX(0, (xEnd - xStart) / xSkip - 1);
  std::uniform_int_distribution<int> distY(0, (yEnd - yStart) / ySkip - 1);

  float x = xStart + distX(rng) * xSkip;
  float y = yStart + distY(rng) * ySkip;

  m_boundaries = {x, y, m_boundaries.w, m_boundaries.h};
}

void Food::draw(SDL_Renderer* renderer) const
{
  SDL_RenderTexture(renderer, m_texture, nullptr, &m_boundaries);
}
