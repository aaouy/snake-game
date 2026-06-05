#include "Game.hpp"
#include "Snake.hpp"
#include "Grid.hpp"
#include "Food.hpp"
#include "Specs.hpp"
#include "SpriteManager.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"

#include <random>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

Game::Game()
	: m_window{SDL_CreateWindow(specs::windowName, specs::windowWidth, specs::windowHeight, SDL_WINDOW_RESIZABLE)}
	, m_renderer{SDL_CreateRenderer(m_window, nullptr)}
	, m_randomEngine{m_seed()}
	, m_spriteManager{SpriteManager{}}
	, m_audioManager{AudioManager{}}
	, m_fontManager{FontManager{}}
	, m_snake{specs::snakeStartPosX, specs::snakeStartPosY, specs::gridCellWidth, specs::gridCellHeight, specs::gridCellWidth, specs::gridCellHeight}
	, m_grid{specs::gridX, specs::gridY, specs::gridWidth, specs::gridHeight, specs::gridCellWidth, specs::gridCellHeight, specs::gridBorder, specs::gridPadding}
	, m_food{specs::gridCellWidth, specs::gridCellHeight}

{
	// Loading fonts, and creating them as textures.
	m_fontManager.loadFont(specs::defaultFontPath, specs::fontSize);
	m_fontManager.loadTextTexture(specs::pausedTextTextureKey, specs::pausedText, m_fontManager.getFont(specs::defaultFontPath, 96), 
			{0, 0, 0, 0}, m_renderer);
	m_fontManager.loadTextTexture(specs::gameOverTextTextureKey, specs::gameOverText, m_fontManager.getFont(specs::defaultFontPath, 96), 
			{0, 0, 0, 0}, m_renderer);
	m_fontManager.loadTextTexture(specs::titleTextTextureKey, specs::titleText, m_fontManager.getFont(specs::defaultFontPath, 96), 
			{0, 0, 0, 0}, m_renderer);

	m_snake.setTexture(m_spriteManager.loadSpriteTexture(specs::defaultSnakeTexturePath, m_renderer));
	m_food.setTexture(m_spriteManager.loadSpriteTexture(specs::defaultFoodTexturePath, m_renderer));

	m_spriteManager.loadSpriteTexture(specs::snakeTexturePausedPath, m_renderer);
	m_spriteManager.loadSpriteTexture(specs::foodTexturePausedPath, m_renderer);
	m_spriteManager.loadSpriteTexture(specs::volumeButtonOffTexturePath, m_renderer);
	m_spriteManager.loadSpriteTexture(specs::volumeButtonOnTexturePath, m_renderer);

	m_audioManager.loadAudio(specs::snakeEatingSound, specs::snakeEatingAudioKey);
	m_audioManager.loadAudio(specs::gameOverSound, specs::gameOverAudioKey);

	m_handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
	m_defaultCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);

	loadHighScore();

	m_food.spawn(m_grid.getX(), m_grid.getY(), m_grid.getX() + m_grid.getWidth(), 
		m_grid.getY() + m_grid.getHeight(), m_grid.getCellWidth(), m_grid.getCellHeight(), m_randomEngine);
}

Game::~Game()
{
	saveHighScore();
	m_audioManager.clearSounds();
	m_fontManager.clearTextures();
	m_spriteManager.clearTextures();

	SDL_DestroyCursor(m_handCursor);
	SDL_DestroyCursor(m_defaultCursor);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	MIX_Quit();
	TTF_Quit(); 
	SDL_Quit();
}

void Game::update()
{
	Uint64 now{SDL_GetTicks()};
	if (now - m_lastUpdate >= m_moveDelay)
	{
		m_state->update(*this);
		m_lastUpdate = now;
	}
}

void Game::draw()
{
	drawVolumeIcon();
	m_state->draw(*this);
}

void Game::loadHighScore()
{
	std::ifstream file (std::string(SDL_GetBasePath()) + "highscore.txt");

	if (file.is_open())
	{
		file >> m_highScore;
	}
	else
	{
		m_highScore = 0;
	}
}

SDL_Cursor* Game::getHandCursor()
{
  return m_handCursor;
}

SDL_Cursor* Game::getDefaultCursor()
{
  return m_defaultCursor;
}

FontManager& Game::getFontManager()
{
  return m_fontManager;
}

AudioManager& Game::getAudioManager()
{
	return m_audioManager;
}

SpriteManager& Game::getSpriteManager()
{
  return m_spriteManager;
}

std::mt19937& Game::getRandomEngine()
{
  return m_randomEngine;
}

SDL_Renderer* Game::getRenderer()
{
  return m_renderer;
}

Snake& Game::getSnake()
{
  return m_snake;
}

Grid& Game::getGrid()
{
  return m_grid;
}

Food& Game::getFood()
{
  return m_food;
}

int Game::getScore() const
{
  return m_score;
}

int Game::getHighScore() const
{
  return m_highScore;
}

bool Game::isMuted() const
{
  return m_isMuted;
}

void Game::setState(std::unique_ptr<GameState> state)
{
  m_state = std::move(state);
}

void Game::setHighScore(int score)
{
  m_highScore = score;
}   

void Game::saveHighScore()
{
	std::ofstream file(std::string(SDL_GetBasePath()) + "highscore.txt");
	file << m_highScore;
}

void Game::mute()
{
  m_isMuted = true;
}

void Game::unmute()
{
  m_isMuted = false;
}

void Game::incrementScore()
{
  m_score += 1;
}

