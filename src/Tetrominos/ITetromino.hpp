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

ITetromino::ITetromino() : Tetromino(4, 4, {.r = 0, .g = 255, .b = 255, .a = 255}, {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0})
{
}

ITetromino::~ITetromino()
{
}
