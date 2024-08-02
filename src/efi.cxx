#include "../include/efi.hxx"

void get_efi_partition(u8& diskNumber, u8& partNumber, const std::string& listPath)
{
    system("@echo off > \"%temp%\\dpout.txt\" && @FOR /F \"tokens=*\" %a IN ('echo Get-Disk ^| powershell') DO (@echo %a >>\"%temp%\\dpout.txt\")");
    system("@mode 120, 30");
    std::cout << std::endl << " In order to mount your EFI partition, you first need to specify the drive it is located on." << std::endl;
    std::cout << " After taking a look at the table below, please enter the number corrisponding to your drive." << std::endl << std::endl;
    std::ifstream diskList(listPath);

    if (!diskList) 
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [E1] Failed to read the disk list. Press any key to go back..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        diskNumber = 255;
        return;
    }
    
    do
    {
        std::getline(diskList, currentLine);
    } 
    while (currentLine[0] != 'N' && diskList.good());

    if (currentLine[0] != 'N') 
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [E2] Failed to read the disk list. Press any key to go back..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        diskNumber = 255;
        return;
    }

    std::vector<char> indexBuffer;
    std::cout << currentLine << std::endl;
    std::getline(diskList, currentLine);
    std::getline(diskList, currentLine);

    do
    {
        std::cout << currentLine << std::endl;
        indexBuffer.push_back(currentLine[0]);
    } 
    while (std::getline(diskList, currentLine) && (currentLine[0] != 'P' || currentLine[1] != 'S')); // Display the disk list
    
    diskList.close();
    std::cout << std::endl;

getDiskNumber:
    std::cout << "   - Enter a valid disk number: ";
    std::getline(std::cin, currentLine); // Get input from the user
    if (currentLine.length() == 0)
        goto getDiskNumber;

    if (currentLine[0] == ' ')
        goto getDiskNumber;

    if (currentLine.length() == 1 && isdigit(currentLine[0]))
    {
        for (u8 i = 0; i < indexBuffer.size(); ++i)
        {
            if (currentLine[0] == indexBuffer[i])
            {
                diskNumber = currentLine[0]-'0';
                goto listPartitions;
            }
        }
    }
    std::cout << "   # ";
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    std::cout << "Not a valid disk number";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << std::endl;
    goto getDiskNumber;

listPartitions:
    system(("@echo off > \"%temp%\\dpout.txt\" && echo Get-Partition -DiskNumber " + std::string(1, diskNumber+'0') + " | powershell >\"%temp%\\dpout.txt\"").c_str());
    std::cout << std::endl << std::endl;
    std::cout <<" Now you need to specify your EFI partition number.\n Choose it from the table below:\n\n ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE_WHITE);
    std::cout << " TIP: ";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " EFI partitions are usually really small (about ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "100MB to 500MB";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " in size) and are marked as ";
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    std::cout << "\"";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "SYSTEM";
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
    std::cout << "\"";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " partitions.\n ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE_WHITE);
    std::cout << " TIP: ";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " You can use these two attributes to narrow down the number of entries.\n\n";

    std::ifstream partList(listPath);

    if (!partList) 
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [E1] Failed to read the partition list. Press any key to go back..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        diskNumber = 255;
        return;
    }

    indexBuffer.clear();

    do
    {
        std::getline(partList, currentLine);
    } 
    while ((currentLine[0] != 'P' || currentLine[1] != 'a' || currentLine[2] != 'r') && partList.good());

    if (currentLine[0] != 'P') 
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << " [E2] Failed to read the partition list. Press any key to go back..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        diskNumber = 255;
        return;
    }

    do
    {
        std::cout << currentLine << std::endl;
        indexBuffer.push_back(currentLine[0]);
    } 
    while (std::getline(partList, currentLine) && (currentLine[0] != 'P' || currentLine[1] != 'S')); // Display the partition list

    partList.close();
    fs::remove_all(listPath);

getPartNumber:
    std::cout << "   - Enter a valid partition number: ";
    std::getline(std::cin, currentLine); // Get input from the user
    if (currentLine.length() == 0 || currentLine[0] == ' ')
        goto getPartNumber;

    if (currentLine.length() == 1 && isdigit(currentLine[0]))
    {
        for (u8 i = 0; i < indexBuffer.size(); ++i)
        {
            if (currentLine[0] == indexBuffer[i])
            {
                partNumber = indexBuffer[i]-'0';
                return;
            }
        }
    }
    std::cout << "   # ";
    SetConsoleTextAttribute(hConsole, COLOR_RED);
    std::cout << "Not a valid partition number";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << std::endl;
    goto getPartNumber;
}

