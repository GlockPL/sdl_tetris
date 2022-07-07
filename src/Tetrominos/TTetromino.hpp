#pragma once

#include "Tetromino.hpp"

class TTetromino: public Tetromino
{
public:
    TTetromino(/* args */);
    ~TTetromino();
};

TTetromino::TTetromino(/* args */) : Tetromino(3, 3, {{{198, 88, 180, 255}, {173, 77, 156, 255}, {152, 56, 160, 136}}}, {0, 1, 0, 1, 1, 1, 0, 0, 0})
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

TTetromino::~TTetromino()
{
}
