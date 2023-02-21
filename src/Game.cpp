#include "Game.hpp"
#include <cassert>

Game::Game()
{
    InitWindow(settings::SCREEN_W, settings::SCREEN_H, "core");
    SetTargetFPS(settings::FPS);

    this->state = EMPTY;

    board9x9.clickEvent.subAction(
            [this] (EventArg* arg){
                this->board = Board{9, 9, 10};
                this->state = EMPTY;
            }
        );
    board16x16.clickEvent.subAction(
            [this] (EventArg* arg){
                this->board = Board{16, 16, 40};
                this->state = EMPTY;
            }
        );
    board16x30.clickEvent.subAction(
            [this] (EventArg* arg){
                this->board = Board{16, 30, 99}; 
                this->state = EMPTY;
            }
        );
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
    if(state == OVER)
        DrawRectangleRec(board.box, (Color){150, 150, 150, 200});
    for(Lable l : menues.at(state))
        l.draw();
    restartButton.draw();
    board16x16.draw();
    board16x30.draw();
    board9x9.draw();
}

void Game::update()
{

    int x;
    int y;
    restartButton.update();
    board9x9.update();
    board16x16.update();
    board16x30.update();
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
