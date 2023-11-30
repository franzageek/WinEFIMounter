# WinEFIMounter
Mount your Hackintosh EFI partition from Windows. 

[a.k.a. MountEFI for Windows].
![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/6904b05f-519e-4c40-92df-559feb890785)
[**Introduction**](#introduction) - [**Usage**](#usage) - [**Problems**](#problems) - [**Credits**](#credits)

## Introduction
WinEFIMounter is a simple and standalone C# program that makes it easy to **mount the EFI partition** on your Hackintosh drive **directly from Windows**. It could be used to mount any EFI partition (also Windows and Linux ones) from a Windows environment, but its main purpose is to let you mount **your Hackintosh EFI partition without having to boot it**. It's hard to believe but in reality _**there isn't any simple software**_ such as [Corpnewt](https://github.com/corpnewt)'s [**MountEFI**](https://github.com/corpnewt/MountEFI) (for Mac) that lets you do it from Windows: you would have to download **third-party programs**. Try WinEFIMounter instead: it's light and easy-to-use!


## Usage
### Supported actions
WinEFIMounter is very easy to use. It's got a **simple CLI** with numbers and menus that are really easy to navigate through.
With WinEFIMounter you can:
- Mount an EFI partiton
- Browse its content
  - Via the Command Prompt
  - Via the File Explorer
- Unmount an EFI partition

It can currently perform some very basic actions, but it will get more and more advanced later in time.

### Used tools
To get its job done, WinEFIMounter utilizes a bunch of Windows' **preinstalled tools**, such as:
  - DiskPart
    > It is used to mount the EFI partition. 
  - XCopy
    > Utilized to clone the entire EFI partition to the "C:\EFIPartition" directory. This is done to make the EFI partition accessible by GUI as it would be impossible to access it just by opening the partition in File Explorer (due to admin rights-related reasons).

### Use cases
WinEFIMounter is the perfect solution for a variety of problems.
You can use it to:
- Fix your Hackintosh if it's not booting and you have no idea how to access the EFI folder
  > If you fuck up with your kexts, SSDTs or drivers (like I did) you will likely need a quick way to fix them to make your Hackintosh ready again.
- Clean up your EFI
  > If you've ever done Hackintoshing before, you'll be familiar with those annoying logs left by OpenCore every time you boot your Hackintosh. With WinEFIMounter you can get rid of them in under than 1 minute!
- Add files to your EFI
  > It's pretty similar to Point 1, both points focus on the ease of access to your EFI folder while on a Windows environment.
- Manage your Windows or Linux EFI folder
  > That's right, WinEFIMounter can mount all kinds of EFI partitions you can think of!
  > The program might often refer to the EFI partition as "the Hackintosh EFI partition" or to the drive as "your Hackintosh disk", but you can use it for non-Hackintosh systems too.

### Application behavior
When you start WinEFIMounter, you are welcomed by a simple introduction window.
![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/ef66e019-d72a-46d3-a22a-13cb6935fb7f)
To skip it, just press any key.



![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/1ad744f3-bfa5-45a5-91ac-a7d283849d43)
After it, you get brought to the main menu.
Right after you start the program, you are able to do two things:
- Choose a partition to mount
- Quit the program

To choose the action to perform, just type <kbd>1</kbd> (to mount a partition) or <kbd>E</kbd> (to exit WinEFIMounter) and then hit Enter.

When you want to mount a partition, you have to press <kbd>1</kbd> at the main menu. You'll get to the point where you need to select the drive and the partition to mount.
![Screenshot 2023-07-16 202956](https://github.com/franzageek/WinEFIMounter/assets/88248950/cdceb712-3afd-465b-a8f7-43a524d12931)
First, locate in the list the drive you want to mount the EFI partition of, then type its number and hit Enter.

![Screenshot 2023-07-16 203527](https://github.com/franzageek/WinEFIMounter/assets/88248950/65c5e495-3f59-4f65-a584-966f762a5ef0)
Do the same thing for the EFI partition you need to mount.

![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/d1109eef-0d9f-438a-a8bb-ffc472fbc02a)
Once you selected your drive and EFI partition, type <kbd>M</kbd> to confirm. The mounting process will begin instantly.

![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/2735dfff-0ed2-4507-85b4-90fc38c38802)
Congrats! Your EFI Partition is now mounted to "`Z:\`" (or, if it's taken, to another letter at the very end of the alphabet).
You'll get to this screen, which basically tells you that you have two ways to edit your EFI partition's content:
- By browsing files and folders using the Command Prompt (via `cd`, `del`, `move` and `copy`)
  > Although it might seem pretty straightforward, this is the most complicated route you can take. Yk, it's always a smarter idea to do things in a GUI when you have the possibility to.
- By opening an EFI partition's clone in File Explorer
  > This is achieved by copying the entire directory tree of the EFI partition onto a directory that can be accessed with standard privileges. In fact, the EFI partition itself it cannot be accessed by TrustedInstaller either, which the highest authority in your system. The fun fact is that despite all that it can be easily accessed by an elevated Command Prompt, and you can use it to copy the content over to a folder that you can access with standard user rights. So, when you run WinEFIMounter as administrator it will be able to copy the entire partition tree over to a standard directory, which will be then flushed back to the EFI partition once you're done modifying your files.
  >  > FYI, the directory that will host the clone of the EFI partition is "`C:\EFIPartition\`".

Anyway, just press any key to skip it.


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/348fdc42-7341-49ae-a7b5-f39bb04ba5ac)
And here we go, once the partition is mounted you get access to the entire set of actions WinEFIMounter is capable of doing.
Now, you're able to do three more things:
- Open the EFI partition in a Command Prompt instance
- Open it in the File Explorer by cloning its content to a directory you can access without admin privileges
- Unmount the partition
  > Perform this action once you're about to exit WinEFIMounter.


![Screenshot 2023-07-17 050930](https://github.com/franzageek/WinEFIMounter/assets/88248950/abcda3ec-626e-4e89-90c3-93de454e2fda)
Option <kbd>1</kbd> will simply open a Command Prompt window in the EFI partition directory.


![Screenshot 2023-07-17 051300](https://github.com/franzageek/WinEFIMounter/assets/88248950/53ba8760-9fce-4379-9eef-5312d49fa8e3)
Option <kbd>2</kbd> will show this message. To start cloning, type `C` and hit Enter.


![Screenshot 2023-07-17 051401](https://github.com/franzageek/WinEFIMounter/assets/88248950/87d57928-cb4f-4fa9-93d5-6a3cdd69cd65)
After you typed `C`, all the files in your EFI folder get copied in "`C:\EFIPartition`". WinEFIMounter will automatically open an Explorer window in that directory for you.

You can now access your files like you normally would, and you won't even notice the fact that you're actually outside of your EFI partition.

But how can you make the changes made to your files in "`C:\EFIPartition`" effective on the EFI partition itself?


Well, there's a simple yet slightly complex solution, but we'll talk about it later in this ReadMe.

Just press `F` and hit Enter to start flushing the updated files back to the EFI.


![Screenshot 2023-07-17 053408](https://github.com/franzageek/WinEFIMounter/assets/88248950/76cb80af-8a14-47e4-b088-da2c0e5bcf7c)
And you will see pretty much the same screen you saw when cloning the EFI partition, except that now every file you see is coming from "`C:\EFIPartition`" and it's heading to your EFI partition.

The files you modified are now in your EFI partition, and you didn't have to worry about it!


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/21835753-d725-4e1a-92d0-e01d97543da3)
Choosing Option `3` in the main menu will result in this screen. Type `U` and press Enter to continue.
> Before unmounting your EFI Partition, make sure you don't have any open file with unsaved work inside of it. Always save your work and close any file that belongs to the EFI partition before unmounting it.


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/c5ec573c-3cbc-4351-a97c-fb08dace2cb8)
And here you have your success screen. Pressing any key will show again the minimalistic version of the main menu (the one we saw earlier yk, just Mount and Exit...).


![image](https://github.com/franzageek/WinEFIMounter/assets/88248950/5ae3f0b3-ed03-4852-b068-f406ec46bbb9)
Choosing Option `E` from the main menu while your partition is still mounted will take you to this warning screen, which basically reminds you to unmount your EFI partition before you leave WinEFIMounter.

> If you didn't care of the message and closed the window, the next time you will have to launch WinEFIMounter you would have to start again from mounting the partition (which is already mounted), resulting in a general mess where the `Z` letter is taken by the already mounted EFI partition and WinEFIMounter is forced to assign the `Y` letter to a partition which is already mounted to "`Z:\`" and when unmounting it WinEFIMounter will unmount a non-existent partition....... not a good situation to be in, after all.
> > TL;DR: Just unmount your partition as you leave WinEFIMounter.

## Problems

### Flushing procedure failed
WinEFIMounter is a simple script. If you scroll through the code, you will see that it's **just about 400 lines long**, and the Mounting and Unmounting parts of the program are literally made of **3 lines of code** each. And those are DiskPart commands!

Other parts of WinEFIMounter are really simple too, such as the "Open partition in Command prompt" option (which literally consists in the `start cmd /k Z:` command) or the "Exit" option (it's all about showing the credits screen and resetting all the variables).

The only part that can appear a little more complex is the cloning part. You see, a lot of stuff is involved there.

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
The main reason I decided to create this program for is the fact that there isn't ANY MountEFI VERSION FOR WINDOWS! I was trying to repair my Hackintosh EFI I've _accidentally_ fucked up with, and I was negatively surprised when I learned that there wasn't any MountEFI version for Windows. So I did it my way, by playing around with Diskpart. But the procedure was long and boring, so I created a script that could automatically mount the partition, and then slightly modified it to make WinEFIMounter.

I hope that with WinEFIMounter you can save the time you would have spent downloading a 3rd-party program.

I hope you find it useful.

