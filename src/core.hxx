#ifndef CORE_HXX
#define CORE_HXX

#include <string>
typedef unsigned char u8;

#define COLOR_BLUE 3
#define COLOR_YELLOW 6
#define COLOR_GREY 7
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_WHITE 15
#define COLOR_BLUE_WHITE 31

namespace core
{
    extern char tempPath[];
    extern std::string diskListFile;
    void init_temp_path();
    bool is_admin();
    void change_text_color(u8 color);
}

#endif