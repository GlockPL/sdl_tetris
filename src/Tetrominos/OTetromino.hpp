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

OTetromino::OTetromino() : Tetromino(2, 2, {{{.r = 255, .g = 236, .b = 28, .a = 255}, {.r = 247, .g = 211, .b = 8, .a = 255}, {.r = 232, .g = 192, .b = 0, .a = 255}}}, {1, 1, 1, 1})
{
}

OTetromino::~OTetromino()
{
}
