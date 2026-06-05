#include <gtest/gtest.h>
#include <SDL3/SDL.h>
#include <cmath>
#include "Food.hpp"
#include "Specs.hpp"

class FoodTest : public testing::Test
{
  protected:
    Food m_food {10, 10};
};

TEST_F(FoodTest, InitialSize)
{
  EXPECT_EQ(m_food.getWidth(), 10);
  EXPECT_EQ(m_food.getHeight(), 10);
}

TEST_F(FoodTest, InitialPosition)
{
  EXPECT_EQ(m_food.getX(), 0);
  EXPECT_EQ(m_food.getY(), 0);
}

TEST_F(FoodTest, TextureSet)
{
  SDL_Window* window {SDL_CreateWindow(specs::windowName, specs::windowWidth, specs::windowHeight, SDL_WINDOW_RESIZABLE)};
  SDL_Renderer* renderer {SDL_CreateRenderer(window, nullptr)};

  SDL_Texture* texture{IMG_LoadTexture(renderer, specs::defaultFoodTexturePath)};
  m_food.setTexture(texture);
  EXPECT_NE(m_food.getTexture(), nullptr);

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

TEST_F(FoodTest, SpawnIsWithinBounds)
{
  std::mt19937 rng(42);

  float xStart {specs::gridX};
  float xEnd {specs::gridX + specs::gridWidth};
  float xSkip {specs::gridCellWidth};
  float yStart {specs::gridY};
  float yEnd {specs::gridY + specs::gridHeight};
  float ySkip {specs::gridCellHeight};

  m_food.spawn(xStart, yStart, xEnd, yEnd, xSkip, ySkip, rng);

  EXPECT_GE(m_food.getX(), xStart);
  EXPECT_LT(m_food.getX(), xEnd);
  EXPECT_GE(m_food.getY(), yStart);
  EXPECT_LT(m_food.getY(), yEnd);
}

TEST_F(FoodTest, SpawnAlignsToGrid)
{
  std::mt19937 rng(42);
  float xStart {specs::gridX};
  float xEnd {specs::gridX + specs::gridWidth};
  float xSkip {specs::gridCellWidth};
  float yStart {specs::gridY};
  float yEnd {specs::gridY + specs::gridHeight};
  float ySkip {specs::gridCellHeight};
  m_food.spawn(xStart, yStart, xEnd, yEnd, xSkip, ySkip, rng);

  EXPECT_FLOAT_EQ(std::fmod(m_food.getX(), specs::gridCellWidth), 0);
  EXPECT_FLOAT_EQ(std::fmod(m_food.getY(), specs::gridCellHeight), 0);
}

