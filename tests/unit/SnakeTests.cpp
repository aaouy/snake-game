#include <gtest/gtest.h>
#include "Snake.hpp"
#include "Specs.hpp"

class SnakeTest : public testing::Test
{
  protected:
    Snake m_snake {specs::snakeStartPosX, specs::snakeStartPosY, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight};
};

TEST_F(SnakeTest, StartingPosition)
{
  EXPECT_FLOAT_EQ(m_snake.getHead().x, specs::snakeStartPosX + specs::gridCellWidth);
  EXPECT_FLOAT_EQ(m_snake.getLength(), 3);
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Right);
}

TEST_F(SnakeTest, ChangeDirection)
{
  m_snake.setDirection(Snake::Direction::Left);
  m_snake.move();
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Right);

  m_snake.setDirection(Snake::Direction::Up);
  m_snake.move();
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Up);

  m_snake.setDirection(Snake::Direction::Down);
  m_snake.move();
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Up);

  m_snake.setDirection(Snake::Direction::Left);
  m_snake.move();
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Left);

  m_snake.setDirection(Snake::Direction::Right);
  m_snake.move();
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Left);

  m_snake.setDirection(Snake::Direction::Down);
  m_snake.move();
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Down);

  m_snake.setDirection(Snake::Direction::Up);
  m_snake.move();
  EXPECT_EQ(m_snake.getDirection(), Snake::Direction::Down);

}

TEST_F(SnakeTest, NewHead)
{
  float startX {m_snake.getHead().x};
  m_snake.addHead();
  EXPECT_FLOAT_EQ(m_snake.getHead().x, startX + specs::gridCellWidth);
  m_snake.move();
  EXPECT_FLOAT_EQ(m_snake.getHead().x, startX + 2 * specs::gridCellWidth);
}

