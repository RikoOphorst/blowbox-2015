#include "../../blowbox/d3d11/d3d11_render_device.h"

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/d3d11/d3d11_blend_state.h"
#include "../../blowbox/d3d11/d3d11_camera.h"
#include "../../blowbox/d3d11/d3d11_constant_buffer.h"
#include "../../blowbox/d3d11/d3d11_depth_stencil.h"
#include "../../blowbox/d3d11/d3d11_index_buffer.h"
#include "../../blowbox/d3d11/d3d11_input_layout.h"
#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/d3d11/d3d11_render_target.h"
#include "../../blowbox/d3d11/d3d11_sampler_state.h"
#include "../../blowbox/d3d11/d3d11_shader.h"
#include "../../blowbox/d3d11/d3d11_swap_chain.h"
#include "../../blowbox/d3d11/d3d11_texture.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_viewport.h"

#include "../../blowbox/win32/window.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderDevice::D3D11RenderDevice() :
		context_(nullptr),
		device_(nullptr),
		back_buffer_(nullptr),
		back_buffer_view_(nullptr)
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderDevice::~D3D11RenderDevice()
	{
		BLOW_SAFE_RELEASE(back_buffer_);
		BLOW_SAFE_RELEASE(back_buffer_view_);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderDevice* D3D11RenderDevice::Instance()
	{
		static SharedPtr<D3D11RenderDevice> ptr(new D3D11RenderDevice());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::Initialize(Window* window)
	{
		swap_chain_ = new D3D11SwapChain(window);
		context_ = swap_chain_->GetContext();
		device_ = swap_chain_->GetDevice();

		CreateBackBuffer();

		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		DXGI_SWAP_CHAIN_DESC desc;
		swap_chain_->GetSwapChain()->GetDesc(&desc);

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (FLOAT)desc.BufferDesc.Width;
		viewport.Height = (FLOAT)desc.BufferDesc.Height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		context_->RSSetViewports(1, &viewport);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::DrawRenderTargets()
	{
		context_->ClearRenderTargetView(back_buffer_view_, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		std::map<std::string, D3D11RenderTarget*>::iterator it = render_targets_.begin();
		while (it != render_targets_.end())
		{
			
		}

		swap_chain_->GetSwapChain()->Present(1, 0);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateBackBuffer()
	{
		HRESULT hr = S_OK;

		hr = swap_chain_->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer_);
		BLOW_ASSERT_HR(hr, "Error while creating back buffer");

		hr = swap_chain_->GetDevice()->CreateRenderTargetView(back_buffer_, 0, &back_buffer_view_);
		BLOW_ASSERT_HR(hr, "Error while creating back buffer view");
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11Device* D3D11RenderDevice::GetDevice() const
	{
		return swap_chain_.get()->GetDevice();
	}
}