#pragma once

#include <map>
#include <queue>
#include "../memory/shared_ptr.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

namespace blowbox
{
	template<typename T>
	class Content;
	
	class D3D11Texture;
	class D3D11Shader;

	class ContentManager : public LuaClass
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
		ContentManager(lua_State* state);

		~ContentManager();

		static ContentManager* Instance();

		static int RegisterFunctions(lua_State* state);

		static int Bla(lua_State* state){ std::cout << "lmao" << std::endl; return 0; };

		void Update();

		D3D11Texture* GetTexture(std::string path);
		D3D11Texture* LoadTexture(std::string path);

		D3D11Shader* GetShader(std::string path);
		D3D11Shader* LoadShader(std::string path);

		LM_NAME("Content");
	private:
		std::map<std::string, SharedPtr<D3D11Texture>>		loaded_textures_;
		std::map<std::string, SharedPtr<D3D11Shader>>		loaded_shaders_;
		std::queue<PendingContent>							pending_content_;
	};
}