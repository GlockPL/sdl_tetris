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

JTetromino::JTetromino(/* args */) : Tetromino(3, 3, {{{102, 128, 104, 255}, {90,101,173, 255}, {72,87,160,255}}}, {0, 1, 0, 0, 1, 0, 1, 1, 0})
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

JTetromino::~JTetromino()
{
}
