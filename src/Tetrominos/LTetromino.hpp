#pragma once 

#include "Tetromino.hpp"


class LTetromino: public Tetromino
{
private:
    /* data */
public:
    LTetromino(/* args */);
    ~LTetromino();
};

LTetromino::LTetromino(/* args */): Tetromino(3, 3, {{{.r = 255, .g = 144, .b = 48, .a = 255}, {.r = 239, .g = 121, .b = 33, .a = 255}, {.r = 224, .g = 104, .b = 16, .a = 255}}}, {0, 1, 0, 0, 1, 0, 0, 1, 1})
{
}

LTetromino::~LTetromino()
{
}
