#include "Cell.hpp"
#include <raylib.h>
#include "settings.hpp"

class Board{
    public:
    Cell cells[settings::CELL_C];

    Board();
    void draw() const;
    void distrobuteBombs();
    void findBombs();
    bool containsMouse();
    bool revealCells(int idx);

    private:
    const Color colors[10] = {
        GRAY,
        BLUE,
        GREEN,
        RED,
        DARKBLUE,
        MAROON,
        SKYBLUE,
        BLACK,
        DARKGRAY,
        BLACK
    };
    
    void initCells();
    inline bool checkX(int x) const;
    inline bool checkY(int y) const;
};