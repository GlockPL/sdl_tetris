#ifndef GRID_H
#define GRID_H

#include <cassert>
#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Structures.h"
#include "Deposits.hpp"
#include "Tetrominos/Tetromino.hpp"

class Grid
{
public:
    Grid(int screen_width, int screen_height, int grid_size) : window_width(screen_width), window_height(screen_height), grid_size(grid_size)
    {
        playfield_height = 24;
        playfield_width = 10;

        total_grid_width = static_cast<int>(window_width / grid_size);
        total_grid_height = static_cast<int>(window_height / grid_size);

        middle_of_screen = static_cast<int>(total_grid_width / 2) - 1;
        playfiled_half_width = static_cast<int>(playfield_width / 2);

        assert(total_grid_width > 1.5 * playfield_width);
        assert(total_grid_height > playfield_height + 2);

        wallColors = {{{.r = 240, .g = 0, .b = 255, .a = 255}, {.r = 217, .g = 32, .b = 228, .a = 255}, {.r = 156, .g = 19, .b = 165, .a = 255}}};

        Block initialBlock;

        blocks = std::vector(total_grid_height * total_grid_width, initialBlock);

        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            // success = false;
        }
        // this opens a font style and sets a size
        Font = TTF_OpenFont("../assets/Roboto-Regular.ttf", 200);

        if (Font == NULL)
        {
            printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        }

        addWalls();
    }

    ~Grid()
    {
        // Free global font
        TTF_CloseFont(Font);
        Font = NULL;
        TTF_Quit();
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
        block.color1 = {.r = 255, .g = 255, .b = 255, .a = 255};
        block.color2 = {.r = 255, .g = 255, .b = 255, .a = 255};
        block.color3 = {.r = 238, .g = 238, .b = 238, .a = 255};
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

    bool detectCollision(int x_push, int y_push)
    {
        for (int i = 0; i < tetr->getHeight(); i++)
        {
            for (int j = 0; j < tetr->getWidth(); j++)
            {
                int x = tetr->getBlock(i, j).x;
                int y = tetr->getBlock(i, j).y;
                int offset = toOffset(y + y_push, x + x_push);

                if (blocks[offset].visible && tetr->getBlock(i, j).visible)
                {
                    return true;
                }
            }
        }

        return false;
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

        SDL_SetRenderDrawColor(renderer, block.color1.r, block.color1.g, block.color1.b, 255);

        rect.x = grid_size * j;
        rect.y = grid_size * i;
        rect.w = grid_size;
        rect.h = grid_size;

        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, block.color2.r, block.color2.g, block.color2.b, 240);

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

        SDL_SetRenderDrawColor(renderer, block.color3.r, block.color3.g, block.color3.b, 255);

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
        displayText(renderer);
        int inner_size = 4;
        int border_size = 2;
        Uint8 val = 25;

        for (int i = 0; i < total_grid_height; i++)
        {
            for (int j = 0; j < total_grid_width; j++)
            {
                Block singleBlock = getBlock(i, j);
                if (singleBlock.visible)
                {
                    drawBlock(renderer, singleBlock, border_size, i, j);                    
                }
                else if (isWithinPlayfield(i, j))
                {
                    Block playfBlc = playfieldBackground();
                    drawBlock(renderer, playfBlc, border_size, i, j);
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

        blocks[offset] = block;
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
    }

    void addNextTetromino(std::shared_ptr<Tetromino> tetromino)
    {
        nextTetr = tetromino;
    }

    void moveTetrominoToStart()
    {
        for (int i = 0; i < tetr->getHeight(); i++)
        {
            for (int j = 0; j < tetr->getWidth(); j++)
            {
                tetr->translateTetromino(i, j, middle_of_screen - tetr->getFirstNonEmptyCol(), -tetr->getFirstNonEmptyRow());
            }
        }
    }

    void moveNextTetrToDisplay()
    {
        for (int i = 0; i < nextTetr->getHeight(); i++)
        {
            for (int j = 0; j < nextTetr->getWidth(); j++)
            {
                nextTetr->translateTetromino(i, j, right_wall_pos + 2 - nextTetr->getFirstNonEmptyCol(), 2 - nextTetr->getFirstNonEmptyRow());
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

    void displayText(SDL_Renderer *renderer)
    {

        // this is the color in rgb format,
        // maxing out all would give you the color white,
        // and it will be your text's color
        SDL_Color White = {255, 255, 100, 255};

        // as TTF_RenderText_Solid could only be used on
        // SDL_Surface then you have to create the surface first
        SDL_Surface *surfaceMessage =
            TTF_RenderText_Solid(Font, "Next Block:", White);

        // now you can convert it into a texture
        SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        SDL_Rect Message_rect;                             // create a rect
        Message_rect.x = (right_wall_pos + 2) * grid_size; // controls the rect's x coordinate
        Message_rect.y = grid_size;                        // controls the rect's y coordinte
        Message_rect.w = grid_size * 4;                    // controls the width of the rect
        Message_rect.h = grid_size;                        // controls the height of the rect

        // (0,0) is on the top left of the window/screen,
        // think a rect as the text's box,
        // that way it would be very simple to understand

        // Now since it's a texture, you have to put RenderCopy
        // in your game loop area, the area where the whole code executes

        // you put the renderer's name first, the Message,
        // the crop size (you can ignore this if you don't want
        // to dabble with cropping), and the rect which is the size
        // and coordinate of your texture
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

        // Don't forget to free your surface and texture
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);
    }

    void addDeposits(std::shared_ptr<Deposits> deposits)
    {
        this->deposits = deposits;
    }

private:
    int toOffset(int y, int x)
    {
        return y * total_grid_width + x;
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
    std::array<SDL_Color, ColorAmount> wallColors;
    std::shared_ptr<Tetromino> tetr;
    std::shared_ptr<Tetromino> nextTetr;
    std::shared_ptr<Deposits> deposits;
    TTF_Font *Font;
};

#endif /* !GRID_H */