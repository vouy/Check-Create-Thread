#include <windows.h>
#include <iostream>
#include <vector>

bool Hooked = false;

void CheckCreateThread()
{
    HMODULE Module = GetModuleHandle(L"kernel32.dll");
    LPVOID Address = (LPVOID)GetProcAddress(Module, "CreateThread");
    const SIZE_T Size = 64;
    std::vector<BYTE> Buffer(Size);
    SIZE_T Read;
    ReadProcessMemory(GetCurrentProcess(), Address, Buffer.data(), Size, &Read);
    for (SIZE_T i = 0; i < Read; i++)
    {
        BYTE Instruction = Buffer[i];
        if (Instruction == 0xE9 || Instruction == 0xC3 || Instruction == 0xCC || Instruction == 0x90 || Instruction == 0x68)
        {
            Hooked = true;
            break;
        }
    }
    if (Hooked)
    {
        printf("CreateThread Is Hooked");
        std::cin.get();
    }
    else
    {
        printf("CreateThread Is Not Hooked");
        std::cin.get();
    }
}

void main()
{
    CheckCreateThread();
}