#pragma once

#include "Tetromino.hpp"

class TTetromino: public Tetromino
{
public:
    TTetromino(/* args */);
    ~TTetromino();
};

TTetromino::TTetromino(/* args */) : Tetromino(3, 3, {{{.r = 198, .g = 88, .b = 180, .a = 255}, {.r = 173, .g = 77, .b = 156, .a = 255}, {.r = 152, .g = 56, .b = 160, .a = 136}}}, {0, 1, 0, 1, 1, 1, 0, 0, 0})
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

TTetromino::~TTetromino()
{
}
