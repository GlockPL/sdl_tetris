#pragma once

#include "Tetromino.hpp"

class TTetromino: public Tetromino
{
private:
    /* data */
public:
    TTetromino(/* args */);
    ~TTetromino();
};

TTetromino::TTetromino(/* args */) : Tetromino(3, 3, {{{.r = 198, .g = 88, .b = 180, .a = 255}, {.r = 173, .g = 77, .b = 156, .a = 255}, {.r = 152, .g = 56, .b = 160, .a = 136}}}, {0, 1, 0, 1, 1, 1, 0, 0, 0})
{
}

TTetromino::~TTetromino()
{
}
