#include "../../blowbox/d3d11/d3d11_sampler_state.h"

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

		sampler_desc.MaxAnisotropy = 16.0f;
		
		if (TEXTURE_FILTERING_TYPE::TEXTURE_ANISOTROPIC)
		{
			sampler_desc.Filter = D3D11_FILTER::
		}
	}
}