void Game::reset()
{
	float x{m_grid.getX() + static_cast<int>(m_grid.getNumCols() / 2) * m_grid.getCellWidth()};
	float y{m_grid.getY() + static_cast<int>(m_grid.getNumRows() / 2) * m_grid.getCellHeight()};

	// Reset score.
	m_score = 0;

	// Reset snake length and position.
	m_snake.reset(x, y, m_grid.getCellWidth(), m_grid.getCellHeight());

	// Respawn food at random location.
	m_food.spawn(m_grid.getX(), m_grid.getY(), m_grid.getX() + m_grid.getWidth(), 
	m_grid.getY() + m_grid.getHeight(), m_grid.getCellWidth(), m_grid.getCellHeight(), m_randomEngine);

	m_snake.setTexture(m_spriteManager.getSpriteTexture(specs::defaultSnakeTexturePath));
	m_food.setTexture(m_spriteManager.getSpriteTexture(specs::defaultFoodTexturePath));
	setState(std::make_unique<MenuState>());
}

void Game::drawHUD()
{
	SDL_Texture* scoreTexture{};

	if (m_score != m_lastRenderedScore) 
	{
		scoreTexture = m_fontManager.loadTextTexture(specs::scoreTextTextureKey, "Score: " + std::to_string(m_score), m_fontManager.getFont(specs::defaultFontPath, 96), {0, 0, 0, 0}, m_renderer);
		m_lastRenderedScore = m_score;
	}
	else
	{
		scoreTexture = m_fontManager.getTextTexture(specs::scoreTextTextureKey);
	}
	
	float w, h;
	// Rendering Score.
	SDL_GetTextureSize(scoreTexture, &w, &h);
	SDL_FRect destRect{m_grid.getX(), m_grid.getY() + m_grid.getHeight() + 10, w / 4, h / 4};
	SDL_RenderTexture(m_renderer, scoreTexture, nullptr, &destRect);

	std::string highScoreText = "High Score: " + std::to_string(m_highScore);
	SDL_Texture* highScoreTexture = m_fontManager.loadTextTexture(specs::highScoreTextTextureKey, highScoreText, 
	m_fontManager.getFont(specs::defaultFontPath, 96), {0, 0, 0, 0}, m_renderer);
	SDL_GetTextureSize(highScoreTexture, &w, &h);
	destRect = {m_grid.getX() + m_grid.getWidth() - w / 4, m_grid.getY() + m_grid.getHeight() + 10, w / 4, h / 4};
	SDL_RenderTexture(m_renderer, highScoreTexture, nullptr, &destRect);
}

void Game::drawVolumeIcon()
{
	const char* path = m_isMuted ? specs::volumeButtonOffTexturePath 
																: specs::volumeButtonOnTexturePath;
	SDL_RenderTexture(m_renderer, m_spriteManager.getSpriteTexture(path), nullptr, &m_volumeIconRect);
}

GameState& Game::getState() const 
{
	return *m_state;
}

void Game::run()
{
	bool running{true};
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}
			else if (event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				int w{event.window.data1};
				int h{event.window.data2};
				
				SDL_FPoint oldGridPos = {m_grid.getX(), m_grid.getY()};

				m_grid.setX((w - m_grid.getWidth()) / 2); 
				m_grid.setY((h - m_grid.getHeight()) / 2);

				SDL_FPoint newGridPos = {m_grid.getX(), m_grid.getY()};
				// Adjust position of snake and food when window size is adjusted.
				m_snake.changePosition(newGridPos.x - oldGridPos.x, newGridPos.y - oldGridPos.y);
				m_food.setX(m_food.getX() + newGridPos.x - oldGridPos.x);
				m_food.setY(m_food.getY() + newGridPos.y - oldGridPos.y);
			}
			else if (event.type == SDL_EVENT_MOUSE_MOTION)
			{
				float mouseX{event.button.x};
				float mouseY{event.button.y};

				if ((mouseX >= m_grid.getX() && mouseX <= m_grid.getX() + m_grid.getWidth() &&
						mouseY >= m_grid.getY() && mouseY <= m_grid.getY() + m_grid.getHeight()) || 
						(mouseX >= m_volumeIconRect.x && mouseX <= m_volumeIconRect.x + m_volumeIconRect.w && 
						mouseY >= m_volumeIconRect.y && mouseY <= m_volumeIconRect.y + m_volumeIconRect.h))
				{
					SDL_SetCursor(getHandCursor());
				}
				else if ((mouseX >= m_volumeIconRect.x && mouseX <= m_volumeIconRect.x + m_volumeIconRect.w) ||
								(mouseY >= m_volumeIconRect.y && mouseY <= m_volumeIconRect.y + m_volumeIconRect.h))
				{
					SDL_SetCursor(getHandCursor());
				}
				else
				{
					SDL_SetCursor(getDefaultCursor());
				}
			}

			else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				float mouseX{event.button.x};
				float mouseY{event.button.y};
				
				if (event.button.button == SDL_BUTTON_LEFT && (mouseX >= m_volumeIconRect.x && mouseX <= m_volumeIconRect.x + m_volumeIconRect.w && 
						mouseY >= m_volumeIconRect.y && mouseY <= m_volumeIconRect.y + m_volumeIconRect.h))
				{
					m_isMuted = !m_isMuted;
				}
			}
			else if (event.type == SDL_EVENT_KEY_DOWN)
			{
				if (event.key.key == SDLK_M)
				{
					m_isMuted = !m_isMuted;
				}
			}
	
			m_state->handleEvent(event, *this);
		}
		
		SDL_SetRenderDrawColor(m_renderer, 175, 225, 175, 255);
		SDL_RenderClear(m_renderer);
		
		update();
		draw();
		SDL_RenderPresent(m_renderer);
	}
}