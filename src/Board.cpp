#include "Board.hpp"
#include <memory.h>
#include <iostream>
#include <cassert>

Board::Board(const int width,
             const int hight) : width(width), hight(hight)
{
    boardX = (settings::SCREEN_W - width*settings::CELL_S) / 2;
    boardY = (settings::SCREEN_H - hight*settings::CELL_S) / 2;
    box = {
        (float)boardX,
        (float)boardY,
        // -1 for because the raylib checkcolisions function is boundry inclusive
        (float)width * settings::CELL_S - 1,
        (float)hight * settings::CELL_S - 1,
    };
}

void Board::onSucces(SuccesState state)
{
    SuccesEventArg arg = SuccesEventArg(state);
    succesEvent.trigger(&arg);
}

void Board::update()
{
    if (!CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, box)) return;

    uint32_t cx = getBoardMouseX();
    uint32_t cy = getBoardMouseY();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        revealCells(cx, cy);
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        cells[idx(cx, cy)].flaged = !cells[idx(cx, cy)].flaged;

    winState();
}

void Board::winState(){
    int flags = 0;
    for(int x = 0; x < width; x++){
        for(int y = 0; y < hight; y++){
            if (!(cells[idx(x, y)].revealed || cells[idx(x, y)].flaged)) return;
            if (!(cells[idx(x, y)].flaged   && cells[idx(x, y)].val == 9))
                continue;
            flags++;
        }
    }
    if(flags == settings::BOMBS)
        onSucces(WIN);
}

void Board::revealCells(int32_t x, int32_t y)
{
    switch(cells[idx(x, y)].val){
    case 9:
    {
        cells[idx(x, y)].revealed = true;
        onSucces(LOOSE);
    }
    break;

    case 0:
    {
        cells[idx(x, y)].revealed = true;
        for(int nx = x-1; nx <= x+1; nx++){
            for(int ny = y-1; ny <= y+1; ny++){

                if(checkX(nx)) break;
                if(checkY(ny)) continue;

                if (!cells[idx(nx, ny)].revealed && !cells[idx(nx, ny)].flaged)
                    revealCells(nx, ny);
            }
        }
    }
    break;

    default:
        cells[idx(x, y)].revealed = true;
        break;
    }
}

void Board::revealBombs()
{
    for(int x=0; x<width; x++){
        for(int y=0; y<hight; y++) {
            if(cells[idx(x, y)].flaged)
                continue;
            if(cells[idx(x, y)].val == 9)
                cells[idx(x, y)].revealed = true;
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
    memset(cells, 0, sizeof(Cell)*width*hight);
}

bool Board::tryInitCells()
{
    if (!CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, box)) return false;

    uint32_t cx = getBoardMouseX();
    uint32_t cy = getBoardMouseY();
    assert(!checkX(cx) && !checkY(cy) && "argument provided are incorect");

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
            cells[idx(x, y)].draw(
                boardX + x * settings::CELL_S,
                boardY + y * settings::CELL_S
            );
    }
}

void Board::distrobuteBombs(int32_t mx, int32_t my)
{
    // TODO(gerick): figure out the chance system with floating point numbers
    int bombs = settings::BOMBS;
    int spots = width*hight - 9;


    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < hight; y++)
        {
            if(forbiddenIdx(x, y, mx, my))
                continue;
            if (bombs == 0)
                break;

            int c = (spots--/bombs)-1;

            assert(c > 0 && "can't devide (or mod) by 0");
            if(rand()%c == 0){
                cells[idx(x, y)].val = 9;
                bombs--;
            }
        }
    }
    assert(bombs == 0);
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

                    if(cells[idx(nx, ny)].val == 9 && cells[idx(x, y)].val < 9){
                        cells[idx(x, y)].val++;
                        assert(cells[idx(x, y)].val < 9);
                    }
                }
            }
            cells[idx(x, y)].color = colors[cells[idx(x, y)].val];
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

inline uint32_t Board::getBoardMouseY(void) const
{
  return (GetMouseY() - boardY) / settings::CELL_S;
}

inline uint32_t Board::getBoardMouseX(void) const
{
  return (GetMouseX() - boardX) / settings::CELL_S;
}
inline Board::idx(const int x, const int y) const {return width*y+x;}
