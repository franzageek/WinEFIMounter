#ifndef EFI_HXX
#define EFI_HXX
#include "core.hxx"

void get_efi_partition(u8& diskNum, u8& partNum, const std::string& listPath);
bool mount_efi_partition(u8& diskNumber, u8& partNumber, char& mntLetter, const std::string& listPath);
bool unmount_efi_partition(const u8& diskNumber, const u8& partNumber, const char& mntLetter);

#endif // EFI_HXX