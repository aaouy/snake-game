#pragma once

#include "GameState.hpp"
#include "Game.hpp"
#include <SDL3/SDL.h>

class PausedState : public GameState
{
  public:
    virtual ~PausedState() = default;
    void handleEvent(const SDL_Event& event, Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
};