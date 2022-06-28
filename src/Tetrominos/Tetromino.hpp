#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../Structures.h"

class Tetromino
{
private:
    int width;
    int height;
    int firstNonEmptyRow = -1;
    int firstNonEmptyCol = -1;
    SDL_Color color;
    std::vector<Block> blocks;
    Block tetrominoBlock;
    Block backgroundBlock;
    std::vector<bool> positions;

public:
    Tetromino(int width, int height, SDL_Color color, std::vector<bool> positions);
    Tetromino();
    ~Tetromino();
    Block getBlock(int y, int x);
    void setBlock(Block block, int y, int x);
    void setTetrominoBlock(int y, int x);
    void setBcgBlock(int y, int x);
    void setupPositions();
    int getLenght();
    int getWidth();
    int getHeight();
    int getFirstNonEmptyRow();
    int getFirstNonEmptyCol();
    int toOffset(int i, int j);
    void rotateClockwise();
    void translateTetromino(int i, int j, int pos_x, int pos_y);
    void moveToInitPos(int y, int x);
    void move(int x_push, int y_push);
    int findMostLeftBlockPos();
    int findMostRightBlockPos();
};

Tetromino::Tetromino()
{
}

Tetromino::Tetromino(int width, int height, SDL_Color color, std::vector<bool> positions) : width(width), height(height), color(color), positions(positions)
{
    tetrominoBlock.blockType = BlockType::TetrominoType;
    tetrominoBlock.color = color;
    tetrominoBlock.visible = true;

    firstNonEmptyCol = width - 1;
    Block initialBlock;
    blocks = std::vector(width * height, initialBlock);
    setupPositions();
}

void Tetromino::setupPositions()
{
    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            int offset = toOffset(i, j);
            bool position = positions[offset];
            if (position)
            {
                if (firstNonEmptyRow == -1)
                    firstNonEmptyRow = i;

                if (j < firstNonEmptyCol)
                    firstNonEmptyCol = j;

                setTetrominoBlock(i, j);
            }
            else
            {
                setBcgBlock(i, j);
            }
        }
    }
}

Block Tetromino::getBlock(int i, int j)
{
    int offset = toOffset(i, j);

    return blocks[offset];
};

void Tetromino::setBlock(Block block, int y, int x)
{
    int offset = toOffset(y, x);

    blocks[offset] = block;
};

void Tetromino::setTetrominoBlock(int y, int x)
{
    int offset = toOffset(y, x);
    tetrominoBlock.x = x;
    tetrominoBlock.y = y;

    blocks[offset] = tetrominoBlock;

    tetrominoBlock.x = 0;
    tetrominoBlock.y = 0;
};

void Tetromino::setBcgBlock(int y, int x)
{
    int offset = toOffset(y, x);
    backgroundBlock.x = x;
    backgroundBlock.y = y;

    blocks[offset] = backgroundBlock;

    backgroundBlock.x = 0;
    backgroundBlock.y = 0;
}

int Tetromino::getLenght()
{
    return blocks.size();
}

int Tetromino::getWidth()
{
    return width;
}

int Tetromino::getHeight()
{
    return height;
}

int Tetromino::getFirstNonEmptyRow()
{
    return firstNonEmptyRow;
}

int Tetromino::getFirstNonEmptyCol()
{
    return firstNonEmptyCol;
}

void Tetromino::translateTetromino(int i, int j, int pos_x, int pos_y)
{
    int offset = toOffset(i, j);

    blocks[offset].x = pos_x + blocks[offset].x;
    blocks[offset].y = pos_y + blocks[offset].y;
}

void Tetromino::move(int x_push, int y_push)
{
    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            int offset = toOffset(i, j);
            blocks[offset].x = blocks[offset].x + x_push;
            blocks[offset].y = blocks[offset].y + y_push;
        }
    }
}

void Tetromino::rotateClockwise()
{
    Block defaultBlock;
    std::vector<Block> rotatedBlocks = std::vector<Block>(getLenght(), defaultBlock);
    int offsetRotated;
    int offsetOriginal;
    firstNonEmptyRow = getHeight() - 1;
    firstNonEmptyCol = getWidth() - 1;

    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            offsetRotated = toOffset(j, getWidth() - 1 - i);
            offsetOriginal = toOffset(i, j);
            rotatedBlocks[offsetRotated] = blocks[offsetOriginal];
            rotatedBlocks[offsetRotated].x = blocks[offsetRotated].x;
            rotatedBlocks[offsetRotated].y = blocks[offsetRotated].y;

            if (rotatedBlocks[offsetRotated].visible)
            {
                if (firstNonEmptyRow > j)
                    firstNonEmptyRow = j;

                if (getWidth() - 1 - i < firstNonEmptyCol)
                    firstNonEmptyCol = j;
            }
        }
    }
    blocks.clear();
    blocks = rotatedBlocks;
}

int Tetromino::findMostLeftBlockPos()
{
    Block currentBlock;
    Block mostLeftBlock;
    int mostLeft = getWidth() - 1;
    int mostLeftPos;
    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            currentBlock = getBlock(i, j);
            if (currentBlock.visible)
            {
                if (j < mostLeft)
                {
                    mostLeft = j;
                    mostLeftPos = currentBlock.x;
                }
            }
        }
    }

    return mostLeftPos;
}

int Tetromino::findMostRightBlockPos()
{
    Block currentBlock;
    Block mostRightBlock;
    int mostRight = 0;
    int mostRightPos;
    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            currentBlock = getBlock(i, j);
            if (currentBlock.visible)
            {
                if (j > mostRight)
                {
                    mostRight = j;
                    mostRightPos = currentBlock.x;
                }
            }
        }
    }

    return mostRightPos;
}

int Tetromino::toOffset(int i, int j)
{
    return i * width + j;
}

Tetromino::~Tetromino()
{
}
