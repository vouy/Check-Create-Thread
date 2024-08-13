#include <windows.h>
#include <iostream>
#include <vector>

void CheckCreateThread()
{
    HMODULE Module = GetModuleHandle(L"kernel32.dll");
    LPVOID Address = (LPVOID)GetProcAddress(Module, "CreateThread");
    const SIZE_T Size = 64;
    std::vector<BYTE> Buffer(Size);
    SIZE_T Read;
    ReadProcessMemory(GetCurrentProcess(), Address, Buffer.data(), Size, &Read);
    bool Hooked = false;
    for (SIZE_T i = 0; i < Read; i++)
    {
        BYTE b = Buffer[i];
        if (b == 0xE9 || b == 0xC3 || b == 0xCC || b == 0x90 || b == 0x68)
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