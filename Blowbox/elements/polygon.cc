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
		render_queue_ = LuaWrapper::Instance()->ParseUserdata<D3D11RenderQueue>(L, 1);
		render_queue_->Add(this);
		
		std::map<std::string, LuaValue> verts = LuaWrapper::Instance()->ToTable(L, 2);

		for (auto it = verts.begin(); it != verts.end(); ++it)
		{
			int x = stoi(it->second.fields.at("1").value);
			int y = stoi(it->second.fields.at("2").value);
			int z = stoi(it->second.fields.at("3").value);

			Vertex vert(XMFLOAT4(x, y, z, 1.0f));

			vertices_.push_back(vert);
		}

		std::map<std::string, LuaValue> indices = LuaWrapper::Instance()->ToTable(L, 3);

		for (auto it = indices.begin(); it != indices.end(); ++it)
		{
			int index = stoi(it->second.value);

			indices_.push_back(index);
		}

		switch (static_cast<POLYGON_TOPOLOGY>(static_cast<int>(LuaWrapper::Instance()->Get<double>(L, 4))))
		{
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLELIST:
			topology_ = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLESTRIP:
			topology_ = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		}

		vertex_buffer_ = new D3D11VertexBuffer();
		Create();
	}

	//------------------------------------------------------------------------------------------------------
	Polygon::~Polygon()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::Create()
	{
		vertex_buffer_->Create(
			vertices_,
			indices_,
			topology_,
			BUFFER_TYPE::BUFFER_TYPE_UNKNOWN
		);
	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::SetPoints(const std::vector<Vertex>& verts)
	{
		vertices_ = verts;
		Create();
	}

	//------------------------------------------------------------------------------------------------------
	const std::vector<Vertex>& Polygon::GetPoints()
	{
		return vertices_;
	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::SetPoint(const Vertex& vert, const int& index)
	{
		vertices_.at(index) = vert;
	}

	//------------------------------------------------------------------------------------------------------
	const Vertex& Polygon::GetPoint(const int& index)
	{
		return vertices_.at(index);
	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::AddPoint(const Vertex& vert)
	{
		vertices_.push_back(vert);
	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::SetIndices(const std::vector<int>& indices)
	{
		indices_ = indices;
	}

	//------------------------------------------------------------------------------------------------------
	const std::vector<int>& Polygon::GetIndices()
	{
		return indices_;
	}

	//------------------------------------------------------------------------------------------------------
	void Polygon::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology)
	{
		topology_ = topology;
	}

	//------------------------------------------------------------------------------------------------------
	const D3D11_PRIMITIVE_TOPOLOGY& Polygon::GetTopology()
	{
		return topology_;
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
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		std::map<std::string, LuaValue> verts = LuaWrapper::Instance()->ToTable(L, 2);

		for (auto it = verts.begin(); it != verts.end(); ++it)
		{
			int x = stoi(it->second.fields.at("1").value);
			int y = stoi(it->second.fields.at("2").value);
			int z = stoi(it->second.fields.at("3").value);

			Vertex vert(XMFLOAT4(x, y, z, 1.0f));

			self->AddPoint(vert);
		}

		self->Create();

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaGetPoints(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);
		
		std::vector<Vertex> verts = self->GetPoints();

		lua_newtable(L);

		for (unsigned int i = 0; i < verts.size(); ++i)
		{
			auto it = verts.at(i);
			
			lua_pushnumber(L, i);
			lua_newtable(L);

			lua_pushstring(L, "position");
			lua_newtable(L);

			lua_pushstring(L, "x");
			lua_pushnumber(L, it.position.x);
			lua_settable(L, -3);

			lua_pushstring(L, "y");
			lua_pushnumber(L, it.position.y);
			lua_settable(L, -3);

			lua_pushstring(L, "z");
			lua_pushnumber(L, it.position.z);
			lua_settable(L, -3);

			lua_settable(L, -3);

			lua_pushstring(L, "color");
			lua_newtable(L);

			lua_pushstring(L, "r");
			lua_pushnumber(L, it.color.x);
			lua_settable(L, -3);

			lua_pushstring(L, "g");
			lua_pushnumber(L, it.color.y);
			lua_settable(L, -3);

			lua_pushstring(L, "b");
			lua_pushnumber(L, it.color.z);
			lua_settable(L, -3);

			lua_pushstring(L, "a");
			lua_pushnumber(L, it.color.w);
			lua_settable(L, -3);

			lua_settable(L, -3);

			lua_pushstring(L, "normal");
			lua_newtable(L);

			lua_pushstring(L, "x");
			lua_pushnumber(L, it.normal.x);
			lua_settable(L, -3);

			lua_pushstring(L, "y");
			lua_pushnumber(L, it.normal.y);
			lua_settable(L, -3);

			lua_pushstring(L, "z");
			lua_pushnumber(L, it.normal.z);
			lua_settable(L, -3);

			lua_settable(L, -3);

			lua_pushstring(L, "uv");
			lua_newtable(L);

			lua_pushstring(L, "u");
			lua_pushnumber(L, it.tex_coords.x);
			lua_settable(L, -3);

			lua_pushstring(L, "v");
			lua_pushnumber(L, it.tex_coords.y);
			lua_settable(L, -3);

			lua_settable(L, -3);

			lua_settable(L, -3);
		}

		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaSetPoint(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		Vertex point;

		point.position.x = LuaWrapper::Instance()->Get<float>(L, 2);
		point.position.y = LuaWrapper::Instance()->Get<float>(L, 3);
		point.position.z = LuaWrapper::Instance()->Get<float>(L, 4);

		point.color.x = LuaWrapper::Instance()->Get<float>(L, 5);
		point.color.y = LuaWrapper::Instance()->Get<float>(L, 6);
		point.color.z = LuaWrapper::Instance()->Get<float>(L, 7);
		point.color.w = LuaWrapper::Instance()->Get<float>(L, 8);

		point.normal.x = LuaWrapper::Instance()->Get<float>(L, 9);
		point.normal.y = LuaWrapper::Instance()->Get<float>(L, 10);
		point.normal.z = LuaWrapper::Instance()->Get<float>(L, 11);

		point.tex_coords.x = LuaWrapper::Instance()->Get<float>(L, 12);
		point.tex_coords.y = LuaWrapper::Instance()->Get<float>(L, 13);

		self->SetPoint(point, LuaWrapper::Instance()->Get<int>(L, 14));
		self->Create();

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaGetPoint(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		Vertex it = self->GetPoint(LuaWrapper::Instance()->Get<int>(L, 2));

		lua_newtable(L);

		lua_pushstring(L, "position");
		lua_newtable(L);

		lua_pushstring(L, "x");
		lua_pushnumber(L, it.position.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, it.position.y);
		lua_settable(L, -3);

		lua_pushstring(L, "z");
		lua_pushnumber(L, it.position.z);
		lua_settable(L, -3);

		lua_settable(L, -3);

		lua_pushstring(L, "color");
		lua_newtable(L);

		lua_pushstring(L, "r");
		lua_pushnumber(L, it.color.x);
		lua_settable(L, -3);

		lua_pushstring(L, "g");
		lua_pushnumber(L, it.color.y);
		lua_settable(L, -3);

		lua_pushstring(L, "b");
		lua_pushnumber(L, it.color.z);
		lua_settable(L, -3);

		lua_pushstring(L, "a");
		lua_pushnumber(L, it.color.w);
		lua_settable(L, -3);

		lua_settable(L, -3);

		lua_pushstring(L, "normal");
		lua_newtable(L);

		lua_pushstring(L, "x");
		lua_pushnumber(L, it.normal.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, it.normal.y);
		lua_settable(L, -3);

		lua_pushstring(L, "z");
		lua_pushnumber(L, it.normal.z);
		lua_settable(L, -3);

		lua_settable(L, -3);

		lua_pushstring(L, "uv");
		lua_newtable(L);

		lua_pushstring(L, "u");
		lua_pushnumber(L, it.tex_coords.x);
		lua_settable(L, -3);

		lua_pushstring(L, "v");
		lua_pushnumber(L, it.tex_coords.y);
		lua_settable(L, -3);

		lua_settable(L, -3);

		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaAddPoint(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		Vertex point;

		point.position.x = LuaWrapper::Instance()->Get<float>(L, 2);
		point.position.y = LuaWrapper::Instance()->Get<float>(L, 3);
		point.position.z = LuaWrapper::Instance()->Get<float>(L, 4);

		point.color.x = LuaWrapper::Instance()->Get<float>(L, 5);
		point.color.y = LuaWrapper::Instance()->Get<float>(L, 6);
		point.color.z = LuaWrapper::Instance()->Get<float>(L, 7);
		point.color.w = LuaWrapper::Instance()->Get<float>(L, 8);

		point.normal.x = LuaWrapper::Instance()->Get<float>(L, 9);
		point.normal.y = LuaWrapper::Instance()->Get<float>(L, 10);
		point.normal.z = LuaWrapper::Instance()->Get<float>(L, 11);

		point.tex_coords.x = LuaWrapper::Instance()->Get<float>(L, 12);
		point.tex_coords.y = LuaWrapper::Instance()->Get<float>(L, 13);

		self->AddPoint(point);
		self->Create();

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaSetTopology(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		switch (static_cast<POLYGON_TOPOLOGY>(LuaWrapper::Instance()->Get<int>(L, 2)))
		{
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLELIST:
			self->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			break;
		case POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLESTRIP:
			self->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			break;
		}

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaGetTopology(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		switch (self->GetTopology())
		{
		case D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
			return LuaWrapper::Instance()->Push(L, static_cast<int>(POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLELIST));
			break;
		case D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
			return LuaWrapper::Instance()->Push(L, static_cast<int>(POLYGON_TOPOLOGY::POLYGON_TOPOLOGY_TRIANGLESTRIP));
			break;
		}

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaSetIndices(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		std::vector<int> indices;

		std::map<std::string, LuaValue> table = LuaWrapper::Instance()->ToTable(L, 2);

		for (auto it = table.begin(); it != table.end(); ++it)
		{
			indices.push_back(stoi(it->second.value));
		}

		self->SetIndices(indices);
		self->Create();
		
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Polygon::LuaGetIndices(lua_State* L)
	{
		Polygon* self = LuaWrapper::Instance()->ParseUserdata<Polygon>(L, 1);

		std::vector<int> indices = self->GetIndices();

		lua_newtable(L);

		for (unsigned int i = 0; i < indices.size(); ++i)
		{
			lua_pushnumber(L, i);
			lua_pushnumber(L, indices.at(i));

			lua_settable(L, -3);
		}

		return 1;
	}
}