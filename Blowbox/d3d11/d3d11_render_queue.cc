#include "../../blowbox/d3d11/d3d11_render_queue.h"

#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderQueue::D3D11RenderQueue()
	{

	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderQueue::~D3D11RenderQueue()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::Add(D3D11RenderElement* element)
	{
		queue_.push_back(element);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::Draw(ID3D11DeviceContext* context)
	{
		D3D11RenderElement* element;

		for (int i = static_cast<int>(queue_.size()) - 1; i >= 0; --i)
		{
			element = queue_.at(i);

			DrawElement(context, element);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderQueue::DrawElement(ID3D11DeviceContext* context, D3D11RenderElement* element)
	{
		element->GetVertexBuffer()->Set(context);
		
		element->GetVertexBuffer()->Draw(context);
	}
}