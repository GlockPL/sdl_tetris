#pragma once

#include <map>
#include <array>
#include <string>
#include "../Structures.h"
#include "Tetromino.hpp"

class JTetromino : public Tetromino
{
public:
    JTetromino(/* args */);
    ~JTetromino();
};

JTetromino::JTetromino(/* args */) : Tetromino(3, 3, {{{.r = 102, .g = 128, .b = 104, .a = 255}, {.r = 90, .g = 101, .b = 173, .a = 255}, {.r = 72, .g = 87, .b = 160, .a = 255}}}, {0, 1, 0, 0, 1, 0, 1, 1, 0})
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

JTetromino::~JTetromino()
{
}
