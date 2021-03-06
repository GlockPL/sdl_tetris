
#include "Grid.hpp"
#include "Deposits.hpp"
#include "Score.hpp"

#include "Tetrominos/Tetromino.hpp"
#include "Tetrominos/TetrominoFactory.hpp"

#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <random>


int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    int speed = 60;
    int height = 1000;
    int width = 1000;
    int tetrominoTypes = 7;
    int x_push = 0;
    int y_push = 0;
    int start_gravity = 20;
    int gravity = start_gravity; // 5 grid moves per second
    int count_frames = 0;
    bool close = false;
    bool newBlock = true;
    bool move = false;
    bool firstCheck = true;
    std::vector<int> linesToClear;
    const char *title = "Tetris::The Begining";
    std::string path_to_exec = argv[0];
    // For random tetromino generation
    srand(time(0));
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(time(0)); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, tetrominoTypes-1);
    int tetrominoTypeNum = distrib(gen);

    path_to_exec = path_to_exec.substr(0, path_to_exec.find_last_of("\\/"));
    std::cout << path_to_exec << std::endl;

    if (SDL_Init(SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        title, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    std::shared_ptr<Score> score = std::make_shared<Score>();    
    Grid grid = Grid(1000, 1000, 35, path_to_exec, score);    
    std::shared_ptr<Deposits> deposits = std::make_shared<Deposits>(grid.getPlayfieldWidth(), grid.getPlayfieldHeight());
    grid.addDeposits(deposits);

    // Tetromino *tetr, *nextTetr;
    std::shared_ptr<Tetromino> tetr;
    std::shared_ptr<Tetromino> nextTetr;

    nextTetr = TetrominoFactory::Create(TetrominoKind(tetrominoTypeNum));

    while (!close)
    {
        y_push = 1;

        if (newBlock)
        {

            linesToClear = deposits->findAllFullLines();
            tetrominoTypeNum = distrib(gen);
            // tetrominoTypeNum = 0;
            tetr = nextTetr;
            nextTetr = TetrominoFactory::Create(TetrominoKind(tetrominoTypeNum));
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
                    grid.rotateCounterClockwiseProcedure();
                    break;
                case SDLK_s:
                    gravity = static_cast<int>(start_gravity * 0.125);
                    break;

                    // default:
                    //     break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_d:
                    // x_push = 0;
                    break;
                case SDLK_a:
                    // x_push = 0;
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

        if (linesToClear.size() > 0)
        {
            y_push = 0;
            if (deposits->fadeLines(linesToClear))
            {
                score->calculateScore(linesToClear.size());
                deposits->clearLines();
                linesToClear.clear();
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

        if (!grid.detectCollision(0, y_push))
        {
            if (move)
            {
                tetr->move(0, y_push);
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
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}