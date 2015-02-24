#include "../../blowbox/d3d11/d3d11_render_device.h"

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/d3d11/d3d11_blend_state.h"
#include "../../blowbox/d3d11/d3d11_camera.h"
#include "../../blowbox/d3d11/d3d11_constant_buffer.h"
#include "../../blowbox/d3d11/d3d11_depth_stencil.h"
#include "../../blowbox/d3d11/d3d11_index_buffer.h"
#include "../../blowbox/d3d11/d3d11_input_layout.h"
#include "../../blowbox/d3d11/d3d11_render_element.h"
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
	D3D11RenderDevice::D3D11RenderDevice()
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderDevice::~D3D11RenderDevice()
	{

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
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::BeginDraw()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::Draw()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::EndDraw()
	{

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