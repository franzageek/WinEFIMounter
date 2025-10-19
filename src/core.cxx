#include "core.hxx"
#include <iostream>
#include <filesystem>
#include <Windows.h>

namespace core
{
    char tempPath[MAX_PATH] = {0};
    std::string diskListFile;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    void init_temp_path(void)
    {
        if (GetTempPathA(MAX_PATH, tempPath) == 0) // Get TEMP path 
        {
            std::cerr << " Failed to get TEMP path: " << GetLastError() << std::endl;
            exit(1);
        }
        diskListFile = std::string(tempPath) + "list.txt";
        if (std::filesystem::exists(diskListFile))
            std::filesystem::remove_all(diskListFile);
        return;
    }

    bool is_admin(void)
    {
        return (system("@echo off && @net session >nul 2>nul") == 0);
    }

    void change_text_color(u8 color)
    {
        SetConsoleTextAttribute(hConsole, color);
    }
}