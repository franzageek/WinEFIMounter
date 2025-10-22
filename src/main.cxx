#include "core.hxx"
#include "efi.hxx"
#include "ui.hxx"
#include <filesystem>
#include <iostream>
#include <string>
#include <Windows.h>

namespace fs = std::filesystem;

int main(void)
{
    SetConsoleTitleA("WinEFIMounter v1.0.3");
    if (!core::is_admin())
    {
        core::change_text_color(COLOR_YELLOW);
        std::cerr << std::endl << " [E0] Please run WinEFIMounter as administrator. Press any key to exit...";
        system("@pause >nul");
        core::change_text_color(COLOR_GREY);
        exit(1);
    }
    core::change_text_color(COLOR_GREY);
    efi::EfiPartition efi;
    efi.clear();
    core::init_temp_path();
    system("@mode 120, 30 && @cls");
    std::cout << std::endl << "   #####################################################\n";
    std::cout <<              "  #                   WinEFIMounter                   #\n" ;
    std::cout <<              " #####################################################\n\n";
    std::cout <<              " Welcome to WinEFIMounter v1.0.3.\n";
    std::cout <<              " This tool is designed to give you quick and easy access to your EFI partition\n";
    std::cout <<              " directly from Windows.\n\n";
    std::cout <<              " While WinEFIMounter can be used to mount all sorts of EFI partitions, it's primarily\n";
    std::cout <<              " aimed at Hackintosh users since Windows doesn't provide any tool they can use\n";
    std::cout <<              " for managing their Hackintosh EFI partition.\n\n";
    std::cout <<              "   - Press any key to begin...";
    system("@pause >nul");
    std::string choice;

    if (efi::check_if_mounted(efi))
        goto mountedMenu;

    unmountedMenu: // Display the stripped down version of the main menu
    {
        system("@cls");
        SetConsoleTitleA("WinEFIMounter v1.0.3 (UNMOUNTED)");
        core::change_text_color(COLOR_GREY);
        std::cout << std::endl << "   #####################################################" << std::endl;
        std::cout <<              "  #                   WinEFIMounter                   #" << std::endl;
        std::cout <<              " #####################################################" << std::endl << std::endl;
        std::cout <<              " The EFI partition is ";
        core::change_text_color(COLOR_RED);
        std::cout <<              "NOT MOUNTED";
        core::change_text_color(COLOR_GREY);
        std::cout <<              "." << std::endl << std::endl;
        std::cout <<              " 1. Mount EFI partition" << std::endl << std::endl;
        std::cout <<              " E. Exit" << std::endl << std::endl << std::endl;
        std::cout <<              "   - Enter your choice: ";
        std::getline(std::cin, choice);
        if (choice.length() == 1)
        {
            switch (choice[0])
            {
                case '1':
                {
                    std::cout << "\n Loading...";
                    if 
                    (
                        efi::select_partition(efi) && 
                        ui::display_prompt(ui::prompt::mount) && 
                        efi::mount_partition(efi)
                    )
                    {
                        goto mountedMenu;
                    }

                    break;
                }

                case 'E':
                    goto exitScr;
            }
        }
        goto unmountedMenu;
    }

    mountedMenu:
    {
        system("@cls");
        SetConsoleTitleA("WinEFIMounter v1.0.3 (MOUNTED)");
        std::cout << std::endl << "   #####################################################" << std::endl;
        std::cout <<              "  #                   WinEFIMounter                   #" << std::endl;
        std::cout <<              " #####################################################" << std::endl << std::endl;
        std::cout <<              " The EFI partition is ";
        core::change_text_color(COLOR_GREEN);
        std::cout <<              "MOUNTED TO \"" << efi.letter << ":\\\"";
        core::change_text_color(COLOR_GREY);
        std::cout <<              "." << std::endl << std::endl;
        std::cout <<              " 1. Browse the EFI partition via CMD" << std::endl;
        std::cout <<              " 2. View EFI partition in Windows Explorer" << std::endl;
        std::cout <<              " 3. Unmount EFI partition" << std::endl;
        std::cout << std::endl;
        std::cout <<              " E. Exit" << std::endl << std::endl << std::endl;
        std::cout <<              "   - Enter your choice: ";
        std::getline(std::cin, choice);
        if (choice.length() == 1)
        {
            switch (choice[0])
            {
                case '1':
                {
                    system(("@start cmd /k \"" + std::string(1, efi.letter) + ":\"").c_str());
                    break;
                }

                case '2':
                {
                    if 
                    (
                        ui::display_prompt(ui::prompt::clone) &&
                        efi::clone_partition(efi)
                    )
                    {
                        efi::flush_partition(efi);
                    }
                    
                    break;
                }

                case '3':
                {
                    if (ui::display_prompt(ui::prompt::unmount))
                    {
                        efi::unmount_partition(efi);
                        goto unmountedMenu;
                    }

                    break;
                }
                
                case 'E':
                {
                    if (ui::display_prompt(ui::prompt::exit))
                        goto exitScr;
                }
            }
        }
        goto mountedMenu;
    }

    exitScr: // Display an exit screen
    {
        system("@cls");
        SetConsoleTitleA("WinEFIMounter v1.0.3");
        core::change_text_color(COLOR_GREY);
        std::cout << std::endl << "   #####################################################" << std::endl;
        std::cout <<              "  #                   WinEFIMounter                   #" << std::endl;
        std::cout <<              " #####################################################" << std::endl << std::endl;
        std::cout <<              " WinEFIMounter version 1.0.3" << std::endl << std::endl;
        std::cout <<              " Developed by ";
        core::change_text_color(COLOR_GREEN);
        std::cout << "<franzageek>" << std::endl << std::endl;
        core::change_text_color(COLOR_GREY);
        std::cout <<              " GitHub repository: [";
        core::change_text_color(COLOR_BLUE);
        std::cout << "https://github.com/franzageek/WinEFIMounter";
        core::change_text_color(COLOR_GREY);
        std::cout <<              "]" << std::endl;
        std::cout <<              " Report a bug: [";
        core::change_text_color(COLOR_BLUE);
        std::cout << "https://github.com/franzageek/WinEFIMounter/issues";
        core::change_text_color(COLOR_GREY);
        std::cout <<              "]" << std::endl << std::endl << std::endl;
        std::cout <<              " Have a good day! " << std::endl << std::endl;
        if (fs::exists("C:\\EFIPartition"))
        {
            core::change_text_color(COLOR_YELLOW);
            std::cout <<              " (The \"C:\\EFIPartition\\\" directory will be ";
            core::change_text_color(COLOR_RED);
            std::cout << "PERMANENTLY";
            core::change_text_color(COLOR_YELLOW);
            std::cout <<              " deleted along with its content)" << std::endl << std::endl << std::endl;
            core::change_text_color(COLOR_GREY);
        }
        std::cout <<              "   - Press any key to exit...";
        system("@pause>nul");
        if (fs::exists("C:\\EFIPartition")) fs::remove_all("C:\\EFIPartition");
        exit(0);
    }
}