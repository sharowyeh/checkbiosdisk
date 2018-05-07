This is a Win32 console application for Windows Preinstall Environment system

The gaol is checking PC uses UEFI BIOS (or with CSM) must ensures the disk type is GPT format,
otherwise the legacy BIOS must using MBR format for disk layout.

C++ code only does windows executing diskpart and reg commands and checks results to improve function,
because requester is lazy and having lack knowledge on his job to design commands flow.

Console application return code:
- 0 :check result is true
- 1 :check result is false or check commands execution failed
