#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"


class DirectXManager
{
public:
    DirectXManager();
    ~DirectXManager();

    BOOL Initialize(UINT window_width, UINT window_height, BOOL enable_fullscreen, BOOL enable_vsync, UINT msaa_count, HWND h_window);
    VOID Terminate();

    VOID StartScene(float r, float g, float b, float a);
    VOID FinishSceneAndPresent();

    ID3D11Device * GetDirectXDevice();
    ID3D11DeviceContext * GetDirectXDeviceContext();
private:
    BOOL DiscoverAdapterAndOutput();

    BOOL CreateDeviceAndContext();
    VOID DestroyDeviceAndContext();

    BOOL CheckMsaa(UINT count, UINT * quality);

    BOOL CreateSwapChain_(DXGI_MODE_DESC * mode_desc, DXGI_SAMPLE_DESC * sample_desc, HWND h_window, BOOL enable_fullscreen);
    VOID DestroySwapChain();

    VOID CreateRenderTargetView();
    VOID DestroyRenderTargetView();

    BOOL CreateDepthStencilBufferAndView(UINT width, UINT height, DXGI_SAMPLE_DESC * sample_desc);
    VOID DestroyDepthStencilBufferAndView();

    BOOL CreateDepthStencilState(BOOL depth);
    VOID DestroyDepthStencilState(BOOL depth);

    BOOL CreateRasterizerState_();
    VOID DestroyRasterizerState_();

    BOOL CreateBlendingState(BOOL with_alpha);
    VOID DestroyBlendingState(BOOL with_alpha);

    VOID BindDSViewToOM();

    BOOL CreateViewportAndBind(UINT width, UINT height);
    VOID DestroyViewport();



private:
    BOOL enableVSync_;
    DXGI_MODE_DESC * displayModes_;
    UINT displayModesCount_;
    UINT videoMemMb_;
    WCHAR videoCardDesc_[128];

    ID3D11Device * directXDevice_;
    ID3D11DeviceContext * directXDeviceContext_;

    IDXGISwapChain * swapChain_;
    ID3D11RenderTargetView * renderTargetView_;
    ID3D11Texture2D * depthStencilBuffer_;
    ID3D11DepthStencilView * depthStencilView_;
    D3D11_VIEWPORT * viewport_;

};

