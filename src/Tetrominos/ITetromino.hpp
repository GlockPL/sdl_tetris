#pragma once

#include <vector>
#include "Tetromino.hpp"

class ITetromino : public Tetromino
{
private:
    /* data */
public:
    ITetromino();
    ~ITetromino();
};

ITetromino::ITetromino() : Tetromino(4, 4, {{{.r = 72, .g = 224, .b = 255, .a = 255}, {.r = 49, .g = 199, .b = 239, .a = 255}, {.r = 32, .g = 176, .b = 224, .a = 255}}}, {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0})
{
}

ITetromino::~ITetromino()
{
}
