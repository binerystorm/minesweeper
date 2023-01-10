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
    Board board{10, 10};
    Button restartButton{200, 0, 100, 50, "rest"};
private:
    GameState state;
    const std::map<GameState, std::vector<Lable>> menues =
    {
        {EMPTY, {Lable(0, 0, "click")}},
        {RUNNING, {}},
        {WON, {Lable(0, 0, "You Won!")}},
        {OVER, {Lable(0,0, "Game Over!"), Lable(100, 100, "press `r` to try again")}},
    };
public:
    Game();
    void tick();
    void gameLoop();
private:
    void update();
    void draw() const;
};
