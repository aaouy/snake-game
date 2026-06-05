#pragma once

#include <SDL3/SDL.h>
#include "Specs.hpp"
#include "Snake.hpp"

#include <random>

class Grid
{
  public:
    Grid(float x, float y, float width, float height, float cellWidth, 
        float cellHeight, float border = 0, float padding = 0);
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    float getCellWidth() const;
    float getCellHeight() const;
    float getNumRows() const;
    float getNumCols() const;
    float getPadding() const;
    float getBorder() const;
    void setX(float x);
    void setY(float y); 
    void setWidth(float w); 
    void setHeight(float h); 
    void draw(SDL_Renderer* renderer) const;
          
  private:
    SDL_FRect m_boundaries{};
    float m_cellWidth{};
    float m_cellHeight{};
    float m_numRows{};
    float m_numCols{};
    float m_border{};
    float m_padding{};
};

