#include <iostream>
#include <Windows.h>
#include "Header.h"

__declspec(naked) void loadModBadges()
{

	__asm {

		pushad
		mov eax, [eax + 0x000001D4]
		add eax, 48
		mov ecx, modBadgesString
		add ecx, 10
		mov[ecx], al
		inc ecx
		mov dword ptr[ecx], 0x3130305F
		popad
		push modBadgesString
		call dword ptr[createWithSprite]
		jmp[retLoadModBadges]

	}
}
__declspec(naked) void loadModBadges2()
{

	__asm {

		pushad
		mov eax, [eax + 0x00000154]
		add eax, 48
		mov ecx, modBadgesString
		add ecx, 10
		mov[ecx], al
		inc ecx
		mov dword ptr[ecx], 0x3130305F
		popad
		push modBadgesString
		call dword ptr[createWithSprite]
		jmp[retLoadModBadges2]

	}
}

__declspec(naked) void loadPointer()
{

	__asm {

		pushad
		mov eax, createWithSprite_
		mov eax, [eax]
		mov[createWithSprite], eax
		mov eax, operatorPlus_
		mov eax, [eax]
		mov[operatorPlus], eax
		mov eax, sharedDirector_
		mov eax, [eax]
		mov[sharedDirector], eax
		popad
		ret

	}
}

void writeByte(BYTE *address, BYTE content)
{
	DWORD oldProtect, newProtect;
	VirtualProtect(address, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	*address = content;
	VirtualProtect(address, 1, oldProtect, &newProtect);
}

void mainMod()
{

	loadPointer();

	placeJMP((BYTE *)base + 0x211187, (DWORD)loadModBadges, 0x5);
	placeJMP((BYTE *)base + 0x5FA21, (DWORD)loadModBadges2, 0x5);

	writeByte((BYTE *)base + 0x49762, 11);
}

BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD ul_reason_for_call,
					  LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainMod, hModule, 0, nullptr);

	case DLL_THREAD_ATTACH:

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}