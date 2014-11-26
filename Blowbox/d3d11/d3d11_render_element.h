#pragma once

#include "d3d11_display_device.h"
#include "d3d11_texture.h"

namespace blowbox
{
	class D3D11RenderElement
	{
	public:
		D3D11RenderElement();
		~D3D11RenderElement();

		virtual void						Draw() = 0;
		virtual XMMATRIX&					GetWorld();

		ID3D11ShaderResourceView*			GetTexture();
		void								SetTexture();
		void								SetTexture(std::string filePath);

		void								SetPosition(float x, float y, float z);
		void								SetRotation(float x, float y, float z);
		void								SetScale(float x, float y, float z);
		void								SetSize(float w, float h);
		void								SetAlpha(float a);

		XMVECTOR&							GetPosition();
		XMVECTOR&							GetRotation();
		XMVECTOR&							GetScale();
		XMFLOAT2&							GetSize();
		float&								GetAlpha();

	private:
		XMMATRIX 							world_;
		XMVECTOR 							position_;
		XMVECTOR							rotation_;
		XMVECTOR							scale_;
		XMFLOAT2							size_;
		SharedPtr<D3D11Texture>				texture_;
		float								alpha_;
	};
}