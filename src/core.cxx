#include "core.hxx"
#include <iostream>
#include <filesystem>
#include <Windows.h>

namespace fs = std::filesystem;

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
        if (fs::exists(diskListFile))
            fs::remove_all(diskListFile);
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

    bool copy_file_sub(std::string from, std::string to)
    {
        fs::path path = to;
        try 
        {
            bool err = true;
            if (!fs::exists(path.parent_path()))
                err &= fs::create_directories(path.parent_path());
            
            err &= fs::copy_file(from, path, fs::copy_options::overwrite_existing);
            return err;
        }
        catch (std::exception& e)
        {
            change_text_color(COLOR_DARK_GREY);
            std::cerr << "\n Error while copying files: " << e.what();
            change_text_color(COLOR_GREY);
        }
        return false;
    }
}