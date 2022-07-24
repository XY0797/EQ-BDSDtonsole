#include <windows.h>
#include <iostream>
#include <stdlib.h>

int EnableDebugPriv(const char* name)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;
    //打开进程令牌环
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
    //获得进程本地唯一ID
    LookupPrivilegeValueA(NULL, name, &luid);

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tp.Privileges[0].Luid = luid;
    //调整权限
    AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
    return 0;
}

//*****************************************************************************************************************************

BOOL InjectDll(const char* DllFullPath, const DWORD dwRemoteProcessId)
{
    HANDLE hRemoteProcess;
    EnableDebugPriv("SeDebugPrivilege");
    //打开远程线程
    hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRemoteProcessId);

    char* pszLibFileRemote;
    
    //使用VirtualAllocEx函数在远程进程的内存地址空间分配DLL文件名空间
    pszLibFileRemote = (char*)VirtualAllocEx(hRemoteProcess, NULL, lstrlenA(DllFullPath) + 1, MEM_COMMIT, PAGE_READWRITE);


    //使用WriteProcessMemory函数将DLL的路径名写入到远程进程的内存空间
    WriteProcessMemory(hRemoteProcess, pszLibFileRemote, (void*)DllFullPath, lstrlenA(DllFullPath) + 1, NULL);

    //##############################################################################
        //计算LoadLibraryA的入口地址
    PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)
        GetProcAddress(GetModuleHandleA("Kernel32"), "LoadLibraryA");
    //(关于GetModuleHandle函数和GetProcAddress函数)

    //启动远程线程LoadLibraryA，通过远程线程调用创建新的线程
    HANDLE hRemoteThread;
    if ((hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, pfnStartAddr, pszLibFileRemote, 0, NULL)) == NULL)
    {
        std::cout << "注入失败";
        return FALSE;
    }
    //##############################################################################

        /*
        // 在//###.....//###里的语句也可以用如下的语句代替:
         DWORD dwID;
         LPVOID pFunc = LoadLibraryA;
         HANDLE hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFunc, pszLibFileRemote, 0, &dwID );
         //是不是感觉简单了很多
        */

        // 释放句柄

    CloseHandle(hRemoteProcess);
    CloseHandle(hRemoteThread);
    std::cout << "注入成功";
    return TRUE;
}

//*****************************************************************************************************************************

int main(int argc, char** argv)
{
    if (argc == 3)
    {
        InjectDll(argv[1], atoi(argv[2]));//这个数字是你想注入的进程的ID号
        return 0;
    }
    return 0;
}