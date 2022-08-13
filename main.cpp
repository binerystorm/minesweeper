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

    switch(state)
    {
    case EMPTY:
      if(b.containsMouse()){
        int idx = mouseLoc2Idx();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        }
      }
      break;

    case RUNNING:
      if(b.containsMouse()){
        int idx = mouseLoc2Idx();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
          if(!b.revealCells(idx)) state = OVER;
        }else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
          b.cells[idx].flaged = !b.cells[idx].flaged;
        }
      break;
      }
    }
  }
  
  return 0;
}