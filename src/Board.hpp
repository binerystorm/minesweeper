#include "Cell.hpp"
#include "settings.hpp"
#include "Event.hpp"
#include <raylib.h>

enum SuccesState
{
    WIN = 0,
    LOOSE
};

class SuccesEventArg : public EventArg
{
public:
    SuccesState succes;
    SuccesEventArg(SuccesState s) : succes(s) {};
};

class Board{
    public:
    static const int32_t width = settings::BOARD_W;
    static const int32_t hight = settings::BOARD_H;

    Cell cells[width][hight];
    Event succesEvent;

    void draw() const;
    void winState();
    void revealCells(int32_t x, int32_t y);
    void onSucces(SuccesState state);
    void clearBoard();
    void distrobuteBombs(int32_t x, int32_t y);
    void findBombs();
    bool tryInitCells();
    void revealBombs();
    void update();

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
    inline bool containsMouse() const;
};
