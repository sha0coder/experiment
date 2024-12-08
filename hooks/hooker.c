#include <stdio.h>
#include <windows.h>
#include "include/MinHook.h"


typedef int (WINAPI *TerminateProcess_t)(HANDLE, UINT);

TerminateProcess_t oTerminateProcess = NULL;
int hTerminateProcess(HANDLE hProcess, UINT uExitCode) {
    return NULL;
}


int main() {
    MH_Initialize();
    MH_CreateHook(TerminateProcess, hTerminateProcess, (void**)&oTerminateProcess);
    MH_EnableHook(TerminateProcess);

    return 0;
}
