#include "Lable.hpp"
#include "Board.hpp"
#include "Button.hpp"
#include <map>
#include <raylib.h>


typedef enum 
{
  EMPTY = 0,
  RUNNING,
  WON,
  OVER,
}GameState;

class Game
{
public:
    Board board;
    Button restartButton{settings::SCREEN_W/2 - 50, 50, 100, 50, "reset"};
    Button board9x9{50, settings::SCREEN_H/5*1, 75, 50, "9x9"};
    Button board16x16{50, settings::SCREEN_H/5*2, 75, 50, "16x16"};
    Button board16x30{50, settings::SCREEN_H/5*3, 75, 50, "16x30"};
private:
    GameState state;
    const std::map<GameState, std::vector<Lable>> menues =
    {
        {EMPTY, {Lable(settings::SCREEN_W/2-25, 110, "click")}},
        {RUNNING, {}},
        {WON, {Lable(settings::SCREEN_W/2-75,settings::SCREEN_H/2-10, "You Won!")}},
        {OVER, {
            Lable(settings::SCREEN_W/2-75,settings::SCREEN_H/2-10, "Game Over!"), 
            Lable(settings::SCREEN_W/2-130, 110, "press `r` to try again")
            }
        },
    };
public:
    Game();
    void tick();
    void gameLoop();
private:
    void update();
    void draw() const;
};
