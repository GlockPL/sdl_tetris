#pragma once 

#include "Tetromino.hpp"

class ZTetromino: public Tetromino
{
public:
    ZTetromino(/* args */);
    ~ZTetromino();
};

ZTetromino::ZTetromino(/* args */) : Tetromino(3, 3, {{{255,72,72,255}, {239,32,41,255}, {208,24,24,255}}}, {1, 1, 0, 0, 1, 1, 0, 0, 0})
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

ZTetromino::~ZTetromino()
{
}
