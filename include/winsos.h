#ifndef WINSOS_H
#define WINSOS_H

#include <cstdlib>
#include "fs.h"
#include "net.h"

#define DLL_NAME L"mscorsvc.DLL"

void DisplayHeader();
bool ExecuteNgenTask(LPCWSTR filePath);

#endif // WINSOS_H