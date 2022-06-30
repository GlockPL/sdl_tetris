#pragma once

#include <vector>
#include "Tetromino.hpp"

class ITetromino : public Tetromino
{
public:
    ITetromino();
    ~ITetromino();
};

ITetromino::ITetromino() : Tetromino(4, 4, {{{.r = 72, .g = 224, .b = 255, .a = 255}, {.r = 49, .g = 199, .b = 239, .a = 255}, {.r = 32, .g = 176, .b = 224, .a = 255}}}, {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0})
{
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->1", {{{.x=0,.y=0}, {.x=-2,.y=0},{.x=-1,.y=0},{.x=+2,.y=+1},{.x=-1,.y=-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->0", {{{.x=0,.y=0}, {.x=-1,.y=0},{.x=+2,.y=0},{.x=-1,.y=2},{.x=2,.y=-1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->2", {{{.x=0,.y=0}, {.x=-1,.y=0},{.x=2,.y=0},{.x=-1,.y=2},{.x=2,.y=-1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->1", {{{.x=0,.y=0}, {.x=1,.y=0},{.x=-2,.y=0},{.x=1,.y=-2},{.x=-2,.y=1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->3", {{{.x=0,.y=0}, {.x=2,.y=0},{.x=-1,.y=0},{.x=2,.y=1},{.x=-1,.y=-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->2", {{{.x=0,.y=0}, {.x=-2,.y=0},{.x=1,.y=0},{.x=-2,.y=-1},{.x=1,.y=2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->0", {{{.x=0,.y=0}, {.x=1,.y=0},{.x=-2,.y=0},{.x=1,.y=-2},{.x=-2,.y=1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->3", {{{.x=0,.y=0}, {.x=-1,.y=0},{.x=2,.y=0},{.x=-1,.y=2},{.x=2,.y=-1}}}));
}

ITetromino::~ITetromino()
{
}
