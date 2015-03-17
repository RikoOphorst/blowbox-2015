#pragma once

#include <map>
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	class D3D11Texture;
	class D3D11Shader;
	
	class ContentManager: public LuaClass
	{
	public:
		ContentManager();

		~ContentManager();

		ContentManager* Instance();

		void LoadShader(const std::string& path);

		void LoadTexture(const std::string& path);

		D3D11Shader* GetShader(const std::string& path);

		D3D11Shader* GetShader(const std::string& path, bool& failed);

		D3D11Texture* GetTexture(const std::string& path);

		D3D11Texture* GetTexture(const std::string& path, bool& failed);
	private:
		std::map<std::string, D3D11Texture*> textures_;
		std::map<std::string, D3D11Shader*> shaders_;
	};
}