[![](https://img.shields.io/github/license/franzageek/WinEFIMounter)](LICENSE)
[![](https://img.shields.io/github/v/release/franzageek/WinEFIMounter)](https://github.com/franzageek/WinEFIMounter/releases/latest)
[![](https://img.shields.io/github/downloads/franzageek/WinEFIMounter/total?label=total%20downloads)](https://github.com/franzageek/WinEFIMounter/releases/)
[![](https://img.shields.io/github/downloads/franzageek/WinEFIMounter/latest/total)](https://github.com/franzageek/WinEFIMounter/releases/latest)
![](https://img.shields.io/endpoint?url=https%3A%2F%2Fhits.dwyl.com%2Ffranzageek%2FWinEFIMounter.json&label=total%20views%20(tracking...))
 
# WinEFIMounter
Mount your Hackintosh EFI partition from Windows. 

[a.k.a. MountEFI for Windows]
![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/6904b05f-519e-4c40-92df-559feb890785)
[**Introduction**](#introduction) - [**Usage**](#usage) - [**Problems**](#problems) - [**Credits**](#credits)

## Introduction
WinEFIMounter is a simple, standalone C++ program designed to make mounting the EFI partition on your Hackintosh drive **directly from Windows** easy. While it can mount any EFI partition (including those from Windows and Linux), its primary purpose is to allow you to access your Hackintosh EFI without having to boot into macOS. 

It's hard to believe but in reality _**there isn't any simple software**_ such as [Corpnewt](https://github.com/corpnewt)'s [**MountEFI**](https://github.com/corpnewt/MountEFI) (for Mac) that lets you do it from Windows: you would have to download **third-party programs**. You might as well try WinEFIMounter instead: it's lightweight and easy to use!


## Usage
### Supported actions
WinEFIMounter is very easy to use. It features a **simple CLI** that makes everything very straightforward.

WinEFIMounter allows you to:
- Mount an EFI partiton
- Browse the content of the partition:
  - Via Command Prompt
  - Via File Explorer
- Unmount the EFI partition
  > i tell you no shit

It can currently perform very basic actions, but it will get more and more advanced later in time.

### Required tools
WinEFIMounter relies on a bunch of **pre-installed Windows tools**, such as:
  - PowerShell
    > Used for mounting and unmounting the EFI partition.
  - XCopy
    > Used for cloning the entire EFI partition to the "C:\EFIPartition" directory. This is done to make the EFI partition accessible by GUI as it would be impossible to access it just by opening the partition in File Explorer (due to admin rights-related reasons).

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

### Application behavior
When you start WinEFIMounter, a welcome screen greets you:
![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/ef66e019-d72a-46d3-a22a-13cb6935fb7f)
Press any key to skip the intro and move to the main menu:



![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/1ad744f3-bfa5-45a5-91ac-a7d283849d43)

The main menu allows you to:
- Choose a partition to mount
- Quit the program

To choose the action to perform, just type <kbd>1</kbd> (to mount a partition) or <kbd>E</kbd> (to exit WinEFIMounter) and then hit Enter.

If you want to mount a partition, press <kbd>1</kbd>. You'll get to the point where you need to select the drive and the partition to mount.
![Screenshot 2023-07-16 202956](https://github.com/franzageek/WinEFIMounter/assets/88248950/cdceb712-3afd-465b-a8f7-43a524d12931)
First, locate in the list the drive you want to mount the EFI partition of, then type its number and hit Enter.

![Screenshot 2023-07-16 203527](https://github.com/franzageek/WinEFIMounter/assets/88248950/65c5e495-3f59-4f65-a584-966f762a5ef0) <br>
Do the same thing for the EFI partition you need to mount.

![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/d1109eef-0d9f-438a-a8bb-ffc472fbc02a)
Once you selected your drive and EFI partition, type <kbd>M</kbd> to confirm. The mounting process will begin instantly.

![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/2735dfff-0ed2-4507-85b4-90fc38c38802)
Congrats! Your EFI Partition is now mounted to "`Z:\`" (or, if it's taken, to another letter at the very end of the alphabet).
You'll get to this screen, which basically tells you that you have two ways of editing your EFI partition's content:
- By browsing files and folders using the Command Prompt (via `cd`, `del`, `move` and `copy`)
  > Although it might seem pretty straightforward, this is the most complicated route you can take. Yk, it's always a smarter idea to do things in a GUI when you're able to.
- By opening an EFI partition's clone in File Explorer
  > This is achieved by copying the entire directory tree of the EFI partition onto a directory that can be accessed with standard privileges. Because yeah, the EFI partition itself it cannot be accessed by TrustedInstaller either, which is the highest authority in your system. The fun fact is that despite all that it can be easily accessed by an elevated Command Prompt, and you can use it to copy the content over to a folder that you can access with standard-user rights. So, when you run WinEFIMounter as administrator it will be able to copy the entire partition tree over to a standard directory, which will be then flushed back to the EFI partition once you're done modifying your files.
  >  > FYI, the directory that will host the clone of the EFI partition is "`C:\EFIPartition\`".

Anyway, just press any key to skip it.


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/348fdc42-7341-49ae-a7b5-f39bb04ba5ac)
Once the EFI partition is mounted, you can:
- Browse the partition via Command Prompt
- Access a cloned version of the EFI partition in File Explorer
- Unmount the partition when you're done


![Screenshot 2023-07-17 050930](https://github.com/franzageek/WinEFIMounter/assets/88248950/abcda3ec-626e-4e89-90c3-93de454e2fda)
Option <kbd>1</kbd> will simply open a Command Prompt window in the EFI partition directory.


![Screenshot 2023-07-17 051300](https://github.com/franzageek/WinEFIMounter/assets/88248950/53ba8760-9fce-4379-9eef-5312d49fa8e3)
Option <kbd>2</kbd> will show this message. To start cloning, type <kbd>C</kbd> and hit Enter.


![Screenshot 2023-07-17 051401](https://github.com/franzageek/WinEFIMounter/assets/88248950/87d57928-cb4f-4fa9-93d5-6a3cdd69cd65)
After you typed <kbd>C</kbd>, all the files in your EFI folder get copied inside of "`C:\EFIPartition`". WinEFIMounter will automatically open an Explorer window in that directory for you.

You can now access your files like you normally would, and you won't even notice the fact that you're actually outside of your EFI partition.

But how can you make the changes made to your files in "`C:\EFIPartition`" effective on the EFI partition itself?


Well, there's a simple yet slightly complex solution, but we'll talk about it later in this ReadMe.

Just press <kbd>F</kbd> and hit Enter to start flushing the updated files back to the EFI.


![Screenshot 2023-07-17 053408](https://github.com/franzageek/WinEFIMounter/assets/88248950/76cb80af-8a14-47e4-b088-da2c0e5bcf7c)

The files you modified are now in your EFI partition, without the need for you to worry about anything!


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/21835753-d725-4e1a-92d0-e01d97543da3)
Choosing Option <kbd>3</kbd> in the main menu will result in this screen. Type <kbd>U</kbd> and press Enter to continue.
> Always save your work and close any file that belongs to the EFI partition before you unmount it.


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/c5ec573c-3cbc-4351-a97c-fb08dace2cb8)
And here you have your success screen. Pressing a key will show the first main menu.


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/5ae3f0b3-ed03-4852-b068-f406ec46bbb9)
Choosing Option <kbd>E</kbd> from the main menu while your partition is still mounted will take you to this warning screen, which basically reminds you to unmount your EFI partition before you leave WinEFIMounter.

> If you didn't care of the message and closed the window, the next time to launched WinEFIMounter you would have to start again from mounting the partition (which is already mounted), resulting in a general mess where the `Z` letter is taken by the already mounted EFI partition and WinEFIMounter is forced to assign the `Y` letter to a partition which is already mounted to "`Z:\`" and when unmounting it WinEFIMounter will unmount a non-existent partition... a bit annoying if you asked me.
> > TL;DR: Just unmount your partition as you leave WinEFIMounter. <br>
> > **NOTE:** v1.0.2 is capable of detecting already mounted EFI partitions at startup. This should not be that much of a concern anymore.

## Problems
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
