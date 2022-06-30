#pragma once 

#include "Tetromino.hpp"

class STetromino: public Tetromino
{
public:
    STetromino(/* args */);
    ~STetromino();
};

STetromino::STetromino(/* args */) : Tetromino(3, 3, {{{.r = 72, .g = 208, .b = 72, .a = 255}, {.r = 66, .g = 182, .b = 66, .a = 255}, {.r = 48, .g = 160, .b = 48, .a = 255}}}, {0, 1, 1, 1, 1, 0, 0, 0, 0})
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

STetromino::~STetromino()
{
}
