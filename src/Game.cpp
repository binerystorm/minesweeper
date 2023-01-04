#include "Game.hpp"
#include <cassert>

Game::Game()
{
    InitWindow(settings::SCREEN_W, settings::SCREEN_H, "core");
    SetTargetFPS(settings::FPS);

    this->state = EMPTY;

    board.succesEvent.subAction([this] (EventArg* arg)
                                {
                                    SuccesEventArg* sucarg = dynamic_cast<SuccesEventArg*>(arg);
                                    assert(sucarg != nullptr);
                                    if (sucarg->succes == WIN)
                                        this->state = WON;
                                    else
                                        this->state = OVER;
                                });
}

void Game::gameLoop()
{
    while(!WindowShouldClose())
    {
        tick();
    }
    
}

void Game::tick()
{
    update();
    BeginDrawing();
    ClearBackground(BLACK);
    draw();
    EndDrawing();
    
}

void Game::draw() const
{
    board.draw();
    //auto &lableList = menues[state];
    for(Lable l : menues.at(state))
        l.draw();
}

void Game::update()
{

    int x;
    int y;
    switch(state)
    {
    case EMPTY:
        {
            if (board.tryInitCells())
                state = RUNNING;
        }
        break;
    case RUNNING:
        {
            board.update();
        }
        break;
    case WON:
        {
            if (IsKeyPressed(KEY_R)){
                state = EMPTY;
                board.clearBoard();
            }
        }
        break;
    case OVER:
        {
            board.revealBombs();
            if (IsKeyPressed(KEY_R)){
                state = EMPTY;
                board.clearBoard();
            }
        }
        break;
    }

}
