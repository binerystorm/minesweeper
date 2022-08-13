#include <raylib.h>
#include <cstdint>


class Cell
{
    public:
    uint16_t val;
    Color color;
    bool revealed;
    bool flaged;

    Cell();
    void draw(int x, int y) const;
};