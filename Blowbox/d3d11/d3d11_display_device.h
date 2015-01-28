#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <D3DX10.h>
#include <D3DX11.h>
#include <xnamath.h>
#include <vector>
#include <algorithm>
#include "../memory/shared_ptr.h"
#include "d3d11_shader.h"

namespace blowbox
{
	struct Vertex
	{
		Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz, float bx, float by, float bz, float tx, float ty, float tz) :
			pos(x, y, z, 1),
			texCoord(u, v),
			normal(nx, ny, nz, 1),
			binormal(bx, by, bz, 1),
			tangent(tx, ty, tz, 1) 
		{}
		XMFLOAT4 pos;
		XMFLOAT2 texCoord;
		XMFLOAT4 normal;
		XMFLOAT4 binormal;
		XMFLOAT4 tangent;
	};

	struct cBufferData
	{
		XMMATRIX WVP;
		float alpha;
		float time;
	};

	class D3D11Camera;
	class D3D11RenderElement;
	class D3D11Shader;
	
	class D3D11DisplayDevice
	{
	public:
		D3D11DisplayDevice();
		~D3D11DisplayDevice();

		static D3D11DisplayDevice*	Instance();
		ID3D11Device*				GetDevice();
		ID3D11DeviceContext*		GetContext();

		void						Create(HWND hWnd);
		void						InitScene();
		void						BeginDraw();
		void						Draw();
		void 						DrawElement(D3D11RenderElement *cube);
		void						EndDraw();

		void						AddElement(D3D11RenderElement* element);
		void						RemoveElement(D3D11RenderElement* element);
		
		void						SetProjectionMatrix(float fov, float aspectRatio, float nearZ, float farZ);

		void						Update(double deltaTime);

		void						SetVertexBuffer(ID3D11Buffer* vertexBuffer);
		ID3D11Buffer*				CreateVertexBuffer(const std::vector<Vertex>& verts);

		void						SetIndexBuffer(ID3D11Buffer* indexBuffer);
		ID3D11Buffer*				CreateIndexBuffer(const std::vector<int>& indices);

		void						SetupDeviceAndSwapChain(HWND hWnd);
		
		void						SetupRenderTargetView();

		void						SetDepthStencilView();

		void						SetRasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode);
		D3D11_FILL_MODE&			GetFillMode();
		D3D11_CULL_MODE&			GetCullMode();
		 
		void						SetCamera(D3D11Camera* camera);
		D3D11Camera*				GetCamera();

		void						Release();

		const int&					GetWidth();
		const int&					GetHeight();

		void						AddTime(float time);
	private:
		IDXGISwapChain*						swapChain_;
		ID3D11Device*						device_;
		ID3D11DeviceContext*				context_;
		ID3D11RenderTargetView*				renderTarget_;
		ID3D11VertexShader*					vs_;
		ID3D11PixelShader*					ps_;
		ID3D10Blob*							vsBuffer_;
		ID3D10Blob*							psBuffer_;
		ID3D11InputLayout*					inputLayout_;
		ID3D11DepthStencilView*				depthStencilView_;
		ID3D11Texture2D*					depthStencilBuffer_;
		ID3D11RasterizerState*				rasterizerState_;
		ID3D11SamplerState*					samplerState_;
		ID3D11DepthStencilState*			depthState_;
		ID3D11BlendState*					Transparency;
		ID3D11RasterizerState*				CCWcullMode;
		ID3D11RasterizerState*				CWcullMode;

		cBufferData							cBufferData_;
		ID3D11Buffer*						cBuffer_;

		D3D11_FILL_MODE						fillMode_;
		D3D11_CULL_MODE						cullMode_;

		std::vector<D3D11RenderElement*>	renderElements_;

		XMMATRIX							WVP_;
		XMMATRIX							world_;

		D3D11Camera*						camera_;
		D3D11Shader*						baseShader_;

		int									width_;
		int									height_;

		float								time_;
	};
}