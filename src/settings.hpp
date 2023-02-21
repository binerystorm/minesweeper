/*
_W: Width
_H: Height
_S: Size (Width == Height => Size is (Width||Height))
_C: Count
_OFF: offset (relitive to screen)
*/

namespace settings
{
    // Window settings
    inline constexpr int SCREEN_W  = 800;
    inline constexpr int SCREEN_H  = 800;
    inline constexpr int FPS       = 30;

    // Game setttings
    inline constexpr unsigned int BOARD_W    = 16;
    inline constexpr unsigned int BOARD_H    = 16;
    inline constexpr unsigned int CELL_C     = BOARD_H*BOARD_W;
    inline constexpr unsigned int CELL_S     = 25;
    inline constexpr unsigned int BOMBS      = 40;
    inline constexpr unsigned int BOARDX_OFF = (SCREEN_W - BOARD_W * CELL_S) / 2;
    inline constexpr unsigned int BOARDY_OFF = (SCREEN_H - BOARD_H * CELL_S) / 2;

    // Lable
    inline constexpr unsigned int FONTSIZE   = 4;

    // Setting checks
    static_assert(
        (CELL_S*BOARD_H <= SCREEN_H) &&
        (CELL_S*BOARD_W <= SCREEN_W)
    );
    static_assert(
        (BOARDX_OFF < SCREEN_W-BOARD_W*CELL_S) && 
        (BOARDY_OFF < SCREEN_H-BOARD_H*CELL_S)
    ); 
    static_assert(BOMBS < CELL_C);
}
