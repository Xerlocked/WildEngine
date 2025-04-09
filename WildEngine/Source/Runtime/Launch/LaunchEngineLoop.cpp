#include "LaunchEngineLoop.h"
#include "Misc/Timer.h"
#include "Window.h"
#include "Renderer.h"

#include <windowsx.h>


LaunchEngineLoop::LaunchEngineLoop()
{
    const FString WindowTitle = "Wild Engine";
    constexpr int WindowWidth = 800;
    constexpr int WindowHeight = 600;

    // Create Window
    ActiveWindow = std::make_unique<Window>(this);
    bWindowCreated = ActiveWindow->Create(WindowTitle, WindowWidth, WindowHeight, false);

    UEngineRenderer = std::make_unique<URenderer>(this);
    UEngineRenderer->Create();
}

int LaunchEngineLoop::Run()
{
    Timer timer;
    timer.Start();

    while (bRunning)
    {
        timer.Tick();
        this->CalculateFrameStats(timer.GetDeltaTime());

        MSG msg = {};
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bRunning = false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Clear the buffers
        UEngineRenderer->Clear();

        // Bind the shader to the pipeline
        // m_Shader->Use();

        // Update the model view projection constant buffer
        // this->ComputeModelViewProjectionMatrix();

        // Bind the raster state (solid/wireframe) to the pipeline
        // m_RasterState->Use();

        // Render the model
        // m_Model->Render();

        // Display the rendered scene
        UEngineRenderer->Present();
    }
    
    return 0;
}

LRESULT LaunchEngineLoop::HandleMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
        return 0;

        case WM_SIZE:
            this->OnResize(hWnd, Msg, wParam, lParam);
        return 0;

        case WM_MOUSEMOVE:
            this->OnMouseMove(hWnd, Msg, wParam, lParam);
        return 0;
    
        case WM_KEYDOWN:
            this->OnKeyDown(hWnd, Msg, wParam, lParam);
        return 0;
    
        default:
            return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
}

void LaunchEngineLoop::CalculateFrameStats(float DeltaTime)
{
    static float Time = 0.0f;

    FrameCount++;
    Time += DeltaTime;

    if (Time > 1.0f)
    {
        // Do something 'FrameCount'
        //

        Time = 0.0f;
        FrameCount = 0;
    }
}

void LaunchEngineLoop::OnResize(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (!bWindowCreated)
    {
        return;
    }

    // Get window size
    int Width = LOWORD(lParam);
    int Height HIWORD(lParam);

    // Resize renderer
    // m_Renderer->Resize(Width, Height);

    // Update camera
    // m_Camera->UpdateAspectRatio(Width, Height);
}

void LaunchEngineLoop::OnMouseMove(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    static int PreviousMouseX = 0;
    static int PreviousMouseY = 0;

    int MouseX = GET_X_LPARAM(lParam);
    int MouseY = GET_Y_LPARAM(lParam);

    if (wParam & MK_LBUTTON)
    {
        float DeltaX = static_cast<float>(MouseX - PreviousMouseX);
        float DeltaY = static_cast<float>(MouseY - PreviousMouseY);

        // Rotate camera
        float Yaw = DeltaX * 0.01f;
        float Pitch = DeltaY * 0.01f;

        // m_Camera->Rotate(pitch, yaw);
    }

    PreviousMouseX = MouseX;
    PreviousMouseY = MouseY;
}

void LaunchEngineLoop::OnKeyDown(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    WORD Flags = HIWORD(lParam);
    BOOL KeyRepeat = (Flags & KF_REPEAT) == KF_REPEAT;

    if (!KeyRepeat)
    {
        // m_RasterState->ToggleWireframe();
    }
}
