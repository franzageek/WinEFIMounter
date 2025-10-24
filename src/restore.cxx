#include "core.hxx"
#include "efi.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

namespace efi
{
    bool decode_cache_file(EfiPartition& efi)
    {
        std::ifstream cacheFile(std::string(1, efi.letter).append(":\\.winefimounter"));
        char currChar;
        do
        {
            cacheFile.get(currChar);
        } while (currChar != '[' && cacheFile.good());
        if (!cacheFile.good())
        {
            cacheFile.close();
            system("@cls");
            core::change_text_color(COLOR_YELLOW);
            std::cout << std::endl << " [E8] WinEFIMounter detected a mounted EFI partition on \"" << efi.letter << ":\\\", but was unable to retrieve further info.";
            std::cout << std::endl << "      Press any key to skip it...";
            system("@pause>nul");
            return false;
        }
        cacheFile.get(currChar);
        efi.disk = currChar-'0';
        cacheFile.get(currChar);
        cacheFile.get(currChar);
        efi.part = currChar-'0'; // Both fields are updated here so that by the time we reach the prompt we already have a well-formed EFI 
        cacheFile.close(); // Retrieve disk and partition number from a cache file
        return true;
    }

    bool restore_mounted(EfiPartition& efi)
    {
        if (!decode_cache_file(efi))
            return false;

        std::string choice;
        while (true)
        {
            system("@cls");
            core::change_text_color(COLOR_YELLOW);
            std::cout << std::endl << " [!!] WinEFIMounter detected a mounted EFI partition (disk " << std::string(1, efi.disk+'0') << ", partition " << std::string(1, efi.part+'0') <<") on " << efi.letter << ":\\.";
            std::cout << std::endl << "   - Type ";
            core::change_text_color(COLOR_BLUE);
            std::cout << "U";
            core::change_text_color(COLOR_YELLOW);
            std::cout << " to unmount the partition, ";
            core::change_text_color(COLOR_GREEN);
            std::cout << "L";
            core::change_text_color(COLOR_YELLOW);
            std::cout << " to load it inside WinEFIMounter or ";
            core::change_text_color(COLOR_RED);
            std::cout << "A";
            core::change_text_color(COLOR_YELLOW);
            std::cout << " to ignore it & mount another one...";
            core::change_text_color(COLOR_GREY);
            std::getline(std::cin, choice);
            if (choice.length() == 1)
            {
                switch (choice[0])
                {
                    case 'L':
                        return true; // Update all the variables and treat the already mounted EFI partition normally
                    
                    case 'U':
                    {
                        efi::unmount_partition(efi);
                        return false;
                    }
                    
                    case 'A':
                    {
                        efi.clear();
                        return false; // Ignore the EFI partition and jump to the main menu
                    }
                }
            }
        }
    }

    bool check_if_mounted(EfiPartition& efi)
    {
        for (char i = 'Z'; i >= 'O'; --i) // Iterate through every letter of the lower part of the alphabet
        {
            if (fs::exists(std::string(1, i).append(":\\.winefimounter")))
            {
                efi.letter = i; // EFI is expected to be empty here, so we set the letter we found and pass everything down to restore_mounted() so that the letter can be read and the other fields can be overwritten
                if (restore_mounted(efi)) // If an EFI partition appears to be mounted, ask the user what to do
                    return true; 
            }
        }
        return false;
    }
}