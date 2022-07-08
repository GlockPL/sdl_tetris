#pragma once

#include "Structures.h"
#include <vector>

class Deposits
{
private:
    std::vector<Block> deposits;
    int playfield_width;
    int playfield_height;
    int a = 255;
    int fade_speed = 10;

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
    void changeAlpha(int i, int j, int alpha);
    bool fadeLines(std::vector<int> line);
    void fadeLine(int i, int alpha);
    void moveLine(int from, int to);
    void addBlock(Block block, int i, int j);
    void swapDeposits(std::vector<Block> newDeposits);
    std::vector<int> findAllFullLines();
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

void Deposits::changeAlpha(int i, int j, int alpha)
{
    int offset = toOffset(i, j);
    Block block = deposits[offset];
    block.color1.a = alpha;
    block.color2.a = alpha;
    block.color2.a = alpha;
    deposits[offset] = block;
}

void Deposits::fadeLine(int i, int alpha)
{
    for (int j = 0; j < getWidth(); j++)
    {
        changeAlpha(i, j, alpha);
    }
}

bool Deposits::fadeLines(std::vector<int> line)
{

    a -= fade_speed;

    for (int &line : line) // access by reference to avoid copying
    {
        fadeLine(line, a);
    }

    return a <= 0;
}

void Deposits::clearLine(int i)
{
    Block defaultBlock;

    for (int j = 0; j < getWidth(); j++)
    {
        deposits[toOffset(i, j)] = defaultBlock;
    }
}
// This assumes that to is always bigger than from
void Deposits::moveLine(int from, int to)
{
    int diff = 0;
    for (int j = 0; j < getWidth(); j++)
    {
        diff = to - from;
        Block fromBlock = deposits[toOffset(from, j)];
        fromBlock.y = fromBlock.y + diff;
        deposits[toOffset(to, j)] = fromBlock;
    }
}

std::vector<int> Deposits::findAllFullLines()
{
    std::vector<int> fullLines;
    if (!deposits.empty())
    {
        for (int i = getHeight() - 1; i >= 0; i--)
        {
            if (lineFull(i))
            {
                fullLines.push_back(i);
            }
        }
    }

    return fullLines;
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

            if (lines > 0)
            {
                moveLine(i, i + lines);
            }
        }
    }

    a = 255;
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