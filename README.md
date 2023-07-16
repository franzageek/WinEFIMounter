# WinEFIMounter
Windows tool to mount your Hackintosh EFI partition.
[a.k.a. MountEFI for Windows].

## Introduction
WinEFIMounter is a simple Batch program that makes it easy to mount the EFI partition on your Hackintosh drive directly from Windows. It could be used to mount any EFI partition (also Windows and Linux ones) from a Windows environment, but its main purpose is to let you mount your Hackintosh EFI partition without having to boot it. It's hard to believe but in reality there isn't any simple software such as [Corpnewt](https://github.com/corpnewt)'s [MountEFI](https://github.com/corpnewt/MountEFI) (for Mac) that lets you do it from Windows: you would have to download third-party programs. Try WinEFIMounter instead: it's light and easy-to-use!


## Usage
### Supported actions
WinEFIMounter is very easy to use. It's got a simple CLI with numbers and menus that are really easy to navigate through.
With WinEFIMounter you can:
- Mount an EFI partiton
- Browse its content
  - Via the Command Prompt
  - Via the File Explorer
- Unmount an EFI partition.

It can currently perform some very basic actions, but it will get more and more advanced later in time.

### Used tools
To get its job done, WinEFIMounter utilizes a bunch of Windows' preinstalled tools, such as:
  - DiskPart
    > It is used to mount the EFI partition. 
  - XCopy
    > Utilized to clone the entire EFI partition to the "C:\EFIPartition" directory. This is done to make the EFI partition accessible by GUI as it would be impossible to access it just by opening the partition in File Explorer (due to admin rights-related reasons).

### Use cases
WinEFIMounter is the perfect solution for a variety of problems.
You can use it to:
- Fix your Hackintosh if it's not booting and you have no idea how to access the EFI folder
  > If you fuck up with your kexts, SSDTs or drivers you will likely need a quick way to fix them to make your Hackintosh ready again ASAP
- Clean up your EFI
  > If you've ever done Hackintoshing before, you'll be familiar with those annoying logs left by OpenCore every time you boot your Hackintosh. With WinEFIMounter you can get rid of them up in under than 1 minute!
- Add files to your EFI
  > It's pretty similar to Point 1, both points focus on the ease of access to your EFI folder while on a Windows environment.
- Manage your Windows or Linux EFI folder
  > That's right, WinEFIMounter can mount all kinds of EFI partitions you can think of!
  > The program might often refer to the EFI partition as "the Hackintosh EFI partition" or to the drive as "your Hackintosh disk", but you can use it for non-Hackintosh systems too.

### Application behavior
Once you start up WinEFIMounter, you are welcomed by a simple introduction window.
![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/ef66e019-d72a-46d3-a22a-13cb6935fb7f)

To skip it, just press any key.


After it, you get brought to the main menu.
![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/29ce972d-19be-45a3-b39d-95cfcb8004c3)

Right after you start the program, you are able to do two things:
- Choose a partition to mount
- Quit the program

To choose the action to perform, just type 1 (to mount a partition) or Q  (to exit WiEFIMounter) and then hit Enter.

When you want to mount a partition, you have to press 1 at the main menu and then M to confirm. You'll get to the point where you need to select the drive and the partition to mount.
![Screenshot 2023-07-16 202956](https://github.com/franzageek/WinEFIMounter/assets/88248950/cdceb712-3afd-465b-a8f7-43a524d12931)
![Screenshot 2023-07-16 203527](https://github.com/franzageek/WinEFIMounter/assets/88248950/65c5e495-3f59-4f65-a584-966f762a5ef0)
First, locate in the list the drive you want to edit the EFI partition of, then type its number and hit Enter.
Do the same thing for the EFI partition you need to mount.

![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/d1109eef-0d9f-438a-a8bb-ffc472fbc02a)
Once you selected your drive and EFI partition, type M to confirm. The mounting process will begin instantly.

![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/2735dfff-0ed2-4507-85b4-90fc38c38802)
You'll get to this screen, which basically tells you that you have two ways to edit your EFI partition's content:
- By browsing files and folders using the Command Prompt (via "cd", "del", "move" and "copy")
  > Although it might seem pretty straightforward, this is the most complicated procedure you can choose. Yk, it's always a smarter idea to do things in a GUI

## Errors
## Credits



