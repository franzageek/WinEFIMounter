#!/bin/bash
clear
if [ -d /mnt/EFIPartition ]; then
  if mount | grep "/mnt/EFIPartition" > /dev/null; then
    umount /mnt/EFIPartition
  fi
fi

if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as a root."
  exit 1
fi
clear
echo " "
echo "   #####################################################"
echo "  #                  LinuxEFIMounter                  #"
echo " #####################################################"
echo " "
echo " Welcome to LinuxEFIMounter. This program is meant to be used to access your"
echo " Hackintosh EFI from Linux. This script is made by GiovsTech as a contribution"
echo " to WinEFIMounter, written by FranzaGeek for Windows."
echo " "
echo " LinuxEFIMounter could be used to mount any EFI partition, but the main purpose of it"
echo " is to let you access your Hackintosh EFI partition from Linux."
echo " "
echo " "
read -s -r -p "   - Press any key to continue..."

exitscr ()
{
  clear
  echo " "
  echo "   #####################################################"
  echo "  #                  LinuxEFIMounter                  #"
  echo " #####################################################"
  echo " "
  echo " LinuxEFIMounter version 1.0.0"
  echo " "
  echo " Developed by GiovsTech and FranzaGeek"
  echo " "
  echo " "
  echo " GitHub Repository [https://github.com/GiovsTech/LinuxEFIMounter]"
  echo " Report an issue [https://github.com/GiovsTech/LinuxEFIMounter/issues]"
  echo " "
  echo " Have a good day!"
  echo " "
  echo " "
  echo " "
  rm -r /mnt/EFIPartition
  exit 0
}

<<<<<<< Updated upstream
=======
0_mount_process ()
{
clear
        echo " "
        read -p "   - Press M to mount the selected partition or B to go back to the main menu..." ch1
      
      while true; do
        case $ch1 in

        M) 
            if [ ! -d /mnt/EFIPartition ]; then
              echo " "
              echo " "
              echo " Creating mount point..."
              mkdir /mnt/EFIPartition/
            fi

        echo " Mounting the selected partition..."
        mount "$disk_path" /mnt/EFIPartition
        mounted_mainmenu
        ;;
          m) 
            if [ ! -d /mnt/EFIPartition ]; then
              echo " "
              echo " "
              echo " Creating mount point..."
              mkdir /mnt/EFIPartition/
            fi

        echo " Mounting the selected partition..."
        mount "$disk_path" /mnt/EFIPartition
        mounted_mainmenu
        ;;
      b)
        0_unmounted_mainmenu
        ;;
      B)
        0_unmounted_mainmenu
          esac
     done
}

0_unmounted_mainmenu () 
{
  clear
  echo " "
  echo "   #####################################################"
  echo "  #                  LinuxEFIMounter                  #"
  echo " #####################################################"
  echo " "
  echo " The EFI partition is currently NOT MOUNTED."
  echo " "
  echo " 1. Mount EFI partition to /mnt/EFIPartition"
  echo " "
  echo " E. Exit"
  echo " " 
  echo " "
  
  
  while true; do
    read -p "   - Enter your choice:" ch0
  
    case $ch0 in
      
       E) 
        exitscr
        ;;
      e) 
        exitscr
        ;;
      1)
        clear
        echo " "
        echo " In order to mount your EFI, you need to specify your Hackintosh EFI's path."
        echo " From the below list, enter the full path of your EFI partition"
        echo " "
        fdisk -l
        echo " "
        read -p "   - Enter your partiton path:" disk_path
  
  
        while [[ ! $(fdisk -l | grep -w -c "$disk_path") -eq 1 ]]; do
          echo " The specified partition is not valid. Please enter a valid partition path."
          read -p "   - Enter your partiton path:" disk_path
        done
      mount_process
    esac
  done
}

>>>>>>> Stashed changes
partition_unmount ()
{
  clear
  echo " "
  read -p "   - Press U to unmount the EFI partition or B to go back to the main menu..." ch3
  case $ch3 in
    b)
      mounted_mainmenu
      ;;
<<<<<<< Updated upstream
=======
     U)
      echo " "
      echo " "
      echo " Unmounting the EFI partition..."
      echo "    - Started unmounting $disk_path..."
      umount /mnt/EFIPartition
      echo " "
      echo " Done."
      read -s -r -p "   - Press any key to go back to the main menu..."
      0_unmounted_mainmenu
      ;;
