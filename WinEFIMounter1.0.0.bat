@echo off
set "params=%*"
cd /d "%~dp0" && ( if exist "%temp%\getadmin.vbs" del "%temp%\getadmin.vbs" ) && fsutil dirty query %systemdrive% 1>nul 2>nul || (  echo Set UAC = CreateObject^("Shell.Application"^) : UAC.ShellExecute "cmd.exe", "/k cd ""%~sdp0"" && %~s0 %params%", "", "runas", 1 >> "%temp%\getadmin.vbs" && "%temp%\getadmin.vbs" && exit /B )
cd "%~dp0"
set ch0=
set ch1=
set chx=
set mntdrive=
set mntpar=
set mntletter=
set /a cpf=0
set /a cnt=0
set /a errl=0

:splashscreen
title WinEFIMounter
cls
echo.
echo    #####################################################
echo   #                   WinEFIMounter                   #
echo  #####################################################
echo.
echo  Welcome to WinEFIMounter. This program is meant to be used to access your
echo  Hackintosh EFI from Windows. 
echo.
echo  WinEFIMounter could be used to mount any EFI partition, but the main purpose of it
echo  is to let you access your Hackintosh EFI partition from Windows since there isn't 
echo  any tool to do that.
echo.
echo.
echo    - Press any key to begin...
pause>nul

:unmounted_mainmenu
title WinEFIMounter
cls
echo.
echo    #####################################################
echo   #                   WinEFIMounter                   #
echo  #####################################################
echo.
echo  The EFI partition is currently NOT MOUNTED.
echo.
echo  1. Mount EFI partition to Z:\
echo.
echo  E. Exit
echo.
echo.
set /p "ch0=---- Enter your choice:"
if /i "%ch0%"=="1" set "ch0=" &goto :mount
if /i "%ch0%"=="E" set "ch0=" &goto :quit
set ch0=
goto :unmounted_mainmenu

:mount
echo lis dis >"%temp%\dpscript.txt"
cls
echo.
echo  In order to mount your EFI, you need to specify your Hackintosh drive first.
echo  From the below list, enter the number corresponding to your Hackintosh drive.
echo.
diskpart /s "%temp%\dpscript.txt"
echo.
:tempbookmark0
set /p mntdrive=---- Enter your drive number:
FOR /F "tokens=2" %%a IN ('diskpart /s "%temp%\dpscript.txt"') DO (
	if "%%a"=="%mntdrive%" goto :proceed0
	if "%mntdrive%"=="" goto :tempbookmark0
)
echo  The drive number you entered is not valid.
echo.
set mntdrive=
goto :tempbookmark0
:proceed0
echo sel dis %mntdrive% >"%temp%\dpscript.txt"
echo lis par >>"%temp%\dpscript.txt"
cls
echo.
echo  Now you need to specify your EFI partition.
echo.
echo    TIP: EFI partitions are usually really small (about 100 or 200MB) and they're marked
echo         as "SYSTEM" partitions. You can use the "Size >= 100MB" and the "Type = System" attributes
echo         to locate your EFI partition.
echo.
echo  From the below list, enter the number corresponding to your EFI partition.
echo.
diskpart /s "%temp%\dpscript.txt"
echo.
:tempbookmark1
set /p mntpar=---- Enter your EFI partition number:
FOR /F "tokens=2" %%a IN ('diskpart /s "%temp%\dpscript.txt"') DO (
	if "%%a"=="%mntpar%" goto :proceed4
	if "%mntpar%"=="" goto :tempbookmark1
)
echo  The EFI partition number you entered is not valid.
echo.
set mntpar=
goto :tempbookmark1
:proceed4
cls
echo.
set /p chx=---- Press M to mount the selected partition or B to go back to the main menu...
if /i "%chx%"=="m" set "chx=" &goto :proceed4
if /i "%chx%"=="b" set "chx=" &goto :unmounted_mainmenu
set "chx="
goto :proceed3
:proceed1
title WinEFIMounter: Mounting...
cls
echo.
echo  Setting the letter...
if not exist "Z:\" (
	set mntletter=Z
) else (
	for %%a in ( Y X V U T M N O P Q R S) do (
			if exist "%%a:\" (
				rem letter already taken
			)
			if not exist "%%a:\" (
				set mntletter=%%a
				echo    - The Z letter was already taken, using %mntletter% instead...
				goto :proceed2
			)
	)
)
:proceed2
echo.
echo  Mounting the selected partition...
(echo sel dis %mntdrive%
echo sel par %mntpar%
echo ass letter=%mntletter%
echo exit
)  | diskpart > nul
cls
mode 122, 40
title WinEFIMounter
echo.
echo  Done! The EFI partition is now mounted!
echo.
echo.
echo.
echo    ===============================================================
echo.
echo    Your EFI partition is now mounted, but for admin rights-related
echo    reasons it is not accessible by the File Explorer. The %mntletter%: drive 
echo    will show up in "This PC", but you will not be able to open it.
echo.
echo    One way you can access the drive is by browsing through all the
echo    files via an elevated Command Prompt, but that would be a huge
echo    pain since you would have to navigate through all the files and
echo    the folders via the cmd-line, with commands like "cd" and "del".
echo.
echo.
echo    Or you can let WinEFIMounter do all the annoying work and browse
echo    the folder directly from the File Explorer.
echo.
echo    How?
echo.
echo    With the help of XCOPY the script will clone the entire EFI partition 
echo    to the "C:\EFIPartition" directory. This way, you can use the
echo    File Explorer to browse its content and make the changes you need,
echo    all in the File Explorer window. And when you're done, WinEFIMounter
echo    will flush the changes back to the EFI partition!
echo.
echo    And the best part is that this procedure is completely safe!
echo    None of the files in the EFI partition will be modified while
echo    you edit their cloned copy. They'll only get deleted once their
echo    updated version has got copied over.
echo. 
echo    Sounds amazing, isn't it?
echo.
echo    ===============================================================
echo.
echo    - Press any key to go back to the main menu...
pause>nul
mode 122, 30
goto :mounted_mainmenu

