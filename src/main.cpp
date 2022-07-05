#include "Grid.hpp"
#include "Deposits.hpp"

#include "Tetrominos/ITetromino.hpp"
#include "Tetrominos/JTetromino.hpp"
#include "Tetrominos/LTetromino.hpp"
#include "Tetrominos/OTetromino.hpp"
#include "Tetrominos/STetromino.hpp"
#include "Tetrominos/TTetromino.hpp"
#include "Tetrominos/ZTetromino.hpp"
#include "Tetrominos/Tetromino.hpp"

#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>

std::shared_ptr<Tetromino> pickTetromino(int num)
{
    switch (num)
    {
    case 0:
        return std::make_shared<ITetromino>();
        break;
    case 1:
        return std::make_shared<OTetromino>();
        break;
    case 2:
        return std::make_shared<TTetromino>();
        break;
    case 3:
        return std::make_shared<JTetromino>();
        break;
    case 4:
        return std::make_shared<LTetromino>();
        break;
    case 5:
        return std::make_shared<STetromino>();
        break;
    case 6:
        return std::make_shared<ZTetromino>();
        break;

    default:
        return std::make_shared<Tetromino>();
        break;
    }

    return std::make_shared<Tetromino>();
}

int main(int argc, char **argv)
{
    srand(time(0));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    int speed = 60;
    int height = 1000;
    int width = 1000;
    int tetrominoTypes = 7;
    int tetrominoTypeNum = rand() % tetrominoTypes;
    int x_push = 0;
    int start_gravity = 10;
    int gravity = start_gravity; // 5 grid moves per second
    int count_frames = 0;
    bool close = false;
    bool newBlock = true;
    bool move = false;
    bool firstCheck = true;
    const char *title = "Tetris::The Begining";
    std::string path_to_exec = argv[0];

    path_to_exec = path_to_exec.substr(0, path_to_exec.find_last_of("\\/"));
    std::cout << path_to_exec << std::endl;

    if (SDL_Init(SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        // success = false;
    }

    window = SDL_CreateWindow(
        title, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    Grid grid = Grid(1000, 1000, 35, path_to_exec);
    std::shared_ptr<Deposits> deposits = std::make_shared<Deposits>(grid.getPlayfieldWidth(), grid.getPlayfieldHeight());
    grid.addDeposits(deposits);

    // Tetromino *tetr, *nextTetr;
    std::shared_ptr<Tetromino> tetr;
    std::shared_ptr<Tetromino> nextTetr;

    nextTetr = pickTetromino(tetrominoTypeNum);

    while (!close)
    {
        if (newBlock)
        {
            deposits->clearLines();
            tetrominoTypeNum = rand() % tetrominoTypes;
            // tetrominoTypeNum = 0;
            tetr = nextTetr;
            nextTetr = pickTetromino(tetrominoTypeNum);
            grid.addTetromino(tetr);
            grid.addNextTetromino(nextTetr);
            grid.moveNextTetrToDisplay();
            tetr->setupPositions();
            grid.moveTetrominoToStart();

            newBlock = false;
            firstCheck = true;
            x_push = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        grid.placeWalls();
        grid.placeDeposits();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch (event.key.keysym.sym)
                {
                case SDLK_d:
                    x_push = 1;
                    break;
                case SDLK_a:
                    x_push = -1;
                    break;
                case SDLK_e:
                    grid.rotateClockwiseProcedure();
                    break;
                case SDLK_q:
                    tetr->rotateCounterClockwise();
                    break;
                case SDLK_s:
                    gravity = static_cast<int>(start_gravity * 0.25);
                    break;

                    // default:
                    //     break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_d:
                    break;
                case SDLK_a:
                    break;
                case SDLK_e:
                    break;
                case SDLK_s:
                    gravity = start_gravity;
                    break;
                }
                break;

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
            }
        }

        if (grid.detectCollision(0, 0))
            close = true;

        if (!grid.detectCollision(x_push, 0))
        {
            if (move)
            {
                tetr->move(x_push, 0);
                x_push = 0;
            }
        }

        if (!grid.detectCollision(0, 1))
        {
            if (move)
            {
                tetr->move(0, 1);
            }
        }
        else
        {
            if (move)
            {
                if (firstCheck)
                {
                    firstCheck = false;
                }
                else
                {
                    grid.tetrominoToDeposit();
                    newBlock = true;
                }
            }
        }

        grid.placeTetrominosOnGrid();

        if (renderer == NULL)
        {
            std::cout << "Renderer null" << std::endl;
        }

        if (renderer == nullptr)
        {
            std::cout << "Renderer null" << std::endl;
        }

        grid.render(renderer);

        SDL_Delay(1000 / speed);

        if (count_frames >= gravity)
        {
            count_frames = 0;
            move = true;
        }
        else
        {
            count_frames++;
            move = false;
        }

        // std::cout << "Current gravity: " << gravity << std::endl;
    }

    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}