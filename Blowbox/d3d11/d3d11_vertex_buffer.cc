#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"

#include "../../blowbox/logging.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11VertexBuffer::D3D11VertexBuffer() :
		vertex_buffer_(nullptr),
		index_buffer_(nullptr)
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	D3D11VertexBuffer::~D3D11VertexBuffer()
	{
		BLOW_SAFE_RELEASE(vertex_buffer_);
		BLOW_SAFE_RELEASE(index_buffer_);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11VertexBuffer::Create(const std::vector<Vertex>& vertices, const std::vector<int>& indices, const D3D11_PRIMITIVE_TOPOLOGY& topology, const BUFFER_TYPE& type)
	{
		HRESULT hr = S_OK;

		// Vertex buffer
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));

		D3D11_SUBRESOURCE_DATA subresource_data;
		ZeroMemory(&subresource_data, sizeof(D3D11_SUBRESOURCE_DATA));

		buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		buffer_desc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
		buffer_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;
		buffer_desc.MiscFlags = 0;

		subresource_data.pSysMem = &vertices[0];

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer_);
		BLOW_ASSERT_HR(hr, "There was an HRESULT error while creating a vertex buffer.");

		vertex_stride_size_ = sizeof(Vertex);
		vertex_offset_ = 0;

		// Index buffer
		ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));
		ZeroMemory(&subresource_data, sizeof(D3D11_SUBRESOURCE_DATA));

		buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		buffer_desc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * indices.size());
		buffer_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;
		buffer_desc.MiscFlags = 0;

		subresource_data.pSysMem = &indices[0];

		hr = D3D11RenderDevice::Instance()->GetDevice()->CreateBuffer(&buffer_desc, &subresource_data, &index_buffer_);
		BLOW_ASSERT_HR(hr, "There was an HRESULT error while creating an index buffer.");

		index_format_ = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
		index_offset_ = 0;
		index_size_ = static_cast<UINT>(indices.size());

		// Topology
		topology_ = topology;

		// Type
		type_ = type;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11VertexBuffer::Set(ID3D11DeviceContext* context)
	{
		if (D3D11RenderDevice::Instance()->GetBufferType() != type_ || D3D11RenderDevice::Instance()->GetBufferType() == BUFFER_TYPE::BUFFER_TYPE_UNKNOWN)
		{
			D3D11RenderDevice::Instance()->SetBufferType(type_);
			context->IASetVertexBuffers(0, 1, &vertex_buffer_, &vertex_stride_size_, &vertex_offset_);
			context->IASetIndexBuffer(index_buffer_, index_format_, index_offset_);
		}

		D3D11_PRIMITIVE_TOPOLOGY last_topology;
		context->IAGetPrimitiveTopology(&last_topology);

		if (last_topology != topology_)
		{
			context->IASetPrimitiveTopology(topology_);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11VertexBuffer::Draw(ID3D11DeviceContext* context)
	{
		context->DrawIndexed(index_size_, 0, 0);
	}

	//------------------------------------------------------------------------------------------------------
	const D3D11_PRIMITIVE_TOPOLOGY& D3D11VertexBuffer::GetTopology() const
	{
		return topology_;
	}
}