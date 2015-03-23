#pragma once

#include "../../blowbox/d3d11/d3d11.h"

#include <vector>
#include <Windows.h>
#include <xnamath.h>

namespace blowbox
{
	/**
	* @struct blowbox::Vertex
	* @brief A structure that holds vertex information
	*/
	struct Vertex
	{
		Vertex(const XMFLOAT4& p) :
			position(p),
			color(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)),
			tex_coords(XMFLOAT2(0.0f, 0.0f)),
			normal(XMFLOAT3(0.0f, 0.0f, 0.0f))
		{}

		Vertex(const XMFLOAT4& p, const XMFLOAT2& t) :
			position(p),
			color(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)),
			tex_coords(t),
			normal(XMFLOAT3(0.0f, 0.0f, 0.0f))
		{}
		
		Vertex(const XMFLOAT4& p, const XMFLOAT4& c, const XMFLOAT2& t) :
			position(p),
			color(c),
			tex_coords(t),
			normal(XMFLOAT3(0.0f, 0.0f, 0.0f))
		{}

		Vertex(const XMFLOAT4& p, const XMFLOAT4& c, const XMFLOAT2& t, const XMFLOAT3& n) :
			position(p),
			color(c),
			tex_coords(t),
			normal(n)
		{}

		XMFLOAT4 position; 
		XMFLOAT4 color;
		XMFLOAT2 tex_coords;
		XMFLOAT3 normal;
	};

	/**
	* @enum blowbox::BUFFER_TYPE
	* @brief Describes the different types of buffer types
	*/
	enum BUFFER_TYPE
	{
		BUFFER_TYPE_QUAD,
		BUFFER_TYPE_CUBE,
		BUFFER_TYPE_UNKNOWN
	};

	/**
	* @class blowbox::D3D11VertexBuffer
	* @brief Handles vertex & index buffers and topology settings
	* @author Riko Ophorst
	*/
	class D3D11VertexBuffer
	{
	public:
		/**
		* @brief Default D3D11VertexBuffer constructor
		*/
		D3D11VertexBuffer();

		/**
		* @brief Default D3D11VertexBuffer destructor
		*/
		~D3D11VertexBuffer();

		/**
		* @brief Creates the buffer
		* @param[in] vertices (const std::vector<Vertex>&) all vertices
		* @param[in] indices (const std::vector<int>&) all indices
		* @param[in] topology (const D3D11_PRIMITIVE_TOPOLOGY&) the topology type for this object
		* @param[in] type (const BUFFER_TYPE&) the type of the buffer
		*/
		void Create(const std::vector<Vertex>& vertices, const std::vector<int>& indices, const D3D11_PRIMITIVE_TOPOLOGY& topology, const BUFFER_TYPE& type);

		/**
		* @brief Sets the vertex & index buffer
		* @param[in] context (ID3D11DeviceContext*) the context
		*/
		void Set(ID3D11DeviceContext* context);

		/**
		* @brief Draws the vertex buffer
		* @param[in] context (ID3D11DeviceContext*) the context
		*/
		void Draw(ID3D11DeviceContext* context);

		/**
		* @return The topology of this vertex buffer
		*/
		const D3D11_PRIMITIVE_TOPOLOGY& GetTopology() const;
	private:
		ID3D11Buffer* vertex_buffer_;
		UINT vertex_stride_size_;
		UINT vertex_offset_;

		ID3D11Buffer* index_buffer_;
		DXGI_FORMAT index_format_;
		UINT index_offset_;
		UINT index_size_;

		BUFFER_TYPE type_;

		D3D11_PRIMITIVE_TOPOLOGY topology_;
	};
}