#pragma once

#include "GameState.hpp"

#include <SDL3/SDL.h>

class Game;

class PlayingState : public GameState
{
  public:
    virtual ~PlayingState() = default;
    void handleEvent(const SDL_Event& event, Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
};