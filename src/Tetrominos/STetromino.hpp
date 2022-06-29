#pragma once 

#include "Tetromino.hpp"

class STetromino: public Tetromino
{
private:
    /* data */
public:
    STetromino(/* args */);
    ~STetromino();
};

STetromino::STetromino(/* args */) : Tetromino(3, 3, {{{.r = 72, .g = 208, .b = 72, .a = 255}, {.r = 66, .g = 182, .b = 66, .a = 255}, {.r = 48, .g = 160, .b = 48, .a = 255}}}, {0, 1, 1, 1, 1, 0, 0, 0, 0})
{
}

STetromino::~STetromino()
{
}
