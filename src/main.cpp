#include <iostream>
#include "Board.hpp"

int main(void);
int mouseLoc2Idx(void);

typedef enum 
{
  EMPTY = 0,
  RUNNING,
  WON,
  OVER
}GameState;

inline uint32_t getBoardMouseY(void)
{
  return (GetMouseY() - settings::BOARDY_OFF) / settings::CELL_S;
}

inline uint32_t getBoardMouseX(void)
{
  return (GetMouseX() - settings::BOARDX_OFF) / settings::CELL_S;
}

int mouseLoc2Idx(void)
{
  int relX;
  int relY;
  const int absX = GetMouseX();
  const int absY = GetMouseY();

  relX = (absX - settings::BOARDX_OFF) / settings::CELL_S;
  relY = (absY - settings::BOARDY_OFF) / settings::CELL_S;
  return relY * settings::BOARD_W + relX;
}

int main(void){

    InitWindow(settings::SCREEN_W, settings::SCREEN_H, "core");
    SetTargetFPS(settings::FPS);

    Board b{};
    GameState state = EMPTY;

    while(!WindowShouldClose())
    {
        b.draw();
        int32_t x = getBoardMouseX();
        int32_t y = getBoardMouseY();

        switch(state)
        {
            case EMPTY:
                b.clearBoard();
                if(b.containsMouse() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    b.initCells(x, y);
                    b.revealCells(x, y);
                    state = RUNNING;
                }
                break;

            case RUNNING:
                if(b.containsMouse()){
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if(!b.revealCells(x, y)) state = OVER;
                    }else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                        b.cells[x][y].flaged = !b.cells[x][y].flaged;
                    }
                }
                break;
            case OVER:
                b.revealBombs();
                DrawText("To play again, press `r`", settings::BOARDX_OFF,
                        settings::BOARDY_OFF      , settings::FONTSIZE,
                        RED);
                if (IsKeyPressed(KEY_R)){
                    state = EMPTY;
                }
        }
    }

    return 0;
}