:mounted_mainmenu
title WinEFIMounter
cls
echo.
echo    #####################################################
echo   #                   WinEFIMounter                   #
echo  #####################################################
echo.
echo  The EFI partition is currently MOUNTED TO "%mntletter%:\".
echo.
echo  1. Browse the EFI partition content via the Command Prompt
echo  2. Open EFI Partition in File Explorer
echo  3. Unmount EFI Partition 
echo.
echo  E. Exit
echo.
echo.
set /p ch1=   - Enter your choice:
if /i "%ch1%"=="e" set "ch1=" &goto :mounted_quit
if /i "%ch1%"=="3" set "ch1=" &goto :unmount
if /i "%ch1%"=="2" (
	if "%cpf%"=="1" (
		goto :cpf
	) else (
		set "ch1=" 
		goto :openefi
	)
)
if /i "%ch1%"=="1" set "ch1=" &goto :opencmd
set ch1=
goto :mounted_mainmenu

:opencmd
cls 
echo  Command Prompt window open.
start cmd /k "%mntletter%:"
cls
goto :mounted_mainmenu 

:cpf
cls
echo.
echo  If you're seeing this screen, it means that you've already tried to clone the EFI partition,
echo  but - at the moment of flushing the modified files back to the EFI - something didn't go as planned.
echo.
echo  Of course you can try to clone it again, but that will result in the loss of your previously
echo  modified files, that were kept in "C:\EFIPartition" to keep the changes you've made to them.
echo.
echo  So, if you now want to clone your EFI again, you will overwrite the modified files that are
echo  currently stored in "C:\EFIPartition".
echo.
echo  You can try to back them up and then clone the EFI again. This way you won't lose
echo  any of the work.
echo.
echo.
set /p chx=---- Press C to start cloning or B to go back to the main menu...
if /i "%chx%"=="c" set "chx=" &goto :openefi
if /i "%chx%"=="b" set "chx=" &goto :mounted_mainmenu
set "chx="
goto :cpf


