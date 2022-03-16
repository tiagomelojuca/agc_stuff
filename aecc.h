// ---------------------------------------------------------------------------------
// ANSI Escape Color Codes (AECC)
// ---------------------------------------------------------------------------------
//
// | ----------------------- |
// | Name            FG   BG |
// | ----------------------- |
// | Black           30   40 |
// | Red             31   41 |
// | Green           32   42 |
// | Yellow          33   43 |
// | Blue            34   44 |
// | Magenta         35   45 |
// | Cyan            36   46 |
// | White           37   47 |
// | Bright Black    90  100 |
// | Bright Red      91  101 |
// | Bright Green    92  102 |
// | Bright Yellow   93  103 |
// | Bright Blue     94  104 |
// | Bright Magenta  95  105 |
// | Bright Cyan     96  106 |
// | Bright White    97  107 |
// | ----------------------- |
//
// SRC: stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c

#ifndef AECC_H_
#define AECC_H_

namespace AECC
{
    enum ColorCodes
    {
        FG_BLACK = 30,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_MAGENTA = 35,
        FG_CYAN = 36,
        FG_WHITE = 37,

        FG_BRIGHT_BLACK = 90,
        FG_BRIGHT_RED = 91,
        FG_BRIGHT_GREEN = 92,
        FG_BRIGHT_YELLOW = 93,
        FG_BRIGHT_BLUE = 94,
        FG_BRIGHT_MAGENTA = 95,
        FG_BRIGHT_CYAN = 96,
        FG_BRIGHT_WHITE = 97,

        BG_BLACK = 40,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_MAGENTA = 45,
        BG_CYAN = 46,
        BG_WHITE = 47,
        
        BG_BRIGHT_BLACK = 100,
        BG_BRIGHT_RED = 101,
        BG_BRIGHT_GREEN = 102,
        BG_BRIGHT_YELLOW = 103,
        BG_BRIGHT_BLUE = 104,
        BG_BRIGHT_MAGENTA = 105,
        BG_BRIGHT_CYAN = 106,
        BG_BRIGHT_WHITE = 107
    };
}

#endif // AECC_H_
