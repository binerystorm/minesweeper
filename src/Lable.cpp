#include "Lable.hpp"
#include <raylib.h>
#include "settings.hpp"

Lable::Lable(int x, int y, std::string text) : 
    x(x),
    y(y),
    text(text)
{}

void Lable::draw() const
{
    DrawText(text.c_str(), x, y, 25, RED);
}
