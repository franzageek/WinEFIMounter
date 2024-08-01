#ifndef CLONE_HXX
#define CLONE_HXX
#include "core.hxx"

bool clone_efi_partition(const char& mntLetter);
bool flush_efi_partition(const char& mntLetter);

#endif // CLONE_HXX