#include <gtest/gtest.h>
#include "Snake.hpp"
#include "Food.hpp"
#include "Specs.hpp"
#include "PlayingState.hpp"
#include "Game.hpp"

class SnakeEatingTests : public testing::Test
{
  protected:
    Game m_game{};
    Snake& m_snake{m_game.getSnake()};
    Food& m_food{m_game.getFood()};
};

TEST_F(SnakeEatingTests, SnakeWillEat)
{
    m_food.setX(specs::snakeStartPosX + 2 * specs::gridCellWidth);
    m_food.setY(specs::snakeStartPosY);

    EXPECT_EQ(m_snake.willEat(m_food), true);

}

TEST_F(SnakeEatingTests, SnakeGrows)
{
    m_game.setState(std::make_unique<PlayingState>());
    m_food.setX(specs::snakeStartPosX + 2 * specs::gridCellWidth);
    m_food.setY(specs::snakeStartPosY);

    GameState& gameState {m_game.getState()};
    gameState.update(m_game);
    EXPECT_EQ(m_snake.getLength(), 4);
    EXPECT_EQ(m_snake.isEating(m_food), true);

}

TEST_F(SnakeEatingTests, FoodRespawns)
{
    m_game.setState(std::make_unique<PlayingState>());
    m_food.setX(specs::snakeStartPosX + 2 * specs::gridCellWidth);
    m_food.setY(specs::snakeStartPosY);

    GameState& gameState {m_game.getState()};
    gameState.update(m_game);
    gameState.update(m_game);
    
    bool isFoodTouching {std::any_of(m_snake.getSections().begin(), m_snake.getSections().end(), [&](const SDL_FRect& s)
      {return s.x == m_food.getX() && s.y == m_food.getY();})};
    
    EXPECT_EQ(isFoodTouching, false);
    
}