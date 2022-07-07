#ifndef GRID_H
#define GRID_H

#include <cassert>
#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "Structures.h"
#include "Deposits.hpp"
#include "Text.hpp"
#include "Tetrominos/Tetromino.hpp"

class Grid
{
public:
    Grid(int screen_width, int screen_height, int grid_size, std::string path_to_exec) : window_width(screen_width), window_height(screen_height), grid_size(grid_size), path_to_exec(path_to_exec), nextBlockText(Text(Fonts::BulkyPixel, 25, path_to_exec))
    {
        std::string path_to_font = path_to_exec + "/../assets/fonts/light_pixel-7.ttf";
        playfield_height = 25;
        playfield_width = 10;

        total_grid_width = static_cast<int>(window_width / grid_size);
        total_grid_height = static_cast<int>(window_height / grid_size);

        middle_of_screen = static_cast<int>(total_grid_width / 2) - 1;
        playfiled_half_width = static_cast<int>(playfield_width / 2);

        assert(total_grid_width > 1.5 * playfield_width);
        assert(total_grid_height > playfield_height + 2);

        wallColors = {{{240, 0, 255, 255}, {217, 32, 228, 255}, {156, 19, 165, 255}}};

        Block initialBlock;

        blocks = std::vector<Block>(total_grid_height * total_grid_width, initialBlock);

        
        // nextBlockText = Text(Fonts::BulkyPixel, 25, path_to_exec);// + "/"

        addWalls();
    }

    ~Grid()
    {        
    }
    // Norma is that y i major and x in minor meaning block[y][x] is correct
    void setupWalls()
    {
        left_wall_pos = middle_of_screen - playfiled_half_width;
        right_wall_pos = middle_of_screen + playfiled_half_width + 1;
        int bottom = middle_of_screen - playfiled_half_width;

        for (int i = 0; i < playfield_height; i++)
        {

            // Left Wall
            setBlock(getWallBlock(i, left_wall_pos), i, left_wall_pos);
            // Right Wall
            setBlock(getWallBlock(i, right_wall_pos), i, right_wall_pos);
            // Floor
            setBlock(getFloorBlock(playfield_height + 1, bottom), playfield_height + 1, bottom);

            bottom = bottom < middle_of_screen + playfiled_half_width + 1 ? bottom + 1 : bottom;
        }
    };

    void addWalls()
    {
        left_wall_pos = middle_of_screen - playfiled_half_width;
        right_wall_pos = middle_of_screen + playfiled_half_width + 1;
        int bottom = middle_of_screen - playfiled_half_width;

        for (int i = 0; i < playfield_height; i++)
        {

            // Left Wall
            walls.push_back(getWallBlock(i, left_wall_pos));
            // setBlock(getWallBlock(i, left_wall_pos), i, left_wall_pos);
            // Right Wall
            setBlock(getWallBlock(i, right_wall_pos), i, right_wall_pos);
            walls.push_back(getWallBlock(i, right_wall_pos));
            // Floor
            if (bottom <= middle_of_screen + playfiled_half_width + 1)
            {
                walls.push_back(getFloorBlock(playfield_height, bottom));
                bottom++;
            }
            // setBlock(getFloorBlock(playfield_height, bottom), playfield_height, bottom);

            // bottom =  ? bottom + 1 : bottom;
        }
    };

    Block playfieldBackground()
    {
        Block block;
        block.blockType = BackgroundType;
        block.visible = false;
        block.color1 = {255, 255, 255, 255};
        block.color2 = {255, 255, 255, 255};
        block.color3 = {238, 238, 238, 255};
        return block;
    }

    void placeWalls()
    {
        for (Block &block : walls)
        {
            setBlock(block, block.y, block.x);
        }
    };

    void placeDeposits()
    {
        for (int i = 0; i < deposits->getHeight(); i++)
        {
            for (int j = 0; j < deposits->getWidth(); j++)
            {
                Block block = deposits->at(i, j);
                if (block.visible)
                {
                    setBlock(block, block.y, block.x);
                }
            }
        }
    };

    // bool detectCollision(int x_push, int y_push)
    // {
    //     for (int i = 0; i < tetr->getHeight(); i++)
    //     {
    //         for (int j = 0; j < tetr->getWidth(); j++)
    //         {
    //             int x = tetr->getBlock(i, j).x;
    //             int y = tetr->getBlock(i, j).y;
    //             int offset = toOffset(y + y_push, x + x_push);

    //             if (blocks[offset].visible && tetr->getBlock(i, j).visible)
    //             {
    //                 return true;
    //             }
    //         }
    //     }

    //     return false;
    // }

    bool detectCollision(int x_push, int y_push)
    {
        return detectCollisionForParticularTetr(tetr, x_push, y_push);
    }

    bool ghostDetectCollision(int x_push, int y_push)
    {
        return detectCollisionForParticularTetr(ghostTetr, x_push, y_push);
    }

