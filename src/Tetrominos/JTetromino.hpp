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

JTetromino::JTetromino(/* args */) : Tetromino(3, 3, {{{.r = 102, .g = 128, .b = 104, .a = 255}, {.r = 90, .g = 101, .b = 173, .a = 255}, {.r = 72, .g = 87, .b = 160, .a = 255}}}, {0, 1, 0, 0, 1, 0, 1, 1, 0})
{
}

JTetromino::~JTetromino()
{
}
