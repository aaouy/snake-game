#pragma once

#include "GameState.hpp"

class Game;

class GameOverState : public GameState
{
  public:
    virtual ~GameOverState() = default;
    void handleEvent(const SDL_Event& event, Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
};