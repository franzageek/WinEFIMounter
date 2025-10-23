[![](https://img.shields.io/github/license/franzageek/WinEFIMounter)](LICENSE)
[![](https://img.shields.io/github/v/release/franzageek/WinEFIMounter)](https://github.com/franzageek/WinEFIMounter/releases/latest)
[![](https://img.shields.io/github/downloads/franzageek/WinEFIMounter/total?label=total%20downloads)](https://github.com/franzageek/WinEFIMounter/releases/)
[![](https://img.shields.io/github/downloads/franzageek/WinEFIMounter/latest/total)](https://github.com/franzageek/WinEFIMounter/releases/latest)
![](https://img.shields.io/endpoint?url=https%3A%2F%2Fhits.dwyl.com%2Ffranzageek%2FWinEFIMounter.json&label=total%20views%20(tracking...))
 
# WinEFIMounter
Mount your EFI partition from Windows. 
<br><br>
![winefimounter](https://github.com/user-attachments/assets/e65dbd86-a4dc-439a-a1a2-860baa5535f8)
<br>

[a.k.a. MountEFI for Windows]

<!---![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/6904b05f-519e-4c40-92df-559feb890785)-->
[**Introduction**](#introduction) - [**Usage**](#usage) - [**Problems**](#problems) - [**Credits**](#credits)

## Introduction
WinEFIMounter is a simple, standalone C++ program designed to make mounting the EFI partition on your Hackintosh drive **directly from Windows** easy. While it can mount any EFI partition (including those from Windows and Linux), its primary purpose is to allow you to access your Hackintosh EFI without having to boot into macOS. 

It's hard to believe but in reality _**there isn't any simple software**_ such as [Corpnewt](https://github.com/corpnewt)'s [**MountEFI**](https://github.com/corpnewt/MountEFI) (for Mac) that lets you do it from Windows: you would have to download **third-party programs**. You might as well try WinEFIMounter instead: it's lightweight and easy to use!


## Usage
### Supported actions
WinEFIMounter is very easy to use. It features a **simple CLI** that makes everything very straightforward.
It allows you to:
- [Mount an EFI partiton](#mount-an-efi-partition)
- [Access the partition via Command Prompt](#access-the-efi-partition-via-command-prompt)
- [Open the partition in File Explorer](#open-the-efi-partition-in-file-explorer)
- [Unmount the EFI partition](#unmount-the-efi-partition)

It can currently perform very basic actions, but it will get more and more advanced later in time.

### Mount an EFI Partition
When you're at the main menu, just enter <kbd>M</kbd> at the prompt.
You will be asked to enter the **drive number** and the **partition number** corresponding to the specific drive and EFI partition to mount.

### Access the EFI partition via Command Prompt
After you've mounted the EFI partition, enter <kbd>1</kbd> at the prompt. You'll be given a **CMD window** from which to work with your EFI partition.

### Open the EFI partition in File Explorer
After you EFI has been mounted successfully, enter <kbd>2</kbd> at the prompt.<br>
Since Windows' weird permission system doesn't allow you to view the EFI partition in File Explorer, WinEFIMounter is forced to **clone it** to some other directory (*"C:\EFIPartition\\"*) so that you can work with the files. WinEFIMounter will then let you **revise the changes** and **apply them** back to the EFI partition on your behalf once you're done, so you don't have to worry about anything.
In case something goes wrong during this process, you'll be provided with a **backup of the EFI partition** (*"C:\EFIPartition_backup\\"*) that gets automatically updated by WinEFIMounter every time you clone it.

### Unmount the EFI partition
Just hit <kbd>3</kbd> at the prompt after you're done working with your EFI partition. 

### Required tools
WinEFIMounter relies on a bunch of **pre-installed Windows tools**, such as:
  - PowerShell
    > Used for mounting and unmounting the EFI partition.
  - XCopy
    > Used for cloning the entire EFI partition to the *"C:\EFIPartition\\"* directory.

### Use cases
WinEFIMounter is the perfect solution for a variety of problems, including:

- Fixing your Hackintosh if it's not booting and you have no way to access the EFI partition
  > If you fuck up with your kexts, SSDTs or drivers (like I did) you will likely need a quick way to fix them in order to make your Hackintosh boot again.
- Cleaning up your EFI
  > OpenCore leaves log files all over your EFI partition every time you boot macOS. WinEFIMounter allows you to get rid of them in the blink of an eye.
- Adding files to your EFI
  > Like fixing issues, accessing your EFI from Windows with WinEFIMounter is now easier than ever before.
- Managing Windows or Linux EFI partitions
  > That's right, WinEFIMounter can mount all kinds of EFI partitions you can think of!
  > The program might often refer to the EFI partition as "the Hackintosh EFI partition" or to the drive as "your Hackintosh disk", but you can use it for other ESPs too.

## Problems

### v1.0.2: Deleted files don't actually get deleted
Due to a misuse of XCopy, only new or modified files are transferred back to the EFI partition. Deleted files don't actually get updated.
Version 1.0.3 fixes the issue, by implementing a new flushing method that updates only the required files, without overwriting the whole partition. 

### v1.0.1: Cannot mount an external EFI partition
As noted by 1dolla, WinEFIMounter has trouble assigning a letter to EFI partitions on external USB drives. There is however a PowerShell command that will allow you to assign it a letter, which you can find here: [#3](https://github.com/franzageek/WinEFIMounter/issues/3). There are a few side effects though, such as the fact that the EFI will be mounted every single time Windows detects it is unmounted. <br>
I've released a C++ update (v1.0.2) that fixes this bug.

### v1.0.0: Flushing procedure failed
WinEFIMounter is a simple script of about 400 lines of code, with basic mounting and unmounting handled by `DiskPart`. The most complex part is the cloning and flushing process, which copies files between the EFI partition and "`C:\EFIPartition\`". 

This is the step-by-step description of what happens at the moment of cloning:

- "`C:\EFIPartition`" folder gets created
- The whole directory tree of the EFI partition is copied over to the destination folder

And this is what happens when you flush the files back to the EFI partition:

- New files from the destination directory are copied over to the EFI partition
- Old files and folders are deleted
- "`C:\EFIPartition`" directory is deleted

Yeah, I agree, that's not a lot of stuff whatsoever. But this is exactly the reason for which I decided to take **extra-precautions** and make the whole program **even safer**: at the end of the day it's just a simple script, and adding an extra part to prevent file loss shouldn't be too difficult.

So here's what I did: the part where errors are most likely to occur is when flushing updated files back to the EFI. So I added an **`ERRORLEVEL` check** after the `XCopy` command. This means that if something goes wrong during the `XCopy` command the `ERRORLEVEL` value will be **different from 0**, making the program show this error screen:
![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/3d15b0ed-86b2-4eac-8f12-61955cf01613)

One of the cases this error is supposed to occur is if the destination directory cannot be found.
> The way I managed to test the error (just to check if everything was working fine) is by mounting and cloning the partition using WinEFIMounter, then unmounting it from outside WinEFIMounter and start flushing back the files with WinEFIMounter. This will restult in `XCopy Error 4: Destination cannot be found`.

I'm planning to add the same `ERRORLEVEL` check when cloning the files from the EFI to the destination folder, to check if the files have been successfully copied to the destination directory or if an error has occurred along the way. I'll do that in a future version.


## Credits
This project began out of necessity when I needed to repair my Hackintosh EFI but couldn't find a version of MountEFI for Windows. I hope WinEFIMounter helps save you time and effort by offering a lightweight, easy-to-use alternative to third-party programs.

Thanks to all of ya that decided to star, clone & download WinEFIMounter! Really appreciate it <3
