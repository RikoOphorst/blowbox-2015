#include "content_manager.h"
#include <fstream>

namespace blowbox
{
	ContentManager::ContentManager()
	{
		
	}

	ContentManager::~ContentManager()
	{
		
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
				SharedPtr<D3D11Texture> texture(new D3D11Texture(it.path));
				loaded_textures_.emplace(it.path, texture);
				break;
			}
			
			pending_content_.pop();
		}
	}

	D3D11Texture* ContentManager::GetTexture(std::string path)
	{
		std::map<std::string, SharedPtr<D3D11Texture>>::const_iterator tex = FindTexture(path);
		if (tex != loaded_textures_.end())
		{
			return tex->second.get();
		}
		else
		{
			return LoadTexture(path);
		}

		return nullptr;
	}

	std::map<std::string, SharedPtr<D3D11Texture>>::const_iterator ContentManager::FindTexture(std::string path)
	{
		std::map<std::string, SharedPtr<D3D11Texture>>::const_iterator tex = loaded_textures_.find(path);
		return tex;
	}

	D3D11Texture* ContentManager::LoadTexture(std::string path)
	{
		std::map<std::string, SharedPtr<D3D11Texture>>::const_iterator tex = FindTexture(path);
		if (tex != loaded_textures_.end())
		{
			tex->second.get()->Set(path);
			return tex->second.get();
		}
		else
		{
			SharedPtr<D3D11Texture> texture(new D3D11Texture(path));
			loaded_textures_.emplace(path, texture);

			return texture.get();
		}
	}
}