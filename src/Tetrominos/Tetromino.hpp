#pragma once

#include <vector>
#include <array>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include "../Structures.h"

class Tetromino
{
protected:
    std::unordered_map<std::string,std::array<KickPair, Tests>> orderedKicks;
private:
    int width;
    int height;
    int firstNonEmptyRow = -1;
    int firstNonEmptyCol = -1;
    int lastFullRow = 0;
    int currentRotation = 0;
    std::array<SDL_Color, ColorAmount> colors;
    std::vector<Block> blocks;
    Block tetrominoBlock;
    Block backgroundBlock;
    std::vector<bool> positions;

public:
    Tetromino(int width, int height, std::array<SDL_Color, ColorAmount> colors, std::vector<bool> positions);
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
    int getLastFullRow();
    int toOffset(int i, int j);
    int rotateClockwise();
    int rotateCounterClockwise();
    int getCurrentRotation();
    int leftYPos();
    void translateTetromino(int i, int j, int pos_x, int pos_y);
    void moveToInitPos(int y, int x);
    void move(int x_push, int y_push);
    void setAlpha(int alpha);
    int findMostLeftBlockPos();
    int findMostRightBlockPos();
    std::array<KickPair, Tests> getKick(std::string type);
};

Tetromino::Tetromino()
{
}

Tetromino::Tetromino(int width, int height,  std::array<SDL_Color, ColorAmount> colors, std::vector<bool> positions) : width(width), height(height), colors(colors), positions(positions)
{
    tetrominoBlock.blockType = BlockType::TetrominoType;
    tetrominoBlock.color1 = colors[0];
    tetrominoBlock.color2 = colors[1];
    tetrominoBlock.color3 = colors[2];
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

                if(lastFullRow < i)
                    lastFullRow = i;

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

int Tetromino::getCurrentRotation() {
    return currentRotation;
}

int Tetromino::getLastFullRow(){ 
    return lastFullRow;
}

void Tetromino::translateTetromino(int i, int j, int pos_x, int pos_y)
{
    int offset = toOffset(i, j);

    blocks[offset].x = pos_x + blocks[offset].x;
    blocks[offset].y = pos_y + blocks[offset].y;
}

void Tetromino::move(int x_push, int y_push)
{
    //Check bounds for move

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

int Tetromino::rotateClockwise()
{
    Block defaultBlock;
    std::vector<Block> rotatedBlocks = std::vector<Block>(getLenght(), defaultBlock);
    int offsetRotated;
    int offsetOriginal;
    firstNonEmptyRow = getHeight() - 1;
    firstNonEmptyCol = getWidth() - 1;
    lastFullRow = 0;

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
                    firstNonEmptyCol = getWidth() - 1 - i;

                if(lastFullRow < i)
                    lastFullRow = i;
            }
        }
    }
    blocks.clear();
    blocks = rotatedBlocks;
    currentRotation = (currentRotation + 1) % 4;
    return currentRotation;
}

int Tetromino::rotateCounterClockwise() {
    Block defaultBlock;
    std::vector<Block> rotatedBlocks = std::vector<Block>(getLenght(), defaultBlock);
    int offsetRotated;
    int offsetOriginal;
    firstNonEmptyRow = getHeight() - 1;
    firstNonEmptyCol = getWidth() - 1;
    lastFullRow = 0;

    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            offsetRotated = toOffset(getHeight() - 1 - j, i);
            offsetOriginal = toOffset(i, j);
            rotatedBlocks[offsetRotated] = blocks[offsetOriginal];
            rotatedBlocks[offsetRotated].x = blocks[offsetRotated].x;
            rotatedBlocks[offsetRotated].y = blocks[offsetRotated].y;

            if (rotatedBlocks[offsetRotated].visible)
            {
                if (firstNonEmptyRow > getHeight() - 1 - j)
                    firstNonEmptyRow = getHeight() - 1 - j;

                if (getWidth() - 1 - i < i)
                    firstNonEmptyCol = i;

                if(lastFullRow < i)
                    lastFullRow = i;
            }
        }
    }
    blocks.clear();
    blocks = rotatedBlocks;
    currentRotation = (currentRotation - 1) % 4;
    return currentRotation;
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

void Tetromino::setAlpha(int alpha) {
    Block currentBlock;
    for (int i = 0; i < getHeight(); i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            currentBlock = getBlock(i, j);
            currentBlock.color1.a = alpha;
            currentBlock.color2.a = alpha;
            currentBlock.color3.a = alpha;

            setBlock(currentBlock, i, j);
        }
    }
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


std::array<KickPair, Tests> Tetromino::getKick(std::string type) {
    return orderedKicks[type];
}

int Tetromino::toOffset(int i, int j)
{
    return i * width + j;
}

int Tetromino::leftYPos() {
    return blocks[0].y;
}

Tetromino::~Tetromino()
{
}
