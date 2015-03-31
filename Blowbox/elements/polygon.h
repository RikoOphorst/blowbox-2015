#pragma once

#include <vector>

#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"

namespace blowbox
{
	/**
	* @enum blowbox::POLOGYON_TOPOLOGY
	* @brief Lua enumerators
	*/enum POLYGON_TOPOLOGY
	{
		POLYGON_TOPOLOGY_TRIANGLELIST,
		POLYGON_TOPOLOGY_TRIANGLESTRIP,
	};
	
	/**
	* @class blowbox::Polygon
	* @brief Creates a polygon render element with varying shapes and sizes
	* @author Riko Ophorst
	*/
	class Polygon: public D3D11RenderElement
	{
	public:
		/**
		* @brief Default Polygon constructor
		*/
		Polygon();

		/**
		* @brief Lua Polygon constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Polygon(lua_State* L);

		/**
		* @brief Default Polygon destructor
		*/
		~Polygon();

		/**
		* @brief Creates the polygon vertex buffer
		*/
		void Create();

		/**
		* @brief Sets all the vertex points
		* @param[in] verts (const std::vector<Vertex>&) vertices
		*/
		void SetPoints(const std::vector<Vertex>& verts);

		/**
		* @brief Gets all the vertex points
		*/
		const std::vector<Vertex>& GetPoints();

		/**
		* @brief Sets a the vertex point
		* @param[in] vert (Vertex) vertex
		* @param[in] index (const int&) the index of the vertex to be set
		*/
		void SetPoint(const Vertex& vert, const int& index);

		/**
		* @brief Adds a the vertex point
		* @param[in] vert (Vertex) vertex
		*/
		void AddPoint(const Vertex& vert);

		/**
		* @brief Get a the vertex point
		* @param[in] index (const int&) the index of the vertex to be gotten
		*/
		const Vertex& GetPoint(const int& index);

		/**
		* @brief Sets the indices
		* @param[in] indices (const std::vector<int>&) the indices
		*/
		void SetIndices(const std::vector<int>& indices);

		/**
		* @brief Gets the indices
		*/
		const std::vector<int>& GetIndices();

		/**
		* @brief Sets the topology
		* @param[in] topology (const D3D11_PRIMITIVE_TOPOLOGY&) the topology
		*/
		void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology);

		/**
		* @brief Gets the topology
		*/
		const D3D11_PRIMITIVE_TOPOLOGY& GetTopology();

		/**
		* @brief Registers this object's functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		/**
		* @brief Sets this object's points via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetPoints(lua_State* L);

		/**
		* @brief Gets this object's points via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetPoints(lua_State* L);

		/**
		* @brief Sets a vertex point via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetPoint(lua_State* L);

		/**
		* @brief Gets a vertex point via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetPoint(lua_State* L);

		/**
		* @brief Add a vertex point via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaAddPoint(lua_State* L);

		/**
		* @brief Set the topology via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetTopology(lua_State* L);

		/**
		* @brief Get the topology via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetTopology(lua_State* L);

		/**
		* @brief Sets the indices
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetIndices(lua_State* L);

		/**
		* @brief Gets the indices
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetIndices(lua_State* L);

		CLASSNAME("Polygon");
	private:
		std::vector<Vertex> vertices_;
		std::vector<int> indices_;
		D3D11_PRIMITIVE_TOPOLOGY topology_;
	};
}