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

STetromino::STetromino(/* args */) : Tetromino(3, 3, {.r = 0, .g = 255, .b = 0, .a = 255}, {0, 1, 1, 1, 1, 0, 0, 0, 0})
{
}

STetromino::~STetromino()
{
}
