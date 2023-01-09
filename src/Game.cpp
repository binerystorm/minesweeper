#include "Game.hpp"
#include <cassert>

Game::Game()
{
    InitWindow(settings::SCREEN_W, settings::SCREEN_H, "core");
    SetTargetFPS(settings::FPS);

    this->state = EMPTY;

    restartButton.clickEvent.subAction(
            [this] (EventArg* arg){
                this->state = EMPTY;
            });
    board.succesEvent.subAction(
            [this] (EventArg* arg){
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
    for(Lable l : menues.at(state))
        l.draw();
    restartButton.draw();
}

void Game::update()
{

    int x;
    int y;
    restartButton.update();
    switch(state)
    {
    case EMPTY:
        {
            board.clearBoard();
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
            }
        }
        break;
    case OVER:
        {
            board.revealBombs();
            if (IsKeyPressed(KEY_R)){
                state = EMPTY;
            }
        }
        break;
    }

}
