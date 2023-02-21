#include "Event.hpp"
#include <string>
#include <raylib.h>

class Button
{
public:
    Rectangle box;
    Vector2 textPos;
    Event clickEvent;
    const std::string text;

public:
    Button(const int x, const int y,
           const int width, const int hight,
           const std::string text);
    void draw() const;
    void onClick();
    void update();
};

