#include <iostream>
#include <Windows.h>

void placeJMP(BYTE *address, DWORD jumpTo, DWORD length)
{
	DWORD oldProtect, newProtect, relativeAddress;
	VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	relativeAddress = (DWORD)(jumpTo - (DWORD)address) - 5;
	*address = 0xE9;
	*((DWORD *)(address + 0x1)) = relativeAddress;
	for (DWORD x = 0x5; x < length; x++)
	{
		*(address + x) = 0x90;
	}
	VirtualProtect(address, length, oldProtect, &newProtect);
}

DWORD base = (DWORD)GetModuleHandleA(0);
DWORD libcocosbase = (DWORD)GetModuleHandleA("libcocos2d.dll");

DWORD createMenu = base + 0x18EE0;

DWORD createWithSprite = base + 0x282284; // USE AS A POINTER
DWORD createWithSprite_ = (DWORD)createWithSprite;

DWORD operatorPlus = base + 0x282278; // USE AS A POINTER
DWORD operatorPlus_ = (DWORD)operatorPlus;

DWORD sharedDirector = base + 0x282270; // USE AS A POINTER
DWORD sharedDirector_ = (DWORD)sharedDirector;

DWORD retLoadModBadges = base + 0x211191;
DWORD retLoadModBadges2 = base + 0x5FA2B;
char modBadgesStringChar[20] = "modBadge_01_001.png";
DWORD modBadgesString = (DWORD)modBadgesStringChar;