#include <windows.h>
#include <iostream>
#include <vector>

void CheckCreateThread()
{
    bool Hooked = false;
    HMODULE Module = GetModuleHandle(L"kernel32.dll");
    LPVOID Address = (LPVOID)GetProcAddress(Module, "CreateThread");
    const SIZE_T Size = 64;
    std::vector<BYTE> Buffer(Size);
    SIZE_T Read;
    ReadProcessMemory(GetCurrentProcess(), Address, Buffer.data(), Size, &Read);
    for (SIZE_T i = 0; i < Read; i++)
    {
        BYTE Instruction = Buffer[i];
        if (Instruction == 0xE9 || Instruction == 0xC3 || Instruction == 0xCC || Instruction == 0x90)
        {
            Hooked = true;
        }
    }
    if (Hooked)
    {
        printf("CreateThread Is Hooked");
    }
    else
    {
        printf("CreateThread Is Not Hooked");
    }
}

int main()
{
    CheckCreateThread();
    std::cin.get();
}