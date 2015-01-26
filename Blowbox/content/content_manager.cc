#include "content_manager.h"

#include "../d3d11/d3d11_texture.h"
#include "../d3d11/d3d11_shader.h"

namespace blowbox
{
	ContentManager::ContentManager()
	{
		
	}

	ContentManager::ContentManager(lua_State* state)
	{
		
	};

	ContentManager::~ContentManager()
	{
		
	}

	int ContentManager::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "bla", Bla },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

		return 1;
	}

	ContentManager* ContentManager::Instance()
	{
		static SharedPtr<ContentManager> ptr(new ContentManager());
		return ptr.get();
	}

	void ContentManager::Update()
	{
		while (!pending_content_.empty())
		{
			auto it = pending_content_.front();
			
			switch (it.type)
			{
			case ContentTypes::kTexture:
				LoadTexture(it.path);
				break;
			case ContentTypes::kShader:
				LoadShader(it.path);
				break;
			}
			
			pending_content_.pop();
		}
	}

	D3D11Texture* ContentManager::GetTexture(std::string path)
	{
		const auto& it = loaded_textures_.find(path);
		if (it != loaded_textures_.end())
		{
			return it->second.get();
		}
		else
		{
			return LoadTexture(path);
		}

		return nullptr;
	}

	D3D11Texture* ContentManager::LoadTexture(std::string path)
	{
		const auto& it = loaded_textures_.find(path);
		if (it != loaded_textures_.end())
		{
			it->second->Set(path);
			return it->second.get();
		}
		else
		{
			SharedPtr<D3D11Texture> texture(new D3D11Texture(path));
			D3D11Texture* tex = texture.get();
			loaded_textures_.emplace(path, std::move(texture));

			return tex;
		}
	}

	D3D11Shader* ContentManager::GetShader(std::string path)
	{
		const auto& it = loaded_shaders_.find(path);
		if (loaded_shaders_.find(path) != loaded_shaders_.end())
		{
			return it->second.get();
		}
		else
		{
			return LoadShader(path);
		}

		return nullptr;
	}

	D3D11Shader* ContentManager::LoadShader(std::string path)
	{
		const auto& it = loaded_shaders_.find(path);
		if (it != loaded_shaders_.end())
		{
			it->second.get()->Set(path);
			return it->second.get();
		}
		else
		{
			SharedPtr<D3D11Shader> shader(new D3D11Shader(path));
			D3D11Shader* ptr = shader.get();
			loaded_shaders_.emplace(path, std::move(shader));

			return ptr;
		}
	}
}