#pragma once 

#include "Tetromino.hpp"

class ZTetromino: public Tetromino
{
public:
    ZTetromino(/* args */);
    ~ZTetromino();
};

ZTetromino::ZTetromino(/* args */) : Tetromino(3, 3, {{{.r = 255, .g = 72, .b = 72, .a = 255}, {.r = 239, .g = 32, .b = 41, .a = 255}, {.r = 208, .g = 24, .b = 24, .a = 255}}}, {1, 1, 0, 0, 1, 1, 0, 0, 0})
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

ZTetromino::~ZTetromino()
{
}
