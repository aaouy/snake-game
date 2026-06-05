#include <gtest/gtest.h>
#include "Snake.hpp"
#include "Grid.hpp"
#include "Specs.hpp"
#include "Game.hpp"

class SnakeCollisionTest : public testing::Test
{
  protected:
    Game m_game{};
    Snake& m_snake{m_game.getSnake()};
    Grid& m_grid{m_game.getGrid()};
};

TEST_F(SnakeCollisionTest, SnakeHeadCollidesWithRightBoundary)
{
  Snake snake{specs::gridX + specs::gridWidth - specs::gridCellWidth, specs::snakeStartPosY, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Right};
  EXPECT_EQ(snake.willCollide(m_grid), true);

}

TEST_F(SnakeCollisionTest, SnakeHeadCollidesWithBottomBoundary)
{
  Snake snake{specs::snakeStartPosX, specs::gridY + specs::gridHeight - specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Down};
  EXPECT_EQ(snake.willCollide(m_grid), true);
}

TEST_F(SnakeCollisionTest, SnakeHeadCollidesWithLeftBoundary)
{
  Snake snake{specs::gridX + specs::gridCellWidth, specs::snakeStartPosY, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Left};
  EXPECT_EQ(snake.willCollide(m_grid), true);
}

TEST_F(SnakeCollisionTest, SnakeHeadCollidesWithTopBoundary)
{
  Snake snake{specs::snakeStartPosX, specs::gridY - specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Up};
  EXPECT_EQ(snake.willCollide(m_grid), true);
}

TEST_F(SnakeCollisionTest, SnakePassesRightBoundary)
{
  Snake snake{specs::gridX + specs::gridWidth, specs::snakeStartPosY, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Right};
  EXPECT_EQ(snake.willCollide(m_grid), true);
}

TEST_F(SnakeCollisionTest, SnakePassesBottomBoundary)
{
  Snake snake{specs::snakeStartPosX, specs::gridY + specs::gridHeight, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Down};
  EXPECT_EQ(snake.willCollide(m_grid), true);
}

TEST_F(SnakeCollisionTest, SnakePassesLeftBoundary)
{
  Snake snake{specs::gridX, specs::snakeStartPosY, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Left};
  EXPECT_EQ(snake.willCollide(m_grid), true);
}

TEST_F(SnakeCollisionTest, SnakePassesTopBoundary)
{
  Snake snake{specs::snakeStartPosX, specs::gridY, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight, Snake::Direction::Up};
  EXPECT_EQ(snake.willCollide(m_grid), true);
}