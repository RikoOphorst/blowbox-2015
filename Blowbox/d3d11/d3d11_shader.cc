#include "../../blowbox/d3d11/d3d11_shader.h"

#include "../../blowbox/logging.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/console/console.h"
#include "../../blowbox/win32/file_watch.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11Shader::D3D11Shader(const std::string& path) :
		pixel_shader_(nullptr),
		pixel_shader_buffer_(nullptr),
		vertex_shader_(nullptr),
		vertex_shader_buffer_(nullptr)
	{
		path_ = path;

		Reload();
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
	void D3D11Shader::Reload()
	{
		HRESULT hr = S_OK;

		BLOW_RELEASE(vertex_shader_);
		BLOW_RELEASE(vertex_shader_buffer_);
		BLOW_RELEASE(pixel_shader_);
		BLOW_RELEASE(pixel_shader_buffer_);

		ID3D10Blob* errors;
		ZeroMemory(&errors, sizeof(errors));

		hr = D3DX11CompileFromFileA(path_.c_str(), 0, 0, "VS", "vs_4_0", D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, 0, &vertex_shader_buffer_, &errors, 0);
		if (hr != S_OK)
		{
			const char* error = static_cast<const char*>(errors->GetBufferPointer());
			Console::Instance()->Log("[SHADER] Error compiling shader (" + path_ + "), this is the error message:\n\n" + error, LOG_COLOR_TYPES::LOG_COLOR_ERROR);
			return;
		}

		hr = D3DX11CompileFromFileA(path_.c_str(), 0, 0, "PS", "ps_4_0", D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, 0, &pixel_shader_buffer_, &errors, 0);
		if (hr != S_OK)
		{
			const char* error = static_cast<const char*>(errors->GetBufferPointer());
			Console::Instance()->Log("[SHADER] Error compiling shader (" + path_ + "), this is the error message:\n\n" + error, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

			return;
		}

		//------------------------------------ Shader creation ---------------------------------------------
		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateVertexShader(vertex_shader_buffer_->GetBufferPointer(), vertex_shader_buffer_->GetBufferSize(), NULL, &vertex_shader_);
		BLOW_ASSERT_HR(hr, "Error creating vertex shader: " + path_);

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreatePixelShader(pixel_shader_buffer_->GetBufferPointer(), pixel_shader_buffer_->GetBufferSize(), NULL, &pixel_shader_);
		BLOW_ASSERT_HR(hr, "Error creating pixel shader: " + path_);

		FileWatch::Instance()->Add(path_, WATCH_FILE_TYPES::WATCH_FILE_SHADER);
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