#pragma once
#include "Tetromino.hpp"

class OTetromino : public Tetromino
{
private:
    /* data */
public:
    OTetromino();
    ~OTetromino();
};

OTetromino::OTetromino() : Tetromino(2, 2, {.r = 255, .g = 255, .b = 0, .a = 255}, {1, 1, 1, 1})
{
}

OTetromino::~OTetromino()
{
}
