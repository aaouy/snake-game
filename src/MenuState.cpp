#include <SDL3/SDL.h>
#include <iostream>

#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "Game.hpp"
#include "Grid.hpp"

void MenuState::handleEvent(const SDL_Event& event, Game& game)
{
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
  {
      Grid& grid = game.getGrid();
      float mouseX{event.button.x};
      float mouseY{event.button.y};

      if (mouseX >= grid.getX() && mouseX <= grid.getX() + grid.getWidth() &&
          mouseY >= grid.getY() && mouseY <= grid.getY() + grid.getHeight())
      {
          game.setState(std::make_unique<PlayingState>());
      }
    }
    else if (event.type == SDL_EVENT_MOUSE_MOTION)
    {
      Grid& grid = game.getGrid();
      float mouseX{event.button.x};
      float mouseY{event.button.y};

      if (mouseX >= grid.getX() && mouseX <= grid.getX() + grid.getWidth() &&
        mouseY >= grid.getY() && mouseY <= grid.getY() + grid.getHeight())
      {
        SDL_SetCursor(game.getHandCursor());
      }
      else
      {
        SDL_SetCursor(game.getDefaultCursor());
      }
    }
}

void MenuState::update(Game& game)
{
  return;
}

void MenuState::draw(Game& game)
{
  SDL_Renderer* renderer = game.getRenderer();
  Grid& grid = game.getGrid();

  grid.draw(renderer);

  FontManager& fontManager{game.getFontManager()};

  float w, h;
  // Rendering Title text.
  SDL_Texture* titleTexture = fontManager.getTextTexture(specs::titleTextTextureKey);
  SDL_GetTextureSize(titleTexture, &w, &h);
  float destRectX {grid.getX() + (grid.getWidth() - w) / 2};
  float destRectY {grid.getY() + (grid.getHeight() - h) / 2};
  SDL_FRect destRect{destRectX, destRectY, w, h};
  SDL_RenderTexture(renderer, titleTexture, nullptr, &destRect);
}