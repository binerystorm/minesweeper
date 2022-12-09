#include <iostream>
#include "Game.hpp"

int main(void);
int mouseLoc2Idx(void);

// typedef enum 
// {
//   EMPTY = 0,
//   RUNNING,
//   WON,
//   OVER
// }GameState;

// inline uint32_t getBoardMouseY(void)
// {
//   return (GetMouseY() - settings::BOARDY_OFF) / settings::CELL_S;
// }
// 
// inline uint32_t getBoardMouseX(void)
// {
//   return (GetMouseX() - settings::BOARDX_OFF) / settings::CELL_S;
// }

int main(void){
    Game g;
    g.gameLoop();
    return(0);

//     InitWindow(settings::SCREEN_W, settings::SCREEN_H, "core");
//     SetTargetFPS(settings::FPS);
//     Lable endGame[] = {Lable(0,0, "GAME OVER"), Lable(50, 50, "`r` to restart")};
//     Lable empty[] = {Lable(settings::SCREEN_W / 2, settings::SCREEN_H / 2, "click")};

//    Board b{};
//    GameState state = EMPTY;

//     while(!WindowShouldClose())
//     {
//         int32_t x = getBoardMouseX();
//         int32_t y = getBoardMouseY();
// 
//         BeginDrawing();
//         ClearBackground(BLACK);
//         b.draw();
//         switch(state)
//         {
//             case EMPTY:
//                 for(Lable l : empty)
//                     l.draw();
//                 b.clearBoard();
//                 if(b.containsMouse() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
//                     b.initCells(x, y);
//                     b.revealCells(x, y);
//                     state = RUNNING;
//                 }
//                 break;
// 
//             case RUNNING:
//                 if(b.containsMouse()){
//                     if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
//                         if(!b.revealCells(x, y)) state = OVER;
//                     }else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
//                         b.cells[x][y].flaged = !b.cells[x][y].flaged;
//                     }
//                 }
//                 break;
//             case OVER:
//                 b.revealBombs();
//                 for (Lable l : endGame)
//                     l.draw();
//                 if (IsKeyPressed(KEY_R)){
//                     state = EMPTY;
//                 }
//         }
//         EndDrawing();
//     }
// 
//     return 0;
}
