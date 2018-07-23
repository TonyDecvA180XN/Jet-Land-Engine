#include "DirectXManager.h"

DirectXManager::DirectXManager()
{
    enableVSync_ = FALSE;
    displayModesCount_ = 0;
    videoMemMb_ = 0;
    ZeroMemory(videoCardDesc_, sizeof videoCardDesc_);

    displayModes_ = NULL;
    directXDevice_ = NULL;
    directXDeviceContext_ = NULL;
    swapChain_ = NULL;
    renderTargetView_ = NULL;
    depthStencilBuffer_ = NULL;
    depthStencilView_ = NULL;
    viewport_ = NULL;
}

DirectXManager::~DirectXManager()
{

}

BOOL DirectXManager::Initialize(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window)
{
    enableVSync_ = enable_vsync;

    BOOL result;
    result = DiscoverAdapterAndOutput();
    if (!result) { return FALSE; }
    INT iMatchingMode = -1;
    for (int i = 0; i != displayModesCount_; i++)
    {
        if (displayModes_[i].Width == window_width)
        {
            if (displayModes_[i].Height == window_height)
            {
                iMatchingMode = i;
                break;
            }
        }
    }
    if (iMatchingMode == -1)
    {
        if (enable_fullscreen)
        {
            iMatchingMode = displayModesCount_ - 1;
        }
        else
        {
            iMatchingMode = 0;
        }
    }
    DXGI_MODE_DESC mode = displayModes_[iMatchingMode];
    if (!enableVSync_)
    {
        mode.RefreshRate.Numerator = 0;
        mode.RefreshRate.Denominator = 1;
    }

    result = CreateDeviceAndContext();
    if (!result) { return FALSE; }

    DXGI_SAMPLE_DESC sample;
    result = CheckMsaa(msaa_count, &sample.Quality);
    if (result)
    {
        sample.Count = msaa_count;
        if (sample.Quality > 0)
        { 
            sample.Quality--;
        } else
        {
            sample.Quality = 0;
            sample.Count = 1;
        }
    }
    else
    {
        sample.Count = 1;
        sample.Quality = 0;
    }

    result = CreateSwapChain_(&mode, &sample, h_window, enable_fullscreen);
    if (!result) { return FALSE; }

    CreateRenderTargetView();

    result = CreateDepthStencilBufferAndView(window_width, window_height, &sample);
    if (!result) { return FALSE; }

    BindDSViewToOM();

    CreateViewportAndBind(window_width, window_height);

    return TRUE;
}


VOID DirectXManager::Terminate()
{
    DestroyDepthStencilBufferAndView();
    DestroyRenderTargetView();
    DestroyDeviceAndContext();
    DestroySwapChain();
}


VOID DirectXManager::StartScene(float r, float g, float b, float a)
{
    float color[4] = { r, g ,b, a };
    directXDeviceContext_->ClearRenderTargetView(renderTargetView_, color);
    directXDeviceContext_->ClearDepthStencilView(depthStencilView_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

VOID DirectXManager::FinishSceneAndPresent()
{
    if (enableVSync_)
    {
        swapChain_->Present(1, 0);
    }
    else
    {
        swapChain_->Present(0, 0);
    }
}

BOOL DirectXManager::DiscoverAdapterAndOutput()
{
    HRESULT result;

    IDXGIFactory * factory;
    result = CreateDXGIFactory(__uuidof(IDXGIFactory), (VOID **)(&factory));
    if (FAILED(result)) { return FALSE; }

    IDXGIAdapter * adapter;
    result = factory->EnumAdapters(0, &adapter);
    if (FAILED(result)) { return FALSE; }

    IDXGIOutput * monitor;
    result = adapter->EnumOutputs(0, &monitor);
    if (FAILED(result)) { return FALSE; }

    result = monitor->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayModesCount_, NULL);
    if (FAILED(result)) { return FALSE; }

    displayModes_ = new DXGI_MODE_DESC[displayModesCount_];
    if (!displayModes_) { return FALSE; }

    result = monitor->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayModesCount_, displayModes_);
    if (FAILED(result)) { return FALSE; }


    DXGI_ADAPTER_DESC adapterDesc;
    result = adapter->GetDesc(&adapterDesc);
    if (FAILED(result)) { return FALSE; }

    videoMemMb_ = UINT(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
    errno_t error = wcscpy_s(videoCardDesc_, 128, adapterDesc.Description);
    if (error) { return FALSE; }

    monitor->Release();
    monitor = NULL;

    adapter->Release();
    adapter = NULL;

    factory->Release();
    factory = NULL;

    return TRUE;
}

BOOL DirectXManager::CreateDeviceAndContext()
{
    UINT deviceCreationFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL featureLevel;
    HRESULT result = D3D11CreateDevice(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        deviceCreationFlags,
        NULL,
        0,
        D3D11_SDK_VERSION,
        &directXDevice_,
        &featureLevel,
        &directXDeviceContext_
    );
    if (FAILED(result)) { return FALSE; }
    if (featureLevel != D3D_FEATURE_LEVEL_11_0) { return FALSE; }

    return TRUE;
}

VOID DirectXManager::DestroyDeviceAndContext()
{
    if (directXDeviceContext_)
    {
        directXDeviceContext_->Release();
        directXDeviceContext_ = NULL;
    }
    if (directXDevice_)
    {
        directXDevice_->Release();
        directXDevice_ = NULL;
    }
}

BOOL DirectXManager::CheckMsaa(UINT count, UINT * quality)
{
    HRESULT result = directXDevice_->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, count, quality);
    return SUCCEEDED(result);
}

