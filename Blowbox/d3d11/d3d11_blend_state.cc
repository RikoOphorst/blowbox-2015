#include "../../blowbox/d3d11/d3d11_blend_state.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11BlendState::D3D11BlendState()
	{
		HRESULT hr = S_OK;
		
		D3D11_RENDER_TARGET_BLEND_DESC render_target_blend_desc;
		ZeroMemory(&render_target_blend_desc, sizeof(render_target_blend_desc));

		D3D11_BLEND_DESC blend_desc;
		ZeroMemory(&blend_desc, sizeof(blend_desc));

		render_target_blend_desc.BlendEnable = true;
		render_target_blend_desc.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		render_target_blend_desc.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		render_target_blend_desc.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		render_target_blend_desc.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		render_target_blend_desc.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		render_target_blend_desc.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		render_target_blend_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

		blend_desc.AlphaToCoverageEnable = false;
		blend_desc.IndependentBlendEnable = false;
		blend_desc.RenderTarget[0] = render_target_blend_desc;

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateBlendState(&blend_desc, &state_);
		BLOW_ASSERT_HR(hr, "Error while creating blend state");
	}

	//------------------------------------------------------------------------------------------------------
	D3D11BlendState::~D3D11BlendState()
	{
		BLOW_SAFE_RELEASE(state_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11BlendState::Set(ID3D11DeviceContext* context)
	{
		ID3D11BlendState* last_state;
		context->OMGetBlendState(&last_state, nullptr, nullptr);

		if (last_state != state_)
		{
			context->OMSetBlendState(state_, NULL, 0x000000ff);
		}

		BLOW_RELEASE(last_state);
	}
}