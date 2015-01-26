#include "d3d11_display_device.h"
#include "d3d11_camera.h"
#include "d3d11_render_element.h"
#include "../precompile/definitions.h"

namespace blowbox
{
	
	//----------------------------------------------------------------------------------------------------------------
	D3D11DisplayDevice::D3D11DisplayDevice()
	{
		
	}

	//----------------------------------------------------------------------------------------------------------------
	D3D11DisplayDevice::~D3D11DisplayDevice()
	{

	}

	//----------------------------------------------------------------------------------------------------------------
	D3D11DisplayDevice* D3D11DisplayDevice::Instance()
	{
		static SharedPtr<D3D11DisplayDevice> ptr(new D3D11DisplayDevice());
		return ptr.get();
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::Create(HWND hWnd)
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);

		width_ = rect.right - rect.left;
		height_ = rect.bottom - rect.top;
		
		// Creates the device & swapchain, and sets the rendertargets
		SetupDeviceAndSwapChain(hWnd);

		SetupRenderTargetView();

		SetDepthStencilView();

		SetRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_NONE);

		context_->OMSetRenderTargets(1, &renderTarget_, NULL);
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::InitScene()
	{
		HRESULT hr = S_OK;

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
		
		//Compile Shaders from shader file
		hr = D3DX11CompileFromFileA("shaders/effects.fx", 0, 0, "VS", "vs_4_0", 0, 0, 0, &vsBuffer_, 0, 0);
		hr = D3DX11CompileFromFileA("shaders/effects.fx", 0, 0, "PS", "ps_4_0", 0, 0, 0, &psBuffer_, 0, 0);
		BLOW_ASSERT_HR(hr, "Error compiling shaders");

		//Create the Shader Objects
		hr = device_->CreateVertexShader(vsBuffer_->GetBufferPointer(), vsBuffer_->GetBufferSize(), NULL, &vs_);
		hr = device_->CreatePixelShader(psBuffer_->GetBufferPointer(), psBuffer_->GetBufferSize(), NULL, &ps_);

		//Set Vertex and Pixel Shaders
		context_->VSSetShader(vs_, 0, 0);
		context_->PSSetShader(ps_, 0, 0);

		//Create the Input Layout
		hr = device_->CreateInputLayout( layout, numElements, vsBuffer_->GetBufferPointer(), 
			vsBuffer_->GetBufferSize(), &inputLayout_ );
		BLOW_ASSERT_HR(hr, "err");

		//Set the Input Layout
		context_->IASetInputLayout(inputLayout_);

		//Set Primitive Topology
		context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//Create the Viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		DXGI_SWAP_CHAIN_DESC desc;
		swapChain_->GetDesc(&desc);

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (FLOAT)desc.BufferDesc.Width;
		viewport.Height = (FLOAT)desc.BufferDesc.Height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		//Set the Viewport
		context_->RSSetViewports(1, &viewport);

		//Create the buffer to send to the cbuffer in effect file
		D3D11_BUFFER_DESC cBufferDesc;
		ZeroMemory(&cBufferDesc, sizeof(D3D11_BUFFER_DESC));

		cBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		cBufferDesc.ByteWidth = sizeof(cBufferData_) * 4;
		cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cBufferDesc.CPUAccessFlags = 0;
		cBufferDesc.MiscFlags = 0;

		hr = device_->CreateBuffer(&cBufferDesc, NULL, &cBuffer_);
		BLOW_ASSERT_HR(hr, "Cannot create constant buffer");

		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		//Create the Sample State
		hr = device_->CreateSamplerState(&sampDesc, &samplerState_);
		BLOW_ASSERT_HR(hr, "Cannot create sampler state");
		context_->PSSetSamplers(0, 1, &samplerState_);

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));

		D3D11_RENDER_TARGET_BLEND_DESC rtbd;
		ZeroMemory(&rtbd, sizeof(rtbd));

		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.RenderTarget[0] = rtbd;

		hr = device_->CreateBlendState(&blendDesc, &Transparency);
		BLOW_ASSERT_HR(hr, "Cannot create blend state");

		D3D11_RASTERIZER_DESC cmdesc;
		ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

		cmdesc.FillMode = D3D11_FILL_SOLID;
		cmdesc.CullMode = D3D11_CULL_BACK;

		cmdesc.FrontCounterClockwise = true;
		hr = device_->CreateRasterizerState(&cmdesc, &CCWcullMode);
		BLOW_ASSERT_HR(hr, "Cannot create rasterizer state");

		cmdesc.FrontCounterClockwise = false;
		hr = device_->CreateRasterizerState(&cmdesc, &CWcullMode);
		BLOW_ASSERT_HR(hr, "Cannot create rasterizer state");
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::Update(double deltaTime)
	{
		
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::BeginDraw()
	{
		D3DXCOLOR bgColor(0.1f, 0.1f, 0.1f, 1.0f);
		context_->ClearRenderTargetView(renderTarget_, bgColor);
		context_->ClearDepthStencilView(depthStencilView_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::Draw()
	{
		struct RenderSorterZ
		{
			bool operator()(D3D11RenderElement* a, D3D11RenderElement* b)
			{
				return a != nullptr && b != nullptr && XMVectorGetZ(a->GetPosition()) < XMVectorGetZ(b->GetPosition());
			}
		} renderSorterZ;

		std::sort(renderElements_.begin(), renderElements_.end(), renderSorterZ);
		
		for (int i = static_cast<int>(renderElements_.size()) - 1; i >= 0; --i)
		{
			if (renderElements_[i] == nullptr)
			{
				renderElements_.erase(renderElements_.begin() + i);
			}

			DrawElement(renderElements_[i]);
		}
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::DrawElement(D3D11RenderElement* renderElement)
	{
		context_->VSSetShader(renderElement->GetShader()->GetVS(), 0, 0);
		context_->PSSetShader(renderElement->GetShader()->GetPS(), 0, 0);

		cBufferData_.WVP = XMMatrixTranspose(renderElement->GetWorld() * camera_->GetView() * camera_->GetProjection());
		cBufferData_.alpha = renderElement->GetAlpha();
		context_->UpdateSubresource(cBuffer_, 0, NULL, &cBufferData_, 0, 0);

		context_->VSSetConstantBuffers(0, 1, &cBuffer_);
		context_->PSSetConstantBuffers(0, 1, &cBuffer_);

		ID3D11ShaderResourceView* tex = renderElement->GetTexture()->Get();
		context_->PSSetShaderResources(0, 1, &tex);
		context_->PSSetSamplers(0, 1, &samplerState_);

		context_->OMSetBlendState(Transparency, NULL, 0xffffffff);

		renderElement->Draw();
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::EndDraw()
	{
		swapChain_->Present(1, 0);
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::AddElement(D3D11RenderElement* renderElement)
	{
		renderElements_.push_back(renderElement);
	}

	void D3D11DisplayDevice::RemoveElement(D3D11RenderElement* renderElement)
	{
		for (auto& it : renderElements_)
		{
			if (it == renderElement)
			{
				it = nullptr;
			}
		}
	}

	//----------------------------------------------------------------------------------------------------------------
	ID3D11Buffer* D3D11DisplayDevice::CreateVertexBuffer(const std::vector<Vertex>& verts)
	{
		HRESULT hr = S_OK;

		ID3D11Buffer* vertBuffer;

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = (UINT)(sizeof(Vertex) * verts.size());
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));

		vertexBufferData.pSysMem = &verts[0];
		hr = device_->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertBuffer);

		BLOW_ASSERT_HR(hr, "Failed creating vertex buffer");

		return vertBuffer;
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::SetVertexBuffer(ID3D11Buffer* vertexBuffer)
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		context_->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	}

	//----------------------------------------------------------------------------------------------------------------
	ID3D11Buffer* D3D11DisplayDevice::CreateIndexBuffer(const std::vector<int>& verts)
	{
		HRESULT hr = S_OK;

		ID3D11Buffer* indexBuffer;

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = (UINT)(sizeof(int) * verts.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData;
		ZeroMemory(&indexBufferData, sizeof(indexBufferData));

		indexBufferData.pSysMem = &verts[0];
		hr = device_->CreateBuffer(&indexBufferDesc, &indexBufferData, &indexBuffer);

		BLOW_ASSERT_HR(hr, "Failed creating index buffer");

		return indexBuffer;
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::SetIndexBuffer(ID3D11Buffer* indexBuffer)
	{
		context_->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::SetupDeviceAndSwapChain(HWND hWnd)
	{
		HRESULT hr = S_OK;

		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = width_;
		bufferDesc.Height = height_;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL,
			D3D11_SDK_VERSION, &swapChainDesc, &swapChain_, &device_, NULL, &context_);
		
		BLOW_ASSERT_HR(hr, "Error creating device & swap chain");

		
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::SetupRenderTargetView()
	{
		HRESULT hr = S_OK;

		ID3D11Texture2D* BackBuffer = NULL;
		hr = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		BLOW_ASSERT_HR(hr, "Error getting backbuffer");

		hr = device_->CreateRenderTargetView(BackBuffer, NULL, &renderTarget_);
		BLOW_ASSERT_HR(hr, "Error creating render target view");
		BackBuffer->Release();
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::SetDepthStencilView()
	{
		HRESULT hr = S_OK;
		
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));

		depthStencilDesc.Width = width_;
		depthStencilDesc.Height = height_;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		depthStencilBuffer_ = nullptr;
		depthStencilView_ = nullptr;

		hr = device_->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer_);
		BLOW_ASSERT_HR(hr, "Error creating Texture2D for depth stencil");

		hr = device_->CreateDepthStencilView(depthStencilBuffer_, NULL, &depthStencilView_);
		BLOW_ASSERT_HR(hr, "Error creating depth stencil view");

		D3D11_DEPTH_STENCIL_DESC dsDesc;

		// Depth test parameters
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		dsDesc.StencilEnable = true;
		dsDesc.StencilReadMask = 0xFF;
		dsDesc.StencilWriteMask = 0xFF;

		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hr = device_->CreateDepthStencilState(&dsDesc, &depthState_);
		BLOW_ASSERT_HR(hr, "ga maar lekker dood");

		context_->OMSetDepthStencilState(depthState_, 1);
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::SetRasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode)
	{
		if (fillMode_ == fillMode && cullMode_ == cullMode)
			return;

		HRESULT hr = S_OK;

		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = fillMode;
		rasterizerDesc.CullMode = cullMode;
		hr = device_->CreateRasterizerState(&rasterizerDesc, &rasterizerState_);

		BLOW_ASSERT_HR(hr, "Cannot create rasterizer state");

		context_->RSSetState(rasterizerState_);
	}

	//----------------------------------------------------------------------------------------------------------------
	D3D11_FILL_MODE& D3D11DisplayDevice::GetFillMode()
	{
		return fillMode_;
	}

	//----------------------------------------------------------------------------------------------------------------
	D3D11_CULL_MODE& D3D11DisplayDevice::GetCullMode()
	{
		return cullMode_;
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::SetCamera(D3D11Camera* camera)
	{
		camera_ = camera;
	}

	//----------------------------------------------------------------------------------------------------------------
	D3D11Camera* D3D11DisplayDevice::GetCamera()
	{
		return camera_;
	}

	//----------------------------------------------------------------------------------------------------------------
	void D3D11DisplayDevice::Release()
	{
		swapChain_->Release();
		device_->Release();
		context_->Release();
		renderTarget_->Release();
		vs_->Release();
		ps_->Release();
		vsBuffer_->Release();
		psBuffer_->Release();
		inputLayout_->Release();
		depthStencilBuffer_->Release();
		depthStencilView_->Release();
		cBuffer_->Release();
		rasterizerState_->Release();
		samplerState_->Release();
		depthState_->Release();
		Transparency->Release();
		CCWcullMode->Release();
		CWcullMode->Release();
	}

	//----------------------------------------------------------------------------------------------------------------
	ID3D11Device* D3D11DisplayDevice::GetDevice()
	{
		return device_;
	}

	//----------------------------------------------------------------------------------------------------------------
	ID3D11DeviceContext* D3D11DisplayDevice::GetContext()
	{
		return context_;
	}

	//----------------------------------------------------------------------------------------------------------------
	const int& D3D11DisplayDevice::GetWidth()
	{
		return width_;
	}

	//----------------------------------------------------------------------------------------------------------------
	const int& D3D11DisplayDevice::GetHeight()
	{
		return height_;
	}
}