    int clipToWithinPlayfield(int x_push)
    {
        int mostRightBx = tetr->findMostRightBlockPos();
        int mostLeftBx = tetr->findMostLeftBlockPos();

        if (mostRightBx + x_push >= right_wall_pos)
            return right_wall_pos - mostRightBx - 1;

        if (mostLeftBx + x_push <= left_wall_pos)
            return left_wall_pos - mostLeftBx + 1;

        return x_push;
    }

    void drawBlock(SDL_Renderer *renderer, Block block, int border_size, int i, int j)
    {
        SDL_Rect rect;
        i -= 1;

        SDL_SetRenderDrawColor(renderer, block.color1.r, block.color1.g, block.color1.b, block.color1.a);

        rect.x = grid_size * j;
        rect.y = grid_size * i;
        rect.w = grid_size;
        rect.h = grid_size;

        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, block.color2.r, block.color2.g, block.color2.b, block.color2.a);

        SDL_Rect rect2;
        rect2.x = grid_size * j + border_size;
        rect2.y = grid_size * i + border_size;
        rect2.w = grid_size - border_size;
        rect2.h = grid_size - border_size;

        SDL_RenderFillRect(renderer, &rect2);

        SDL_Rect small_rect;
        small_rect.x = grid_size * j;
        small_rect.y = grid_size * i + grid_size - border_size;
        small_rect.w = border_size;
        small_rect.h = border_size;

        SDL_RenderFillRect(renderer, &small_rect);

        small_rect.x = grid_size * j + grid_size - border_size;
        small_rect.y = grid_size * i;
        small_rect.w = border_size;
        small_rect.h = border_size;

        SDL_RenderFillRect(renderer, &small_rect);

        SDL_SetRenderDrawColor(renderer, block.color3.r, block.color3.g, block.color3.b, block.color3.a);

        small_rect.x = grid_size * (j + 1) - border_size;
        small_rect.y = grid_size * i + border_size;
        small_rect.w = border_size;
        small_rect.h = grid_size - border_size;

        SDL_RenderFillRect(renderer, &small_rect);

        small_rect.x = grid_size * j + border_size;
        small_rect.y = grid_size * (i + 1) - border_size;
        small_rect.w = grid_size - border_size;
        small_rect.h = border_size;

