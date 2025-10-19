#ifndef EFI_HXX
#define EFI_HXX

typedef unsigned char u8;

namespace efi
{
    struct EfiPartition
    {
        bool mounted;
        u8 disk;
        u8 part;
        char letter;
    };
    
    bool select_partition(EfiPartition& efi);
    bool mount_partition(EfiPartition& efi);
    void unmount_partition(EfiPartition& efi);
    bool clone_partition(EfiPartition& efi);
    void flush_partition(EfiPartition& efi);
    bool check_if_mounted(EfiPartition& efi);
}

#endif