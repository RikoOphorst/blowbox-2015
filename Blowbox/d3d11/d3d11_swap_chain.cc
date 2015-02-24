#include "../../blowbox/d3d11/d3d11_swap_chain.h"

#include "../../blowbox/win32/window.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11SwapChain::D3D11SwapChain(Window* window)
	{
		Initialize(window);
	};

	//------------------------------------------------------------------------------------------------------
	D3D11SwapChain::~D3D11SwapChain()
	{
		BLOW_SAFE_RELEASE(swap_chain_);
		BLOW_SAFE_RELEASE(context_);
		BLOW_SAFE_RELEASE(device_);
	};

	//------------------------------------------------------------------------------------------------------
	void D3D11SwapChain::Initialize(Window* window)
	{
		HRESULT hr = S_OK;

		RECT rect = window->GetDimensions();
		UINT width = rect.right - rect.left;
		UINT height = rect.bottom - rect.top;

		DXGI_MODE_DESC modeDesc;
		ZeroMemory(&modeDesc, sizeof(DXGI_MODE_DESC));

		modeDesc.Width = width;
		modeDesc.Height = height;
		modeDesc.RefreshRate.Numerator = 60;
		modeDesc.RefreshRate.Denominator = 1;
		modeDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		modeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		modeDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = modeDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = window->GetHandle();
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		UINT flags = 0;

#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, flags, NULL, NULL,
			D3D11_SDK_VERSION, &swapChainDesc, &swap_chain_, &device_, NULL, &context_);

		BLOW_ASSERT_HR(hr, "Error creating device & swap chain");
	};

	//------------------------------------------------------------------------------------------------------
	IDXGISwapChain* D3D11SwapChain::GetSwapChain()
	{
		return swap_chain_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11Device* D3D11SwapChain::GetDevice()
	{
		return device_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11DeviceContext* D3D11SwapChain::GetContext()
	{
		return context_;
	}
}