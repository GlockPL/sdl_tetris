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

LTetromino::LTetromino(/* args */): Tetromino(3, 3, {.r = 255, .g = 129, .b = 0, .a = 255}, {0, 1, 0, 0, 1, 0, 0, 1, 1})
{
}

LTetromino::~LTetromino()
{
}
