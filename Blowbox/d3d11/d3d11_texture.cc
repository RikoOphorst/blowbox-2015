#include "../../blowbox/d3d11/d3d11_texture.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/win32/file_watch.h"
#include "../../blowbox/console/console.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11Texture::D3D11Texture(const std::string& path)
	{
		BLOW_RELEASE(resource_);

		path_ = path;

		Reload();
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Texture::~D3D11Texture()
	{
		BLOW_RELEASE(resource_);
	}

	//------------------------------------------------------------------------------------------------------
	bool D3D11Texture::Reload()
	{
		BLOW_RELEASE(resource_);

		HRESULT hr = S_OK;

		if (path_ != BLOW_BASE_TEXTURE)
		{
			hr = D3DX11CreateShaderResourceViewFromFileA(D3D11RenderDevice::Instance()->GetDevice(), path_.c_str(), NULL, NULL, &resource_, NULL);

			if (hr != S_OK)
			{
				Console::Instance()->Log("[TEXTURE] There was an error while loading a texture: " + path_, LOG_COLOR_TYPES::LOG_COLOR_ERROR);
				return false;
			}
			FileWatch::Instance()->Add(path_, WATCH_FILE_TYPES::WATCH_FILE_TEXTURE);
		}
		else
		{
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

			BLOW_RELEASE(resource_);

			hr = D3D11RenderDevice::Instance()->GetDevice()->CreateTexture2D(&texDesc, &initData, &texture);
			
			if (hr != S_OK)
			{
				Console::Instance()->Log("[TEXTURE] There was an error while creating the base texture", LOG_COLOR_TYPES::LOG_COLOR_ERROR);

				BLOW_RELEASE(texture);

				return false;
			}

			hr = D3D11RenderDevice::Instance()->GetDevice()->CreateShaderResourceView(texture, NULL, &resource_);
			
			if (hr != S_OK)
			{
				Console::Instance()->Log("[TEXTURE] There was an error while creating the base texture", LOG_COLOR_TYPES::LOG_COLOR_ERROR);

				BLOW_RELEASE(texture);
				return false;
			}

			BLOW_RELEASE(texture);
		}
		return true;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11ShaderResourceView* D3D11Texture::GetResource()
	{
		return resource_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Texture::Set(ID3D11DeviceContext* context, const int& slot)
	{
		ID3D11ShaderResourceView* last_resource;
		context->PSGetShaderResources(slot, 1, &last_resource);

		if (last_resource != resource_)
		{
			context->PSSetShaderResources(slot, 1, &resource_);
		}

		BLOW_RELEASE(last_resource);
	}
}