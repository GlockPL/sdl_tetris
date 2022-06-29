#pragma once
#include <SDL2/SDL.h>

const int ColorAmount = 3;

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
    SDL_Color color1 = {.r = 123, .g = 123, .b = 123};
    SDL_Color color2 = {.r = 123, .g = 123, .b = 123};
    SDL_Color color3 = {.r = 123, .g = 123, .b = 123};

    bool operator < (const Block& str) const
    {
        return (y < str.y);
    }
};