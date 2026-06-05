#include "Specs.hpp"
#include <SDL3/SDL.h>
#include <string>

namespace specs
{
  constexpr float windowWidth{900};
  constexpr float windowHeight{900};

  constexpr float gridWidth{500};
  constexpr float gridHeight{300};
  constexpr float gridX{(windowWidth - gridWidth) / 2};
  constexpr float gridY{(windowHeight - gridHeight) / 2};
  constexpr float gridCellWidth{20};
  constexpr float gridCellHeight{20};

  constexpr float snakeStartPosX{gridX + static_cast<int>(gridWidth / (2 * gridCellWidth)) * gridCellWidth};
  constexpr float snakeStartPosY{gridY + static_cast<int>(gridHeight / (2 * gridCellHeight)) * gridCellHeight};

  constexpr float gridBorder{3};
  constexpr float gridPadding{2};

  const char* defaultSnakeTexturePath = "assets/sprites/snake.png";
  const char* defaultFoodTexturePath = "assets/sprites/food.png";
  const char* defaultFontPath = "assets/fonts/Quantico-Bold.ttf";
  const char* snakeTexturePausedPath = "assets/sprites/snake-paused.png";
  const char* foodTexturePausedPath = "assets/sprites/food-paused.png";
  const char* volumeButtonOnTexturePath = "assets/sprites/unmuted.png";
  const char* volumeButtonOffTexturePath = "assets/sprites/muted.png";

  const char* snakeEatingSound = "assets/sounds/eating.wav";
  const char* gameOverSound = "assets/sounds/game-over.wav";

  const char* snakeEatingAudioKey = "Snake Eating";
  const char* gameOverAudioKey = "Game Over";

  const char* pausedText = "Paused";
  const char* gameOverText = "Game Over";
  const char* titleText = "Snake";

  const char* scoreTextTextureKey = "Score";
  const char* highScoreTextTextureKey = "High Score";
  const char* gameOverTextTextureKey = "Game Over";
  const char* pausedTextTextureKey = "Paused";
  const char* titleTextTextureKey = "Title";

  const char* windowName = "Snake";

  constexpr int fontSize{96};
}