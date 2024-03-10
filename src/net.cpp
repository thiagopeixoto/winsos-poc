#include "net.h"

bool DownloadFile(LPCWSTR url, LPCWSTR savePath)
{
    HINTERNET hInternet = ::InternetOpen(L"WinSOS", INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
    if (!hInternet)
    {
        printf("[x] InternetOpen failed with status 0x%x\n", ::GetLastError());
        return false;
    }

    HINTERNET hUrl = ::InternetOpenUrl(hInternet, url, nullptr, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl)
    {
        printf("[x] InternetOpenUrl failed with status 0x%x\n", ::GetLastError());
        ::InternetCloseHandle(hInternet);
        return false;
    }

    HANDLE hFile = ::CreateFile(savePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("[x] CreateFile failed with status 0x%x\n", ::GetLastError());
        ::InternetCloseHandle(hUrl);
        ::InternetCloseHandle(hInternet);
        return false;
    }

    constexpr int bufferSize = 1024;
    BYTE buffer[bufferSize];
    DWORD bytesRead = 0;
    DWORD bytesWritten = 0;
    while (::InternetReadFile(hUrl, buffer, bufferSize, &bytesRead) && bytesRead > 0)
    {
        ::WriteFile(hFile, buffer, bytesRead, &bytesWritten, nullptr);
    }

    ::CloseHandle(hFile);
    ::InternetCloseHandle(hUrl);
    ::InternetCloseHandle(hInternet);

    return true;
}