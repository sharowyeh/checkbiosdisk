========================================================================
    CONSOLE APPLICATION : checkbiosdisk Project Overview
========================================================================

This is a Win32 console application for Windows Preinstall Environment system

The gaol is checking uses UEFI BIOS (or with CSM) must ensures the disk type is GPT format.
Otherwise the legacy BIOS for boot must using MBR format for disk layout format.

Console application return code:
0 - check result is true
1 - check result is false or check commands execution failed
