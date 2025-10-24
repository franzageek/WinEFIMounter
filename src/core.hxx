#ifndef CORE_HXX
#define CORE_HXX

#include <string>
typedef unsigned char u8;

#define COLOR_BLUE 3
#define COLOR_YELLOW 6
#define COLOR_GREY 7
#define COLOR_DARK_GREY 8
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_WHITE 15
#define COLOR_BLUE_WHITE 31

namespace core
{
    extern char tempPath[];
    extern std::string diskListFile;
    void init_temp_path();
    void del_temp_files();
    bool is_admin();
    bool has_pwsh();
    void change_text_color(u8 color);
    bool copy_file_sub(std::string from, std::string to);
}

#endif