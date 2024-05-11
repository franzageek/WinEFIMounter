global using global::System;
global using global::System.IO;
global using global::System.Threading;
global using global::System.Diagnostics;

namespace WinEFIMounter
{
    public class WinEFIMounter
    {
        static readonly string tmpdir = @Path.GetTempPath().ToString();
        public static void Main()
        {
            Console.Title = "WinEFIMounter";
            bool cpf = false;
            DelTempFiles();
            char choice;
            Console.Clear();
            Console.WriteLine();
            Console.WriteLine("   #####################################################");
            Console.Write("  #                   WinEFIMounter");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.Write(" CSharpRewrite     ");
            Console.ResetColor();
            Console.Write("#\n");
            Console.WriteLine(" #####################################################");
            Console.WriteLine();
            Console.WriteLine(" Welcome to WinEFIMounter v1.0.1. This program is meant to be used to access your");
            Console.WriteLine(" EFI parititon from Windows with complete ease.");
            Console.WriteLine();
            Console.WriteLine(" WinEFIMounter could be used to mount any EFI partition, but its main purpose");
            Console.WriteLine(" is to let you access your Hackintosh EFI partition from Windows since there isn't");
            Console.WriteLine(" any tool to do that.");
            Console.WriteLine();
            Console.WriteLine();
            Console.Write("   - Press any key to begin...");
            _ = Console.ReadKey().KeyChar;
            goto UnmountedMainMenu;

        UnmountedMainMenu:
            Console.Clear();
            Console.WriteLine();
            Console.WriteLine("   #####################################################");
            Console.WriteLine("  #                   WinEFIMounter                   #");
            Console.WriteLine(" #####################################################");
            Console.WriteLine();
            Console.Write(" The EFI partition is currently ");
            Console.ForegroundColor= ConsoleColor.Red;
            Console.Write("NOT MOUNTED");
            Console.ResetColor();
            Console.Write(".\n");
            Console.WriteLine();
            Console.WriteLine(" 1. Mount EFI partition to Z:\\");
            Console.WriteLine();
            Console.WriteLine(" E. Exit");
            Console.WriteLine();
            Console.WriteLine();
            Console.Write("   - Enter your choice: ");
            choice = Char.ToUpper(Console.ReadKey().KeyChar);
            switch (choice)
            {
                case 'E':
                    goto ExitScr;
                case '1':
                    goto MountPass0;
                default:
                    goto UnmountedMainMenu;
            }

        MountPass0:
            GenFile(tmpdir, "dpsetup.bat", "@echo off\n" + @"echo lis dis > %temp%\dpscript.txt" + "\n"+ @"diskpart /s %temp%\dpscript.txt >%temp%\dpout.txt");
            Console.Clear();
            Console.WriteLine();
            Console.WriteLine(" In order to mount your EFI, you need to specify your drive first.");
            Console.WriteLine(" From the below list, enter the number corresponding to your drive.");
            Console.WriteLine();
            ProcessStartInfo psi = new()
            {
                FileName = Path.Combine(tmpdir, "dpsetup.bat"),
                UseShellExecute = false,
                CreateNoWindow = true
            };
            Process? p = Process.Start(psi);
            p?.WaitForExit();
            string dpout = File.ReadAllText(Path.Combine(tmpdir, "dpout.txt"));
            Console.WriteLine(dpout);
            File.Delete(Path.Combine(tmpdir, "dpsetup.bat"));
            File.Delete(Path.Combine(tmpdir, "dpout.txt"));
            Console.WriteLine();
            Console.Write("   - Enter your disk number: ");
            string? userinput = Console.ReadLine();
            GenFile(tmpdir, "dpsetup.bat", "@echo off\nFOR /F \"tokens=2\" %%a IN ('diskpart /s \"%temp%\\dpscript.txt\"') DO (echo %%a >>\"%temp%\\dpout.txt\")\nFOR /F \"tokens=* skip=5\" %%g IN (%temp%\\dpout.txt) DO (\n	for /l %%d in (0,1,0) do echo|set /p=\"%%g\">>\"%temp%\\dpout2.txt\"\n)\ndel /f /s /q \"%temp%\\dpout.txt\" >nul 2>&1\nrename \"%temp%\\dpout2.txt\" \"dpout.txt\" >nul 2>&1");
            p?.Start();
            p?.WaitForExit();
            string[] disknums = File.ReadAllText(Path.Combine(tmpdir, "dpout.txt")).Split(' ');
            File.Delete(Path.Combine(tmpdir, "dpscript.txt"));
            File.Delete(Path.Combine(tmpdir, "dpsetup.bat"));
            File.Delete(Path.Combine(tmpdir, "dpout.txt"));
            int disknumber;
            foreach (string diskn in disknums)
            {
                if (diskn == userinput && userinput != "")
                {
                    disknumber = Convert.ToInt32(diskn);
                    goto MountPass1;
                }
            }
            Console.Beep();
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("\n   The disk number you entered was not valid.");
            Console.ResetColor();
            Thread.Sleep(500);
            goto MountPass0;

        MountPass1:
            GenFile(tmpdir, "dpscript.txt", "sel dis " + disknumber + "\nlis par");
            GenFile(tmpdir, "dpsetup.bat", "@echo off\n"+ @"diskpart /s %temp%\dpscript.txt >%temp%\dpout.txt");
            Console.Clear();
            Console.WriteLine();
            Console.WriteLine(" Now you need to specify your EFI partition.");
            Console.WriteLine();
            Console.Write("   ");
            Console.ForegroundColor = ConsoleColor.Black;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Write("TIP:");
            Console.ResetColor();
            Console.Write(" EFI partitions are usually really small (about 100 or 200MB) and they're marked\n");
            Console.Write("        as \"SYSTEM\" partitions. You can use the \"");
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write("Size >= 100MB");
            Console.ResetColor();
            Console.Write("\" and the \"");
            Console.ForegroundColor= ConsoleColor.DarkCyan;
            Console.Write("Type = System");
            Console.ResetColor();
            Console.Write("\" attributes\n");
            Console.WriteLine("        to locate your EFI partition.");
            Console.WriteLine();
            Console.WriteLine(" From the below list, enter the number corresponding to your EFI partition.");
            Console.WriteLine();
            p?.Start();
            p?.WaitForExit();
            dpout = File.ReadAllText(Path.Combine(tmpdir, "dpout.txt"));
            Console.WriteLine(dpout);
            File.Delete(Path.Combine(tmpdir, "dpsetup.bat"));
            File.Delete(Path.Combine(tmpdir, "dpout.txt"));
            Console.WriteLine();
            Console.Write("   - Enter your EFI partition number: ");
            userinput = Console.ReadLine();
            GenFile(tmpdir, "dpsetup.bat", "@echo off\nFOR /F \"tokens=2\" %%a IN ('diskpart /s \"%temp%\\dpscript.txt\"') DO (echo %%a >>\"%temp%\\dpout.txt\")\nFOR /F \"tokens=* skip=6\" %%g IN (%temp%\\dpout.txt) DO (\n	for /l %%d in (0,1,0) do echo|set /p=\"%%g\">>\"%temp%\\dpout2.txt\"\n)\ndel /f /s /q \"%temp%\\dpout.txt\" >nul 2>&1\nrename \"%temp%\\dpout2.txt\" \"dpout.txt\" >nul 2>&1");
            p?.Start();
            p?.WaitForExit();
            string[] partitionnums = File.ReadAllText(Path.Combine(tmpdir, "dpout.txt")).Split(' ');
            File.Delete(Path.Combine(tmpdir, "dpscript.txt"));
            File.Delete(Path.Combine(tmpdir, "dpsetup.bat"));
            File.Delete(Path.Combine(tmpdir, "dpout.txt"));
            int partitionnumber;
            foreach (string partn in partitionnums)
            {
                if (partn == userinput && userinput != "")
                {
                    partitionnumber = Convert.ToInt32(partn);
                    goto MountPass2;
                }
            }
            Console.Beep();
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("\n   The EFI partition number you entered was not valid.");
            Console.ResetColor();
            Thread.Sleep(500);
            goto MountPass1;

        MountPass2:
            Console.Clear();
            Console.WriteLine();
            Console.Write("   - Press ");
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write("M");
            Console.ResetColor();
            Console.Write(" to mount the selected partition or ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("B");
            Console.ResetColor();
            Console.Write(" to go back to the main menu...");
            userinput = Convert.ToString(Console.ReadKey().KeyChar).ToUpper();
            switch (userinput)
            {
                case "B":
                    goto UnmountedMainMenu;
                case "M":
                    goto MountPass3;
                default:
                    goto MountPass2;
            }
        MountPass3:
            Console.Title = "WinEFIMounter - Mounting...";
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine(" Setting mount letter...");
            char[] letters = { 'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P', 'O' };
            char? mntletter = null;
            foreach (char l in letters)
            {
                if (!Directory.Exists(l+@":\"))
                {
                    mntletter = l;
                    Console.WriteLine($"   > Mount letter is \"{mntletter}:\\\"");
                    break;
                }
            }
            Console.WriteLine();
            Console.WriteLine(" Mounting the selected partition...");
            GenFile(tmpdir, "dpscript.txt", "sel dis " + disknumber + "\nsel par " + partitionnumber + "\nass letter=" + mntletter + "\nexit");
            GenFile(tmpdir, "dpsetup.bat", "@echo off\n" + @"diskpart /s %temp%\dpscript.txt >nul");
            Console.Write($"   > Started mounting disk {disknumber}, partition {partitionnumber}...");
            p?.Start();
            p?.WaitForExit();
            Console.Write("done.");
            goto EndMount;
        EndMount:
            Console.Clear();
            Console.SetWindowSize(75, 40);
            Console.SetBufferSize(75, 40);
            Console.Title = "WinEFIMounter";
            File.Delete(Path.Combine(tmpdir, "dpscript.txt"));
            File.Delete(Path.Combine(tmpdir, "dpsetup.bat"));
            Console.WriteLine();
            Console.WriteLine("   Done! The EFI partition is now mounted!");
            Console.WriteLine();
            Console.WriteLine("   ══════════════════════════════════════════════════════════════════");
            Console.WriteLine();
            Console.WriteLine("   Your EFI partition is now mounted, but due to admin rights-related");
            Console.WriteLine($"   reasons it is not accessible by the File Explorer. The {mntletter}: drive");
            Console.WriteLine("   will show up in \"This PC\", but you will not be able to access it.");
            Console.WriteLine();
            Console.WriteLine("   One way you can access the drive is by browsing through all the");
            Console.WriteLine("   files via an elevated Command Prompt, but that would be a huge pain");
            Console.WriteLine("   since you would have to navigate through all the files and folders");
            Console.WriteLine("   via the command-line.");
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("   Or you can let WinEFIMounter do all the annoying work and browse the");
            Console.WriteLine("   EFI partition directly from the File Explorer.");
            Console.WriteLine();
            Console.WriteLine("   How?");
            Console.WriteLine();
            Console.WriteLine("   WinEFIMounter will clone the entire EFI partition content to the");
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write("   C:\\EFIPartition");
            Console.ResetColor();
            Console.WriteLine(" directory. This way, you can use the File Explorer");
            Console.WriteLine("   to browse its content and make the changes you need, all in the");
            Console.WriteLine("   File Explorer window. And when you're done, WinEFIMounter will flush");
            Console.WriteLine("   the updated files back to the EFI partition!");
            Console.WriteLine();
            Console.WriteLine("   And the best part is that this procedure is completely safe!");
            Console.WriteLine("   None of the files in the EFI partition will be modified while you edit");
            Console.WriteLine("   their cloned copy. They'll only get deleted once their updated version");
            Console.WriteLine("   has got successfully copied over.");
            Console.WriteLine();
            Console.WriteLine("   Sounds amazing, right?");
            Console.WriteLine();
            Console.WriteLine("   ══════════════════════════════════════════════════════════════════");
            Console.WriteLine();
            Console.Write("   - Press any key to go back to the main menu...");
            _ = Console.ReadKey().KeyChar;
            goto MountedMainMenu;

        MountedMainMenu:
            Console.Clear();
            Console.SetWindowSize(120, 30);
            Console.WriteLine();
            Console.WriteLine("   #####################################################");
            Console.WriteLine("  #                   WinEFIMounter                   #");
            Console.WriteLine(" #####################################################");
            Console.WriteLine();
            Console.Write($" The EFI partition is currently ");
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            Console.Write($"MOUNTED TO ");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write($"\"{mntletter}:\\\"");
            Console.ResetColor();
            Console.Write(".\n");
            Console.WriteLine();
            Console.WriteLine(" 1. Browse the EFI partition content via the Command Prompt");
            Console.WriteLine(" 2. Open EFI partition in File Explorer");
            Console.WriteLine(" 3. Unmount EFI partition");
            Console.WriteLine();
            Console.WriteLine(" E. Exit");
            Console.WriteLine();
            Console.WriteLine();
            Console.Write("   - Enter your choice: ");
            choice = Char.ToUpper(Console.ReadKey().KeyChar);
            switch (choice)
            {
                case 'E':
                    Console.Clear();
                    Console.WriteLine();
                    Console.WriteLine(" It seems like you want to exit WinEFIMounter, but your EFI partition is still mounted. ");
                    Console.WriteLine(" You need to unmount it first.");
                    Console.WriteLine();
                    Console.Write("   - Press any key to go back to the main menu...");
                    _ = Console.ReadKey().KeyChar;
                    goto MountedMainMenu;
                case '1':
                    goto OpenCmd;
                case '2':
                    goto OpenEFI;
                case '3':
                    goto UnmountPass0;
                default:
                    goto MountedMainMenu;
            }

        OpenCmd:
            Console.Clear();
            Console.WriteLine();
            ProcessStartInfo psi_ = new()
            {
                FileName = "cmd.exe",
                Arguments = $"/k \"{mntletter}:\"",
                UseShellExecute = true,
                CreateNoWindow = false
            };
            Process? p_ = Process.Start(psi_);
            Console.Write(" Command Prompt window open.");
            goto MountedMainMenu;
        OpenEFI:
            if (cpf)
            {
                Console.Clear();
                Console.WriteLine();
                Console.WriteLine(" If you're seeing this screen, it means that you've already tried to clone the EFI partition,");
                Console.WriteLine(" but something didn't go as planned.");
                Console.WriteLine();
                Console.WriteLine(" You can try to clone it again, but that will result in the loss of your previously");
                Console.WriteLine(" modified files, that are being held in \"C:\\EFIPartition\" to keep the changes you've made to them.");
                Console.WriteLine();
                Console.WriteLine(" So, if you now want to clone your EFI again, you will overwrite the modified files that are");
                Console.WriteLine(" currently stored in \"C:\\EFIPartition\".");
                Console.WriteLine();
                Console.WriteLine(" You can try to back them up and then clone the EFI again. You will then be able to replace old files with");
                Console.WriteLine(" new ones and then flush everything back to the EFI partition. This way you won't lose any of the work.");
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("   - Press C to start cloning or B to go back to the main menu...");
                userinput = Convert.ToString(Console.ReadKey().KeyChar).ToUpper();
                switch (userinput)
                {
                    case "C":
                        cpf = false;
                        goto ClonePass0;
                    case "B":
                        goto MountedMainMenu;
                    default:
                        goto OpenEFI;
                }
            }
            Console.Clear();
            Console.WriteLine();
            Console.WriteLine(" In order to open the EFI partition in File Explorer, WinEFIMounter needs to clone the EFI partition content");
            Console.WriteLine(" to  the \"C:\\EFIPartition\" directory.");
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine(" All the files and folders in your EFI partition will be copied to \"C:\\EFIPartition\".");
            Console.WriteLine(" Once you're done modifying your files, you can flush them back to the EFI partition,");
            Console.WriteLine(" and all the changes you've made to them will be kept.");
            Console.WriteLine();
            Console.WriteLine();
            Console.Write("   - Press ");
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write("C");
            Console.ResetColor();
            Console.Write(" to start cloning or ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("B");
            Console.ResetColor();
            Console.Write(" to go back to the main menu...");

            userinput = Convert.ToString(Console.ReadKey().KeyChar).ToUpper();
            switch (userinput)
            {
                case "C":
                    goto ClonePass0;
                case "B":
                    goto MountedMainMenu;
                default:
                    goto OpenEFI;
            }
        ClonePass0:
            Console.Title = "WinEFIMounter - Cloning...";
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine(" Creating the target directory...");
            if (!Directory.Exists(@"C:\EFIPartition"))
            {
                Directory.CreateDirectory("C:\\EFIPartition");
            }
            Console.WriteLine("   > \"C:\\EFIPartition\" has been created successfully.");
            Console.WriteLine();
            Console.Write(" Copying files...");
            ProcessStartInfo _psi = new()
            {
                FileName = "xcopy.exe",
                Arguments = $"/e /Y \"{mntletter}:\\*\" \"C:\\EFIPartition\\\"",
                UseShellExecute = false,
                CreateNoWindow = true
            };
            Process? _p = Process.Start(_psi);
            _p?.WaitForExit();
            int clexcode = _p.ExitCode;
            if (clexcode != 0)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.Title = "WinEFIMounter";
                Console.Write("failed.");
                cpf = true;
                Console.WriteLine();
                Console.WriteLine($" [ERROR] Something went wrong while cloning the EFI partition ({clexcode}).");
                Console.WriteLine($"         No file has been touched.\n         Aborting.");
                Console.WriteLine();
                Console.ResetColor();
                Console.Write("   - Press any key to go back to the main menu...");
                _ = Console.ReadKey().KeyChar;
                goto MountedMainMenu;

            }
            Console.Write("done.");
            Console.Title = "WinEFIMounter";
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine(" Done! Your EFI partition has been cloned to \"C:\\EFIPartition\" and you can now access it from the File Explorer.");
            ProcessStartInfo _psi_ = new()
            {
                FileName = "explorer.exe",
                Arguments = "\"C:\\EFIPartition\"",
                UseShellExecute = true,
                CreateNoWindow = false
            };
            Process? _p_ = Process.Start(_psi_);
            goto ClonePass1;
        ClonePass1:
            Console.Write("\n   - Press ");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write("F");
            Console.ResetColor();
            Console.Write(" to start flushing the modified files back to the EFI partition...");
            userinput = Convert.ToString(Console.ReadKey().KeyChar).ToUpper();
            switch (userinput)
            {
                case "F":
                    goto FlushPass0;
                default:
                    goto ClonePass1;
            }
        FlushPass0:
            Console.Title = "WinEFIMounter - Flushing...";
            GenFile(tmpdir, "dpsetup.bat", $"@echo off\nfor /R \"{mntletter}:\\\" %%G in (\"*.*\") do del /f /S /Q \"%%G\" >nul 2>&1\nfor /D /r %%G in (\"*\") do rmdir /S /Q \"%%G\" >nul 2>&1 \ncd /d %temp%");
            p.Start();
            p.WaitForExit();
            Console.WriteLine();
            Console.WriteLine();
            Console.Write(" Flushing files...");
            ProcessStartInfo __psi_ = new()
            {
                FileName = "xcopy.exe",
                Arguments = $"/e /Y \"C:\\EFIPartition\\*\" \"{mntletter}:\\\"",
                UseShellExecute = false,
                CreateNoWindow = true
            };
            Process? __p_ = Process.Start(__psi_);
            __p_?.WaitForExit();
            int flexcode = __p_.ExitCode;
            if (flexcode == 0)
            {
                Console.Write("done.\n");
                Console.Title = "WinEFIMounter";
                Console.WriteLine();
                Console.Write(" Deleting \"C:\\EFIPartition\"...");
                Directory.Delete(@"C:\EFIPartition", true);
                Console.Write("done.\n");
                Console.WriteLine();
                Console.WriteLine(" Done! Your updated files are now in your EFI partition.");
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("   - Press any key to go back to the main menu...");
                _ = Console.ReadKey().KeyChar;
                goto MountedMainMenu;
            } 
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.Write("failed.");
                Console.WriteLine();
                cpf = true;
                Console.Title = "WinEFIMounter";
                Console.WriteLine($" [ERROR] Something went wrong while flushing files back to the EFI partition ({flexcode}).");
                Console.WriteLine($"         The files you modified will remain in \"C:\\EFIPartition\\\" so that no work is lost.\n         Aborting.");
                Console.WriteLine();
                Console.ResetColor();
                Console.Write("   - Press any key to go back to the main menu...");
                _ = Console.ReadKey().KeyChar;
                goto MountedMainMenu;
            }
        UnmountPass0:
            Console.Clear();
            Console.WriteLine();
            Console.Write("   - Press ");
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.Write("U");
            Console.ResetColor();
            Console.Write(" to unmount the EFI partition or ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("B");
            Console.ResetColor();
            Console.Write(" to go back to the main menu...");
            userinput = Convert.ToString(Console.ReadKey().KeyChar).ToUpper();
            switch (userinput)
            {
                case "U":
                    goto UnmountPass1;
                case "B":
                    goto MountedMainMenu;
                default:
                    goto UnmountPass0;
            }
        UnmountPass1:
            Console.Title = "WinEFIMounter - Unmounting...";
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine(" Unmounting the EFI partition...");
            GenFile(tmpdir, "dpscript.txt", "sel dis " + disknumber + "\nsel par " + partitionnumber + "\nremove letter=" + mntletter + "\nexit");
            GenFile(tmpdir, "dpsetup.bat", "@echo off\n" + @"diskpart /s %temp%\dpscript.txt >nul");
            Console.Write($"   > Started unmounting disk {disknumber}, partition {partitionnumber}...");
            p?.Start();
            p?.WaitForExit();
            Console.Write("done.");
            Console.Title = "WinEFIMounter";
            Console.WriteLine();
            Console.WriteLine();
            Console.Write("   - Press any key to go back to the main menu...");
            _ = Console.ReadKey().KeyChar;
            goto UnmountedMainMenu;
        ExitScr:
            Console.Clear();
            Console.WriteLine();
            Console.WriteLine("   #####################################################");
            Console.Write("  #                   WinEFIMounter");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.Write(" CSharpRewrite     ");
            Console.ResetColor();
            Console.Write("#\n");
            Console.WriteLine(" #####################################################");
            Console.WriteLine();
            Console.WriteLine(" WinEFIMounter version 1.0.1");
            Console.WriteLine();
            Console.WriteLine(" Developed by <franzageek>");
            Console.WriteLine();
            Console.WriteLine();
            Console.Write(" GitHub Repository [");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.Write("https://github.com/franzageek/WinEFIMounter");
            Console.ResetColor();
            Console.Write("]\n Report an issue [");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.Write("https://github.com/franzageek/WinEFIMounter/issues");
            Console.ResetColor();
            Console.Write("]\n\n Have a good day!\n\n [All the files in \"C:\\EFIPartition\" are going be ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("permanently");
            Console.ResetColor();
            Console.Write(" deleted.]\n\n");
            Console.Write("   - Press any key to exit...");
            _ = Console.ReadKey().KeyChar;
            DelTempFiles();
            if (Directory.Exists(@"C:\EFIPartition"))
            {
                Directory.Delete(@"C:\EFIPartition", true);
            }
            cpf = false;

            Environment.Exit(0);
        }

        public static void GenFile(string filepath, string filename, string text)
        {
            filepath = Path.Combine(filepath, filename);
            File.WriteAllText(filepath, text);
            return;
        }

        public static void DelTempFiles()
        {
            if (File.Exists(Path.Combine(tmpdir, "dpscript.txt")))
            {
                File.Delete(Path.Combine(tmpdir, "dpscript.txt"));
            }

            if (File.Exists(Path.Combine(tmpdir, "dpsetup.bat")))
            {
                File.Delete(Path.Combine(tmpdir, "dpsetup.bat"));
            }

            if (File.Exists(Path.Combine(tmpdir, "dpout.txt")))
            {
                File.Delete(Path.Combine(tmpdir, "dpout.txt"));
            }

            if (File.Exists(Path.Combine(tmpdir, "dpout2.txt")))
            {
                File.Delete(Path.Combine(tmpdir, "dpout2.txt"));
            }
            return;
        }
    }
}
