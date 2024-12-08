#include <windows.h>
#include <stdio.h>

const char* getPermissionName(DWORD access) {
    switch(access) {
        case PROCESS_TERMINATE: return "PROCESS_TERMINATE";
        case PROCESS_CREATE_THREAD: return "PROCESS_CREATE_THREAD";
        case PROCESS_VM_OPERATION: return "PROCESS_VM_OPERATION";
        case PROCESS_VM_READ: return "PROCESS_VM_READ";
        case PROCESS_VM_WRITE: return "PROCESS_VM_WRITE";
        case PROCESS_DUP_HANDLE: return "PROCESS_DUP_HANDLE";
        case PROCESS_CREATE_PROCESS: return "PROCESS_CREATE_PROCESS";
        case PROCESS_SET_QUOTA: return "PROCESS_SET_QUOTA";
        case PROCESS_SET_INFORMATION: return "PROCESS_SET_INFORMATION";
        case PROCESS_QUERY_INFORMATION: return "PROCESS_QUERY_INFORMATION";
        case PROCESS_SUSPEND_RESUME: return "PROCESS_SUSPEND_RESUME";
        case PROCESS_QUERY_LIMITED_INFORMATION: return "PROCESS_QUERY_LIMITED_INFORMATION";
        case SYNCHRONIZE: return "SYNCHRONIZE";
        case PROCESS_ALL_ACCESS: return "PROCESS_ALL_ACCESS";
        default: return "UNKNOWN";
    }
}

void tryOpenProcess(DWORD pid, DWORD access) {
    HANDLE hProcess = OpenProcess(access, FALSE, pid);
    if (hProcess != NULL) {
        printf("%s (0x%08X): SUCCESS\n", getPermissionName(access), access);
        CloseHandle(hProcess);
    } else {
        printf("%s (0x%08X): FAILED (Error: %lu)\n", getPermissionName(access), access, GetLastError());
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    DWORD pid = atoi(argv[1]);
    
    // Probar diferentes combinaciones de permisos
    DWORD permissions[] = {
        PROCESS_TERMINATE,                    // 0x0001
        PROCESS_CREATE_THREAD,                // 0x0002
        PROCESS_VM_OPERATION,                 // 0x0008
        PROCESS_VM_READ,                      // 0x0010
        PROCESS_VM_WRITE,                     // 0x0020
        PROCESS_DUP_HANDLE,                   // 0x0040
        PROCESS_CREATE_PROCESS,               // 0x0080
        PROCESS_SET_QUOTA,                    // 0x0100
        PROCESS_SET_INFORMATION,              // 0x0200
        PROCESS_QUERY_INFORMATION,            // 0x0400
        PROCESS_SUSPEND_RESUME,               // 0x0800
        PROCESS_QUERY_LIMITED_INFORMATION,    // 0x1000
        SYNCHRONIZE                           // 0x00100000
    };

    int num_permissions = sizeof(permissions) / sizeof(permissions[0]);
    
    for (int i = 0; i < num_permissions; i++) {
        tryOpenProcess(pid, permissions[i]);
    }

    // También probar PROCESS_ALL_ACCESS
    tryOpenProcess(pid, PROCESS_ALL_ACCESS);

    return 0;
}
