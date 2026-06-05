# Snake

A classic Snake game built with SDL3 and C++.

## Dependencies

- [SDL3](https://github.com/libsdl-org/SDL)
- [SDL3_image](https://github.com/libsdl-org/SDL_image)
- [SDL3_ttf](https://github.com/libsdl-org/SDL_ttf)
- [CMake](https://cmake.org/) 3.14+
- A C++17 compatible compiler

> SDL3_mixer and GoogleTest are fetched automatically at build time.

## Building

### 1. Clone the repository

```bash
git clone https://github.com/yourusername/snake.git
cd snake
```

### 2. Install dependencies

**macOS (Homebrew)**
```bash
brew install sdl3 sdl3_image sdl3_ttf
```

**Linux (apt)**
```bash
sudo apt install libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev
```

**Windows**

Download the development libraries for [SDL3](https://github.com/libsdl-org/SDL/releases), [SDL3_image](https://github.com/libsdl-org/SDL_image/releases), and [SDL3_ttf](https://github.com/libsdl-org/SDL_ttf/releases) and follow the setup instructions for your compiler.

### 3. Configure and build

```bash
cmake -B build
cmake --build build
```

### 4. Run

```bash
./build/src/Snake
```

## How to Play

| Key | Action |
|-----|--------|
| `W` / `↑` | Move up |
| `S` / `↓` | Move down |
| `A` / `←` | Move left |
| `D` / `→` | Move right |

- Click on the grid to pause.
- Eat food to grow your snake and increase your score
- Avoid hitting the walls or your own tail
- Your high score is saved between runs
