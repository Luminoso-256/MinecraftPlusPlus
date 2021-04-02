// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <fstream>
#include <MinHook.h>
#include "sdk.h"
#include <iostream>




//Function Pointers (start with fp)
openGl::glFlush fpGlFlush = NULL;
openGl::glClear fpGlClear = NULL;
openGl::glDisable fpGlDisable = NULL;
openGl::glEnable fpGlEnable = NULL;
user32::RedrawWindow fpRedrawWindow = NULL;

//Detour functions (start with detour)
void detourGlFlush(){
    fpGlFlush();
}

void detourGlClear() {
    fpGlClear();
}

void detourGlEnable() {
    fpGlEnable();
}

void detourGlDisable() {
    fpGlDisable();
}

void detourRedrawWindow() {
    fpRedrawWindow();
}

//the true entry point of the DLL for us
void init() {
    //initialize our console window 
    BOOL f = AllocConsole();
    FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;

    freopen_s(&fpstdin, "CONIN$", "r", stdin);
    freopen_s(&fpstdout, "CONOUT$", "w", stdout);
    freopen_s(&fpstderr, "CONOUT$", "w", stderr);
    SetConsoleTitleA("Minecraft PlusPlus | Log Window");

    std::cout << "[Info] DLL Injected into process successfully\n";
    std::cout << "[Info] Initializing Minhook \n";
    if (MH_Initialize() != MH_OK)
    {
        std::cout << "[Error] Minhook failed to initialize!\n";
    }
    else {
        std::cout << "[Info] Minhook initialized successfully.\n";
    }
    std::cout << "[Info] Initializing hooks. \n";

    if (MH_CreateHookApi(L"opengl32", "glFlush", &detourGlFlush, reinterpret_cast<LPVOID*>(&fpGlFlush)) != MH_OK) {
        std::cout << "[Error] Creating glFlush hook failed!\n";
    }

    if (MH_CreateHookApi(L"opengl32", "glClear", &detourGlClear, reinterpret_cast<LPVOID*>(&fpGlClear)) != MH_OK) {
        std::cout << "[Error] Creating glClear hook failed! \n";
    }

    if (MH_CreateHookApi(L"opengl32", "glEnable", &detourGlEnable, reinterpret_cast<LPVOID*>(&fpGlEnable)) != MH_OK) {
        std::cout << "[Error] Creating glEnable hook failed! \n";
    }

    if (MH_CreateHookApi(L"opengl32", "glDisable", &detourGlDisable, reinterpret_cast<LPVOID*>(&fpGlDisable)) != MH_OK) {
        std::cout << "[Error] Creating glDisablehook failed! \n";
    }
    if (MH_CreateHookApi(L"user32", "RedrawWindow", &detourRedrawWindow, reinterpret_cast<LPVOID*>(&fpRedrawWindow)) != MH_OK) {
        std::cout << "[Error] Creating RedrawWindow hook failed! \n";
    }

    std::cout << "[Info] Hook Initialization finished.";


    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
        std::cout << "[Error] Enabling minhook hooks failed!\n";
    }
   
}





BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

