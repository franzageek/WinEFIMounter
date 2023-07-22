#!/bin/bash

if [ -d /mnt/LinuxEFIMounter ]; then
  if mount | grep "/mnt/LinuxEFIMounter" > /dev/null; then
    umount /mnt/LinuxEFIMounter
  fi
fi

if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as a root."
  exit 1
fi

echo " "
echo "   #####################################################"
echo "  #                  LinuxEFIMounter                  #"
echo " #####################################################"
echo " "
echo " Welcome to LinuxEFIMounter. This program is meant to be used to access your"
echo " Hackintosh EFI from Linux. This script is made by GiovsTech as a contribution to FranzaGeek's batch script, written for Windows."
echo " "
echo " LinuxEFIMounter could be used to mount any EFI partition, but the main purpose of it"
echo " is to let you access your Hackintosh EFI partition from Linux."
echo " "
echo " "
read -s -r -p "   - Press any key to continue..."
clear
echo " "
echo "   #####################################################"
echo "  #                  LinuxEFIMounter                  #"
echo " #####################################################"
echo " "
echo " The EFI partition is currently NOT MOUNTED."
echo " "
echo " 1. Mount EFI partition to /mnt/LinuxEFIMounter"
echo " "
echo " E. Exit"
echo " " 
echo " "


while true; do
  read -p "Please select a function: " function

  case $function in
    1)
      clear
      fdisk -l

      echo "What is the path of the disk you want to mount?"
      read -p "Disk path: " disk_path

      while [[ ! $(fdisk -l | grep -w -c "$disk_path") -eq 1 ]]; do
        echo "Disk not found. Please enter a valid disk path."
        read -p "Disk path: " disk_path
      done

      if [ ! -d /mnt/LinuxEFIMounter ]; then
        echo "Creating /mnt/LinuxEFIMounter folder..."
        mkdir /mnt/LinuxEFIMounter/
      else
        echo "/mnt/LinuxEFIMounter folder already exists."
      fi

      mount "$disk_path" /mnt/LinuxEFIMounter
      break;;

    E)
      echo "Exiting..."
      exit 0

  esac
done




if [ -d /mnt/LinuxEFIMounter ]; then
  clear
  echo "The EFI partition is successfully mounted to /mnt/LinuxEFIMounter."
  echo "Please choose one of the following features:"
  echo " "
  echo "1. Navigate to the disk folder in the terminal"
  echo "2. Navigate to the disk folder in the file manager"
  echo "3. Unmount the disk"
  echo " "
  read -p "Please select a feature: " feature
  case $feature in
    1)
      echo "Opening /mnt/LinuxEFIMounter folder in the terminal..."
      cd ~/mnt/LinuxEFIMounter
      clear
      ;;

    2)
      echo "Opening /mnt/LinuxEFIMounter folder in the file manager of your D.E."
      xdg-open /mnt/LinuxEFIMounter
      
      ;;

    3)
      echo "Unmounting disk..."
      umount /mnt/LinuxEFIMounter
      echo "Disk unmounted."
      exit
      ;;

  esac
else
  echo "The EFI partition is not mounted."
fi