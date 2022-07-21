# Tetris SDL2
### Tetris written in C++ based on SDL2 library  
It requires to run SLD2 and SDL2_TTF

Installing on Ubuntu:  
```
sudo apt-get install -y libsdl2-dev
sudo apt-get install -y libsdl2-ttf-dev
```

Installing on Windows requires downloading libraries and than linking them during configuration of cmake project:  
[SDL2 Development Libraries 2.0.22](https://www.libsdl.org/download-2.0.php)  
[SDL2 TTF Development Libraries](https://github.com/libsdl-org/SDL_ttf/releases)

In order to build on Linux run this command:
```
cmake --build ./build --config Release --target Tetris
```

