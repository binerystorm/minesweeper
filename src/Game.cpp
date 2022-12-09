#include "Game.hpp"

inline uint32_t getBoardMouseY(void)
{
  return (GetMouseY() - settings::BOARDY_OFF) / settings::CELL_S;
}

inline uint32_t getBoardMouseX(void)
{
  return (GetMouseX() - settings::BOARDX_OFF) / settings::CELL_S;
}

Game::Game()
{
    InitWindow(settings::SCREEN_W, settings::SCREEN_H, "core");
    SetTargetFPS(settings::FPS);

    //this->board = Board();
    this->state = EMPTY;
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
    int32_t x = getBoardMouseX();
    int32_t y = getBoardMouseY();

    switch(state)
    {
    case EMPTY:
        {
            board.clearBoard();
            if(board.containsMouse() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                board.initCells(x, y);
                board.revealCells(x, y);
                state = RUNNING;
            }
        }
        break;
    case RUNNING:
        {
            if(board.containsMouse()){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    if(!board.revealCells(x, y)) state = OVER;
                }else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                    board.cells[x][y].flaged = !board.cells[x][y].flaged;
                }
            }
            if(board.winState()) state = WON;
        }
        break;
    case WON:
        {
            if (IsKeyPressed(KEY_R))
                state = EMPTY;
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
