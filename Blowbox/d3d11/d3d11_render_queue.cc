#include "../../blowbox/d3d11/d3d11_render_queue.h"

#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_constant_buffer.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_sampler_state.h"
#include "../../blowbox/d3d11/d3d11_shader.h"
#include "../../blowbox/d3d11/d3d11_texture.h"
#include "../../blowbox/d3d11/d3d11_rasterizer_state.h"
#include "../../blowbox/d3d11/d3d11_blend_state.h"
#include "../../blowbox/d3d11/d3d11_render_target.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderQueue::D3D11RenderQueue()
	{

	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderQueue::D3D11RenderQueue(lua_State* L) :
		LuaClass(L)
	{
		D3D11RenderTarget* render_target = LuaWrapper::Instance()->ParseUserdata<D3D11RenderTarget>(L, 1);

		if (render_target->GetQueue() != this)
		{
			render_target->SetQueue(this);
		}

		lua_functions = std::map<std::string, lua_CFunction>({
			{ "add", LuaAdd }
		});
	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderQueue::~D3D11RenderQueue()
	{
		for (int i = static_cast<int>(queue_.size()) - 1; i >= 0; --i)
		{
			//queue_.at(i)->Destroy();
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::Add(D3D11RenderElement* element)
	{
		if (element->GetType() == RENDER_ELEMENT_TYPE::RENDER_ELEMENT_MISC)
		{
			queue_.push_back(element);
		}
		else
		{
			ui_queue_.push_back(element);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::Remove(D3D11RenderElement* element)
	{
		for (unsigned int i = 0; i < queue_.size(); ++i)
		{
			if (queue_.at(i) == element)
			{
				queue_.erase(queue_.begin() + i);
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	const std::vector<D3D11RenderElement*>& D3D11RenderQueue::GetElements()
	{
		return queue_;
	}

	//------------------------------------------------------------------------------------------------------
	const std::vector<D3D11RenderElement*>& D3D11RenderQueue::GetUIElements()
	{
		return ui_queue_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::Draw(ID3D11DeviceContext* context)
	{
		for (int i = static_cast<int>(queue_.size()) - 1; i >= 0; --i)
		{
			DrawElement(context, queue_.at(i));
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::DrawUI(ID3D11DeviceContext* context)
	{
		for (int i = static_cast<int>(ui_queue_.size()) - 1; i >= 0; --i)
		{
			DrawElement(context, ui_queue_.at(i));
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::DrawElement(ID3D11DeviceContext* context, D3D11RenderElement* element)
	{
		D3D11RenderDevice::Instance()->GetObjectBuffer()->Map(context, {
			element->GetWorld(),
			static_cast<float>(element->GetAlpha())
		});
		D3D11RenderDevice::Instance()->GetObjectBuffer()->Set(context, 1);

		D3D11SamplerState::GetSamplerState(element->GetFilteringType())->Set(context);

		element->GetTexture()->Set(context);
		element->GetShader()->Set(context);
		element->GetBlendState()->Set(context);
		element->GetRasterizerState()->Set(context);

		element->GetVertexBuffer()->Set(context);
		element->GetVertexBuffer()->Draw(context);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11RenderQueue::LuaAdd(lua_State* L)
	{
		D3D11RenderQueue* self = LuaWrapper::Instance()->ParseUserdata<D3D11RenderQueue>(L, 1);

		self->Add(LuaWrapper::Instance()->ParseUserdata<D3D11RenderElement>(L, 2));

		return 0;
	}
}