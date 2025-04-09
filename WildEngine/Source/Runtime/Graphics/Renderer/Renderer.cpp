#include "Renderer.h"

#include "LaunchEngineLoop.h"
#include "Window.h"

URenderer::URenderer(LaunchEngineLoop* InApp) : Application(InApp) { }

void URenderer::Create()
{
    int WindowWidth, WindowHeight;
    Application->GetWindow()->GetSize(&WindowWidth, &WindowHeight);

    // Setup
    CreateDeviceAndContext();
    CreateSwapChain(WindowWidth, WindowHeight);
    CreateRenderTargetAndDepthStencilView(WindowWidth, WindowHeight);
    SetViewport(WindowWidth, WindowHeight);
}

void URenderer::CreateDeviceAndContext()
{
    D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    
    DX::Check(
        D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
            FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION,
            Device.ReleaseAndGetAddressOf(), nullptr, DeviceContext.ReleaseAndGetAddressOf())
    );
}

void URenderer::CreateSwapChain(int Width, int Height)
{
    ComPtr<IDXGIDevice> dxgiDevice = nullptr;
    DX::Check(Device.As(&dxgiDevice));

    ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
    DX::Check(dxgiDevice->GetAdapter(&dxgiAdapter));

    ComPtr<IDXGIFactory> dxgiFactory = nullptr;
    DX::Check(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf())));

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = Width;
    swapChainDesc.BufferDesc.Height = Height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2; // BackBuffer
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.OutputWindow = Application->GetWindow()->GetHWND();
    swapChainDesc.Windowed = true;

    DX::Check(dxgiFactory->CreateSwapChain(Device.Get(), &swapChainDesc, &SwapChain));
}

void URenderer::CreateRenderTargetAndDepthStencilView(int Width, int Height)
{
    ComPtr<ID3D11Texture2D> BackBuffer = nullptr;
    DX::Check(SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(BackBuffer.GetAddressOf())));
    DX::Check(Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, RenderTargetView.GetAddressOf()));

    D3D11_TEXTURE2D_DESC DepthStencilDesc = {};
    DepthStencilDesc.Width = Width;
    DepthStencilDesc.Height = Height;
    DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    DepthStencilDesc.MipLevels = 1;
    DepthStencilDesc.ArraySize = 1;
    DepthStencilDesc.SampleDesc.Count = 1;
    DepthStencilDesc.SampleDesc.Quality = 0;
    DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    ComPtr<ID3D11Texture2D> DepthStencil = nullptr;
    DX::Check(Device->CreateTexture2D(&DepthStencilDesc, nullptr, DepthStencil.GetAddressOf()));
    DX::Check(Device->CreateDepthStencilView(DepthStencil.Get(), nullptr, DepthStencilView.GetAddressOf()));

    // Binds both the render target and depth stencil to the pipeline's output merger stage
    DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());
}

void URenderer::SetViewport(int Width, int Height) const
{
    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<float>(Width);
    viewport.Height = static_cast<float>(Height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    DeviceContext->RSSetViewports(1, &viewport);
}

void URenderer::Clear()
{
    DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), ClearColor);
    DeviceContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());
}

void URenderer::Present() const
{
    DX::Check(SwapChain->Present(1, 0));
}

void URenderer::Resize(int Width, int Height)
{
    if (Width <= 0 || Height <= 0)
    {
        return;
    }

    // Release the current render target and depth stencil view
    DepthStencilView.ReleaseAndGetAddressOf();
    RenderTargetView.ReleaseAndGetAddressOf();

    // Resize the swapchain
    DX::Check(SwapChain->ResizeBuffers(2, Width, Height, DXGI_FORMAT_B8G8R8A8_UNORM, 0));

    // Creates a new render target and depth stencil view with the new window size
    CreateRenderTargetAndDepthStencilView(Width, Height);

    // Sets a new viewport with the new window size
    SetViewport(Width, Height);
}


