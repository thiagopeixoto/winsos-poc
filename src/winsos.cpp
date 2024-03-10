#include "winsos.h"

void DisplayHeader()
{
    std::string header = R"(
___       __   ___  ________   ________  ________  ________      
|\  \     |\  \|\  \|\   ___  \|\   ____\|\   __  \|\   ____\     
\ \  \    \ \  \ \  \ \  \\ \  \ \  \___|\ \  \|\  \ \  \___|_    
 \ \  \  __\ \  \ \  \ \  \\ \  \ \_____  \ \  \\\  \ \_____  \   
  \ \  \|\__\_\  \ \  \ \  \\ \  \|____|\  \ \  \\\  \|____|\  \  
   \ \____________\ \__\ \__\\ \__\____\_\  \ \_______\____\_\  \ 
    \|____________|\|__|\|__| \|__|\_________\|_______|\_________\
                                  \|_________|        \|_________|
---
    )";

    printf("%s\n", header.c_str());
}

bool ExecuteNgenTask(LPCWSTR filePath)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    WCHAR currentDirectory[MAX_PATH];
    ::GetCurrentDirectory(MAX_PATH, currentDirectory);

    ::ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ::ZeroMemory(&pi, sizeof(pi));

    if (!::CreateProcess(nullptr,
                         (LPWSTR)filePath,
                         nullptr,
                         nullptr,
                         FALSE,
                         0,
                         nullptr,
                         currentDirectory,
                         &si,
                         &pi))
    {
        printf("[x] CreateProcess failed with status 0x%x\n", ::GetLastError());
        return false;
    }

    ::CloseHandle(pi.hProcess);
    ::CloseHandle(pi.hThread);

    return true;
}