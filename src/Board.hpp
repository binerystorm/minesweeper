#include "Cell.hpp"
#include <raylib.h>
#include "settings.hpp"

class Board{
    public:
    static const int32_t width = settings::BOARD_W;
    static const int32_t hight = settings::BOARD_H;

    Cell cells[width][hight];

    void draw() const;
    void distrobuteBombs(int32_t x, int32_t y);
    void findBombs();
    bool containsMouse();
    bool revealCells(int32_t x, int32_t y);
    void initCells(int32_t x, int32_t y);
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
    bool forbiddenIdx(int32_t x, int32_t y, int32_t mx, int32_t my);
    inline bool checkX(int x) const;
    inline bool checkY(int y) const;
};
