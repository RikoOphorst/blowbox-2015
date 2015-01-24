#pragma once

#include "../memory/shared_ptr.h"
#include "d3d11_display_device.h"

namespace blowbox
{
	class D3D11Shader
	{
	public:
		D3D11Shader(std::string path);
		D3D11Shader(std::string vertexShaderPath, std::string pixelShaderPath);
		~D3D11Shader();

		void						Set();
		void						Set(std::string path);
		void						Set(std::string vertexShaderPath, std::string pixelShaderPath);

		ID3D11VertexShader*			GetVS();
		ID3D10Blob*					GetVSBuffer();
		ID3D11PixelShader*			GetPS();
		ID3D10Blob*					GetPSBuffer();
	private:
		ID3D11PixelShader*			ps_;
		ID3D11VertexShader*			vs_;
		ID3D10Blob*					vsBuffer_;
		ID3D10Blob*					psBuffer_;
	};
}