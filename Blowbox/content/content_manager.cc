#include "../../blowbox/content/content_manager.h"

#include "../../blowbox/d3d11/d3d11_texture.h"
#include "../../blowbox/d3d11/d3d11_shader.h"
#include "../../blowbox/console/console.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	ContentManager::ContentManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	ContentManager::~ContentManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void ContentManager::LoadShader(const std::string& path)
	{
		if (shaders_.find(path) == shaders_.end())
		{
			D3D11Shader* shader = new D3D11Shader(path);

			shaders_.emplace(path, shader);
		}
	}

	void ContentManager::LoadTexture(const std::string& path)
	{
		if (textures_.find(path) == textures_.end())
		{
			D3D11Texture* texture = new D3D11Texture();

			textures_.emplace(path, texture);
		}
	}

	D3D11Shader* ContentManager::GetShader(const std::string& path)
	{
		auto it = shaders_.find(path);

		if (it != shaders_.end())
		{
			return it->second;
		}

		Console::Instance()->Log("[CONTENTMANAGER] Shader has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}

	D3D11Shader* ContentManager::GetShader(const std::string& path, bool& failed)
	{
		auto it = shaders_.find(path);

		failed = false;

		if (it != shaders_.end())
		{
			return it->second;
		}

		failed = true;

		Console::Instance()->Log("[CONTENTMANAGER] Shader has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}

	D3D11Texture* ContentManager::GetTexture(const std::string& path)
	{
		auto it = textures_.find(path);

		if (it != textures_.end())
		{
			return it->second;
		}

		Console::Instance()->Log("[CONTENTMANAGER] Texture has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}

	D3D11Texture* ContentManager::GetTexture(const std::string& path, bool& failed)
	{
		auto it = textures_.find(path);

		failed = false;

		if (it != textures_.end())
		{
			return it->second;
		}

		failed = true;

		Console::Instance()->Log("[CONTENTMANAGER] Texture has not yet been loaded but you did try to load it: " + path, LOG_COLOR_TYPES::LOG_COLOR_ERROR);

		return nullptr;
	}
}