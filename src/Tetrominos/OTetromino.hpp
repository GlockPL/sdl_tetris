#pragma once
#include "Tetromino.hpp"

class OTetromino : public Tetromino
{

public:
    OTetromino();
    ~OTetromino();
};

OTetromino::OTetromino() : Tetromino(2, 2, {{{255, 236, 28, 255}, {247, 211, 8, 255}, {232, 192, 0, 255}}}, {1, 1, 1, 1})
{
}

OTetromino::~OTetromino()
{
}
