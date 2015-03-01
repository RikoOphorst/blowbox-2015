#include "../../blowbox/d3d11/d3d11_render_target.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_render_queue.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget::D3D11RenderTarget()
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget::~D3D11RenderTarget()
	{
		BLOW_SAFE_RELEASE(target_);
		BLOW_SAFE_RELEASE(view_);
		BLOW_RELEASE(resource_);
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11Texture2D* D3D11RenderTarget::GetTarget() const
	{
		return target_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11RenderTargetView* D3D11RenderTarget::GetView() const
	{
		return view_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11ShaderResourceView* D3D11RenderTarget::GetResource() const
	{
		return resource_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Create(RENDER_TARGET_TYPE type, IDXGISwapChain* swap_chain, ID3D11Device* device)
	{
		HRESULT hr = S_OK;

		if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER == type)
		{
			type_ = type;
			
			hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&target_);
			BLOW_ASSERT_HR(hr, "Error while creating back buffer");

			hr = device->CreateRenderTargetView(target_, 0, &view_);
			BLOW_ASSERT_HR(hr, "Error while creating back buffer view");
		}
		else if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_RENDER_TARGET == type)
		{
			type_ = type;

			D3D11_TEXTURE2D_DESC target_desc;
			D3D11RenderDevice::Instance()->GetBackBuffer()->GetTarget()->GetDesc(&target_desc);
			target_desc.BindFlags |= D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
			
			hr = device->CreateTexture2D(&target_desc, NULL, &target_);
			BLOW_ASSERT_HR(hr, "Error while creating render target texture");

			D3D11_SHADER_RESOURCE_VIEW_DESC view_desc;
			view_desc.ViewDimension = D3D_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;
			view_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
			view_desc.Texture2D.MipLevels = 1;
			view_desc.Texture2D.MostDetailedMip = 0;

			hr = device->CreateShaderResourceView(target_, &view_desc, &resource_);
			BLOW_ASSERT_HR(hr, "Error while creating resource view for render target");

			hr = device->CreateRenderTargetView(target_, NULL, &view_);
			BLOW_ASSERT_HR(hr, "Error while creating render target view");

			queue_ = new D3D11RenderQueue();
		}
		else
		{
			BLOW_BREAK("Unknown RenderTargetType");
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Set(ID3D11DeviceContext* context)
	{
		context->OMSetRenderTargets(1, &view_, NULL);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Draw(ID3D11DeviceContext* context)
	{
		queue_->Draw(context);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Clear(ID3D11DeviceContext* context)
	{	
		if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER == type_)
		{
			context->ClearRenderTargetView(view_, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_RENDER_TARGET == type_)
		{
			context->ClearRenderTargetView(view_, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderQueue* D3D11RenderTarget::GetQueue()
	{
		return queue_.get();
	}
}