#ifndef FS_H
#define FS_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

void SearchFileRecursive(LPCWSTR parentPath, std::vector<std::wstring> &pathList);
bool Is64BitLibrary(LPCWSTR dllPath, bool &is64BitLibrary);
std::wstring GetDllCurrentFolder();

#endif // FS_H