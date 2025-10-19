#include "ui.hxx"
#include "core.hxx"
#include <iostream>
#include <string>

namespace ui
{
    bool display_prompt(prompt type)
    {
        std::string choice;
        switch (type)
        {
            case prompt::mount:
            {
                while (true)
                {
                    system("@cls");
                    std::cout << std::endl << "   - Type ";
                    core::change_text_color(COLOR_BLUE);
                    std::cout << "M";
                    core::change_text_color(COLOR_GREY);
                    std::cout << " to mount the selected partition or ";
                    core::change_text_color(COLOR_RED);
                    std::cout << "B";
                    core::change_text_color(COLOR_GREY);
                    std::cout << " to go back to the main menu...";
                    std::getline(std::cin, choice);
                    if (choice.length() == 1)
                    {
                        switch (choice[0])
                        {
                            case 'B':
                                return false;
                            case 'M':
                                return true;
                        }
                    }
                }
                break;
            }

            case prompt::unmount:
            {
                while (true)
                {
                    system("@cls");
                    std::cout << std::endl << "   - Type ";
                    core::change_text_color(COLOR_BLUE);
                    std::cout << "U";
                    core::change_text_color(COLOR_GREY);
                    std::cout << " to unmount the EFI partition or ";
                    core::change_text_color(COLOR_RED);
                    std::cout << "B";
                    core::change_text_color(COLOR_GREY);
                    std::cout << " to go back to the main menu...";
                    std::getline(std::cin, choice);
                    if (choice.length() == 1)
                    {
                        switch (choice[0])
                        {
                            case 'B':
                                return false;
                            case 'U':
                                return true;
                        }
                    }
                }
                break;
            }

            case prompt::clone:
            {
                while (true)
                {
                    system("@cls");
                    std::cout << std::endl << "   - Type ";
                    core::change_text_color(COLOR_BLUE);
                    std::cout << "C";
                    core::change_text_color(COLOR_GREY);
                    std::cout << " to start cloning the EFI partition to \"C:\\EFIPartition\" or ";
                    core::change_text_color(COLOR_RED);
                    std::cout << "B";
                    core::change_text_color(COLOR_GREY);
                    std::cout << " to go back to the main menu...";
                    std::getline(std::cin, choice);
                    if (choice.length() == 1)
                    {
                        switch (choice[0])
                        {
                            case 'B':
                                return false;
                            case 'C':
                                return true;
                        }
                    }
                }
                break;
            }

            case prompt::exit:
            {
                while (true)
                {
                    system("@cls");
                    core::change_text_color(COLOR_YELLOW);
                    std::cout << std::endl << " [!!] Your EFI partition is still mounted!\n      Unmounting the EFI partition before leaving is recommended, although WinEFIMounter is able\n      to detect mounted partitions on startup, and will let you choose whether or not to unmount one if found.";
                    std::cout << std::endl << std::endl << "    - Type ";
                    core::change_text_color(COLOR_BLUE);
                    std::cout << "B";
                    core::change_text_color(COLOR_YELLOW);
                    std::cout << " to go back to the main menu or ";
                    core::change_text_color(COLOR_RED);
                    std::cout << "E";
                    core::change_text_color(COLOR_YELLOW);
                    std::cout << " to exit WinEFIMounter right away...";
                    core::change_text_color(COLOR_GREY);
                    std::getline(std::cin, choice);
                    if (choice.length() == 1)
                    {
                        switch (choice[0])
                        {
                            case 'B':
                                return false;
                            case 'E':
                                return true;
                        }
                    }
                }
            }
        }
        return false;
    }
}