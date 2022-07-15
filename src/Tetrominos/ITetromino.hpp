#pragma once

#include <vector>
#include "Tetromino.hpp"

class ITetromino : public Tetromino
{
public:
    ITetromino();
    ~ITetromino();
};

ITetromino::ITetromino() : Tetromino(4, 4, {{{72, 224, 255, 255}, {49, 199, 239, 255}, {32, 176, 224, 255}}}, {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0})
{
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->1", {{{0,0}, {-2,0},{-1,0},{+2,+1},{-1,-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->0", {{{0,0}, {-1,0},{+2,0},{-1,2},{2,-1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->2", {{{0,0}, {-1,0},{2,0},{-1,2},{2,-1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->1", {{{0,0}, {1,0},{-2,0},{1,-2},{-2,1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->3", {{{0,0}, {2,0},{-1,0},{2,1},{-1,-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->2", {{{0,0}, {-2,0},{1,0},{-2,-1},{1,2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->0", {{{0,0}, {1,0},{-2,0},{1,-2},{-2,1}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->3", {{{0,0}, {-1,0},{2,0},{-1,2},{2,-1}}}));
}

ITetromino::~ITetromino()
{
}
