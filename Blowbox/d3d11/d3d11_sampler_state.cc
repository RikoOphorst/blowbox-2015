#include "../../blowbox/d3d11/d3d11_sampler_state.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11SamplerState::D3D11SamplerState(const TEXTURE_FILTERING_TYPE& type)
	{
		D3D11_SAMPLER_DESC sampler_desc;
		ZeroMemory(&sampler_desc, sizeof(sampler_desc));

		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		sampler_desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

		sampler_desc.MinLOD = 0.0f;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
		sampler_desc.MipLODBias = 0.0f;

		sampler_desc.BorderColor[0] = 0.0f;
		sampler_desc.BorderColor[1] = 0.0f;
		sampler_desc.BorderColor[2] = 0.0f;
		sampler_desc.BorderColor[3] = 0.0f;

		sampler_desc.MaxAnisotropy = 16;
		
		if (TEXTURE_FILTERING_TYPE::TEXTURE_ANISOTROPIC == type)
		{
			sampler_desc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		}
		else if (TEXTURE_FILTERING_TYPE::TEXTURE_TRILINEAR == type)
		{
			sampler_desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		}
		else if (TEXTURE_FILTERING_TYPE::TEXTURE_BILINEAR == type)
		{
			sampler_desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		}
		else if (TEXTURE_FILTERING_TYPE::TEXTURE_POINT == type)
		{
			sampler_desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		}

		D3D11RenderDevice::Instance()->GetDevice()->CreateSamplerState(&sampler_desc, &state_);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11SamplerState::~D3D11SamplerState()
	{
		BLOW_SAFE_RELEASE(state_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11SamplerState::Set(ID3D11DeviceContext* context)
	{
		/**
		* @todo Make support for setting the samplers for specific shader types
		*/

		ID3D11SamplerState* last_state_;
		context->VSGetSamplers(0, 1, &last_state_);

		if (last_state_ != state_)
		{
			context->VSSetSamplers(0, 1, &state_);
			context->PSSetSamplers(0, 1, &state_);
		}
	}
}