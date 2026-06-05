#pragma once

#include "GameState.hpp"
#include <SDL3/SDL.h>

class Game;

class MenuState : public GameState
{
  public:
    virtual ~MenuState() = default;
    void handleEvent(const SDL_Event& event, Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
};