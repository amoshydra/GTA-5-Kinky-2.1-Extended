#pragma warning(disable:4996)
#include <windows.h>
#include <stdio.h>
#include <string>
#include <psapi.h>
#include <stdint.h>
using namespace std;


DWORD64 GetModuleBase(HANDLE hProc, string &sModuleName) {
	HMODULE *hModules;
	hModules = 0;
	char szBuf[50];
	DWORD cModules = 0;
	DWORD64 dwBase = 0;

	EnumProcessModules(hProc, hModules, 0, &cModules);
	hModules = new HMODULE[cModules / sizeof(HMODULE)];

	if (EnumProcessModules(hProc, hModules, cModules / sizeof(HMODULE), &cModules)) {
		for (int i = 0; i < cModules / sizeof(HMODULE); i++) {
			if (GetModuleBaseName(hProc, hModules[i], szBuf, sizeof(szBuf))) {
				if (sModuleName.compare(szBuf) == 0) {
					dwBase = (DWORD64)hModules[i];
					break;
				}
			}
		}
	}

	delete[] hModules;

	return dwBase;
}


void bypass_online() {
	__int64 Address = GetModuleBase(GetCurrentProcess(), string("GTA5.exe"));
	INT p;
	CHAR *MemoryBuff = new CHAR[512];
	int ok = 0;
	HANDLE hProcess = GetCurrentProcess();
	BYTE bytes[] = { 0x48, 0x8B, 0x88, 0x10, 0x01, 0x00, 0x00 };
	BYTE bytes2[] = { 0x4C, 0x8D, 0x8A, 0xC4, 0x00, 0x00, 0x00 };
	BYTE jmp[] = { 0xEB, 0x1B };
	BYTE nop2[] = { 0x90, 0x90 };
	int count = 0;
	int adc = 0;
	for (int i = 0; i < 0x9FFF9840; i++) {
		ReadProcessMemory(hProcess, (LPVOID)Address, (LPVOID)MemoryBuff, 512, NULL);
		for (p = 0; p < 512; p++) {
			Address++;
			MemoryBuff++;
			if (ok == 0) {
				if (memcmp(MemoryBuff, bytes, 7) == 0) {
					count++;
					if (count == 2) {
						WriteProcessMemory(hProcess, (LPVOID)(Address + 0x2D), nop2, 2, 0);
						ok = 1;
						count = 0;
					}
				}
			}
			if (ok == 1) {
				if (adc == 0) {
					Address = GetModuleBase(GetCurrentProcess(), string("GTA5.exe"));
					adc = 1;
				}

				if (memcmp(MemoryBuff, bytes2, 7) == 0) {
					count++;
					if (count == 4) {
						WriteProcessMemory(hProcess, (LPVOID)(Address - 0x278), jmp, 2, 0);
						goto endfunc;
					}
				}
			}
		}
		MemoryBuff = MemoryBuff - 512;
	}
	endfunc:;
}
