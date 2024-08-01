#ifndef CORE_HXX
#define CORE_HXX
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <Windows.h>
#define COLOR_BLUE 3
#define COLOR_YELLOW 6
#define COLOR_GREY 7
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_WHITE 15
#define COLOR_BLUE_WHITE 31
typedef unsigned char u8;
namespace fs=std::filesystem;

extern HANDLE hConsole;
extern std::string currentLine;

bool check_if_admin(void);
bool check_if_already_mounted(u8& diskNumber, u8& partNumber, char& mntLetter);
bool efi_is_already_mounted(u8& diskNumber, u8& partNumber, const char& mntLetter);

#endif // CORE_HXX