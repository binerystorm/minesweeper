#include "Button.hpp"

Button::Button(const int x, const int y,
               const int width, const int height,
               const std::string text) : text(text)
{
    box = {
        .x = (float)x,
        .y = (float)y,
        .width = (float)width,
        .height = (float)height,
    };
}

void Button::onClick()
{
    EventArg arg = EventArg();
    clickEvent.trigger(&arg);
}

void Button::update()
{
    if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, box) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        onClick();
}

void Button::draw() const
{
    DrawRectangleLinesEx(box, 0.5, BLUE);
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), 20.0f, 1.0f);
    Vector2 textPos = {
        .x = box.x + box.width/2 - textSize.x/2,
        .y = box.y + box.height/2 - textSize.y/2,
    };
    DrawTextEx(GetFontDefault(), text.c_str(), textPos, 20.0f, 1.0f, DARKBLUE);
}
