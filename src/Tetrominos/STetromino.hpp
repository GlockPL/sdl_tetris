#pragma once 

#include "Tetromino.hpp"

class STetromino: public Tetromino
{
public:
    STetromino(/* args */);
    ~STetromino();
};

STetromino::STetromino(/* args */) : Tetromino(3, 3, {{{72, 208, 72, 255}, {66, 182, 66, 255}, {48, 160, 48, 255}}}, {0, 1, 1, 1, 1, 0, 0, 0, 0})
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

STetromino::~STetromino()
{
}
