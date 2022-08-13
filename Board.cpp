#include "Board.hpp"
#include <memory.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <thread>

Board::Board()
{

}

void Board::initCells()
{
    for(Cell &cell : cells)
    {
        cell.val = 0;
        cell.flaged = false;
        cell.revealed = false;
        cell.color = GRAY;
    }
    distrobuteBombs();
    findBombs();
}

bool Board::revealCells(int idx)
{

    assert(idx > 0 || idx < settings::CELL_C-1);

    switch(cells[idx].val){
    case 9:
        cells[idx].revealed = true;
        return false;

    case 0:
    {
        int x = idx % settings::BOARD_W;
        int y = idx / settings::BOARD_W;

        cells[idx].revealed = true;
        draw();
        for(int nx = x-1; nx <= x+1; nx++){
            for(int ny = y-1; ny <= y+1; ny++){
                int nidx = ny * settings::BOARD_W + nx;

                if(nidx < 0 || nidx > settings::CELL_C-1) continue;
                if(checkX(nx)) break;
                if(checkY(ny)) continue;

                if (!cells[nidx].revealed && !cells[nidx].flaged)
                    revealCells(nidx);
            }
        }
        return true;
    }

    default:
        cells[idx].revealed = true;
        break;
    }
    return true;
}

void Board::draw() const
{
    BeginDrawing();
    ClearBackground(BLACK);
    for(int i = 0; i<(settings::CELL_C); i ++) 
        cells[i].draw(
            settings::BOARDX_OFF + (i % settings::BOARD_W) * settings::CELL_S,
            settings::BOARDY_OFF + (i / settings::BOARD_H) * settings::CELL_S);
    EndDrawing();
}

void Board::distrobuteBombs()
{
    int bombs = settings::BOMBS;
    int spots = settings::CELL_C;

    for(Cell &x : cells)
    {
        if (bombs == 0)
            break;

        int c = (spots--/bombs)-1;
        if(rand()%c == 0){
            x.val = 9;
            bombs--;
        }
    }
}

void Board::findBombs()
{
    for(int idx = 0; idx < settings::CELL_C; idx++)
    {
        for(int dx=-1; dx<=1; dx++){
            for(int dy=-1; dy<=1; dy++){
                int nx = idx % settings::BOARD_W + dx;
                int ny = idx / settings::BOARD_W + dy;
                if(dx==0 && dy==0) continue;
                if(checkX(nx)) break;
                if (checkY(ny)) continue;
                
                if(cells[ny*settings::BOARD_W+nx].val == 9 && cells[idx].val < 9)
                    cells[idx].val++;
                    assert(cells[idx].val++ < 9);
            }
        }
        cells[idx].color = colors[cells[idx].val];
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

inline bool Board::checkX(int x) const
{
    return (x < 0 || x > settings::BOARD_W-1);
}

inline bool Board::checkY(int y) const
{
    return y < 0 || y > settings::BOARD_H-1;
}
