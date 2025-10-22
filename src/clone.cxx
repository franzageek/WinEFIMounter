#include "core.hxx"
#include "efi.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <Windows.h>

namespace fs = std::filesystem;

namespace efi
{
    bool clone_partition(EfiPartition efi)
    {
        SetConsoleTitleA("WinEFIMounter v1.0.3 (Cloning...)");
        std::cout << std::endl << std::endl;
        std::cout << std::endl << " > Creating the destination directory..." << std::endl;
        if (fs::exists("C:\\EFIPartition"))
        {
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [!!] The destination directory already exists!\n      This may mean you've already tried to clone the EFI partition, but something\n      didn't go as expected. The \"C:\\EFIPartition\\\" directory currently contains the files\n      you modified earlier. Please make sure to back them up, then delete the directory\n      and try again.\n      Press any key to go back to the main menu..." << std::endl;
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }
        if (fs::exists("C:\\EFIPartition_backup"))
            fs::remove_all("C:\\EFIPartition_backup");
            
        if (!fs::create_directory("C:\\EFIPartition") || !fs::create_directory("C:\\EFIPartition_backup"))
        {
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E5] Failed to create the destination directory.\n      Press any key to go back to the main menu..." << std::endl;
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }
        std::cout << "   > Successfully created the \"C:\\EFIPartition\\\" directory, proceeding..." << std::endl;
        std::cout << std::endl << " > Copying files..." << std::endl;
        
        if ((system(("@xcopy /E /Y \"" + std::string(1, efi.letter) + ":\\*\" \"C:\\EFIPartition\\\" >nul 2>nul").c_str()) != 0) ||
            (system(("@xcopy /E /Y \"" + std::string(1, efi.letter) + ":\\*\" \"C:\\EFIPartition_backup\\\" >nul 2>nul").c_str()) != 0)) // Copy files from EFI both to "C:\EFIPartition" and "C:\EFIPartition_backup"
        {
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E6] Failed to clone the EFI partition to \"C:\\EFIPartition\\\".\n      Press any key to go back to the main menu..." << std::endl;
            fs::remove_all("C:\\EFIPartition");
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }
        std::cout << std::endl << " > ";
        core::change_text_color(COLOR_GREEN);
        std::cout << "Done!"; 
        core::change_text_color(COLOR_GREY);
        std::cout << " Your EFI partition has been cloned to \"C:\\EFIPartition\\\" and you can now access it from Windows Explorer." << std::endl;
        SetConsoleTitleA("WinEFIMounter v1.0.3 (MOUNTED)");
        system("@start explorer \"C:\\EFIPartition\"");
        return true;
    }
}