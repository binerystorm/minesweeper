#include "Cell.hpp"
#include "settings.hpp"
#include <cstdint>
#include <assert.h>

Cell::Cell()
{
    this->val = 0;
    this->color = GRAY;
    this->revealed = false;
    this->flaged = false;
}

void Cell::draw(int x, int y) const
{
    assert(val >= 0 && val <= 9);
    if(revealed){
        DrawRectangle(x, y , settings::CELL_S, settings::CELL_S, GRAY);
        switch (val)
        {
        case 9:
            
            DrawText("*", x, y, settings::CELL_S, color);
            break;
        case 0:
            break;
        default:
            DrawText(TextFormat("%i", val), x, y, settings::CELL_S, color);
            break;
        }

    }
    else if(flaged)
    {
        DrawRectangle(x, y , settings::CELL_S, settings::CELL_S, GRAY);
        DrawText("?", x, y, settings::CELL_S, BLACK);
    }
    else
    {
        DrawRectangle(x, y, settings::CELL_S, settings::CELL_S, GRAY);
        DrawRectangleLines(x, y, settings::CELL_S, settings::CELL_S, DARKGRAY);
    }
}
