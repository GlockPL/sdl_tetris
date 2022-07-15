#pragma once
#include <SDL2/SDL.h>

const int ColorAmount = 3;
const int Tests = 5;

struct KickPair
{
    int x;
    int y;
};


enum BlockType
{
    TetrominoType,
    DepositType,
    WallType,
    FloorType,
    BackgroundType
};

struct Block
{
    int x = 0;
    int y = 0;
    BlockType blockType = BlockType::BackgroundType;
    bool visible = false;
    SDL_Color color1 = {123, 123, 123,255};
    SDL_Color color2 = {123, 123, 123,255 };
    SDL_Color color3 = {123, 123, 123,255 };

    bool operator < (const Block& str) const
    {
        return (y < str.y);
    }
};