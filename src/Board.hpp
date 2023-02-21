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
    int32_t width;
    int32_t hight;
    int bombs;
    int32_t boardX;
    int32_t boardY;
    Rectangle box;

    Cell *cells = new Cell[width*hight]();
    static Event succesEvent;

    Board(const int width = settings::BOARD_W,
          const int hight = settings::BOARD_H,
          const int bombs = settings::BOMBS);
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
    constexpr static Color colors[10] = {
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
    inline uint32_t getBoardMouseY(void) const;
    inline uint32_t getBoardMouseX(void) const;
    inline idx(const int x, const int y) const;
};