bool mount_efi_partition(u8& diskNumber, u8& partNumber, char& mntLetter, const std::string& listPath)
{
    get_efi_partition(diskNumber, partNumber, listPath);
    if (diskNumber == 255)
        return false;
    
mountStep0:
    system("@cls");
    std::cout << std::endl << "   - Type ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "M";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " to mount the selected partition or ";
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
            case 'M':
                goto mountStep1;
        }
    }
    goto mountStep0;

mountStep1:
    SetConsoleTitleA("WinEFIMounter v1.0.2 (Mounting...)");
    std::cout << std::endl << std::endl << std::endl;
    std::cout << " > Setting mount letter..." << std::endl;
    for (char i = 'Z'; i >= 'O'; --i)
    {
        if (!fs::exists(std::string(1, i).append(":\\"))) // Find a free letter
        {
            mntLetter = i;
            std::cout << "   > Mounting to \"" << i << ":\\\"..." << std::endl;
            goto mountStep2;
        }
    }
    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
    std::cerr << " [E3] Failed to locate a suitable letter. Please try to free a letter after \'O:\\\', then run WinEFIMounter again.\n      Press any key to exit..." << std::endl;
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    system("@pause >nul");
    exit(3);

mountStep2:
    std::cout << std::endl << " > Mounting the selected partition..." << std::endl;
    int exitCode = system(("@echo Add-PartitionAccessPath -DiskNumber " + std::string(1, diskNumber+'0') + " -PartitionNumber " + std::string(1, partNumber+'0') + " -AccessPath \"" + std::string(1, mntLetter) + ":\" | powershell>nul").c_str());
    std::cout << "   > Started mounting disk " << std::string(1, diskNumber+'0') << ", partition " << std::string(1, partNumber+'0') << "..." << std::endl;
    if (exitCode != 0)
    {
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        std::cerr << std::endl << " [E4] Failed to mount the selected partition (error " << std::string(1, exitCode+'0') << ").\n      The partition might not be formatted correctly. Double-check that it is FAT formatted, then retry.\n      Make sure you're not trying to mount an already mounted EFI partition either.\n      Press any key to exit..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        exit(exitCode);
    }
    system(("@echo off && @echo ## [" + std::string(1, diskNumber+'0') + ":" + std::string(1, partNumber+'0') + "] MOUNTED ON %date% @ %time% ## > \"" + std::string(1, mntLetter) + ":\\.winefimounter\"").c_str()); // Create cache file
    std::cout << std::endl << " > Done!" << std::endl;
    return true;
}

bool unmount_efi_partition(const u8& diskNumber, const u8& partNumber, const char& mntLetter)
{
unmountStep0:
    system("@cls");
    std::cout << std::endl << "   - Type ";
    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
    std::cout << "U";
    SetConsoleTextAttribute(hConsole, COLOR_GREY);
    std::cout << " to unmount the EFI partition or ";
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
                return true;
            case 'U':
                goto unmountStep1;
        }
    }
    goto unmountStep0;

unmountStep1:
    SetConsoleTitleA("WinEFIMounter v1.0.2 (Unmounting...)");
    std::cout << std::endl << std::endl;
    std::cout << std::endl << " > Unmounting the EFI partition..." << std::endl;
    std::cout << "   > Started unmounting disk " << std::string(1, diskNumber+'0') << ", partition " << std::string(1, partNumber+'0') << "..." << std::endl;
    fs::remove_all(std::string(1, mntLetter).append(":\\.winefimounter")); // Delete cache file
    int exitCode = system(("@echo Remove-PartitionAccessPath -DiskNumber " + std::string(1, diskNumber+'0') + " -PartitionNumber " + std::string(1, partNumber+'0') + " -AccessPath \"" + std::string(1, mntLetter) + ":\" | powershell>nul 2>nul").c_str());
    if (exitCode != 0)
    {
        SetConsoleTitleA("WinEFIMounter v1.0.2");
        SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
        system(("@echo off && @echo ## [" + std::string(1, diskNumber+'0') + ":" + std::string(1, partNumber+'0') + "] MOUNTED ON %date% @ %time% ## > \"" + std::string(1, mntLetter) + ":\\.winefimounter\"").c_str());
        std::cerr << " [E4] Failed to unmount the partition (error " << std::string(1, exitCode+'0') << ").\n      Make sure it hasn't been unmounted from outside WinEFIMounter.\n      If that's not the case, you can always run WinEFIMounter again after you have fixed the issue\n      in order to unmount the EFI partition.\n      Press any key to exit..." << std::endl;
        SetConsoleTextAttribute(hConsole, COLOR_GREY);
        system("@pause >nul");
        exit(exitCode);
    }
    std::cout << " > Done!";
    return false;
}
