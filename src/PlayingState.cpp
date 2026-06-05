#include "PlayingState.hpp"
#include "PausedState.hpp"
#include "GameOverState.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include "Grid.hpp"
#include "Food.hpp"

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

void PlayingState::handleEvent(const SDL_Event& event, Game& game)
{
  if (event.type == SDL_EVENT_KEY_DOWN)
  {
    Snake& snake = game.getSnake();
    if ((event.key.key == SDLK_UP || event.key.key == SDLK_W) && snake.getDirection() != Snake::Direction::Down)
    {
      snake.setDirection(Snake::Direction::Up);
    }
    else if ((event.key.key == SDLK_DOWN || event.key.key == SDLK_S) && snake.getDirection() != Snake::Direction::Up)
    {
      snake.setDirection(Snake::Direction::Down);
    }
    else if ((event.key.key == SDLK_LEFT || event.key.key == SDLK_A) && snake.getDirection() != Snake::Direction::Right)
    {
      snake.setDirection(Snake::Direction::Left);
    }
    else if ((event.key.key == SDLK_RIGHT || event.key.key == SDLK_D) && snake.getDirection() != Snake::Direction::Left)
    {
      snake.setDirection(Snake::Direction::Right);
    }
  }
  else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
  {
    Grid& grid = game.getGrid();
    float mouseX{event.button.x};
    float mouseY{event.button.y};

    if (mouseX >= grid.getX() && mouseX <= grid.getX() + grid.getWidth() &&
        mouseY >= grid.getY() && mouseY <= grid.getY() + grid.getHeight())
    {
      game.setState(std::make_unique<PausedState>());
    }
  }
}

void PlayingState::update(Game& game)
{
  Snake& snake = game.getSnake();
  Food& food = game.getFood();
  Grid& grid = game.getGrid();

  if (snake.willCollide(grid))
  {
    if (!game.isMuted())
        game.getAudioManager().playAudio(specs::gameOverAudioKey, 100, -1);
    game.setState(std::make_unique<GameOverState>());
    return;
  }
  if (snake.willEat(food))
  {
    if (!game.isMuted())
        game.getAudioManager().playAudio(specs::snakeEatingAudioKey, 75, -1);
    snake.addHead();
    return;
  }
  if (snake.isEating(food))
  {   
    std::vector<SDL_FRect> sections{snake.getSections()};
    do 
    {
      food.spawn(grid.getX(), grid.getY(), grid.getX() + grid.getWidth(),
          grid.getY() + grid.getHeight(), grid.getCellWidth(), grid.getCellHeight(), game.getRandomEngine());
    }
    while (std::any_of(sections.begin(), sections.end(), [&](const SDL_FRect& s)
    {
      return s.x == food.getX() && s.y == food.getY();
    }));

    game.incrementScore();
      
  }
  snake.move();

}

void PlayingState::draw(Game& game)
{
  SDL_Renderer* renderer = game.getRenderer();
  Grid& grid = game.getGrid();

  grid.draw(renderer);
  game.getSnake().draw(renderer);
  game.getFood().draw(renderer);

  game.drawHUD();

}