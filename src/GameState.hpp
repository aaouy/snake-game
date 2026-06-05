#pragma once

#include <SDL3/SDL.h>

class Game;

class GameState
{
  public:
    virtual ~GameState() = default;
    virtual void handleEvent(const SDL_Event& event, Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void draw(Game& game) = 0;
};