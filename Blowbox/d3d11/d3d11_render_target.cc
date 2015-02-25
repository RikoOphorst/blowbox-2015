#include "../../blowbox/d3d11/d3d11_render_target.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget::D3D11RenderTarget()
	{

	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget::~D3D11RenderTarget()
	{

	}

	//------------------------------------------------------------------------------------------------------
	ID3D11Texture2D* D3D11RenderTarget::GetTarget() const
	{
		return target_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11RenderTargetView* D3D11RenderTarget::GetView() const
	{
		return view_;
	}

	//------------------------------------------------------------------------------------------------------
	ID3D11ShaderResourceView* D3D11RenderTarget::GetResource() const
	{
		return resource_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Create()
	{
		BLOW_RELEASE(target_);
		BLOW_RELEASE(view_);
		BLOW_RELEASE(resource_);

		HRESULT hr = S_OK;

		ID3D11Device* device = D3D11RenderDevice::Instance()->GetDevice();

		D3D11_TEXTURE2D_DESC desc;
		/*device->.back_buffer()->GetDesc(&desc);
		desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

		result = dev.device()->CreateTexture2D(&desc, NULL, &target_);

		SNUFF_XASSERT(result == S_OK, dev.HRToString(result, "Render Target"));

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;

		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		viewDesc.Texture2D.MipLevels = 1;
		viewDesc.Texture2D.MostDetailedMip = 0;

		result = dev.device()->CreateShaderResourceView(target_, &viewDesc, &resource_);

		SNUFF_XASSERT(result == S_OK, dev.HRToString(result, "Render Target"));

		result = dev.device()->CreateRenderTargetView(target_, NULL,
			&view_);

		SNUFF_XASSERT(result == S_OK, dev.HRToString(result, "Render Target"));*/
	}
}