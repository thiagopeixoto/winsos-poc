#ifndef NET_H
#define NET_H

#include <cstdio>
#include <Windows.h>
#include <wininet.h>

bool DownloadFile(LPCWSTR url, LPCWSTR savePath);

#endif // NET_H