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
		RECT rect = window->GetDimensions();
		resolution_.width = static_cast<float>(rect.right - rect.left);
		resolution_.height = static_cast<float>(rect.bottom - rect.top);

		Create(window);
	};

	//------------------------------------------------------------------------------------------------------
	void D3D11SwapChain::Create(Window* window)
	{
		HRESULT hr = S_OK;

		DXGI_MODE_DESC mode_desc;
		ZeroMemory(&mode_desc, sizeof(DXGI_MODE_DESC));

		mode_desc.Width = static_cast<UINT>(resolution_.width);
		mode_desc.Height = static_cast<UINT>(resolution_.height);
		mode_desc.RefreshRate.Numerator = 60;
		mode_desc.RefreshRate.Denominator = 1;
		mode_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		mode_desc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swap_chain_desc.BufferDesc = mode_desc;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.SampleDesc.Quality = 0;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.OutputWindow = window->GetHandle();
		swap_chain_desc.Windowed = TRUE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		UINT flags = 0;

#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
#endif

		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, flags, NULL, NULL,
			D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain_, &device_, NULL, &context_);

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

	//------------------------------------------------------------------------------------------------------
	void D3D11SwapChain::SetResolution(const float& width, const float& height)
	{
		resolution_.width = width;
		resolution_.height = height;

		UINT flags = 0;

#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
#endif

		swap_chain_->ResizeBuffers(0, static_cast<UINT>(width), static_cast<UINT>(height), DXGI_FORMAT::DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	}

	//------------------------------------------------------------------------------------------------------
	const Resolution& D3D11SwapChain::GetResolution()
	{
		return resolution_;
	}
}