>>>>>>> Stashed changes
    u)
      echo " "
      echo " "
      echo " Unmounting the EFI partition..."
      echo "    - Started unmounting $disk_path..."
      umount /mnt/EFIPartition
      echo " "
      echo " Done."
      read -s -r -p "   - Press any key to go back to the main menu..."
<<<<<<< Updated upstream
      unmounted_mainmenu
=======
      0_unmounted_mainmenu
>>>>>>> Stashed changes
      ;;
  esac
}

<<<<<<< Updated upstream
=======
mount_process ()
{
clear
        echo " "
        read -p "   - Press M to mount the selected partition or B to go back to the main menu..." ch1
      
      while true; do
        case $ch1 in

        M) 
            if [ ! -d /mnt/EFIPartition ]; then
              echo " "
              echo " "
              echo " Creating mount point..."
              mkdir /mnt/EFIPartition/
            fi

        echo " Mounting the selected partition..."
        mount "$disk_path" /mnt/EFIPartition
        mounted_mainmenu
        ;;
          m) 
            if [ ! -d /mnt/EFIPartition ]; then
              echo " "
              echo " "
              echo " Creating mount point..."
              mkdir /mnt/EFIPartition/
            fi

        echo " Mounting the selected partition..."
        mount "$disk_path" /mnt/EFIPartition
        mounted_mainmenu
        ;;
      b)
        0_unmounted_mainmenu
        ;;
      B)
        0_unmounted_mainmenu
          esac
     done
}

>>>>>>> Stashed changes
mounted_mainmenu ()
{
  clear
  echo " "
  echo "   #####################################################"
  echo "  #                  LinuxEFIMounter                  #"
  echo " #####################################################"
  echo " "
  echo " The EFI partition is currently MOUNTED TO /mnt/EFIPartition."
  echo " "
  echo " 1. Browse the EFI partition content via command line"
  echo " 2. Open EFI Partition in the file manager"
  echo " 3. Unmount EFI Partition "
  echo " "
  echo " E. Exit"
  echo " " 
  echo " "
  
  while true; do
    read -p "   - Enter your choice:" ch2
    case $ch2 in
      1)
        echo " Terminal window open."
        cd /mnt/EFIPartition
        clear
        ;;
  
      2)
        echo " File manager window open."
        xdg-open /mnt/EFIPartition
        ;;
  
      3)
        partition_unmount
        ;;
      e) 
        exitscr
        ;;
      E) 
        exitscr
        ;;
    esac
  done
}


mount_process ()
{
  clear
  echo " "
  read -p "   - Press M to mount the selected partition or B to go back to the main menu..." ch1
  while true; do
    case $ch1 in

      m) 
        if [ ! -d /mnt/EFIPartition ]; then
          echo " "
          echo " "
          echo " Creating mount point..."
          mkdir /mnt/EFIPartition/
        fi
        echo " Mounting the selected partition..."
        mount "$disk_path" /mnt/EFIPartition
        mounted_mainmenu
        ;;
      b)
        unmounted_mainmenu
        ;;
    esac
  done
}

unmounted_mainmenu () 
{
  clear
  echo " "
  echo "   #####################################################"
  echo "  #                  LinuxEFIMounter                  #"
  echo " #####################################################"
  echo " "
  echo " The EFI partition is currently NOT MOUNTED."
  echo " "
  echo " 1. Mount EFI partition to /mnt/EFIPartition"
  echo " "
  echo " E. Exit"
  echo " " 
  echo " "
  while true; do
    read -p "   - Enter your choice:" ch0
  
    case $ch0 in
      
      e) 
        exitscr
        ;;
      1)
        clear
        echo " "
        echo " In order to mount your EFI, you need to specify your Hackintosh EFI's path."
        echo " From the below list, enter the full path of your EFI partition"
        echo " "
        fdisk -l
        echo " "
        read -p "   - Enter your partiton path:" disk_path
        while [[ ! $(fdisk -l | grep -w -c "$disk_path") -eq 1 ]]; do
          echo " The specified partition is not valid. Please enter a valid partition path."
          read -p "   - Enter your partiton path:" disk_path
        done
        mount_process
        ;;
    esac
  done
}
unmounted_mainmenu