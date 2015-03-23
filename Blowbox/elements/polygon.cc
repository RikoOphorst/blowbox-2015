#include "../../blowbox/elements/polygon.h"

#include "../../blowbox/d3d11/d3d11_render_queue.h"
#include "../../blowbox/console/console.h"
#include "../../blowbox/utility/lua_enum.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Polygon::Polygon() :
		D3D11RenderElement()
	{
		Create();
	}

	//------------------------------------------------------------------------------------------------------
	Polygon::Polygon(lua_State* L) :
		D3D11RenderElement(L)
	{
		D3D11RenderQueue* render_queue = LuaWrapper::Instance()->ParseUserdata<D3D11RenderQueue>(L, -4);
		render_queue->Add(this);
		
		std::map<std::string, LuaValue> verts = LuaWrapper::Instance()->ToTable(L, -3);

		for (auto it = verts.begin(); it != verts.end(); ++it)
		{
			int x = stoi(it->second.fields.at("1").value);
			int y = stoi(it->second.fields.at("2").value);
			int z = stoi(it->second.fields.at("3").value);

			Vertex vert(XMFLOAT4(x, y, z, 1.0f));

			vertices_.push_back(vert);
		}

		std::map<std::string, LuaValue> indices = LuaWrapper::Instance()->ToTable(L, -2);

		for (auto it = indices.begin(); it != indices.end(); ++it)
		{
			int index = stoi(it->second.value);

			indices_.push_back(index);
		}

		switch (static_cast<POLYGON_TOPOLOGY>(static_cast<int>(LuaWrapper::Instance()->Get<double>(L, -1))))
		{
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLELIST:
			topology_ = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLESTRIP:
			topology_ = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		}

		Create();
	}

	//------------------------------------------------------------------------------------------------------
	Polygon::~Polygon()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::Create()
	{
		vertex_buffer_ = new D3D11VertexBuffer();
		vertex_buffer_->Create(
			vertices_,
			indices_,
			topology_,
			BUFFER_TYPE::BUFFER_TYPE_UNKNOWN
		);
	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] =
		{
			{ "setPosition", LuaSetPosition },
			{ "getPosition", LuaGetPosition },
			{ "setPosition2D", LuaSetPosition2D },
			{ "getPosition2D", LuaGetPosition2D },
			{ "setX", LuaSetX },
			{ "getX", LuaGetX },
			{ "setY", LuaSetY },
			{ "getY", LuaGetY },
			{ "setZ", LuaSetZ },
			{ "getZ", LuaGetZ },
			{ "setRotation", LuaSetRotation },
			{ "getRotation", LuaGetRotation },
			{ "setRotation2D", LuaSetRotation2D },
			{ "getRotation2D", LuaGetRotation2D },
			{ "setScale", LuaSetScale },
			{ "getScale", LuaGetScale },
			{ "setScale2D", LuaSetScale2D },
			{ "getScale2D", LuaGetScale2D },
			{ "setOffset", LuaSetOffset },
			{ "getOffset", LuaGetOffset },
			{ "setOffset2D", LuaSetOffset2D },
			{ "getOffset2D", LuaGetOffset2D },
			{ "setAlpha", LuaSetAlpha },
			{ "getAlpha", LuaGetAlpha },
			{ "setTexture", LuaSetTexture },
			{ "getTexture", LuaGetTexture },
			{ "setShader", LuaSetShader },
			{ "getShader", LuaGetShader },
			{ "setFiltering", LuaSetFiltering },
			{ "getFiltering", LuaGetFiltering },
			{ "setBlend", LuaSetBlend },
			{ "getBlend", LuaGetBlend },
			{ "setPoints", LuaSetPoints },
			{ "getPoints", LuaGetPoints },
			{ "setPoint", LuaSetPoint },
			{ "getPoint", LuaGetPoint },
			{ "addPoint", LuaAddPoint },
			{ "setTopology", LuaSetTopology },
			{ "getTopology", LuaGetTopology },
			{ "setIndices", LuaSetIndices },
			{ "getIndices", LuaGetIndices },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);

		LuaEnum::Set(L, "Topology", {
			"TriangleList",
			"TriangleStrip"
		});
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaSetPoints(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, -4);

		std::map<std::string, LuaValue> verts = LuaWrapper::Instance()->ToTable(L, -3);

		for (auto it = verts.begin(); it != verts.end(); ++it)
		{
			int x = stoi(it->second.fields.at("1").value);
			int y = stoi(it->second.fields.at("2").value);
			int z = stoi(it->second.fields.at("3").value);

			Vertex vert(XMFLOAT4(x, y, z, 1.0f));

			self->vertices_.push_back(vert);
		}

		std::map<std::string, LuaValue> indices = LuaWrapper::Instance()->ToTable(L, -2);

		for (auto it = indices.begin(); it != indices.end(); ++it)
		{
			int index = stoi(it->second.value);

			self->indices_.push_back(index);
		}

		switch (static_cast<POLYGON_TOPOLOGY>(static_cast<int>(LuaWrapper::Instance()->Get<double>(L, -1))))
		{
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLELIST:
			self->topology_ = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLESTRIP:
			self->topology_ = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		}

		self->Create();

		return 0;
	}
}