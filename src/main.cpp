#include "Snake.hpp"
#include "Grid.hpp"
#include "Food.hpp"
#include "Game.hpp"
#include "Specs.hpp"

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  MIX_Init();
  Game game{};
  game.run();
}