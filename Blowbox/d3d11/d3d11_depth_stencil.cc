#include "../../blowbox/d3d11/d3d11_depth_stencil.h"

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_settings.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11DepthStencil::D3D11DepthStencil()
	{
		Create();
	}

	//------------------------------------------------------------------------------------------------------
	D3D11DepthStencil::~D3D11DepthStencil()
	{
		BLOW_SAFE_RELEASE(state_);
		BLOW_SAFE_RELEASE(view_);
		BLOW_SAFE_RELEASE(buffer_);
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11DepthStencilState* D3D11DepthStencil::GetState()
	{
		return state_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11DepthStencilView* D3D11DepthStencil::GetView()
	{
		return view_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11Texture2D* D3D11DepthStencil::GetBuffer()
	{
		return buffer_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11DepthStencil::Set(ID3D11DeviceContext* context)
	{
		ID3D11DepthStencilState* last_state;
		context->OMGetDepthStencilState(&last_state, NULL);

		if (last_state != state_)
		{
			context->OMSetDepthStencilState(state_, NULL);
		}

		BLOW_RELEASE(last_state);
	}

	void D3D11DepthStencil::Create()
	{
		HRESULT hr = S_OK;

		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		D3D11RenderDevice::Instance()->GetSwapChain()->GetDesc(&swap_chain_desc);

		D3D11_TEXTURE2D_DESC texture_desc;
		ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));

		texture_desc.Width = (UINT)D3D11Settings::Instance()->GetResolution().width;
		texture_desc.Height = (UINT)D3D11Settings::Instance()->GetResolution().height;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;
		texture_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		texture_desc.SampleDesc.Count = 1;
		texture_desc.SampleDesc.Quality = 0;
		texture_desc.Usage = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		texture_desc.CPUAccessFlags = 0;
		texture_desc.MiscFlags = 0;

		buffer_ = nullptr;
		view_ = nullptr;

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateTexture2D(&texture_desc, NULL, &buffer_);
		BLOW_ASSERT_HR(hr, "Error creating Texture2D for depth stencil");

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateDepthStencilView(buffer_, NULL, &view_);
		BLOW_ASSERT_HR(hr, "Error creating depth stencil view");

		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;

		// Depth test parameters
		depth_stencil_desc.DepthEnable = true;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;

		depth_stencil_desc.StencilEnable = true;
		depth_stencil_desc.StencilReadMask = 0xFF;
		depth_stencil_desc.StencilWriteMask = 0xFF;

		depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_INCR;
		depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

		depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_DECR;
		depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateDepthStencilState(&depth_stencil_desc, &state_);
		BLOW_ASSERT_HR(hr, "Error creating depth stencil state");
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11DepthStencil::Release()
	{
		BLOW_RELEASE(state_);
		BLOW_RELEASE(view_);
		BLOW_RELEASE(buffer_);
	}
}