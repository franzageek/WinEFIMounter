---
layout: page
title:  Usage
permalink: /usage/
---

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
    > Used to clone the entire EFI partition to the "C:\EFIPartition" directory. This is done to make the EFI partition accessible by GUI as it would be impossible to access it just by opening the partition in File Explorer (due to admin rights-related reasons).

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

To mount a partition, press <kbd>1</kbd> and follow the prompts to select your drive and EFI partition. Once selected, type <kbd>M</kbd> to confirm, and the partition will mount instantly.

![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/2735dfff-0ed2-4507-85b4-90fc38c38802)
Congrats! Your EFI partition is now mounted to "`Z:\`" (or another drive letter at the very end of the alphabet if `Z:\` is already taken). 

You can now:
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
