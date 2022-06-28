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

TTetromino::TTetromino(/* args */) : Tetromino(3, 3, {.r = 255, .g = 0, .b = 255, .a = 255}, {0, 1, 0, 1, 1, 1, 0, 0, 0})
{
}

TTetromino::~TTetromino()
{
}
