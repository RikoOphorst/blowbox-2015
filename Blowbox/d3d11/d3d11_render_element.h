#pragma once

#include "d3d11_display_device.h"
#include "d3d11_texture.h"
#include "d3d11_shader.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

namespace blowbox
{
	class D3D11RenderElement: public LuaClass
	{
	public:
		D3D11RenderElement();
		~D3D11RenderElement();

		virtual void						Draw() = 0;
		virtual XMMATRIX&					GetWorld();

		void								SetTexture(std::string path);
		D3D11Texture*						GetTexture();

		void								SetShader(std::string path);
		D3D11Shader*						GetShader();

		void								SetPosition(float x, float y, float z);
		void								SetRotation(float x, float y, float z);
		void								SetScale(float x, float y, float z);
		void								SetSize(float w, float h);
		void								SetAlpha(float a);

		D3D11_PRIMITIVE_TOPOLOGY			GetTopology();
		void								SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);

		XMVECTOR&							GetPosition();
		XMVECTOR&							GetRotation();
		XMVECTOR&							GetScale();
		XMFLOAT2&							GetSize();
		float&								GetAlpha();

		static int							LuaSetTexture(lua_State* state);
		static int							LuaSetShader(lua_State* state);
		static int							LuaSetPosition(lua_State* state);
		static int							LuaSetRotation(lua_State* state);
		static int							LuaSetScale(lua_State* state);
		static int							LuaSetSize(lua_State* state);
		static int							LuaSetAlpha(lua_State* state);

		static int							LuaGetTexture(lua_State* state);
		static int							LuaGetShader(lua_State* state);
		static int							LuaGetPosition(lua_State* state);
		static int							LuaGetRotation(lua_State* state);
		static int							LuaGetScale(lua_State* state);
		static int							LuaGetSize(lua_State* state);
		static int							LuaGetAlpha(lua_State* state);
	private:
		XMMATRIX 							world_;
		XMVECTOR 							position_;
		XMVECTOR							rotation_;
		XMVECTOR							scale_;
		XMFLOAT2							size_;
		D3D11Texture*						texture_;
		D3D11Shader*						shader_;
		D3D11_PRIMITIVE_TOPOLOGY			topology_;
		float								alpha_;
	};
}