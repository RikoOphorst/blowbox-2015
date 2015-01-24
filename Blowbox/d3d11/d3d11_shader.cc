#include "d3d11_shader.h"

namespace blowbox
{
	D3D11Shader::D3D11Shader(std::string path)
		: vs_(NULL), vsBuffer_(NULL), ps_(NULL), psBuffer_(NULL)
	{
		Set(path);
	}

	D3D11Shader::D3D11Shader(std::string vertexShaderPath, std::string pixelShaderPath)
		: vs_(NULL), vsBuffer_(NULL), ps_(NULL), psBuffer_(NULL)
	{
		Set(vertexShaderPath, pixelShaderPath);
	}

	D3D11Shader::~D3D11Shader()
	{
		BLOW_SAFE_RELEASE(vs_);
		BLOW_SAFE_RELEASE(vsBuffer_);

		BLOW_SAFE_RELEASE(ps_);
		BLOW_SAFE_RELEASE(psBuffer_);
	}

	void D3D11Shader::Set()
	{
		vs_->Release();
		vsBuffer_->Release();

		ps_->Release();
		vsBuffer_->Release();
	}

	void D3D11Shader::Set(std::string path)
	{
		HRESULT hr = S_OK;

		BLOW_SAFE_RELEASE_NB(vs_);
		BLOW_SAFE_RELEASE_NB(vsBuffer_);
		BLOW_SAFE_RELEASE_NB(ps_);
		BLOW_SAFE_RELEASE_NB(psBuffer_);

		hr = D3DX11CompileFromFileA(path.c_str(), 0, 0, "VS", "vs_4_0", 0, 0, 0, &vsBuffer_, 0, 0);
		BLOW_ASSERT_HR(hr, "Error compiling vertex shader: " + path);

		hr = D3DX11CompileFromFileA(path.c_str(), 0, 0, "PS", "ps_4_0", 0, 0, 0, &psBuffer_, 0, 0);
		BLOW_ASSERT_HR(hr, "Error compiling pixel shader: " + path);

		hr = D3D11DisplayDevice::Instance()->GetDevice()->CreateVertexShader(vsBuffer_->GetBufferPointer(), vsBuffer_->GetBufferSize(), NULL, &vs_);
		BLOW_ASSERT_HR(hr, "Error creating vertex shader: " + path);

		hr = D3D11DisplayDevice::Instance()->GetDevice()->CreatePixelShader(psBuffer_->GetBufferPointer(), psBuffer_->GetBufferSize(), NULL, &ps_);
		BLOW_ASSERT_HR(hr, "Error creating pixel shader: " + path);
	}

	void D3D11Shader::Set(std::string vertexShaderPath, std::string pixelShaderPath)
	{
		HRESULT hr = S_OK;

		BLOW_SAFE_RELEASE_NB(vs_);
		BLOW_SAFE_RELEASE_NB(vsBuffer_);
		BLOW_SAFE_RELEASE_NB(ps_);
		BLOW_SAFE_RELEASE_NB(psBuffer_);

		hr = D3DX11CompileFromFileA(vertexShaderPath.c_str(), 0, 0, "VS", "vs_4_0", 0, 0, 0, &vsBuffer_, 0, 0);
		BLOW_ASSERT_HR(hr, "Error compiling vertex shader: " + vertexShaderPath);

		hr = D3DX11CompileFromFileA(pixelShaderPath.c_str(), 0, 0, "PS", "ps_4_0", 0, 0, 0, &psBuffer_, 0, 0);
		BLOW_ASSERT_HR(hr, "Error compiling pixel shader: " + pixelShaderPath);

		hr = D3D11DisplayDevice::Instance()->GetDevice()->CreateVertexShader(vsBuffer_->GetBufferPointer(), vsBuffer_->GetBufferSize(), NULL, &vs_);
		BLOW_ASSERT_HR(hr, "Error creating vertex shader: " + vertexShaderPath);

		hr = D3D11DisplayDevice::Instance()->GetDevice()->CreatePixelShader(psBuffer_->GetBufferPointer(), psBuffer_->GetBufferSize(), NULL, &ps_);
		BLOW_ASSERT_HR(hr, "Error creating pixel shader: " + pixelShaderPath);
	}

	ID3D11VertexShader* D3D11Shader::GetVS()
	{
		return vs_;
	}

	ID3D10Blob* D3D11Shader::GetVSBuffer()
	{
		return vsBuffer_;
	}

	ID3D11PixelShader* D3D11Shader::GetPS()
	{
		return ps_;
	}

	ID3D10Blob* D3D11Shader::GetPSBuffer()
	{
		return psBuffer_;
	}
}