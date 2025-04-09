#include "Window.h"
#include "LaunchEngineLoop.h"

namespace
{
    static LaunchEngineLoop* GetApplication(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        LaunchEngineLoop* App;
        
        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            App = static_cast<Window*>(pCreate->lpCreateParams)->GetApp();
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(App));
        }
        else
        {
            App = reinterpret_cast<LaunchEngineLoop*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }

        return App;
    }
    
    LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        // Application handling
        LaunchEngineLoop* App = GetApplication(hWnd, Msg, wParam, lParam);
        if (App == nullptr)
        {
            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }

        return App->HandleMessage(hWnd, Msg, wParam, lParam);
    }
}

FWString ConvertToFWString(const FString& str)
{
    if (str.empty())
        return {};

    int str_size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);

    FWString conversion(str_size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), conversion.data(), str_size);
    return conversion;
}

FString ConvertToFString(const FWString& str)
{
    if (str.empty())
        return {};

    int str_size = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0, nullptr, nullptr);

    FString conversion;
    conversion.resize(str_size);

    WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), conversion.data(), str_size, nullptr, nullptr);
    return conversion;
}

Window::Window(LaunchEngineLoop* App) : App(App)
{
}

Window::~Window()
{
    this->Destroy();
}

bool Window::Create(const FString& AppName, int Width, int Height, bool bFullScreen)
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    FWString WindowName = ConvertToFWString(AppName);

    // Setup window class
    WNDCLASS wc = {};
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = ::MainWndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.lpszClassName = WindowName.c_str();

    if (!RegisterClass(&wc))
    {
        MessageBox(nullptr, L"RegisterClass Failed", L"Error", MB_OK);
        throw std::exception();
    }

    // Create window
    hWnd = CreateWindow(wc.lpszClassName, WindowName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, NULL, NULL, hInstance, this);
    if (hWnd == nullptr)
    {
        MessageBox(nullptr, L"CreateWindow Failed", L"Error", MB_OK);
        throw std::exception();
    }

    // Borderless fullscreen
    if (bFullScreen)
    {
        SetWindowLong(hWnd, GWL_STYLE, 0);
    }

    // Show window
    int CmdShow = (bFullScreen ? SW_MAXIMIZE : SW_SHOWNORMAL);
    ShowWindow(hWnd, CmdShow);

    return true;
}

void Window::Destroy()
{
    DestroyWindow(hWnd);
}

void Window::GetSize(int* Width, int* Height)
{
    RECT Rect;
    GetClientRect(hWnd, &Rect);

    *Width = Rect.right - Rect.left;
    *Height = Rect.bottom - Rect.top;
}

void Window::SetTitle(const FString& Title) const
{
    SetWindowText(hWnd, ConvertToFWString(Title).c_str());
}
