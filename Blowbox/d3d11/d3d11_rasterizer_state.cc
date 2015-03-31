#include "../../blowbox/d3d11/d3d11_rasterizer_state.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RasterizerState::D3D11RasterizerState() :
		fill_mode_(D3D11_FILL_MODE::D3D11_FILL_SOLID),
		cull_mode_(D3D11_CULL_MODE::D3D11_CULL_NONE)
	{
		SetFillMode(fill_mode_);
		SetCullMode(cull_mode_);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RasterizerState::D3D11RasterizerState(const D3D11_FILL_MODE& fill, const D3D11_CULL_MODE& cull) :
		fill_mode_(fill),
		cull_mode_(cull)
	{
		SetFillMode(fill_mode_);
		SetCullMode(cull_mode_);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RasterizerState::~D3D11RasterizerState()
	{
		BLOW_SAFE_RELEASE(state_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RasterizerState::Set(ID3D11DeviceContext* context)
	{
		ID3D11RasterizerState* last_state;
		context->RSGetState(&last_state);
		
		if (last_state != state_)
		{
			context->RSSetState(state_);
		}

		BLOW_RELEASE(last_state);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RasterizerState::SetCullMode(const D3D11_CULL_MODE& cull)
	{
		BLOW_RELEASE(state_);
		
		HRESULT hr = S_OK;

		D3D11_RASTERIZER_DESC rasterizer_desc;
		ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizer_desc.FillMode = fill_mode_;
		rasterizer_desc.CullMode = cull_mode_ = cull;
		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateRasterizerState(&rasterizer_desc, &state_);
		BLOW_ASSERT_HR(hr, "Error while creating rasterizer state for cull mode change");
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RasterizerState::SetFillMode(const D3D11_FILL_MODE& fill)
	{
		BLOW_RELEASE(state_);
		
		HRESULT hr = S_OK;

		D3D11_RASTERIZER_DESC rasterizer_desc;
		ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizer_desc.FillMode = fill_mode_ = fill;
		rasterizer_desc.CullMode = cull_mode_;
		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateRasterizerState(&rasterizer_desc, &state_);
		BLOW_ASSERT_HR(hr, "Error while creating rasterizer state for fill mode change");
	}

	//------------------------------------------------------------------------------------------------------
	const D3D11_CULL_MODE& D3D11RasterizerState::GetCullMode() const
	{
		return cull_mode_;
	}

	//------------------------------------------------------------------------------------------------------
	const D3D11_FILL_MODE& D3D11RasterizerState::GetFillMode() const
	{
		return fill_mode_;
	}
}