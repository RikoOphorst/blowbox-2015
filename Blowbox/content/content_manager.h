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
	
	class ContentManager
	{
	public:
		enum ContentTypes
		{
			kTexture,
		};

		struct PendingContent
		{
			std::string path;
			ContentTypes type;
		};
	public:
		ContentManager();
		~ContentManager();

		void LoadTexture(std::string path);
	private:
		std::map<std::string, SharedPtr<Content<D3D11Texture>>>		loaded_textures_;
		std::queue<PendingContent>									pending_content_;
	};
}