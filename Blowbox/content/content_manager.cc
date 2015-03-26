#include "../../blowbox/content/content_manager.h"

#include "../../blowbox/d3d11/d3d11_texture.h"
#include "../../blowbox/d3d11/d3d11_shader.h"
#include "../../blowbox/console/console.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	ContentManager::ContentManager()
	{
		LoadShader(BLOW_BASE_SHADER);
		LoadTexture(BLOW_BASE_TEXTURE);

		lua_functions = std::map<std::string, lua_CFunction>({
			{ "loadShader", LuaLoadShader },
			{ "loadTexture", LuaLoadTexture }
		});
	}

	//------------------------------------------------------------------------------------------------------
	ContentManager::~ContentManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	ContentManager* ContentManager::Instance()
	{
		static SharedPtr<ContentManager> ptr(new ContentManager());
		return ptr.get();
	}

	/************
	** SHADERS **
	*************/

	//------------------------------------------------------------------------------------------------------
	void ContentManager::LoadShader(const std::string& path)
	{
		auto it = shaders_.find(path);
		
		if (it == shaders_.end())
		{
			D3D11Shader* shader = new D3D11Shader(path);

			shaders_.emplace(path, shader);

			Console::Instance()->Log("[CONTENTMANAGER] Loaded a new shader: " + path, LOG_COLOR_TYPES::LOG_COLOR_NOTICE);
		}
		else
		{
			it->second->Reload();
		}
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Shader* ContentManager::GetShader(const std::string& path)
	{
		auto it = shaders_.find(path);

		if (it != shaders_.end())
		{
			return it->second.get();
		}

		Console::Instance()->Log("[CONTENTMANAGER] Shader has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}

	//------------------------------------------------------------------------------------------------------
	bool ContentManager::IsShaderLoaded(const std::string& path)
	{
		if (shaders_.find(path) != shaders_.end())
			return true;

		return false;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Shader* ContentManager::GetShader(const std::string& path, bool& failed)
	{
		auto it = shaders_.find(path);

		failed = false;

		if (it != shaders_.end())
		{
			return it->second.get();
		}

		failed = true;

		Console::Instance()->Log("[CONTENTMANAGER] Shader has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}

	/*************
	** TEXTURES **
	**************/

	//------------------------------------------------------------------------------------------------------
	void ContentManager::LoadTexture(const std::string& path)
	{
		auto it = textures_.find(path);
		
		if (it == textures_.end() || path == BLOW_BASE_TEXTURE)
		{
			D3D11Texture* texture = new D3D11Texture(path);

			textures_.emplace(path, texture);

			Console::Instance()->Log("[CONTENTMANAGER] Loaded a new texture: " + path, LOG_COLOR_TYPES::LOG_COLOR_NOTICE);
		}
		else
		{
			it->second->Reload();
		}
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Texture* ContentManager::GetTexture(const std::string& path)
	{
		auto it = textures_.find(path);

		if (it != textures_.end())
		{
			return it->second.get();
		}

		Console::Instance()->Log("[CONTENTMANAGER] Texture has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Texture* ContentManager::GetTexture(const std::string& path, bool& failed)
	{
		auto it = textures_.find(path);

		failed = false;

		if (it != textures_.end())
		{
			return it->second.get();
		}

		failed = true;

		Console::Instance()->Log("[CONTENTMANAGER] Texture has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}

	//------------------------------------------------------------------------------------------------------
	bool ContentManager::IsTextureLoaded(const std::string& path)
	{
		if (textures_.find(path) != textures_.end())
			return true;

		return false;
	}

	//------------------------------------------------------------------------------------------------------
	void ContentManager::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {

			{ "loadShader", LuaLoadShader },
			{ "loadTexture", LuaLoadTexture },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int ContentManager::LuaLoadShader(lua_State* L)
	{
		ContentManager::Instance()->LoadShader(LuaWrapper::Instance()->Get<std::string>(L, 1));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int ContentManager::LuaLoadTexture(lua_State* L)
	{
		ContentManager::Instance()->LoadTexture(LuaWrapper::Instance()->Get<std::string>(L, 1));

		return 0;
	}
}