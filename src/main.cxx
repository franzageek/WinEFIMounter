#include "../include/core.hxx"
#include "../include/efi.hxx"
#include "../include/clone.hxx"

int main()
{
    SetConsoleTitleA("WinEFIMounter v1.0.2");
    if (!check_if_admin()) // If not admin, throw an error
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << std::endl << " [E0] Please run WinEFIMounter as administrator. Press any key to exit...";
        system("@pause >nul");
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        exit(1);
    }

    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    char tempPath[MAX_PATH];
    u8 diskNumber;
    u8 partNumber;
    char mntLetter;

    DWORD pathLen = GetTempPathA(MAX_PATH, tempPath); // Get TEMP path
    if (pathLen == 0) 
    {
        std::cerr << " Failed to get TEMP path: " << GetLastError() << std::endl;
        exit(1);
    }
    std::string listPath = std::string(tempPath) + "dpout.txt";
    del_temp_files(listPath);
    system("@mode 120, 30");
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << std::endl << "   #####################################################" << std::endl;
    std::cout <<              "  #                   WinEFIMounter                   #" << std::endl;
    std::cout <<              " #####################################################" << std::endl << std::endl;
    std::cout <<              " Welcome to WinEFIMounter v1.0.2. This program is meant to be used to let you access" << std::endl;
    std::cout <<              " your EFI parititon from Windows with ease." << std::endl << std::endl;
    std::cout <<              " WinEFIMounter could be used to mount any EFI partition, but its main purpose" << std::endl;
    std::cout <<              " is to let you mount your Hackintosh EFI partition since there isn't" << std::endl;
    std::cout <<              " any (non-3rd party) tool to do that on Windows." << std::endl << std::endl;
    std::cout <<              "   - Press any key to begin...";
    system("@pause >nul");

    if (check_if_already_mounted(diskNumber, partNumber, mntLetter))
        goto mountedMainMenu;

unmountedMainMenu: // Display the stripped down version of the main menu
    system("@cls");
    SetConsoleTitleA("WinEFIMounter v1.0.2 (UNMOUNTED)");
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << std::endl << "   #####################################################" << std::endl;
    std::cout <<              "  #                   WinEFIMounter                   #" << std::endl;
    std::cout <<              " #####################################################" << std::endl << std::endl;
    std::cout <<              " The EFI partition is ";
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    std::cout <<              "NOT MOUNTED";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout <<              "." << std::endl << std::endl;
    std::cout <<              " 1. Mount EFI partition" << std::endl << std::endl;
    std::cout <<              " E. Exit" << std::endl << std::endl << std::endl;
    std::cout <<              "   - Enter your choice: ";
    std::getline(std::cin, currentLine);
    if (currentLine.length() == 1)
    {
        switch (currentLine[0])
        {
            case '1':
                goto mountEFIPartition;
            case 'E':
                goto exitScr;
        }
    }
    goto unmountedMainMenu;

mountEFIPartition:
    if (!mount_efi_partition(diskNumber, partNumber, mntLetter, listPath))
        goto unmountedMainMenu;

mountedMainMenu: // Display the full-fledged main menu
    system("@cls");
    SetConsoleTitleA("WinEFIMounter v1.0.2 (MOUNTED)");
    std::cout << std::endl << "   #####################################################" << std::endl;
    std::cout <<              "  #                   WinEFIMounter                   #" << std::endl;
    std::cout <<              " #####################################################" << std::endl << std::endl;
    std::cout <<              " The EFI partition is ";
    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
    std::cout <<              "MOUNTED TO \"" << mntLetter << ":\\\"";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout <<              "." << std::endl << std::endl;
    std::cout <<              " 1. Browse the EFI partition via CMD" << std::endl;
    std::cout <<              " 2. View EFI partition in Windows Explorer" << std::endl;
    std::cout <<              " 3. Unmount EFI partition" << std::endl;
    std::cout << std::endl;
    std::cout <<              " E. Exit" << std::endl << std::endl << std::endl;
    std::cout <<              "   - Enter your choice: ";
    std::getline(std::cin, currentLine);
    switch (currentLine[0])
    {
        case '1':
        {
            system(("@start cmd /k \"" + std::string(1, mntLetter) + ":\"").c_str());
            goto mountedMainMenu;
        }
        case '2':
            goto cloneEFIPartition;
        case '3':
            goto unmountEFIPartition;
        case 'E':
            goto mountedExitScr;
    }
    goto mountedMainMenu;    

cloneEFIPartition:
    if (!clone_efi_partition(mntLetter)) // Clone, then flush the EFI partition
        goto mountedMainMenu;
    flush_efi_partition(mntLetter);
    goto mountedMainMenu;

unmountEFIPartition:
    if (unmount_efi_partition(diskNumber, partNumber, mntLetter)) // Unmount the EFI partition
        goto mountedMainMenu;
    goto unmountedMainMenu;

mountedExitScr: // If the EFI partition is still mounted, throw an error
    system("@cls");
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cout << std::endl << " [!!] Your EFI partition is still mounted!\n      Unmounting the EFI partition before leaving is recommended, although WinEFIMounter is able\n      to detect mounted partitions on startup, and will let you choose whether or not to unmount one if found.";
    std::cout << std::endl << std::endl << "    - Type ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "B";
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cout << " to go back to the main menu or ";
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    std::cout << "E";
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cout << " to exit WinEFIMounter right away...";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::getline(std::cin, currentLine);
    if (currentLine.length() == 1)
    {
        switch (currentLine[0])
        {
            case 'B':
                goto mountedMainMenu;
            case 'E':
                goto exitScr;
        }
    }
    goto mountedExitScr;

exitScr: // Display an exit screen
    system("@cls");
    SetConsoleTitleA("WinEFIMounter v1.0.2");
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << std::endl << "   #####################################################" << std::endl;
    std::cout <<              "  #                   WinEFIMounter                   #" << std::endl;
    std::cout <<              " #####################################################" << std::endl << std::endl;
    std::cout <<              " WinEFIMounter version 1.0.2" << std::endl << std::endl;
    std::cout <<              " Developed by ";
    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
    std::cout << "<franzageek>" << std::endl << std::endl;
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout <<              " GitHub repository: [";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "https://github.com/franzageek/WinEFIMounter";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout <<              "]" << std::endl;
    std::cout <<              " Report a bug: [";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "https://github.com/franzageek/WinEFIMounter/issues";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout <<              "]" << std::endl << std::endl << std::endl;
    std::cout <<              " Have a good day! " << std::endl << std::endl;
    if (fs::exists("C:\\EFIPartition"))
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cout <<              " (The \"C:\\EFIPartition\" directory will be ";
        SetConsoleTextAttribute(hConsole, COLOR_RED);
        std::cout << "PERMANENTLY";
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cout <<              " deleted along with its content)" << std::endl << std::endl << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
    }
    std::cout <<              "   - Press any key to exit...";
    system("@pause>nul");
    if (fs::exists("C:\\EFIPartition")) fs::remove_all("C:\\EFIPartition");
    exit(0);
}
