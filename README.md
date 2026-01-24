# Tetris SDL2

A modern, feature-rich implementation of the classic Tetris game written in C++ using the SDL2 library.

![Build Status](https://github.com/GlockPL/sdl_tetris/workflows/Build%20and%20Release/badge.svg)

## Features

- **Classic Tetris Gameplay** - All 7 standard tetrominos (I, O, T, S, Z, J, L)
- **SRS Rotation System** - Super Rotation System with proper wall kicks for smooth gameplay
- **Ghost Piece** - Visual preview showing where your piece will land
- **Next Piece Preview** - See what's coming next to plan your strategy
- **Score Tracking** - Points awarded for clearing lines
- **Smooth Controls** - 60 FPS with responsive input handling
- **Speed Control** - Hold 's' to drop pieces faster
- **Auto-Repeat** - Hold movement keys for continuous movement with proper delays

## Controls

| Key | Action |
|-----|--------|
| `A` | Move left |
| `D` | Move right |
| `S` | Speed up falling (soft drop) |
| `Q` | Rotate counter-clockwise |
| `E` | Rotate clockwise |

## Download & Play

### Pre-built Binaries

Download the latest release for your platform from the [Releases](../../releases) page:

- **Linux** - `tetris-linux-x64.zip`
- **Windows** - `tetris-windows-x64.exe.zip` (includes all required DLLs)

Simply extract the ZIP file and run the executable. On Linux, you may need to make it executable:

```bash
unzip tetris-linux-x64.zip
cd artifacts
chmod +x Tetris
./Tetris
```

On Windows, extract and double-click `Tetris.exe`.

## Building from Source

### Prerequisites

The game requires SDL2 and SDL2_ttf libraries to build.

#### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install -y libsdl2-dev libsdl2-ttf-dev cmake build-essential
```

#### Fedora/RHEL

```bash
sudo dnf install SDL2-devel SDL2_ttf-devel cmake gcc-c++
```

#### Arch Linux

```bash
sudo pacman -S sdl2 sdl2_ttf cmake base-devel
```

#### Windows

Download the development libraries:
- [SDL2 Development Libraries](https://github.com/libsdl-org/SDL/releases/latest)
- [SDL2_ttf Development Libraries](https://github.com/libsdl-org/SDL_ttf/releases/latest)

Extract them and note the paths for CMake configuration.

### Build Instructions

#### Linux

```bash
# Clone the repository
git clone https://github.com/GlockPL/sdl_tetris.git
cd sdl_tetris

# Create build directory
mkdir build && cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Run the game
./Tetris
```

#### Windows

```bash
# Clone the repository
git clone https://github.com/GlockPL/sdl_tetris.git
cd sdl_tetris

# Create build directory
mkdir build
cd build

# Configure (adjust paths to your SDL2 installation)
cmake .. -DCMAKE_BUILD_TYPE=Release -DSDL2_DIR="path/to/SDL2" -DSDL2_TTF_DIR="path/to/SDL2_ttf"

# Build
cmake --build . --config Release

# Copy SDL2 DLLs to the build directory
copy path\to\SDL2\lib\x64\SDL2.dll Release\
copy path\to\SDL2_ttf\lib\x64\SDL2_ttf.dll Release\

# Run the game
cd Release
Tetris.exe
```

## CI/CD

This project uses GitHub Actions for automated building and releasing:

- **Continuous Integration**: Every push to `main` triggers builds on both Linux and Windows
- **Automated Releases**: Pushing a tag (e.g., `v1.0.0`) automatically creates a GitHub Release with pre-built binaries for both platforms

### Creating a Release

```bash
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0
```

The GitHub Actions workflow will automatically:
1. Build the game on Ubuntu and Windows
2. Package the executables with assets
3. Include necessary DLLs for Windows
4. Create a GitHub Release with downloadable artifacts

See the workflow configuration in `.github/workflows/build-and-release.yml`.

## Project Structure

```
sdl_tetris/
├── src/
│   ├── main.cpp                 # Main game loop
│   ├── Grid.hpp                 # Game grid and rendering
│   ├── Deposits.hpp             # Placed blocks management
│   ├── Score.hpp                # Score tracking
│   └── Tetrominos/              # Tetromino implementations
│       ├── Tetromino.hpp        # Base tetromino class
│       ├── ITetromino.hpp       # I-piece
│       ├── OTetromino.hpp       # O-piece
│       ├── TTetromino.hpp       # T-piece
│       ├── STetromino.hpp       # S-piece
│       ├── ZTetromino.hpp       # Z-piece
│       ├── JTetromino.hpp       # J-piece
│       ├── LTetromino.hpp       # L-piece
│       └── TetrominoFactory.hpp # Factory pattern
├── assets/                      # Game assets (fonts, etc.)
├── CMakeLists.txt              # CMake build configuration
└── .github/workflows/          # CI/CD workflows
```

## Technical Details

- **Language**: C++17
- **Graphics Library**: SDL2
- **Font Rendering**: SDL2_ttf
- **Build System**: CMake 3.0+
- **Rotation System**: Super Rotation System (SRS) with wall kicks
- **Frame Rate**: Locked at 60 FPS
- **Gravity System**: Configurable fall speed (independent of frame rate)

## Game Mechanics

- **Fall Speed**: Pieces fall based on a gravity timer, not frame rate
- **Soft Drop**: Holding 's' increases fall speed by 8x
- **Wall Kicks**: Pieces automatically shift when rotating near walls
- **Line Clearing**: Complete lines are cleared with a fade animation
- **Ghost Piece**: Semi-transparent preview shows landing position

## Contributing

Contributions are welcome! Feel free to:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is open source and available under the MIT License.

## Acknowledgments

- SDL2 development team for the excellent multimedia library
- The Tetris Company for the original game concept
- SRS (Super Rotation System) specification for rotation mechanics
