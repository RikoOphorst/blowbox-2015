#include "d3d11_texture.h"

namespace blowbox
{
	D3D11Texture::D3D11Texture()
		: texture_(nullptr)
	{
		Set();
		SetName(std::to_string(++id()));
	}

	D3D11Texture::D3D11Texture(std::string filePath)
		: texture_(nullptr)
	{
		Set(filePath);
		SetName(filePath);
	}

	D3D11Texture::D3D11Texture(std::string filePath, std::string name)
		: texture_(nullptr)
	{
		Set(filePath);
		SetName(name);
	}

	D3D11Texture::~D3D11Texture()
	{
		texture_->Release();
	}

	ID3D11ShaderResourceView* D3D11Texture::Get()
	{
		return texture_;
	}

	void D3D11Texture::Set()
	{
		HRESULT hr = S_OK;
		
		ID3D11Texture2D* texture;
		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.ArraySize = 1;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		texDesc.Width = 1;
		texDesc.Height = 1;
		texDesc.MipLevels = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.MiscFlags = 0;

		D3DXCOLOR data(1.0f, 1.0f, 1.0f, 1.0f);
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = data;
		initData.SysMemPitch = sizeof(data);
		initData.SysMemSlicePitch = sizeof(data);

		if (texture_ != NULL)
		{
			texture_->Release();
		}

		hr = D3D11DisplayDevice::Instance()->GetDevice()->CreateTexture2D(&texDesc, &initData, &texture);
		BLOW_ASSERT_HR(hr, "Error creating texture");

		hr = D3D11DisplayDevice::Instance()->GetDevice()->CreateShaderResourceView(texture, NULL, &texture_);
		BLOW_ASSERT_HR(hr, "Error creating resource view");

		texture->Release();
	}

	void D3D11Texture::Set(std::string filePath)
	{	
		if (texture_ != NULL)
		{
			texture_->Release();
		}
		
		HRESULT hr = S_OK;

		hr = D3DX11CreateShaderResourceViewFromFileA(D3D11DisplayDevice::Instance()->GetDevice(), filePath.c_str(), NULL, NULL, &texture_, NULL);

		BLOW_ASSERT_HR(hr, "There was an error loading a texture, filepath: " + filePath);

		FileWatch::Instance()->Add(filePath, FileType::Texture);
	}

	std::string& D3D11Texture::GetName()
	{
		return name_;
	}

	void D3D11Texture::SetName(std::string name)
	{
		name_ = name;
	}

	int& D3D11Texture::id()
	{
		static int id_ = 0;
		return id_;
	}

}