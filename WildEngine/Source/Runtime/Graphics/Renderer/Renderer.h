#pragma once
// D3D 사용에 필요한 라이브러리들을 링크합니다.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <exception>

#include <wrl/client.h> // ComPtr
using Microsoft::WRL::ComPtr;

class LaunchEngineLoop;

namespace DX
{
    inline void Check(HRESULT hr)
    {
#ifdef _DEBUG
        if (FAILED(hr))
        {
            throw std::exception("Check failed");
        }
#endif
    }
}

class UGraphics
{
public:
    UGraphics() = default;
    /** Delete copy constructor */
    UGraphics(const UGraphics&) = delete;
    UGraphics& operator=(const UGraphics&) = delete;
    UGraphics(UGraphics&&) = delete;
    UGraphics& operator=(UGraphics&&) = delete;
    virtual ~UGraphics() = default;
    
    virtual ID3D11Device* GetDevice() const = 0;
    virtual ID3D11DeviceContext* GetDeviceContext() const = 0;
};


class URenderer : public UGraphics
{
    LaunchEngineLoop* Application = nullptr;

public:
    URenderer(LaunchEngineLoop* InApp);
    
    // Creates the rendering device and context
    void Create();

    // Clear the buffers
    void Clear();

    // Display the rendered scene
    void Present() const;

    void Resize(int Width, int Height);

    ID3D11Device* GetDevice() const override { return Device.Get(); }

    ID3D11DeviceContext* GetDeviceContext() const override { return DeviceContext.Get(); }

private:
    FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f }; // 화면을 초기화(clear) 할 때 사용할 색상(RGBA)

    // Device & Context
    ComPtr<ID3D11Device> Device = nullptr;
    ComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
    void CreateDeviceAndContext();

    // Swapchain
    ComPtr<IDXGISwapChain> SwapChain = nullptr;
    void CreateSwapChain(int Width, int Height);

    // Render target & depth stencil view
    ComPtr<ID3D11RenderTargetView> RenderTargetView = nullptr;
    ComPtr<ID3D11DepthStencilView> DepthStencilView = nullptr;
    void CreateRenderTargetAndDepthStencilView(int Width, int Height);

    void SetViewport(int Width, int Height) const;
};