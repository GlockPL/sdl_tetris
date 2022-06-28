#pragma once 

#include "Tetromino.hpp"

class ZTetromino: public Tetromino
{
private:
    /* data */
public:
    ZTetromino(/* args */);
    ~ZTetromino();
};

ZTetromino::ZTetromino(/* args */) : Tetromino(3, 3, {.r = 255, .g = 0, .b = 0, .a = 255}, {1, 1, 0, 0, 1, 1, 0, 0, 0})
{
}

ZTetromino::~ZTetromino()
{
}
