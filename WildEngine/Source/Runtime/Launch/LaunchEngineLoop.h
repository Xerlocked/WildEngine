#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <memory>

class URenderer;
class Window;

class LaunchEngineLoop
{
public:
    LaunchEngineLoop();
    virtual ~LaunchEngineLoop() = default;
    
    int Run();

    LRESULT HandleMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    // Get Window
    inline Window* GetWindow() const { return ActiveWindow.get(); }

private:
    // Main Property
    std::unique_ptr<Window> ActiveWindow = nullptr;
    std::unique_ptr<URenderer> UEngineRenderer = nullptr;

    // Property
    bool bRunning = true;
    bool bWindowCreated = false;


    // Tick
    void CalculateFrameStats(float DeltaTime);
    int FrameCount = 0;
    
    // Event
    void OnResize(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    void OnMouseMove(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    void OnKeyDown(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};