        SDL_RenderFillRect(renderer, &small_rect);
    }

    void render(SDL_Renderer *renderer)
    {
        // Add moved tetromino to grid
        // displayText(renderer);
        nextBlockText.displayText((right_wall_pos + 2) * grid_size, grid_size, "Next Block:", {255, 255, 255, 255}, renderer);
        int inner_size = 4;
        int border_size = 2;
        Uint8 val = 25;
        int hiddenLines = 1;

        for (int i = 0; i < total_grid_height; i++)
        {
            for (int j = 0; j < total_grid_width; j++)
            {
                if (i >= hiddenLines)
                {
                    Block singleBlock = getBlock(i, j);

                    if (isWithinPlayfield(i, j))
                    {
                        Block playfBlc = playfieldBackground();
                        drawBlock(renderer, playfBlc, border_size, i, j);
                    }

                    if (singleBlock.visible)
                    {
                        drawBlock(renderer, singleBlock, border_size, i, j);
                    }
                }

                Block freshBlock;
                setBlock(freshBlock, i, j);
            }
        }

        SDL_RenderPresent(renderer);
    };

    Block getBlock(int y, int x)
    {
        int offset = toOffset(y, x);

        return blocks[offset];
    };

    void setBlock(Block block, int y, int x)
    {
        int offset = toOffset(y, x);

        if (offset < maxSize())
        {
            blocks[offset] = block;
        }
    };

    Block getWallBlock(int y, int x)
    {
        Block block;
        block.color1 = wallColors[0];
        block.color2 = wallColors[1];
        block.color3 = wallColors[2];
        block.blockType = BlockType::WallType;
        block.visible = true;
        block.x = x;
        block.y = y;

        return block;
    }

    Block getFloorBlock(int y, int x)
    {
        Block block;
        block.color1 = wallColors[0];
        block.color2 = wallColors[1];
        block.color3 = wallColors[2];
        block.blockType = BlockType::FloorType;
        block.visible = true;
        block.x = x;
        block.y = y;

        return block;
    }

    int getPlayfieldWidth()
    {
        return playfield_width;
    }

    int getPlayfieldHeight()
    {
        return playfield_height;
    }

    void addTetromino(std::shared_ptr<Tetromino> tetromino)
    {
        tetr = tetromino;
        // Copying content of tetromino to ghost tetromino
    }

    void addNextTetromino(std::shared_ptr<Tetromino> tetromino)
    {
        nextTetr = tetromino;
    }

    void placeGhostTetromino()
    {
        ghostTetr = std::make_shared<Tetromino>(*tetr);

        ghostTetr->setAlpha(100);
        int lastFullRow = ghostTetr->getLastFullRow();
        int y_pos = ghostTetr->getBlock(lastFullRow, 0).y;

        bool collision = true;

        for (int i = y_pos; i <= playfield_height + 1; i++)
        {
            int shift = i - y_pos;
            collision = ghostDetectCollision(0, shift);
            if (collision)
            {
                if ((ghostTetr->leftYPos() + shift - 1) > 0)
                    ghostTetr->move(0, shift - 1);
                placeTetrominoOnGrid(ghostTetr);
                break;
            }
        }
    }

    void moveTetrominoToStart()
    {
        for (int i = 0; i < tetr->getHeight(); i++)
        {
            for (int j = 0; j < tetr->getWidth(); j++)
            {
                tetr->translateTetromino(i, j, middle_of_screen - tetr->getFirstNonEmptyCol(), 0); //-tetr->getFirstNonEmptyRow()
            }
        }
    }

    void moveNextTetrToDisplay()
    {
        for (int i = 0; i < nextTetr->getHeight(); i++)
        {
            for (int j = 0; j < nextTetr->getWidth(); j++)
            {
                nextTetr->translateTetromino(i, j, right_wall_pos + 2 - nextTetr->getFirstNonEmptyCol(), 3 - nextTetr->getFirstNonEmptyRow());
            }
        }
    }

    void placeTetrominoOnGrid(std::shared_ptr<Tetromino> currentTetr)
    {
        if (currentTetr != nullptr)
        {
            for (int i = 0; i < currentTetr->getHeight(); i++)
            {
                for (int j = 0; j < currentTetr->getWidth(); j++)
                {
                    Block block = currentTetr->getBlock(i, j);

                    if (block.visible)
                    {
                        setBlock(block, block.y, block.x);
                    }
                }
            }
        }
    }

    void placeTetrominosOnGrid()
    {
        placeGhostTetromino();
        placeTetrominoOnGrid(tetr);
        placeTetrominoOnGrid(nextTetr);
    }

    void tetrominoToDeposit()
    {
        for (int i = 0; i < tetr->getHeight(); i++)
        {
            for (int j = 0; j < tetr->getWidth(); j++)
            {
                Block block = tetr->getBlock(i, j);

                if (block.visible)
                {
                    deposits->addBlock(block, block.y, convertFromGridXToDepositsX(block.x));
                }
            }
        }
    }

    int convertFromGridXToDepositsX(int j)
    {
        return j - left_wall_pos - 1;
    }

    bool isWithinPlayfield(int y, int x)
    {
        return x > left_wall_pos && x < right_wall_pos && y < playfield_height;
    }


    void addDeposits(std::shared_ptr<Deposits> deposits)
    {
        this->deposits = deposits;
    }

    void rotateClockwiseProcedure()
    {
        int x_p = 0;
        int y_p = 0;

        int from = tetr->getCurrentRotation();
        int to = tetr->rotateClockwise();
        bool collision = false;
        std::string kickSignature = std::to_string(from) + "->" + std::to_string(to);
        std::array<KickPair, Tests> kickMoves = tetr->getKick(kickSignature);

        for (int i = 0; i < Tests; i++)
        {
            x_p = kickMoves[i].x;
            y_p = kickMoves[i].y;
            collision = detectCollision(x_p, y_p);
            if (!collision)
            {
                tetr->move(x_p, y_p);
                break;
            }
        }

        if (collision)
        {
            tetr->rotateCounterClockwise();
        }
    }

private:
    int toOffset(int y, int x)
    {
        int addr = y * total_grid_width + x;

        if (addr >= blocks.size() || addr < 0)
        {
            throw std::out_of_range("Position is outside of grid!");
        }

        return addr >= blocks.size() ? blocks.size() - 1 : addr;
    }

    int maxSize()
    {
        return total_grid_height * total_grid_width;
    }

    bool detectCollisionForParticularTetr(std::shared_ptr<Tetromino> particularTetr, int x_push, int y_push)
    {
        for (int i = 0; i < particularTetr->getHeight(); i++)
        {
            for (int j = 0; j < particularTetr->getWidth(); j++)
            {
                int x = particularTetr->getBlock(i, j).x;
                int y = particularTetr->getBlock(i, j).y;
                int offset = toOffset(y + y_push, x + x_push);

                if (y + y_push < 0 || x + x_push < 0)
                {
                    return true;
                }

                if (blocks[offset].visible && particularTetr->getBlock(i, j).visible)
                {
                    return true;
                }
            }
        }

        return false;
    }

    std::vector<Block> blocks;
    std::vector<Block> walls;
    int playfield_width;
    int playfield_height;
    int window_width;
    int window_height;
    int total_grid_width;
    int total_grid_height;
    int grid_size;
    int middle_of_screen;
    int playfiled_half_width;
    int left_wall_pos;
    int right_wall_pos;
    std::string path_to_exec;
    std::array<SDL_Color, ColorAmount> wallColors;
    std::shared_ptr<Tetromino> tetr;
    std::shared_ptr<Tetromino> ghostTetr;
    std::shared_ptr<Tetromino> nextTetr;
    std::shared_ptr<Deposits> deposits;
    Text nextBlockText;
};

#endif /* !GRID_H */