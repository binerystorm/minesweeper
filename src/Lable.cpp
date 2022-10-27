#include "Lable.hpp"
#include <raylib.h>
#include "settings.hpp"

Lable::Lable(int x, int y, std::string text)
{
    this->x = x;
    this->y = y;
    this->text = text;
}

void Lable::draw() const
{
    DrawText(text.c_str(), x, y, 100, RED);
}
