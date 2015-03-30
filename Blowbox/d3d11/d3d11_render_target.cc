#include "../../blowbox/d3d11/d3d11_render_target.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_render_queue.h"
#include "../../blowbox/d3d11/d3d11_shader.h"
#include "../../blowbox/d3d11/d3d11_blend_state.h"
#include "../../blowbox/d3d11/d3d11_depth_stencil.h"
#include "../../blowbox/content/content_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget::D3D11RenderTarget()
	{
		if (!ContentManager::Instance()->IsShaderLoaded("shaders/post_processing.fx"))
		{
			ContentManager::Instance()->LoadShader("shaders/post_processing.fx");
		}

		shader_ = ContentManager::Instance()->GetShader("shaders/post_processing.fx");
		blend_state_ = new D3D11BlendState();
		depth_stencil_ = new D3D11DepthStencil();
		queue_ = new D3D11RenderQueue();
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget::D3D11RenderTarget(lua_State* L) :
		LuaClass(L)
	{
		if (!ContentManager::Instance()->IsShaderLoaded("shaders/post_processing.fx"))
		{
			ContentManager::Instance()->LoadShader("shaders/post_processing.fx");
		}

		shader_ = ContentManager::Instance()->GetShader("shaders/post_processing.fx");
		blend_state_ = new D3D11BlendState();
		depth_stencil_ = new D3D11DepthStencil();
		queue_ = new D3D11RenderQueue();

		Create(RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_RENDER_TARGET, D3D11RenderDevice::Instance()->GetSwapChain(), D3D11RenderDevice::Instance()->GetDevice());

		D3D11RenderDevice::Instance()->AddRenderTarget(LuaWrapper::Instance()->Get<std::string>(L, 1), this);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderTarget::~D3D11RenderTarget()
	{
		BLOW_SAFE_RELEASE(target_);
		BLOW_SAFE_RELEASE(view_);
		BLOW_RELEASE(resource_);
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
	void D3D11RenderTarget::Create(RENDER_TARGET_TYPE type, IDXGISwapChain* swap_chain, ID3D11Device* device)
	{
		HRESULT hr = S_OK;

		if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER == type)
		{
			type_ = type;
			
			hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&target_);
			BLOW_ASSERT_HR(hr, "Error while creating back buffer");

			hr = device->CreateRenderTargetView(target_, 0, &view_);
			BLOW_ASSERT_HR(hr, "Error while creating back buffer view");
		}
		else if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_RENDER_TARGET == type)
		{
			type_ = type;

			D3D11_TEXTURE2D_DESC target_desc;
			D3D11RenderDevice::Instance()->GetBackBuffer()->GetTarget()->GetDesc(&target_desc);
			target_desc.BindFlags |= D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
			
			target_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;

			hr = device->CreateTexture2D(&target_desc, NULL, &target_);
			BLOW_ASSERT_HR(hr, "Error while creating render target texture");

			D3D11_SHADER_RESOURCE_VIEW_DESC view_desc;
			view_desc.ViewDimension = D3D_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;
			view_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
			view_desc.Texture2D.MipLevels = 1;
			view_desc.Texture2D.MostDetailedMip = 0;

			hr = device->CreateShaderResourceView(target_, &view_desc, &resource_);
			BLOW_ASSERT_HR(hr, "Error while creating resource view for render target");

			hr = device->CreateRenderTargetView(target_, NULL, &view_);
			BLOW_ASSERT_HR(hr, "Error while creating render target view");
		}
		else
		{
			BLOW_BREAK("Unknown RenderTargetType");
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Set(ID3D11DeviceContext* context)
	{
		ID3D11DepthStencilView* ds_view = depth_stencil_->GetView();
		
		if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER == type_)
		{
			context->OMSetRenderTargets(1, &view_, nullptr);
		}
		else
		{
			context->OMSetRenderTargets(1, &view_, nullptr);
		}
		
		//depth_stencil_->Set(context);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Draw(ID3D11DeviceContext* context)
	{
		queue_->Draw(context);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::DrawUI(ID3D11DeviceContext* context)
	{
		queue_->DrawUI(context);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Clear(ID3D11DeviceContext* context)
	{	
		if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_BACKBUFFER == type_)
		{
			context->ClearRenderTargetView(view_, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));
		}
		else if (RENDER_TARGET_TYPE::RENDER_TARGET_TYPE_RENDER_TARGET == type_)
		{
			context->ClearRenderTargetView(view_, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			//context->ClearDepthStencilView(depth_stencil_->GetView(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::SetQueue(D3D11RenderQueue* queue)
	{
		queue_ = queue;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderQueue* D3D11RenderTarget::GetQueue()
	{
		return queue_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::ApplyShader(ID3D11DeviceContext* context)
	{
		shader_->Set(context);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::ApplyBlendState(ID3D11DeviceContext* context)
	{
		blend_state_->Set(context);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::SetShader(const std::string& path)
	{
		shader_ = ContentManager::Instance()->GetShader(path);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Shader* D3D11RenderTarget::GetShader()
	{
		return shader_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::Release()
	{
		BLOW_RELEASE(resource_);
		BLOW_RELEASE(view_);
		BLOW_RELEASE(target_);

		depth_stencil_->Release();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::RecreateDepthStencil()
	{
		depth_stencil_->Create();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderTarget::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "getShader", LuaGetShader },
			{ "setShader", LuaSetShader },
			{ "setQueue", LuaSetQueue },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderTarget::LuaGetShader(lua_State* L)
	{
		D3D11RenderTarget* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderTarget>(L, 1);

		return LuaWrapper::Instance()->Push(L, "");
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderTarget::LuaSetShader(lua_State* L)
	{
		D3D11RenderTarget* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderTarget>(L, 1);

		self->SetShader(LuaWrapper::Instance()->Get<std::string>(L, 2));

		return LuaWrapper::Instance()->Push(L, "");
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderTarget::LuaSetQueue(lua_State* L)
	{	
		D3D11RenderTarget* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderTarget>(L, 1);

		self->SetQueue(LuaWrapper::Instance()->ParseUserdata<D3D11RenderQueue>(L, 2));

		return 0;
	}
}