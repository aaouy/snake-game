#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>

#include "Specs.hpp"
#include "Food.hpp"

class Grid;

class Snake
{
  public:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    Snake(float posX, float posY, float width, float height, float speedX, float speedY, Direction direction = Direction::Right);
    const SDL_FRect& getHead() const;
    float getLength() const;
    const std::vector<SDL_FRect>& getSections() const;
    const Direction& getDirection() const;
    void setSpeedX(float speedX);
    void setSpeedY(float speedY);
    void setDirection(const Snake::Direction& direction);
    void setTexture(SDL_Texture* texture);
    void setPosition(float x, float y);
    void incrementPosX();
    void incrementPosY();
    void decrementPosX();
    void decrementPosY();
    bool isEating(const Food& food) const;
    bool willCollide(const Grid& grid) const;
    bool willEat(const Food& food) const;
    void changePosition(float dx, float dy);
    void addHead();
    void move();
    void draw(SDL_Renderer* renderer) const;
    void reset(float posX, float posY, float width, float height);

  private:
    std::vector<SDL_FRect> m_sections;
    float m_speedX{};
    float m_speedY{};
    float m_width{};
    Direction m_direction{Direction::Right};
    Direction m_nextDirection{Direction::Right}; // Prevents snake reversing direction immediately and colliding w/ itself.
    SDL_Texture* m_texture{};

}; 