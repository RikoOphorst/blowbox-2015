#pragma once

#include "d3d11_display_device.h"
#include "d3d11_texture.h"
#include "d3d11_shader.h"
#include "../content/content_manager.h"

namespace blowbox
{
	class D3D11RenderElement
	{
	public:
		D3D11RenderElement();
		~D3D11RenderElement();

		virtual void						Draw() = 0;
		virtual XMMATRIX&					GetWorld();

		void								SetTexture(D3D11Texture* texture);
		D3D11Texture*						GetTexture();

		void								SetShader(D3D11Shader* shader);
		D3D11Shader*						GetShader();

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
		D3D11Texture*						texture_;
		D3D11Shader*						shader_;
		float								alpha_;
	};
}