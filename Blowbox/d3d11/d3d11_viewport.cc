#include "../../blowbox/d3d11/d3d11_viewport.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11Viewport::D3D11Viewport()
	{
		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		D3D11RenderDevice::Instance()->GetSwapChain()->GetDesc(&swap_chain_desc);

		viewport_.TopLeftX = 0.0f;
		viewport_.TopLeftY = 0.0f;
		viewport_.Width = static_cast<float>(swap_chain_desc.BufferDesc.Width);
		viewport_.Height = static_cast<float>(swap_chain_desc.BufferDesc.Height);
		viewport_.MinDepth = 0.0f;
		viewport_.MaxDepth = 1.0f;

		resolution_ = { static_cast<float>(swap_chain_desc.BufferDesc.Width), static_cast<float>(swap_chain_desc.BufferDesc.Height) };
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Viewport::D3D11Viewport(float minDepth, float maxDepth)
	{
		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		D3D11RenderDevice::Instance()->GetSwapChain()->GetDesc(&swap_chain_desc);

		viewport_.TopLeftX = 0.0f;
		viewport_.TopLeftY = 0.0f;
		viewport_.Width = static_cast<float>(swap_chain_desc.BufferDesc.Width);
		viewport_.Height = static_cast<float>(swap_chain_desc.BufferDesc.Height);
		viewport_.MinDepth = minDepth;
		viewport_.MaxDepth = maxDepth;

		resolution_ = { static_cast<float>(swap_chain_desc.BufferDesc.Width), static_cast<float>(swap_chain_desc.BufferDesc.Height) };
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Viewport::D3D11Viewport(float x, float y, float width, float height, float minDepth, float maxDepth)
	{
		viewport_.TopLeftX = x;
		viewport_.TopLeftY = y;
		viewport_.Width = width;
		viewport_.Height = height;
		viewport_.MinDepth = minDepth;
		viewport_.MaxDepth = maxDepth;

		resolution_ = { width, height };
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Viewport::~D3D11Viewport()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Viewport::Set()
	{
		D3D11RenderDevice* device = D3D11RenderDevice::Instance();

		device->GetContext()->RSSetViewports(1, &viewport_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Viewport::SetResolution(const float& width, const float& height)
	{
		resolution_.width = width;
		resolution_.height = height;

		viewport_.Width = width;
		viewport_.Height = height;
	}

	//------------------------------------------------------------------------------------------------------
	const Resolution& D3D11Viewport::GetResolution()
	{
		return resolution_;
	}
}