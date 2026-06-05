#pragma once

#include "Snake.hpp"
#include "Grid.hpp"
#include "Food.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"
#include "SpriteManager.hpp"

#include <random>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

class Game
{
  private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::random_device m_seed;
    std::mt19937 m_randomEngine;
    FontManager m_fontManager;
    AudioManager m_audioManager;
    SpriteManager m_spriteManager;
    std::unique_ptr<GameState> m_state = std::make_unique<MenuState>();
    Snake m_snake;
    Grid m_grid;
    Food m_food;
    int m_score{0};
    int m_highScore{0};
    SDL_Cursor* m_handCursor{};
    SDL_Cursor* m_defaultCursor{};
    const Uint64 m_moveDelay{150};
    Uint64 m_lastUpdate{SDL_GetTicks()};
    bool m_isMuted{false};
    SDL_FRect m_volumeIconRect{20, 20, 40, 40};
    int m_lastRenderedScore{-1};

  private:
    void draw();
    void loadHighScore();
  
  public:
    Game();
    ~Game();
    SDL_Cursor* getHandCursor();
    SDL_Cursor* getDefaultCursor();
    FontManager& getFontManager();
    SpriteManager& getSpriteManager();
    AudioManager& getAudioManager();
    std::mt19937& getRandomEngine();
    SDL_Renderer* getRenderer();
    Snake& getSnake();
    Grid& getGrid();
    Food& getFood();
    int getScore() const;
    int getHighScore() const;
    GameState& getState() const;
    bool isMuted() const;
    void setState(std::unique_ptr<GameState> state);
    void setHighScore(int score);
    void saveHighScore();
    void mute();
    void unmute();
    void incrementScore();
    void reset();
    void drawHUD();
    void drawVolumeIcon();
    void run();
    void update();

};