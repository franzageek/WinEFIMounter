# Script used inside of efi::show_whats_changed() 
# The below script has been turned into a one-liner that generates a list of added, modified and deleted files
# which then gets interpreted by WinEFIMounter and shown to the user.

# Compare the EFI with its updated clone 
$dir1 = "$letter:\";
$dir2 = "C:\EFIPartition\";

$files1 = Get-ChildItem -Recurse -File $dir1 | ForEach-Object {
    $_.FullName.Replace($dir1, '');
}
$files2 = Get-ChildItem -Recurse -File $dir2 | ForEach-Object {
    $_.FullName.Replace($dir2, '');
}

$added = $files2 | Where-Object { $_ -notin $files1 }
$deleted = $files1 | Where-Object { $_ -notin $files2 }
$common = $files1 | Where-Object { $_ -in $files2 }

$modified = @()
foreach ($file in $common) {
    $hash1 = Get-FileHash (Join-Path $dir1 $file);
    $hash2 = Get-FileHash (Join-Path $dir2 $file);
    if ($hash1.Hash -ne $hash2.Hash) {
        $modified += $file;
    }
}

$addedStr   = ($added   -join '>');
$modifiedStr= ($modified-join '>');
$deletedStr = ($deleted -join '>');

$diff = "|$addedStr|$modifiedStr|$deletedStr|";

$diff | Out-File -FilePath "$env:TEMP\diff.txt" -Encoding default;


# Enable scrollbar by increasing buffer size
$h = Get-Host; 
$w = $h.UI.RawUI;
$b = $w.BufferSize; 
$b.Height = 999; 
$w.BufferSize = $b;