BOOL DirectXManager::CreateSwapChain_(DXGI_MODE_DESC * mode_desc, DXGI_SAMPLE_DESC * sample_desc, HWND h_window, BOOL enable_fullscreen)
{
    DXGI_SWAP_CHAIN_DESC description;
    description.BufferDesc = *mode_desc;
    description.SampleDesc = *sample_desc;
    description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    description.BufferCount = 1;
    description.OutputWindow = h_window;
    description.Windowed = !enable_fullscreen;
    description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    description.Flags = 0;

    HRESULT result;

    IDXGIDevice * device;
    result = directXDevice_->QueryInterface(__uuidof(IDXGIDevice), (VOID **)(&device));
    if (FAILED(result)) { return FALSE; }

    IDXGIAdapter * adapter;
    result = device->GetParent(__uuidof(IDXGIAdapter), (VOID **)(&adapter));
    if (FAILED(result)) { return FALSE; }

    IDXGIFactory * factory;
    result = adapter->GetParent(__uuidof(IDXGIFactory), (VOID **)(&factory));
    if (FAILED(result)) { return FALSE; }

    result = factory->CreateSwapChain(directXDevice_, &description, &swapChain_);
    if (FAILED(result)) { return FALSE; }

    device->Release();
    device = NULL;
    adapter->Release();
    adapter = NULL;
    factory->Release();
    factory = NULL;

    return TRUE;
}

VOID DirectXManager::DestroySwapChain()
{
    if (swapChain_)
    {
        swapChain_->SetFullscreenState(FALSE, NULL);
        swapChain_->Release();
        swapChain_ = NULL;
    }
}

VOID DirectXManager::CreateRenderTargetView()
{
    ID3D11Texture2D * backBuffer;
    swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (VOID **)(&backBuffer));
#pragma warning(suppress: 6387)
    directXDevice_->CreateRenderTargetView(backBuffer, NULL, &renderTargetView_);
    backBuffer->Release();
}

VOID DirectXManager::DestroyRenderTargetView()
{
    renderTargetView_->Release();
    renderTargetView_ = NULL;
}

BOOL DirectXManager::CreateDepthStencilBufferAndView(UINT width, UINT height, DXGI_SAMPLE_DESC * sample_desc)
{
    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    depthStencilBufferDesc.Width = width;
    depthStencilBufferDesc.Height = height;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilBufferDesc.SampleDesc = *sample_desc;
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;

    HRESULT result;
    result = directXDevice_->CreateTexture2D(&depthStencilBufferDesc, NULL, &depthStencilBuffer_);
    if (FAILED(result)) { return FALSE; }

    result = directXDevice_->CreateDepthStencilView(depthStencilBuffer_, NULL, &depthStencilView_);
    if (FAILED(result)) { return FALSE; }

    return TRUE;
}

VOID DirectXManager::DestroyDepthStencilBufferAndView()
{
    if (depthStencilView_)
    {
        depthStencilView_->Release();
        depthStencilView_ = NULL;
    }
    if (depthStencilBuffer_)
    {
        depthStencilBuffer_->Release();
        depthStencilBuffer_ = NULL;
    }
}


BOOL DirectXManager::CreateDepthStencilState(BOOL depth)
{
    // TODO : Implement this
    return TRUE;
}

VOID DirectXManager::DestroyDepthStencilState(BOOL depth)
{
    // TODO : Implement this
}

BOOL DirectXManager::CreateRasterizerState_()
{
    // TODO : Implement this
    return TRUE;
}

VOID DirectXManager::DestroyRasterizerState_()
{
    // TODO : Implement this
}

BOOL DirectXManager::CreateBlendingState(BOOL with_alpha)
{
    // TODO : Implement this
    return TRUE;
}

VOID DirectXManager::DestroyBlendingState(BOOL with_alpha)
{
    // TODO : Implement this
}

VOID DirectXManager::BindDSViewToOM()
{
    directXDeviceContext_->OMSetRenderTargets(1, &renderTargetView_, depthStencilView_);
}

BOOL DirectXManager::CreateViewportAndBind(UINT width, UINT height)
{
    viewport_ = new D3D11_VIEWPORT;
    if (!viewport_) { return FALSE; }

    viewport_->Width = float(width);
    viewport_->Height = float(height);
    viewport_->MinDepth = 0.0f;
    viewport_->MaxDepth = 1.0f;
    viewport_->TopLeftX = 0.0f;
    viewport_->TopLeftY = 0.0f;

    directXDeviceContext_->RSSetViewports(1, viewport_);

    return TRUE;
}

VOID DirectXManager::DestroyViewport()
{
    if (viewport_)
    {
        delete viewport_;
        viewport_ = NULL;
    }
}

ID3D11Device * DirectXManager::GetDirectXDevice()
{
    return directXDevice_;
}

ID3D11DeviceContext * DirectXManager::GetDirectXDeviceContext()
{
    return directXDeviceContext_;
}
