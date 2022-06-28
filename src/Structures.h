#pragma once
#include <SDL2/SDL.h>

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
    SDL_Color color = {.r = 123, .g = 123, .b = 123};

    bool operator < (const Block& str) const
    {
        return (y < str.y);
    }
};