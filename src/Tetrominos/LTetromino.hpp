#pragma once 

#include "Tetromino.hpp"


class LTetromino: public Tetromino
{
public:
    LTetromino(/* args */);
    ~LTetromino();
};

LTetromino::LTetromino(/* args */): Tetromino(3, 3, {{{255, 144, 48, 255}, {239, 121, 33, 255}, {224, 104, 16, 255}}}, {0, 1, 0, 0, 1, 0, 0, 1, 1})
{
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->1", {{{0,0}, {-1,0},{-1,1},{0,-2},{-1,-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->0", {{{0,0}, {1,0},{1,-1},{0,2},{1,2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("1->2", {{{0,0}, {1,0},{1,-1},{0,2},{1,2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->1", {{{0,0}, {-1,0},{-1,1},{0,-2},{-1,-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("2->3", {{{0,0}, {1,0},{1,1},{0,-2},{1,-2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->2", {{{0,0}, {-1,0},{-1,-1},{0,2},{-1,2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("3->0", {{{0,0}, {-1,0},{-1,-1},{0,2},{-1,2}}}));
    orderedKicks.insert(std::pair<std::string, std::array<KickPair, Tests>>("0->3", {{{0,0}, {1,0},{1,1},{0,-2},{1,-2}}}));
}

LTetromino::~LTetromino()
{
}
