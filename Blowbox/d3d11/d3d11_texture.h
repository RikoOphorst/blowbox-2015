#pragma once

#include "d3d11_display_device.h"

#define BASE_TEXTURE std::string("")

namespace blowbox
{
	class D3D11Texture
	{
	public:
		D3D11Texture(std::string filePath);
		~D3D11Texture();

		ID3D11ShaderResourceView*		Get();
		void							Set(std::string filePath);
		void							CreateBaseTexture();

		std::string						GetPath();
	private:
		ID3D11ShaderResourceView*		texture_;
		std::string						path_;
	};
}