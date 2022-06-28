#pragma once

#include "Tetromino.hpp"

class JTetromino : public Tetromino
{
private:
    /* data */
public:
    JTetromino(/* args */);
    ~JTetromino();
};

JTetromino::JTetromino(/* args */) : Tetromino(3, 3, {.r = 0, .g = 0, .b = 255, .a = 255}, {0, 1, 0, 0, 1, 0, 1, 1, 0})
{
}

JTetromino::~JTetromino()
{
}
