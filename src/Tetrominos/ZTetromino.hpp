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

ZTetromino::ZTetromino(/* args */) : Tetromino(3, 3, {{{.r = 255, .g = 72, .b = 72, .a = 255}, {.r = 239, .g = 32, .b = 41, .a = 255}, {.r = 208, .g = 24, .b = 24, .a = 255}}}, {1, 1, 0, 0, 1, 1, 0, 0, 0})
{
}

ZTetromino::~ZTetromino()
{
}
