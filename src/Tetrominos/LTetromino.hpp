#pragma once 

#include "Tetromino.hpp"


class LTetromino: public Tetromino
{
public:
    LTetromino(/* args */);
    ~LTetromino();
};

LTetromino::LTetromino(/* args */): Tetromino(3, 3, {{{.r = 255, .g = 144, .b = 48, .a = 255}, {.r = 239, .g = 121, .b = 33, .a = 255}, {.r = 224, .g = 104, .b = 16, .a = 255}}}, {0, 1, 0, 0, 1, 0, 0, 1, 1})
{
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->1", {{{.x=0,.y=0}, {.x=-1,.y=0},{.x=-1,.y=1},{.x=0,.y=-2},{.x=-1,.y=-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->0", {{{.x=0,.y=0}, {.x=1,.y=0},{.x=1,.y=-1},{.x=0,.y=2},{.x=1,.y=2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->2", {{{.x=0,.y=0}, {.x=1,.y=0},{.x=1,.y=-1},{.x=0,.y=2},{.x=1,.y=2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->1", {{{.x=0,.y=0}, {.x=-1,.y=0},{.x=-1,.y=1},{.x=0,.y=-2},{.x=-1,.y=-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->3", {{{.x=0,.y=0}, {.x=1,.y=0},{.x=1,.y=1},{.x=0,.y=-2},{.x=1,.y=-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->2", {{{.x=0,.y=0}, {.x=-1,.y=0},{.x=-1,.y=-1},{.x=0,.y=2},{.x=-1,.y=2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->0", {{{.x=0,.y=0}, {.x=-1,.y=0},{.x=-1,.y=-1},{.x=0,.y=2},{.x=-1,.y=2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->3", {{{.x=0,.y=0}, {.x=1,.y=0},{.x=1,.y=1},{.x=0,.y=-2},{.x=1,.y=-2}}}));
}

LTetromino::~LTetromino()
{
}
