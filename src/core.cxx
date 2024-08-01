#include "../include/core.hxx"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::string currentLine = "";

bool check_if_admin(void)
{
    return (system("@echo off && @cls && @net session >nul 2>nul") == 0);
}

bool check_if_already_mounted(u8& diskNumber, u8& partNumber, char& mntLetter)
{
    for (char i = 'Z'; i >= 'O'; --i) // Iterate through every letter of the lower part of the alphabet
    {
        if (fs::exists(std::string(1, i).append(":\\.winefimounter")))
        {
            if (efi_is_already_mounted(diskNumber, partNumber, i)) // If an EFI partition appears to be mounted, ask the user to unmount it
            {
                mntLetter = i;
                return true;
            }
        }
    }
    return false;
}

bool efi_is_already_mounted(u8& diskNumber, u8& partNumber, const char& mntLetter)
{
    std::ifstream cacheFile(std::string(1, mntLetter).append(":\\.winefimounter"));
    char currChar;
    do
    {
        cacheFile.get(currChar);
    } while (currChar != '[' && cacheFile.good());
    if (!cacheFile.good())
    {
        cacheFile.close();
        system("@cls");
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cout << std::endl << " [E8] WinEFIMounter detected a mounted EFI partition on " << mntLetter << ":\\, but was unable to retrieve further info.";
        std::cout << std::endl << "      Press any key to skip it...";
        system("@pause>nul");
        return false;
    }
    cacheFile.get(currChar);
    u8 mountedEFIDiskNumber = currChar-'0';
    cacheFile.get(currChar);
    cacheFile.get(currChar);
    u8 mountedEFIPartNumber = currChar-'0';
    cacheFile.close(); // Retrieve disk and partition number from a cache file

displayMsg:
    system("@cls");
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cout << std::endl << " [!!] WinEFIMounter detected a mounted EFI partition (disk " << std::string(1, mountedEFIDiskNumber+'0') << ", partition " << std::string(1, mountedEFIPartNumber+'0') <<") on " << mntLetter << ":\\.";
    std::cout << std::endl << "   - Type ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "U";
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cout << " to unmount the partition, ";
    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
    std::cout << "K";
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cout << " to keep it mounted or ";
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    std::cout << "A";
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cout << " to ignore it & mount another one...";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::getline(std::cin, currentLine);
    if (currentLine.length() == 1)
    {
        switch (currentLine[0])
        {
            case 'K':
            {
                diskNumber = mountedEFIDiskNumber;
                partNumber = mountedEFIPartNumber;
                return true; // Update all the variables and treat the already mounted EFI partition normally
            }
            case 'U':
                goto unmountMountedEFI; // Unmount the EFI partition
            case 'A':
                return false; // Ignore the EFI partition and jump to the main menu
        }
    }
    goto displayMsg;

unmountMountedEFI: 
    std::cout << std::endl << std::endl;
    std::cout << " > Unmounting disk " << std::string(1, mountedEFIDiskNumber+'0') << ", partition " << std::string(1, mountedEFIPartNumber+'0') << "..." << std::endl;
    fs::remove_all(std::string(1, mntLetter).append(":\\.winefimounter"));
    int exitCode = system(("@echo Remove-PartitionAccessPath -DiskNumber " + std::string(1, mountedEFIDiskNumber+'0') + " -PartitionNumber " + std::string(1, mountedEFIPartNumber+'0') + " -AccessPath \"" + std::string(1, mntLetter) + ":\" | powershell>nul").c_str());
    if (exitCode != 0)
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        system(("@echo off && @echo ## [" + std::string(1, mountedEFIDiskNumber+'0') + ":" + std::string(1, mountedEFIPartNumber+'0') + "] MOUNTED ON %date% @ %time% ## > \"" + std::string(1, mntLetter) + ":\\.winefimounter\"").c_str());
        std::cerr << " [E4] Failed to unmount the partition (error " << std::string(1, exitCode+'0') << ").\n      Press any key to exit..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        exit(exitCode);
    }
    std::cout << " > Done!";
    return false;
}
