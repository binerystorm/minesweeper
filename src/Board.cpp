#include "Board.hpp"
#include <memory.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <thread>

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
void Board::initForbIdxs(int idx, int *output) const
{
    int x = idx % settings::BOARD_W;
    int y = idx / settings::BOARD_W;
    int i = 0;
    for(int nx = x-1; nx <= x+1; nx++){
        for(int ny = y-1; ny <= y+1; ny++){
            int nidx = ny * settings::BOARD_W + nx;

            if(nidx < 0 || nidx > settings::CELL_C-1) output[i] = -1;
            if(checkX(nx)) output[i] = -1;
            if(checkY(ny)) output[i] = -1;

            output[i++] = nidx;
            
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

void Board::initCells(int32_t x, int32_t y)
{
    assert(!checkX(x) && !checkY(y) && "given arguments out of range");
    clearBoard();
    distrobuteBombs(x, y);
    findBombs();
}

bool Board::revealCells(int32_t x, int32_t y)
{


    switch(cells[x][y].val){
    case 9:
        cells[x][y].revealed = true;
        return false;

    case 0:
    {
        cells[x][y].revealed = true;
        draw();
        for(int nx = x-1; nx <= x+1; nx++){
            for(int ny = y-1; ny <= y+1; ny++){

                if(checkX(nx)) break;
                if(checkY(ny)) continue;

                if (!cells[nx][ny].revealed && !cells[nx][ny].flaged)
                    revealCells(nx, ny);
            }
        }
        return true;
    }

    default:
        cells[x][y].revealed = true;
        break;
    }
    return true;
}

void Board::draw() const
{
    BeginDrawing();
    ClearBackground(BLACK);
    for(int x=0; x<width; x++){
        for(int y=0; y<hight; y++)
            cells[x][y].draw(
                settings::BOARDX_OFF + x * settings::CELL_S,
                settings::BOARDY_OFF + y * settings::CELL_S
            );
    }
    EndDrawing();
}

void Board::distrobuteBombs(int32_t mx, int32_t my)
{
    int bombs = settings::BOMBS;
    int spots = settings::CELL_C - 9;

    //initForbIdxs(idx, forbidden_idxs);

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < hight; y++)
        {
            //assert(false && "TODO: replace with is forbidden function");
            // if(in_intArr(i, forbidden_idxs, 9))
            //     continue;
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

bool Board::containsMouse()
{
    int x;
    int y;
    return (x = GetMouseX()) > settings::BOARDX_OFF &&
           x < settings::BOARDX_OFF + settings::BOARD_W * settings::CELL_S &&
           (y = GetMouseY()) > settings::BOARDY_OFF &&
           y < settings::BOARDY_OFF + settings::BOARD_H * settings::CELL_S;
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