#include "../../blowbox/d3d11/d3d11_render_device.h"

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/d3d11/d3d11_blend_state.h"
#include "../../blowbox/d3d11/d3d11_camera.h"
#include "../../blowbox/d3d11/d3d11_constant_buffer.h"
#include "../../blowbox/d3d11/d3d11_depth_stencil.h"
#include "../../blowbox/d3d11/d3d11_input_layout.h"
#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/d3d11/d3d11_render_target.h"
#include "../../blowbox/d3d11/d3d11_render_queue.h"
#include "../../blowbox/d3d11/d3d11_sampler_state.h"
#include "../../blowbox/d3d11/d3d11_shader.h"
#include "../../blowbox/d3d11/d3d11_swap_chain.h"
#include "../../blowbox/d3d11/d3d11_texture.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_viewport.h"
#include "../../blowbox/content/content_manager.h"

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
		CreateSwapChain(window);

		CreateViewport();

		CreateBackBuffer();

		CreateInputLayout();

		CreateScreenQuad();
		
		CreateGlobalBuffer();

		CreateObjectBuffer();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateSwapChain(Window* window)
	{
		swap_chain_manager_ = new D3D11SwapChain(window);
		swap_chain_ = swap_chain_manager_->GetSwapChain();
		context_ = swap_chain_manager_->GetContext();
		device_ = swap_chain_manager_->GetDevice();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateViewport()
	{
		viewport_ = new D3D11Viewport();
		viewport_->Set();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateBackBuffer()
	{
		back_buffer_ = new D3D11RenderTarget();
		back_buffer_->Create(RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER, swap_chain_, device_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateScreenQuad()
	{
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
			BUFFER_TYPE::BUFFER_TYPE_UNKNOWN
		);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateInputLayout()
	{
		default_shader_ = ContentManager::Instance()->GetShader(BLOW_BASE_SHADER);
		
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOUR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT stride = sizeof(layout);
		input_layout_ = new D3D11InputLayout(layout, stride, default_shader_);

		input_layout_->Set(context_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateGlobalBuffer()
	{
		global_buffer_ = new D3D11ConstantBuffer();
		global_buffer_->Create(CONSTANT_BUFFER_TYPE::CONSTANT_BUFFER_GLOBAL);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::CreateObjectBuffer()
	{
		per_object_buffer_ = new D3D11ConstantBuffer();
		per_object_buffer_->Create(CONSTANT_BUFFER_TYPE::CONSTANT_BUFFER_OBJECT);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::Draw(D3D11Camera* camera)
	{
		if (camera == nullptr)
		{
			return;
		}
		
		back_buffer_->Clear(context_);

		global_buffer_->Map(context_, {
			0.0f,
			camera->GetView(),
			camera->GetProjection()
		});
		global_buffer_->Set(context_, 0);

		default_shader_->Set(context_);

		for (auto it = render_targets_.begin(); it != render_targets_.end(); ++it)
		{
			if (it->second->GetQueue()->GetElements().size() > 0)
			{
				DrawRenderTarget(it->second);
			}
		}

		swap_chain_->Present(D3D11Settings::Instance()->GetVSync(), 0);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::DrawRenderTarget(D3D11RenderTarget* render_target)
	{
		render_target->Clear(context_);
		render_target->Set(context_);
		render_target->Draw(context_);

		back_buffer_->Set(context_);

		screen_quad_->Set(context_);

		ID3D11ShaderResourceView* resource = render_target->GetResource();
		context_->PSSetShaderResources(0, 1, &resource);

		render_target->ApplyShader(context_);
		render_target->ApplyBlendState(context_);
		screen_quad_->Draw(context_);

		ID3D11ShaderResourceView* buffer[] = { NULL };
		context_->PSSetShaderResources(0, 1, buffer);
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
	D3D11Viewport* D3D11RenderDevice::GetViewport()
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
	D3D11RenderTarget* D3D11RenderDevice::GetBackBuffer()
	{
		return back_buffer_.get();
	}

	//------------------------------------------------------------------------------------------------------
	D3D11ConstantBuffer* D3D11RenderDevice::GetObjectBuffer()
	{
		return per_object_buffer_.get();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderDevice::SetResolution(const float& width, const float& height)
	{
		back_buffer_->Release();

		for (auto it = render_targets_.begin(); it != render_targets_.end(); it++)
		{
			it->second->Release();
		}

		swap_chain_manager_->SetResolution(width, height);

		back_buffer_->Create(RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER, swap_chain_, device_);
		back_buffer_->RecreateDepthStencil();

		for (auto it = render_targets_.begin(); it != render_targets_.end(); it++)
		{
			it->second->Create(RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_RENDER_TARGET, swap_chain_, device_);
			it->second->RecreateDepthStencil();
		}

		viewport_->SetResolution(width, height);
		viewport_->Set();
	}
}