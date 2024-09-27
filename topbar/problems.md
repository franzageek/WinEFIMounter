---
layout: page
title:  Problems
permalink: /problems/
---

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
