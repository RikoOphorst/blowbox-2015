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
		buffer_type_(BUFFER_TYPE::BUFFER_TYPE_UNKNOWN)
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
		swap_chain_manager_ = new D3D11SwapChain(window);
		swap_chain_ = swap_chain_manager_->GetSwapChain();
		context_ = swap_chain_manager_->GetContext();
		device_ = swap_chain_manager_->GetDevice();

		viewport_ = new D3D11Viewport();
		viewport_->Set();

		back_buffer_ = new D3D11RenderTarget();
		back_buffer_->Create(RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER, swap_chain_, device_);

		screen_quad_ = new D3D11VertexBuffer();

		screen_quad_->Create(
			{
				{ XMFLOAT4(-1.0f, -1.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
				{ XMFLOAT4(-1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
				{ XMFLOAT4(1.0f, -1.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
				{ XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }
			}, 
			{ 0, 1, 2, 3 },
			D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, 
			BUFFER_TYPE::BUFFER_TYPE_QUAD
		);

		target_ = new D3D11RenderTarget();
		target_->Create(RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_RENDER_TARGET, swap_chain_, device_);

		default_shader_ = new D3D11Shader(std::string("shaders/base.fx"));

		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOUR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT stride = sizeof(layout);
		input_layout_ = new D3D11InputLayout(layout, stride, default_shader_.get());

		input_layout_->Set(context_);

		AddRenderTarget(std::string("hurdur"), target_.get());
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::Draw()
	{
		back_buffer_->Clear(context_);

		context_->VSSetShader(default_shader_->GetVertexShader(), 0, 0);
		context_->PSSetShader(default_shader_->GetPixelShader(), 0, 0);

		for (auto it = render_targets_.begin(); it != render_targets_.end(); it++)
		{
			DrawRenderTarget(it->second);
		}

		swap_chain_->Present(1, 0);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::DrawRenderTarget(D3D11RenderTarget* render_target)
	{
		render_target->Clear(context_);
		render_target->Set(context_);
		render_target->Draw(context_);

		back_buffer_->Set(context_);

		screen_quad_->Set(context_);

		screen_quad_->Draw(context_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::AddRenderTarget(const std::string& name, D3D11RenderTarget* render_target)
	{
		render_targets_.emplace(name, render_target);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget* D3D11RenderDevice::GetRenderTarget(const std::string& name)
	{
		return render_targets_.find(name)->second;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11Device* D3D11RenderDevice::GetDevice() const
	{
		return device_;
	}

	//------------------------------------------------------------------------------------------------------
	IDXGISwapChain* D3D11RenderDevice::GetSwapChain() const
	{
		return swap_chain_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11DeviceContext* D3D11RenderDevice::GetContext() const
	{
		return context_;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Viewport* D3D11RenderDevice::GetViewport() const
	{
		return viewport_.get();
	}

	//------------------------------------------------------------------------------------------------------
	const BUFFER_TYPE& D3D11RenderDevice::GetBufferType() const
	{
		return buffer_type_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::SetBufferType(const BUFFER_TYPE& buffer_type)
	{
		buffer_type_ = buffer_type;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget* D3D11RenderDevice::GetBackBuffer() const
	{
		return back_buffer_.get();
	}
}