:openefi
cls
echo.
echo  To open the EFI partition in File Explorer, the script needs to clone the EFI partition
echo  to "C:\EFIPartition".
echo.
echo  All the files and folders in your EFI partition will be copied in "C:\EFIPartition".
echo  Once you're done with your changes, you can flush them back to the EFI partition,
echo  keeping all the changes you've made to them.
echo.
echo.
set /p chx=---- Press C to start cloning or B to go back to the main menu...
if /i "%chx%"=="c" set "chx=" &goto :clone
if /i "%chx%"=="b" set "chx=" &goto :mounted_mainmenu
set "chx="
goto :openefi
:clone
title WinEFIMounter: Cloning...
echo.
echo  Creating the destination folder...
if not exist "C:\EFIPartition" mkdir "C:\EFIPartition"
echo.
echo  Copying files...
echo.
xcopy /e /Y "%mntletter%:\*" "C:\EFIPartition\"
echo.
title WinEFIMounter
echo  Done! Your EFI is now cloned to "C:\EFIPartition" and you can now access it.
explorer "C:\EFIPartition"
echo.
:tempbookmark2
set /p chx=---- Press F to flush the updated files back to the EFI partition...
if /i "%chx%"=="f" set "chx=" &goto :flush
set "chx="
goto :tempbookmark2
:flush
title WinEFIMounter: Flushing...
cls
echo.
echo  Flushing updated files back to "%mntletter%:\"...
echo.
for /R "%mntletter%:\" %%G in ("*.*") do del /f /S /Q "%%G" >nul 2>&1 
%mntletter%:
for /D /r %%G in ("*") do rmdir /S /Q %%G >nul 2>&1 
cd /d %temp%
xcopy /e /Y "C:\EFIPartition\*" "%mntletter%:\"
set /a errl=%errorlevel%
:errlcheck
if "%errl%"=="0" (
	set /a cpf=0
	set /a errl=0
) else (
	title WinEFIMounter: [ERROR]
	echo.
	echo  [### ERROR ###]
	echo.
	echo  An error occurred while trying to flush the updated files back to "%mntletter%:\".
	echo  The files you modified will remain in "C:\EFIPartition\" so that no work is lost.
	echo  Aborting.
	echo.
	echo    - Press any key to go back to the main menu...
	pause >nul
	set /a errl=0
	set /a cpf=1
	rem cpf=cloning procedure failed
	goto :mounted_mainmenu
)
echo.
echo  Deleting the "C:\EFIPartition\" directory...
rmdir /s /q "C:\EFIPartition\" > nul 2>&1
echo.
echo  Done! Your updated files are now in your EFI partition.
echo.
echo.
echo    - Press any key to go back to the main menu...
pause >nul
goto :mounted_mainmenu

:unmount
cls
echo.
set /p chx=---- Press U to unmount the EFI partition or B to go back to the main menu...
if /i "%chx%"=="u" set "chx=" &goto :proceed3
if /i "%chx%"=="b" set "chx=" &goto :mounted_mainmenu
set "chx="
goto :unmount
:proceed3
title WinEFIMounter: Unmounting...
echo.
echo  Unmounting the EFI partition...
echo    - Started unmounting disk %mntdrive%, partition %mntpar%...
(echo sel dis %mntdrive%
echo sel par %mntpar%
echo remove letter=%mntletter%
echo exit
)  | diskpart > nul
echo.
echo  Done.
set mntdrive=
set mntpar=
set mntletter=
echo.
echo.
echo    - Press any key to go back to the main menu...
pause >nul
goto :unmounted_mainmenu

:mounted_quit
title WinEFIMounter
cls
echo.
echo  It seems like you want to exit WinEFIMounter, but your EFI partition
echo  is still mounted. You need to unmount it first.
echo.
echo    - Press any key to go back to the main menu...
pause >nul
goto :mounted_mainmenu

:quit
title WinEFIMounter
cls
echo.
echo    #####################################################
echo   #                   WinEFIMounter                   #
echo  #####################################################
echo.
echo  WinEFIMounter version 1.0.0
echo.
echo  Developed by ^<franzageek^>
echo.
echo.
echo  GitHub Repository [https://github.com/franzageek/WinEFIMounter]
echo  Report an issue [https://github.com/franzageek/WinEFIMounter/issues]
echo.
echo  Have a good day!
echo.
echo  [All the files in "C:\EFIPartition" will be deleted.]
echo.
echo    - Press any key to exit...
pause >nul
set ch0=
set ch1=
set chx=
set mntdrive=
set mntpar=
set mntletter=
set /a cpf=0
set /a cnt=0
set /a errl=0
if exist "C:\EFIPartition" rmdir /s /q "C:\EFIPartition" > nul 2>&1
del /f /s /q "%temp%\dpscript.txt" >nul 2>&1
exit
