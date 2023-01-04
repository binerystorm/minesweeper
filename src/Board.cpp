#include "Board.hpp"
#include <memory.h>
#include <iostream>
#include <cassert>

static inline uint32_t getBoardMouseY(void)
{
  return (GetMouseY() - settings::BOARDY_OFF) / settings::CELL_S;
}

static inline uint32_t getBoardMouseX(void)
{
  return (GetMouseX() - settings::BOARDX_OFF) / settings::CELL_S;
}

void Board::onSucces(SuccesState state)
{
    SuccesEventArg arg = SuccesEventArg(state);
    succesEvent.trigger(&arg);
}

void Board::update()
{
    if (!containsMouse()) return;

    uint32_t cx = getBoardMouseX();
    uint32_t cy = getBoardMouseY();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        revealCells(cx, cy);
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        cells[cx][cy].flaged = !cells[cx][cy].flaged;

    winState();
}

void Board::winState(){
    int flags = 0;
    for(int x = 0; x < width; x++){
        for(int y = 0; y < hight; y++){
            if (!(cells[x][y].revealed || cells[x][y].flaged)) return;
            if (!(cells[x][y].flaged && cells[x][y].val == 9))
                continue;
            flags++;
        }
    }
    if(flags == settings::BOMBS)
        onSucces(WIN);
}

void Board::revealCells(int32_t x, int32_t y)
{
    switch(cells[x][y].val){
    case 9:
    {
        cells[x][y].revealed = true;
        onSucces(LOOSE);
    }
    break;

    case 0:
    {
        cells[x][y].revealed = true;
        for(int nx = x-1; nx <= x+1; nx++){
            for(int ny = y-1; ny <= y+1; ny++){

                if(checkX(nx)) break;
                if(checkY(ny)) continue;

                if (!cells[nx][ny].revealed && !cells[nx][ny].flaged)
                    revealCells(nx, ny);
            }
        }
    }
    break;

    default:
        cells[x][y].revealed = true;
        break;
    }
}

void Board::revealBombs()
{
    for(int x=0; x<width; x++){
        for(int y=0; y<hight; y++) {
            if(cells[x][y].flaged)
                continue;
            if(cells[x][y].val == 9)
                cells[x][y].revealed = true;
        }
    }
}

bool Board::forbiddenIdx(int32_t x, int32_t y, int32_t mx, int32_t my)
{
    for(int nx = mx-1; nx <= mx+1; nx++){
        for(int ny = my-1; ny <= my+1; ny++){
            if(checkX(nx)) break;
            if(checkY(ny)) continue;
            if(x == nx && y == ny) return true;
        }
    }
    return false;
}

void Board::clearBoard()
{
    for(int x=0; x<width; x++){
        for(int y=0; y<hight; y++) {
            cells[x][y].val = 0;
            cells[x][y].flaged = false;
            cells[x][y].revealed = false;
            cells[x][y].color = GRAY;
        }
    }
}

bool Board::tryInitCells()
{
    if (!containsMouse()) return false;

    uint32_t cx = getBoardMouseX();
    uint32_t cy = getBoardMouseY();

    assert(!checkX(cx) && !checkY(cy) && "given arguments out of range");
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        distrobuteBombs(cx, cy);
        findBombs();
        revealCells(cx, cy);
        return true;
    }
    return false;

}

void Board::draw() const
{
    for(int x=0; x<width; x++){
        for(int y=0; y<hight; y++)
            cells[x][y].draw(
                settings::BOARDX_OFF + x * settings::CELL_S,
                settings::BOARDY_OFF + y * settings::CELL_S
            );
    }
}

void Board::distrobuteBombs(int32_t mx, int32_t my)
{
    int bombs = settings::BOMBS;
    int spots = settings::CELL_C - 9;


    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < hight; y++)
        {
            if(forbiddenIdx(x, y, mx, my))
                continue;
            if (bombs == 0)
                break;

            int c = (spots--/bombs)-1;

            if(rand()%c == 0){
                cells[x][y].val = 9;
                bombs--;
            }
        }
    }
}

void Board::findBombs()
{
    for(int x=0; x<width; x++){
        for(int y=0; y<hight; y++){
            for(int nx = x-1; nx <= x+1; nx++){
                for(int ny = y-1; ny <= y+1; ny++){
                    if(nx==x && ny==y) continue;
                    if(checkX(nx)) break;
                    if (checkY(ny)) continue;

                    if(cells[nx][ny].val == 9 && cells[x][y].val < 9){
                        cells[x][y].val++;
                        assert(cells[x][y].val < 9);
                    }
                }
            }
            cells[x][y].color = colors[cells[x][y].val];
        }
    }
}

// returns true in out of bounds
inline bool Board::checkX(int x) const
{
    return (x < 0 || x > width-1);
}

// returns true in out of bounds
inline bool Board::checkY(int y) const
{
    return y < 0 || y > hight-1;
}

inline bool Board::containsMouse() const
{
    return (GetMouseY() > settings::BOARDY_OFF) && (GetMouseY() < (settings::BOARDY_OFF + settings::BOARD_H * settings::CELL_S)) &&
           (GetMouseX() > settings::BOARDX_OFF) && (GetMouseX() < (settings::BOARDX_OFF + settings::BOARD_W * settings::CELL_S));
}

