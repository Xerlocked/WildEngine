#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Templates/UnrealTypes.h"

class LaunchEngineLoop;

FWString ConvertToFWString(const FString& str);
FString ConvertToFString(const FWString& str);

class Window final
{
    LaunchEngineLoop* App = nullptr;
    
public:
    Window(LaunchEngineLoop* App);
    virtual ~Window();

    // Create the Window
    bool Create(const FString& AppName, int Width, int Height, bool bFullScreen);

    // Destroy Window
    void Destroy();

    // Get Window Size
    void GetSize(int* Width, int* Height);

    inline HWND GetHWND() const { return hWnd; }

    inline LaunchEngineLoop* GetApp() const { return App; }

    void SetTitle(const FString& Title) const;

private:
    HWND hWnd = nullptr;
};
