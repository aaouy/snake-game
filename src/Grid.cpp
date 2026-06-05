#include "Grid.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Specs.hpp"

#include <iostream>
#include <random>
#include <stdexcept>

Grid::Grid(float x, float y, float width, float height, float cellWidth, float cellHeight, float m_border, float m_padding)
  : m_boundaries{x, y, width, height}
  , m_cellWidth{cellWidth}
  , m_cellHeight{cellHeight}
  , m_numRows{height / cellHeight}
  , m_numCols{width / cellWidth}
  , m_border{m_border}
  , m_padding{m_padding} 
{
  if (m_padding >= cellWidth || m_padding >= cellHeight)
  {
    throw std::out_of_range("Padding must be smaller than cell width and height.");
  }
}

float Grid::getX() const
{
  return m_boundaries.x;
}

float Grid::getY() const
{
  return m_boundaries.y;
}

float Grid::getWidth() const
{
  return m_boundaries.w;
}

float Grid::getHeight() const
{
  return m_boundaries.h;
}

float Grid::getCellWidth() const
{
  return m_cellWidth;
}

float Grid::getCellHeight() const
{
  return m_cellHeight;
}

float Grid::getNumRows() const
{
  return m_numRows;
}

float Grid::getNumCols() const
{
  return m_numCols;
}

float Grid::getPadding() const
{
  return m_padding;
}

float Grid::getBorder() const
{
  return m_border;
}

void Grid::setX(float x)
{
  m_boundaries.x = x;
}

void Grid::setY(float y)
{
  m_boundaries.y = y;
}

void Grid::setWidth(float w)
{
  m_boundaries.w = w;
}

void Grid::setHeight(float h)
{
  m_boundaries.h = h;
}

void Grid::draw(SDL_Renderer* renderer) const
{
  SDL_FRect paddingRect{
    m_boundaries.x - m_padding,
    m_boundaries.y - m_padding,
    m_boundaries.w + 2 * m_padding,
    m_boundaries.h + 2 * m_padding
  };

  SDL_FRect borderRect{
    m_boundaries.x - m_padding - m_border,
    m_boundaries.y - m_padding - m_border,
    m_boundaries.w + 2 * (m_border + m_padding),
    m_boundaries.h + 2 * (m_border + m_padding)
  };

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &borderRect);

  SDL_SetRenderDrawColor(renderer, 175, 225, 175, 255);
  SDL_RenderFillRect(renderer, &m_boundaries);
  SDL_RenderFillRect(renderer, &paddingRect);

}







