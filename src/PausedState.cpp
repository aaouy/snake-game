#include <SDL3/SDL.h>

#include "PausedState.hpp"
#include "PlayingState.hpp"
#include "Game.hpp"
#include "Grid.hpp"

void PausedState::handleEvent(const SDL_Event& event, Game& game)
{
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
  {
    Grid& grid = game.getGrid();
    float mouseX{event.button.x};
    float mouseY{event.button.y};

    if (mouseX >= grid.getX() && mouseX <= grid.getX() + grid.getWidth() &&
        mouseY >= grid.getY() && mouseY <= grid.getY() + grid.getHeight())
    {
      SpriteManager& spriteManager{game.getSpriteManager()};
      game.getSnake().setTexture(spriteManager.getSpriteTexture(specs::defaultSnakeTexturePath));
      game.getFood().setTexture(spriteManager.getSpriteTexture(specs::defaultFoodTexturePath));
      game.setState(std::make_unique<PlayingState>());
    }
  }
}

void PausedState::update(Game& game)
{
  return;
}

void PausedState::draw(Game& game)
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
  
  float w, h;
  // Rendering Paused text.
  FontManager& fontManager{game.getFontManager()};
  SDL_Texture* pausedTexture{fontManager.getTextTexture(specs::pausedTextTextureKey)};
  SDL_GetTextureSize(pausedTexture, &w, &h);
  SDL_FRect destRect{grid.getX() + (grid.getWidth() - w) / 2, grid.getY() + (grid.getHeight() - h) / 2, w, h};
  SDL_RenderTexture(renderer, pausedTexture, nullptr, &destRect);
}