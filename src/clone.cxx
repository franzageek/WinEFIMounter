#include "../include/clone.hxx"

bool clone_efi_partition(const char& mntLetter)
{
cloneStep0:
    system("@cls");
    std::cout << std::endl << "   - Type ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "C";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " to start cloning the EFI partition to \"C:\\EFIPartition\" or ";
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    std::cout << "B";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " to go back to the main menu...";
    std::getline(std::cin, currentLine);
    if (currentLine.length() == 1)
    {
        switch (currentLine[0])
        {
            case 'B':
                return false;
            case 'C':
                goto cloneStep1;
        }
    }
    goto cloneStep0;

cloneStep1:
    SetConsoleTitleA("WinEFIMounter v1.0.2 (Cloning...)");
    std::cout << std::endl << std::endl;
    std::cout << std::endl << " > Creating the destination directory..." << std::endl;
    if (fs::exists("C:\\EFIPartition"))
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [!!] The destination directory already exists!\n      This may mean you've already tried to clone the EFI partition, but something\n      didn't go as expected. The \"C:\\EFIPartition\" directory currently contains the files\n      you modified earlier. Please make sure to back them up, then delete the directory\n      and try again.\n      Press any key to go back to the main menu..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        return false;
    }
    if (!fs::create_directory("C:\\EFIPartition"))
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [E5] Failed to create the destination directory.\n      Press any key to go back to the main menu..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        return false;
    }
    std::cout << "   > Successfully created the \"C:\\EFIPartition\" directory, proceeding..." << std::endl;
    std::cout << std::endl << " > Copying files..." << std::endl;
    if (system(("@xcopy /E /Y \"" + std::string(1, mntLetter) + ":\\*\" \"C:\\EFIPartition\\\" >nul 2>nul").c_str()) != 0) // Copy files from EFI to the "C:\EFIPartition" directory
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [E6] Failed to clone the EFI partition to \"C:\\EFIPartition\\\".\n      Press any key to go back to the main menu..." << std::endl;
        fs::remove_all("C:\\EFIPartition");
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        return false;
    }
    std::cout << std::endl << " > ";
    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
    std::cout << "Done!"; 
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " Your EFI partition has been cloned to \"C:\\EFIPartition\" and you can now access it from Windows Explorer." << std::endl;
    SetConsoleTitleA("WinEFIMounter v1.0.2 (MOUNTED)");
    system("@start explorer \"C:\\EFIPartition\"");
    return true;
}

bool flush_efi_partition(const char& mntLetter)
{
    std::cout << std::endl << "   - Press a key to start flushing your files back to the EFI partition..." << std::endl;
    system("@pause >nul");
    SetConsoleTitleA("WinEFIMounter v1.0.2 (Flushing...)");
    std::cout << std::endl << " > Flushing..." << std::endl;
    if (system(("@xcopy /E /Y \"C:\\EFIPartition\\*\" \"" + std::string(1, mntLetter) + ":\\\" >nul 2>nul").c_str()) != 0) // Flush files back to the EFI partition
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [E7] Failed to flush the updated files back to the EFI partition.\n      The files you've worked on are being kept inside of \"C:\\EFIPartition\\\" so that no work is lost.\n      Press any key to go back to the main menu..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        return false;
    }
    std::cout << std::endl << " > Done! Your files have been successfully copied back to the EFI partition." << std::endl;
    fs::remove_all("C:\\EFIPartition");
    return true;
}
