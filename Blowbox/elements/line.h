#pragma once

#include <vector>

#include "../../blowbox/lua/lua_class.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_shader.h"

#define BASE_LINE_SHADER "shaders/line.fx"

namespace blowbox
{
	/**
	* @class blowbox::Line
	* @brief Draws debug lines on top of the screen - Note: Line does not inherit from anything except LuaClass, because it is meant to be used as a debugging tool so it should stand on its own
	* @author Riko Ophorst
	*/
	class Line: public LuaClass
	{
	public:
		/**
		* @brief Default Line constructor
		*/
		Line();

		/**
		* @brief Lua Line constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Line(lua_State* L);

		/**
		* @brief Default Line destructor
		*/
		~Line();

		/**
		* @brief Gets the Line instance
		*/
		static Line* Instance();

		/**
		* @brief Pushes a vertex - Note: not const referenced, because of the way LuaDraw works
		* @param[in] vert (Vertex) the vertex
		*/
		void Push(Vertex vert);

		/**
		* @brief Sets the shader
		* @param[in] path (const std::string&) the path to the shader
		*/
		void SetShader(const std::string& path);

		/**
		* @brief Gets the shader
		*/
		D3D11Shader* GetShader();

		/**
		* @brief Draws all the debugging lines
		* @param[in] context (Id3D11DeviceContext*) the context
		*/
		void Draw(ID3D11DeviceContext* context);

		/**
		* @brief Registers this object's functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		/**
		* @brief Adds two vertex points to the line instance
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaDraw(lua_State* L);

		/**
		* @brief Sets the line's shader
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetShader(lua_State* L);

		/**
		* @brief Gets the line's shader
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetShader(lua_State* L);

		CLASSNAME("Line");
	private:
		SharedPtr<D3D11VertexBuffer> buffer_;
		std::vector<Vertex> lines_;
		D3D11Shader* shader_;
	};
}