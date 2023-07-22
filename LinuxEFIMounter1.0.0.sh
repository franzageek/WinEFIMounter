#!/bin/bash

# Check if it is opened as root
if [[ $EUID -ne 0 ]]; then
  echo "This script must be opened as a root"
  exit 1
fi


echo       "#####################################################"
echo      "#                   LinuxEFIMounter                   #"
echo       "#####################################################"
echo  Welcome to Linux. This program is meant to be used to access your
echo  Hackintosh EFI from Linux. 
echo
echo  LinuxEFIMounter could be used to mount any EFI partition, but the main purpose of it
echo  is to let you access your Hackintosh EFI partition from Linux since there is not
echo  any tool to do that, apart mounting it by terminal.
echo 
read -n 1 -s -r -p "Press any key to continue"
clear
echo
echo    "#####################################################"
echo    "#                  LinuxEFIMounter                   #"
echo    "#####################################################"
echo
echo  The EFI partition is currently NOT MOUNTED."
echo
echo  "1. Mount EFI partition to /mnt"
echo
echo  "E. Exit"



