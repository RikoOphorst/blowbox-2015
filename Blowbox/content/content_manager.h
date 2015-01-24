#pragma once

#include <map>
#include <queue>
#include "../memory/shared_ptr.h"
#include "../d3d11/d3d11_texture.h"
#include "content.h"

namespace blowbox
{
	template<typename T>
	class Content;
	
	class D3D11Texture;

	class ContentManager
	{
	public:
		enum ContentTypes
		{
			kTexture,
			kShader
		};

		struct PendingContent
		{
			std::string path;
			ContentTypes type;
		};
	public:
		ContentManager();
		~ContentManager();

		static ContentManager* Instance();

		void Update();

		D3D11Texture* GetTexture(std::string path);
		D3D11Texture* LoadTexture(std::string path);
		std::map<std::string, SharedPtr<D3D11Texture>>::const_iterator FindTexture(std::string path);
	private:
		std::map<std::string, SharedPtr<D3D11Texture>>		loaded_textures_;
		std::queue<PendingContent>									pending_content_;
	};
}