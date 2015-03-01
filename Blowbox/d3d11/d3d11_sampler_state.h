#pragma once

#include "../../blowbox/logging.h"
#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	enum TEXTURE_FILTERING_TYPE
	{
		TEXTURE_POINT,
		TEXTURE_BILINEAR,
		TEXTURE_TRILINEAR,
		TEXTURE_ANISOTROPIC
	};

	class D3D11SamplerState
	{
	public:
		D3D11SamplerState(const TEXTURE_FILTERING_TYPE& type);

		~D3D11SamplerState();

		void Set(ID3D11DeviceContext* context);
	private:
		ID3D11SamplerState* state_;
	};
}