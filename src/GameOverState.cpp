#include "GameOverState.hpp"
#include "MenuState.hpp"
#include "Game.hpp"
#include "SpriteManager.hpp"

#include <SDL3/SDL.h>
#include <memory>
#include <iostream>


void GameOverState::handleEvent(const SDL_Event& event, Game& game)
{
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
  {
    Grid& grid = game.getGrid();
    float mouseX{event.button.x};
    float mouseY{event.button.y};

    if (mouseX >= grid.getX() && mouseX <= grid.getX() + grid.getWidth() &&
        mouseY >= grid.getY() && mouseY <= grid.getY() + grid.getHeight())
    {
      game.reset();
      SpriteManager& spriteManager{game.getSpriteManager()};
    }
  }
}

void GameOverState::update(Game& game)
{
  int score{game.getScore()};
  if (score > game.getHighScore())
  {
    game.setHighScore(score);
    game.saveHighScore();
  }
}

void GameOverState::draw(Game& game)
{
  SDL_Renderer* renderer = game.getRenderer();
  Grid& grid = game.getGrid();
  Snake& snake = game.getSnake();
  Food& food = game.getFood();

  SpriteManager& spriteManager{game.getSpriteManager()};

  grid.draw(renderer);

  snake.setTexture(spriteManager.getSpriteTexture(specs::snakeTexturePausedPath));
  snake.draw(renderer);

  food.setTexture(spriteManager.getSpriteTexture(specs::foodTexturePausedPath));
  food.draw(renderer);

  game.drawHUD();

  // Rendering game over text.
  float w, h;

  FontManager& fontManager{game.getFontManager()};
  
  SDL_Texture* gameOverTexture{fontManager.getTextTexture(specs::gameOverTextTextureKey)};
  SDL_GetTextureSize(gameOverTexture, &w, &h);
  SDL_FRect destRect{grid.getX() + (grid.getWidth() - w) / 2, grid.getY() + (grid.getHeight() - h) / 2, w, h};
  SDL_RenderTexture(renderer, gameOverTexture, nullptr, &destRect);
}