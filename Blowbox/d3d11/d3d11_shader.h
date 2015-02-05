#pragma once

#include "d3d11_display_device.h"

#define BASE_SHADER std::string("shaders/effects.fx")

namespace blowbox
{
	class D3D11Shader
	{
	public:
		D3D11Shader(std::string path);
		~D3D11Shader();

		void						Set(std::string path);

		ID3D11VertexShader*			GetVS();
		ID3D10Blob*					GetVSBuffer();
		ID3D11PixelShader*			GetPS();
		ID3D10Blob*					GetPSBuffer();
		std::string					GetPath();
	private:
		ID3D11PixelShader*			ps_;
		ID3D11VertexShader*			vs_;
		ID3D10Blob*					vsBuffer_;
		ID3D10Blob*					psBuffer_;
		std::string					path_;
	};
}