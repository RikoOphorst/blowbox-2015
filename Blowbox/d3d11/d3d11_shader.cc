#include "../../blowbox/d3d11/d3d11_shader.h"

#include "../../blowbox/logging.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11Shader::D3D11Shader(const std::string& path) :
		pixel_shader_(nullptr),
		pixel_shader_buffer_(nullptr),
		vertex_shader_(nullptr),
		vertex_shader_buffer_(nullptr)
	{
		SetShader(path);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Shader::~D3D11Shader()
	{
		BLOW_SAFE_RELEASE(pixel_shader_);
		BLOW_SAFE_RELEASE(pixel_shader_buffer_);
		BLOW_SAFE_RELEASE(vertex_shader_);
		BLOW_SAFE_RELEASE(vertex_shader_buffer_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Shader::SetShader(const std::string& path)
	{
		HRESULT hr = S_OK;

		BLOW_RELEASE(vertex_shader_);
		BLOW_RELEASE(vertex_shader_buffer_);
		BLOW_RELEASE(pixel_shader_);
		BLOW_RELEASE(pixel_shader_buffer_);

		hr = D3DX11CompileFromFileA(path.c_str(), 0, 0, "VS", "vs_4_0", D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, 0, &vertex_shader_buffer_, 0, 0);
		BLOW_ASSERT_HR(hr, "Error compiling vertex shader: " + path);

		hr = D3DX11CompileFromFileA(path.c_str(), 0, 0, "PS", "ps_4_0", D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, 0, &pixel_shader_buffer_, 0, 0);
		BLOW_ASSERT_HR(hr, "Error compiling pixel shader: " + path);

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateVertexShader(vertex_shader_buffer_->GetBufferPointer(), vertex_shader_buffer_->GetBufferSize(), NULL, &vertex_shader_);
		BLOW_ASSERT_HR(hr, "Error creating vertex shader: " + path);

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreatePixelShader(pixel_shader_buffer_->GetBufferPointer(), pixel_shader_buffer_->GetBufferSize(), NULL, &pixel_shader_);
		BLOW_ASSERT_HR(hr, "Error creating pixel shader: " + path);

		path_ = path;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Shader::Reload()
	{
		SetShader(path_);
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11VertexShader* D3D11Shader::GetVertexShader() const
	{
		return vertex_shader_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D10Blob* D3D11Shader::GetVertexShaderBuffer() const
	{
		return vertex_shader_buffer_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11PixelShader* D3D11Shader::GetPixelShader() const
	{
		return pixel_shader_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D10Blob* D3D11Shader::GetPixelShaderBuffer() const
	{
		return pixel_shader_buffer_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Shader::Set(ID3D11DeviceContext* context)
	{
		context->VSSetShader(vertex_shader_, 0, 0);
		context->PSSetShader(pixel_shader_, 0, 0);
	}
}