// checkbiosdisk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	bool command_success = true;
	bool is_gpt = false;
	bool is_uefi = false;
	wchar_t pCmd[4096];
	pCmd[0] = 0;
	
	wcscpy_s(pCmd, L"cmd.exe /c echo lis disk > checkdisk.dat");
	BOOL res = CreateProcess(NULL, pCmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (res == FALSE)
		command_success = false;
	wcscpy_s(pCmd, L"cmd.exe /c echo exit >> checkdisk.dat");
	res = CreateProcess(NULL, pCmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (res == FALSE)
		command_success = false;
	wcscpy_s(pCmd, L"cmd.exe /c diskpart.exe /s checkdisk.dat > checkdisk.log");
	res = CreateProcess(NULL, pCmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (res == FALSE)
		command_success = false;
	wcscpy_s(pCmd, L"cmd.exe /c find \"*\" checkdisk.log");
	res = CreateProcess(NULL, pCmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (res == FALSE)
		command_success = false;
	ULONG rc;
	res = GetExitCodeProcess(pi.hProcess, &rc);
	if (res == FALSE)
		command_success = false;

	if (command_success == false)
		std::cout << "command failed!";
	else if (rc == 0)
	{
		is_gpt = true;
		std::cout << "gpt";
	}
	else
	{
		is_gpt = false;
		std::cout << "mbr";
	}
	//system("pause");


	wcscpy_s(pCmd, L"cmd.exe /c reg query HKLM\\System\\CurrentControlSet\\Control /v PEFirmwareType > checkbios.log");
	res = CreateProcess(NULL, pCmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (res == FALSE)
		command_success = false;

	wcscpy_s(pCmd, L"cmd.exe /c find \"REG_DWORD\" checkbios.log | find \"0x2\"");
	res = CreateProcess(NULL, pCmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (res == FALSE)
		command_success = false;
	res = GetExitCodeProcess(pi.hProcess, &rc);
	if (res == FALSE)
		command_success = false;
	if (command_success == false)
		std::cout << "command failed!";
	else if (rc == 0)
	{
		is_uefi = true;
		std::cout << "uefi";
	}
	else
	{
		is_uefi = false;
		std::cout << "legacy";
	}
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	//system("pause");
	if (command_success == false)
		return 1;
	if (is_gpt != is_uefi)
		return 1;
	return 0;
}

