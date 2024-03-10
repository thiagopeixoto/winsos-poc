#include "fs.h"

void SearchFileRecursive(LPCWSTR parentPath, std::vector<std::wstring> &pathList)
{
    std::wstring searchPath{parentPath};
    searchPath.append(L"\\*");

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &findFileData);
    std::vector<std::wstring> filePath;

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0)
                {
                    std::wstring subDir{parentPath};
                    subDir.append(L"\\");
                    subDir.append(findFileData.cFileName);
                    SearchFileRecursive(subDir.c_str(), pathList);
                }
            }
            else
            {
                if (_wcsicmp(findFileData.cFileName, L"ngentask.exe") == 0)
                {
                    std::wstring fullPath = std::wstring{parentPath} + L"\\" + findFileData.cFileName;
                    pathList.push_back(fullPath);
                }
            }
        } while (::FindNextFile(hFind, &findFileData) != 0);

        ::FindClose(hFind);
    }
}

bool Is64BitLibrary(LPCWSTR dllPath, bool &is64BitLibrary)
{
    IMAGE_DOS_HEADER dosHeader;
    IMAGE_NT_HEADERS ntHeaders;

    HANDLE hFile = ::CreateFile(dllPath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("[x] CreateFile failed with status 0x%x\n", ::GetLastError());
        return false;
    }

    DWORD bytesRead;
    if (!::ReadFile(hFile, &dosHeader, sizeof(IMAGE_DOS_HEADER), &bytesRead, nullptr))
    {
        ::CloseHandle(hFile);
        printf("[x] Failed to read DOS header\n");
        return false;
    }

    if (dosHeader.e_magic != IMAGE_DOS_SIGNATURE)
    {
        ::CloseHandle(hFile);
        printf("[x] Invalid DOS header signature\n");
        return false;
    }

    if (::SetFilePointer(hFile, dosHeader.e_lfanew, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        ::CloseHandle(hFile);
        printf("[x] SetFilePointer failed with status 0x%x\n", ::GetLastError());
        return false;
    }

    if (!::ReadFile(hFile, &ntHeaders, sizeof(IMAGE_NT_HEADERS), &bytesRead, nullptr))
    {
        ::CloseHandle(hFile);
        printf("[x] Failed to read NT headers\n");
        return false;
    }

    if (ntHeaders.Signature != IMAGE_NT_SIGNATURE)
    {
        ::CloseHandle(hFile);
        printf("[x] Invalid NT header signature\n");
        return false;
    }

    if (ntHeaders.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64)
    {
        ::CloseHandle(hFile);
        is64BitLibrary = true;
    }

    ::CloseHandle(hFile);
    return true;
}

std::wstring GetDllCurrentFolder()
{
    WCHAR buffer[MAX_PATH];
    
    ::GetModuleFileName(nullptr, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\");
    if (pos != std::wstring::npos)
    {
        return std::wstring(buffer).substr(0, pos + 1);
    }
    return L"";
}