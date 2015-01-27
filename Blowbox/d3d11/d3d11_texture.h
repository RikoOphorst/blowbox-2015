#pragma once

#include "d3d11_display_device.h"

namespace blowbox
{
	class D3D11Texture
	{
	public:
		D3D11Texture();
		D3D11Texture(std::string filePath);
		D3D11Texture(std::string filePath, std::string name);
		~D3D11Texture();

		ID3D11ShaderResourceView*		Get();
		void							Set(std::string filePath);
		void							Set();

		std::string&					GetPath();
	private:
		ID3D11ShaderResourceView*		texture_;
		std::string						path_;
	};
}