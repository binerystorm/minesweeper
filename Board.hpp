#include "Cell.hpp"
#include <raylib.h>
#include "settings.hpp"

class Board{
    public:
    Cell cells[settings::CELL_C];

    Board();
    void draw() const;
    void distrobuteBombs(int idx);
    void findBombs();
    bool containsMouse();
    bool revealCells(int idx);
    void initCells(int idx);
    void clearBoard();
    void revealBombs();

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
    
    void initForbIdxs(int idx, int *output) const;
    inline bool checkX(int x) const;
    inline bool checkY(int y) const;
};
