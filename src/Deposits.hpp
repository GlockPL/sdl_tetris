#pragma once

#include "Structures.h"
#include <vector>

class Deposits
{
private:
    std::vector<Block> deposits;
    int playfield_width;
    int playfield_height;

public:
    Deposits(int playfield_width, int playfield_height);
    int toOffset(int i, int j);
    int getWidth();
    int getHeight();
    bool gameOver();
    bool empty();
    bool lineFull(int i);
    void clearLine(int i);
    void clearLines();
    void moveLine(int from, int to);
    void addBlock(Block block, int i, int j);
    void swapDeposits(std::vector<Block> newDeposits);
    Block at(int i, int j);
    ~Deposits();
};

Deposits::Deposits(int playfield_width, int playfield_height) : playfield_width(playfield_width), playfield_height(playfield_height)
{
    Block defaultBlock;
    deposits = std::vector<Block>(playfield_height * playfield_width, defaultBlock);
}

Deposits::~Deposits()
{
}

bool Deposits::empty()
{
    return deposits.empty();
}

int Deposits::getHeight()
{
    return playfield_height;
}

int Deposits::getWidth()
{
    return playfield_width;
}

Block Deposits::at(int i, int j)
{
    return deposits[toOffset(i, j)];
}

bool Deposits::lineFull(int i)
{
    int col = 0;

    for (int j = 0; j < getWidth(); j++)
    {
        if (deposits[toOffset(i, j)].visible)
            col++;
    }

    return col == playfield_width;
}

void Deposits::clearLine(int i)
{
    Block defaultBlock;

    for (int j = 0; j < getWidth(); j++)
    {
        deposits[toOffset(i, j)] = defaultBlock;
    }
}
//This assumes that to is always bigger than from
void Deposits::moveLine(int from, int to) {
    int diff=0;
    for (int j = 0; j < getWidth(); j++)
    {
        diff = to - from;
        Block fromBlock = deposits[toOffset(from, j)];
        fromBlock.y = fromBlock.y + diff;
        deposits[toOffset(to, j)] = fromBlock;
    }
}

void Deposits::clearLines()
{
    if (!deposits.empty())
    {
        int lines = 0;

        for (int i = getHeight() - 1; i >= 0; i--)
        {
            if (lineFull(i))
            {
                lines++;
                clearLine(i);
                continue;
            }

            if(lines > 0) {
                moveLine(i, i+lines);
            }
        }
    }
}

void Deposits::addBlock(Block block, int i, int j)
{
    deposits[toOffset(i, j)] = block;
}

bool Deposits::gameOver()
{

    for (int j = 0; j < getWidth(); j++)
    {
        int offset = toOffset(0, j);
        Block block = deposits[offset];

        if (block.visible)
        {
            return true;
        }
    }

    return false;
}

void Deposits::swapDeposits(std::vector<Block> newDeposits)
{
    assert(deposits.size() == newDeposits.size());

    deposits = newDeposits;
}

int Deposits::toOffset(int i, int j)
{
    return i * playfield_width + j;
}