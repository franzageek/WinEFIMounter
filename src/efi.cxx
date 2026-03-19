#include "core.hxx"
#include "efi.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

namespace fs = std::filesystem;

namespace efi
{
    bool select_partition(EfiPartition& efi)
    {
        system("@echo off > \"%temp%\\list.txt\" && @FOR /F \"tokens=*\" %a IN ('echo Get-Disk ^| powershell') DO (@echo %a >>\"%temp%\\list.txt\")");
        system("@mode 120, 30");
        std::cout << std::endl << " In order to mount your EFI partition, you first need to specify the ";
        core::change_text_color(COLOR_BLUE);
        std::cout << "drive";
        core::change_text_color(COLOR_GREY);
        std::cout << " it is located on.\n";
        std::cout << " After taking a look at the table below, please enter the number corrisponding to the ";
        core::change_text_color(COLOR_BLUE);
        std::cout << "correct disk";
        core::change_text_color(COLOR_GREY);
        std::cout << ".\n\n";
        std::ifstream diskList(core::diskListFile);
        std::string currentLine;
        if (!diskList) 
        {
            diskList.close();
            fs::remove_all(core::diskListFile);
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E1] Failed to read the disk list. Press any key to go back to the main menu...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }

        do
        {
            std::getline(diskList, currentLine);
        } 
        while (currentLine[0] != 'N' && diskList.good());
        if (currentLine[0] != 'N' || (currentLine[0] == 'P' && currentLine[1] == 'S')) 
        {
            diskList.close();
            fs::remove_all(core::diskListFile);
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E2] Failed to read the disk list. Press any key to go back to the main menu...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }

        std::vector<u8> indexBuffer;
        std::cout << currentLine << std::endl;
        std::getline(diskList, currentLine);
        std::getline(diskList, currentLine);
        char tmp[3];
        do
        {
            std::cout << currentLine << std::endl;
            memset(&tmp, 0, 3 * sizeof(char));
            if (isdigit(currentLine[0]))
            {
                if (isdigit(currentLine[1]))
                {
                    tmp[0] = currentLine[0];
                    tmp[1] = currentLine[1];
                    indexBuffer.push_back(atoi(tmp));

                }
                else
                {
                    tmp[0] = currentLine[0];
                    indexBuffer.push_back(atoi(tmp));
                }
            }
        } 
        while (std::getline(diskList, currentLine) && (currentLine[0] != 'P' || currentLine[1] != 'S')); // Display the disk list
        
        diskList.close();
        std::cout << std::endl;
        bool found = false;
        std::cout << " Enter ";
        core::change_text_color(COLOR_RED);
        std::cout << "A";
        core::change_text_color(COLOR_GREY);
        std::cout << " to abort.\n\n";
        while (true)
        {
            std::cout << "   - Enter a valid disk number: ";
            std::getline(std::cin, currentLine); // Get input from the user - reuse currentLine for better efficiency
            if (currentLine.length() == 0 || currentLine[0] == ' ')
                continue;

            if (currentLine[0] == 'A')
            {
                fs::remove_all(core::diskListFile);
                return false;
            }

            if (currentLine.length() == 1 && isdigit(currentLine[0]))
            {
                for (u8 i = 0; i < indexBuffer.size(); ++i)
                {
                    if (currentLine[0]-'0' == indexBuffer[i])
                    {
                        efi.disk = indexBuffer[i];
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }
            if (currentLine.length() == 2 && isdigit(currentLine[0]) && isdigit(currentLine[1]))
            {
                for (u8 i = 0; i < indexBuffer.size(); ++i)
                {
                    if (atoi(currentLine.c_str()) == indexBuffer[i])
                    {
                        efi.disk = indexBuffer[i];
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }
            std::cout << "   # ";
            core::change_text_color(COLOR_RED);
            std::cout << "Invalid disk number";
            core::change_text_color(COLOR_GREY);
            std::cout << std::endl;
        }
        found = false;
        std::cout << "\n Loading...";
        system(("@echo off > \"%temp%\\list.txt\" && echo Get-Partition -DiskNumber " + std::to_string(efi.disk) + " | powershell >\"%temp%\\list.txt\"").c_str());
        system("@cls");
        std::cout << std::endl;
        std::cout <<" Now you need to specify your EFI partition number.\n Choose it from the table below:\n\n ";
        core::change_text_color(COLOR_BLUE_WHITE);
        std::cout << " TIP: ";
        core::change_text_color(COLOR_GREY);
        std::cout << " EFI partitions are usually really small (about ";
        core::change_text_color(COLOR_BLUE);
        std::cout << "100MB to 500MB";
        core::change_text_color(COLOR_GREY);
        std::cout << " in size) and are marked as ";
        core::change_text_color(COLOR_WHITE);
        std::cout << "\"";
        core::change_text_color(COLOR_BLUE);
        std::cout << "SYSTEM";
        core::change_text_color(COLOR_WHITE);
        std::cout << "\"";
        core::change_text_color(COLOR_GREY);
        std::cout << " partitions.\n ";
        core::change_text_color(COLOR_BLUE_WHITE);
        std::cout << " TIP: ";
        core::change_text_color(COLOR_GREY);
        std::cout << " You can use these two attributes to narrow down the number of entries.\n\n";
        std::ifstream partList(core::diskListFile);
        indexBuffer.clear();
        if (!partList) 
        {
            partList.close();
            fs::remove_all(core::diskListFile);
            efi.clear();
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E1] Failed to read the partition list. Press any key to go back to the main menu...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }

        do
        {
            std::getline(partList, currentLine);
        } 
        while ((currentLine[0] != 'P' || currentLine[1] != 'a' || currentLine[2] != 'r') && partList.good());
        if (currentLine[0] != 'P' || (currentLine[0] == 'P' && currentLine[1] == 'S')) 
        {
            partList.close();
            fs::remove_all(core::diskListFile);
            efi.clear();
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E2] Failed to read the partition list. Press any key to go back to the main menu...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }

        do
        {
            std::cout << currentLine << std::endl;
            memset(&tmp, 0, 3 * sizeof(char));
            if (isdigit(currentLine[0]))
            {
                if (isdigit(currentLine[1]))
                {
                    tmp[0] = currentLine[0];
                    tmp[1] = currentLine[1];
                    indexBuffer.push_back(atoi(tmp));

                }
                else
                {
                    tmp[0] = currentLine[0];
                    indexBuffer.push_back(atoi(tmp));
                }
            }
        } 
        while (std::getline(partList, currentLine) && (currentLine[0] != 'P' || currentLine[1] != 'S')); // Display the partition list
        
        partList.close();
        fs::remove_all(core::diskListFile);
        std::cout << " Enter ";
        core::change_text_color(COLOR_RED);
        std::cout << "A";
        core::change_text_color(COLOR_GREY);
        std::cout << " to abort.\n\n";
        while (true)
        {
            std::cout << "   - Enter a valid partition number: ";
            std::getline(std::cin, currentLine); // Get input from the user
            if (currentLine.length() == 0 || currentLine[0] == ' ')
                continue;

            if (currentLine[0] == 'A')
            {
                efi.disk = 0;
                return false;
            }

            if (currentLine.length() == 1 && isdigit(currentLine[0]))
            {
                for (u8 i = 0; i < indexBuffer.size(); ++i)
                {
                    if (currentLine[0]-'0' == indexBuffer[i])
                    {
                        efi.part = indexBuffer[i];
                        return true;
                    }
                }
            }
            if (currentLine.length() == 2 && isdigit(currentLine[0]) && isdigit(currentLine[1]))
            {
                for (u8 i = 0; i < indexBuffer.size(); ++i)
                {
                    if (atoi(currentLine.c_str()) == indexBuffer[i])
                    {
                        efi.part = indexBuffer[i];
                        return true;
                    }
                }
            }
            std::cout << "   # ";
            core::change_text_color(COLOR_RED);
            std::cout << "Invalid partition number";
            core::change_text_color(COLOR_GREY);
            std::cout << std::endl;
        }
        
        return false;
    }

    bool mount_partition(EfiPartition& efi)
    {
        SetConsoleTitleA("WinEFIMounter v1.0.4 (Mounting...)");
        std::cout << std::endl << std::endl << std::endl;
        std::cout << " > Setting mount point..." << std::endl;
        DWORD availableDrives = GetLogicalDrives();
        if (availableDrives == 0)
        {
            efi.clear();
            core::change_text_color(COLOR_YELLOW);
            std::cerr << std::endl << " [E4] Failed to mount the selected partition (error " << std::to_string(GetLastError()) << ").\n      WinEFIMounter was unable to retrieve available drive letters.\n      Press any key to go back to the main menu...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }
        availableDrives = ~availableDrives; // Get free letters
        availableDrives &= 0x03FFC000; // Keep only letters O..=Z
        u8 count = 0;
        DWORD tmp = availableDrives;
        while (tmp) 
        {
            tmp &= (tmp - 1);
            ++count;
        }
        std::cout << "   > Found " << std::to_string(count) << " suitable letter(s)" << std::endl;
        if (!count)
        {
            SetConsoleTitleA("WinEFIMounter v1.0.4");
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E3] Failed to locate a suitable letter. Please try to free a letter after \'N:\\\', then run WinEFIMounter again.\n      Press any key to exit...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            exit(3);
        }
        availableDrives >>= 14;
        for (u8 i = 12; i > 0; --i) // Reverse the order (start from Z up)
        {
            if ((availableDrives & (1 << (i-1))) > 0)
            {
                efi.letter = 'O' + (i-1);
                std::cout << "   >> Mounting to \"" << efi.letter << ":\\\"..." << std::endl;
                break;
            }
        }
        std::cout << std::endl << " > Mounting the selected partition..." << std::endl;
        std::cout << "   >> Start mounting disk " << std::to_string(efi.disk) << ", partition " << std::to_string(efi.part) << "..." << std::endl;
        int exitCode = system(("@echo Add-PartitionAccessPath -DiskNumber " + std::to_string(efi.disk) + " -PartitionNumber " + std::to_string(efi.part) + " -AccessPath \"" + std::string(1, efi.letter) + ":\" | powershell>nul").c_str());
        if (exitCode != 0)
        {
            efi.clear();
            core::change_text_color(COLOR_YELLOW);
            std::cerr << std::endl << " [E4] Failed to mount the selected partition (error " << std::to_string(exitCode) << ").\n      The partition might not be formatted correctly. Double-check that it is FAT formatted, then retry.\n      Make sure you're not trying to mount an already mounted EFI partition either.\n      Press any key to go back to the main menu...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            return false;
        }
        system(("@echo off && @echo ## [" + std::to_string(efi.disk) + ":" + std::to_string(efi.part) + "] Do NOT delete this file! It's needed by WinEFIMounter as a failsafe. It will be automatically deleted after unmounting the partition. Mounted on %date% @ %time% ## > \"" + std::string(1, efi.letter) + ":\\.winefimounter\"").c_str()); // Create cache file
        std::cout << std::endl << " > Done!" << std::endl;
        return true;
    }

    void unmount_partition(EfiPartition& efi)
    {
        SetConsoleTitleA("WinEFIMounter v1.0.4 (Unmounting...)");
        std::cout << std::endl << std::endl;
        std::cout << std::endl << " > Unmounting the EFI partition..." << std::endl;
        std::cout << "   >> Start unmounting disk " << std::to_string(efi.disk) << ", partition " << std::to_string(efi.part) << "..." << std::endl;
        fs::remove_all(std::string(1, efi.letter).append(":\\.winefimounter")); // Delete cache file
        core::change_text_color(COLOR_DARK_GREY);
        std::cout << "\n ";
        int exitCode = system(("@echo Remove-PartitionAccessPath -DiskNumber " + std::to_string(efi.disk) + " -PartitionNumber " + std::to_string(efi.part) + " -AccessPath \"" + std::string(1, efi.letter) + ":\" | powershell>nul 2>nul").c_str());
        if (exitCode != 0)
        {
            SetConsoleTitleA("WinEFIMounter v1.0.4");
            system(("@echo off && @echo ## [" + std::to_string(efi.disk) + ":" + std::to_string(efi.part) + "] Do NOT delete this file! It's needed by WinEFIMounter as a failsafe. It will be automatically deleted after unmounting the partition. Mounted on %date% @ %time% ## > \"" + std::string(1, efi.letter) + ":\\.winefimounter\"").c_str()); // Restore cache file
            core::change_text_color(COLOR_YELLOW);
            std::cerr << " [E4] Failed to unmount the partition (error " << std::to_string(exitCode) << ").\n      Make sure it hasn't been already unmounted from outside WinEFIMounter.\n      If that's not the case, you can always run WinEFIMounter again after you have fixed the issue\n      in order to unmount the EFI partition.\n      Press any key to exit...";
            core::change_text_color(COLOR_GREY);
            system("@pause >nul");
            exit(exitCode);
        }
        efi.clear();
        core::change_text_color(COLOR_GREY);
        std::cout << "> Done!";
        return;
    }

    void EfiPartition::clear(void)
    {
        this->disk = 0;
        this->letter = 0;
        this->part = 0;
        return;
    }
}