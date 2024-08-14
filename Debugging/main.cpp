#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>

bool Hooked = false;

void CheckCreateThread()
{
    while (true)
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
            if (Instruction == 0xE9 || Instruction == 0xC3 || Instruction == 0xCC || Instruction == 0x90)
            {
                Hooked = true;
            }
        }
        if (Hooked)
        {
            printf("CreateThread Is Hooked \n");
            Sleep(1500);
        }
        else
        {
            printf("CreateThread Is Not Hooked \n");
            Sleep(1500);
        }
    }
}

int main()
{
    std::thread(CheckCreateThread).detach();
    std::cin.get();
}