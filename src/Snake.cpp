#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>

#include "Food.hpp"
#include "Grid.hpp"
#include "Snake.hpp"

Snake::Snake(float posX, float posY, float width, float height, float speedX, float speedY, Direction direction)
  : m_speedX{speedX}, m_speedY{speedY},  m_direction{direction}, m_nextDirection{direction}, m_width{width}
{
  SDL_FRect body{posX, posY, width, height};
  SDL_FRect head{posX + width, posY, width, height};
  SDL_FRect tail{posX - width, posY, width, height};

  switch (direction)
  {
  case Direction::Up:
    head.y = posY - specs::gridCellHeight;
    tail.y = posY + specs::gridCellHeight;
    break;
  case Direction::Left:
    head.x = posX - specs::gridCellWidth;
    tail.x = posX + specs::gridCellWidth;
    break;
  case Direction::Down:
    head.y = posY + specs::gridCellHeight;
    tail.y = posY - specs::gridCellHeight;
  default:
    break;
  }
  m_sections = {head, body, tail};
}

const SDL_FRect &Snake::getHead() const { return m_sections.front(); }

float Snake::getLength() const { return m_sections.size(); }

const std::vector<SDL_FRect> &Snake::getSections() const { return m_sections; }

const Snake::Direction &Snake::getDirection() const { return m_direction; }

void Snake::setSpeedX(float speedX) { m_speedX = speedX; }

void Snake::setSpeedY(float speedY) { m_speedY = speedY; }

void Snake::setDirection(const Snake::Direction &direction) {
  if (direction == Direction::Up && m_direction == Direction::Down)
    return;
  if (direction == Direction::Down && m_direction == Direction::Up)
    return;
  if (direction == Direction::Left && m_direction == Direction::Right)
    return;
  if (direction == Direction::Right && m_direction == Direction::Left)
    return;

  m_nextDirection = direction;
}

void Snake::setTexture(SDL_Texture *texture) { m_texture = texture; }

void Snake::incrementPosX() {
  SDL_FRect oldHead = m_sections[0];
  m_sections.insert(m_sections.begin(),
                    {oldHead.x + oldHead.w, oldHead.y, oldHead.w, oldHead.h});
  m_sections.pop_back();
}

void Snake::incrementPosY() {
  SDL_FRect oldHead = m_sections[0];
  m_sections.insert(m_sections.begin(),
                    {oldHead.x, oldHead.y + oldHead.h, oldHead.w, oldHead.h});
  m_sections.pop_back();
}

void Snake::decrementPosX() {
  SDL_FRect oldHead = m_sections[0];
  m_sections.insert(m_sections.begin(),
                    {oldHead.x - oldHead.w, oldHead.y, oldHead.w, oldHead.h});
  m_sections.pop_back();
}

void Snake::decrementPosY() {
  SDL_FRect oldHead = m_sections[0];
  m_sections.insert(m_sections.begin(),
                    {oldHead.x, oldHead.y - oldHead.h, oldHead.w, oldHead.h});
  m_sections.pop_back();
}

bool Snake::isEating(const Food &food) const {
  return getHead().x == food.getX() && getHead().y == food.getY();
}

bool Snake::willCollide(const Grid& grid) const 
{
  float nextX = getHead().x;
  float nextY = getHead().y;

  // Getting next position of head.
  switch (m_nextDirection) {
  case Direction::Up:
    nextY -= m_speedY;
    break;
  case Direction::Down:
    nextY += m_speedY;
    break;
  case Direction::Left:
    nextX -= m_speedX;
    break;
  case Direction::Right:
    nextX += m_speedX;
    break;
  }

  bool willCollideWithItself{
    std::any_of(m_sections.begin() + 1, m_sections.end(),
    [nextX, nextY](SDL_FRect section) {
      return section.x == nextX && section.y == nextY;
    })};
  
  bool willCollideWithGrid{(nextX < grid.getX()) ||
    (nextX + this->getHead().w > grid.getX() + grid.getWidth()) ||
    (nextY < grid.getY()) ||
    (nextY + this->getHead().h > grid.getY() + grid.getHeight())};

  return willCollideWithItself || willCollideWithGrid;

}

bool Snake::willEat(const Food &food) const {
  switch (m_nextDirection) {
  case Direction::Up:
    return (m_sections[0].x == food.getX() &&
            m_sections[0].y - m_speedY == food.getY());
  case Direction::Down:
    return (m_sections[0].x == food.getX() &&
            m_sections[0].y + m_speedY == food.getY());
  case Direction::Left:
    return (m_sections[0].x - m_speedX == food.getX() &&
            m_sections[0].y == food.getY());
  case Direction::Right:
    return (m_sections[0].x + m_speedX == food.getX() &&
            m_sections[0].y == food.getY());
  default:
    return false;
  }
}

void Snake::changePosition(float dx, float dy) {
  for (SDL_FRect &section : m_sections) 
  {
    section.x += dx;
    section.y += dy;
  }
}

void Snake::addHead() {
  m_direction = m_nextDirection;
  switch (m_direction) {
  case Direction::Up:
    m_sections.insert(m_sections.begin(), {getHead().x, getHead().y - m_speedY,
                                           getHead().w, getHead().h});
    break;
  case Direction::Down:
    m_sections.insert(m_sections.begin(), {getHead().x, getHead().y + m_speedY,
                                           getHead().w, getHead().h});
    break;
  case Direction::Left:
    m_sections.insert(m_sections.begin(), {getHead().x - m_speedX, getHead().y,
                                           getHead().w, getHead().h});
    break;
  case Direction::Right:
    m_sections.insert(m_sections.begin(), {getHead().x + m_speedX, getHead().y,
                                           getHead().w, getHead().h});
    break;
  default:
    break;
  }
}

void Snake::move() {
  m_direction = m_nextDirection;
  switch (m_direction) {
  case Direction::Up:
    decrementPosY();
    break;
  case Direction::Down:
    incrementPosY();
    break;
  case Direction::Left:
    decrementPosX();
    break;
  case Direction::Right:
    incrementPosX();
    break;
  default:
    break;
  }
}

void Snake::draw(SDL_Renderer *renderer) const {
  for (SDL_FRect section : m_sections) {
    SDL_RenderTexture(renderer, m_texture, nullptr, &section);
  }
}

void Snake::reset(float posX, float posY, float width, float height) {
  SDL_FRect tail{posX - width, posY, width, height};
  SDL_FRect body{posX, posY, width, height};
  SDL_FRect head{posX + width, posY, width, height};

  m_direction = Direction::Right;
  m_nextDirection = Direction::Right;
  m_sections = {head, body, tail};
}