#pragma once

#include <map>
#include "../../blowbox/lua/lua_class.h"
#include "../../blowbox/memory/shared_ptr.h"

namespace blowbox
{
	class D3D11Texture;
	class D3D11Shader;
	
	/**
	* @class blowbox::ContentManager
	* @brief Manages all the content used in the game
	* @author Riko Ophorst
	*/
	class ContentManager: public LuaClass
	{
	public:
		/**
		* @brief Default ContentManager constructor
		*/
		ContentManager();

		/**
		* @brief Default ContentManager destructor
		*/
		~ContentManager();

		/**
		* @brief Retrieves the ContentManager instance
		*/
		static ContentManager* Instance();

		/************
		** SHADERS **
		*************/
		
		/**
		* @brief Loads a shader into the contentmanager
		* @param[in] path (const std::string&) the path to the shader file
		*/
		void LoadShader(const std::string& path);

		/**
		* @brief Retrieves a shader
		* @param[in] path (const std::string&) the path to the shader file
		*/
		D3D11Shader* GetShader(const std::string& path);

		/**
		* @brief Retrieves a shader
		* @param[in] path (const std::string&) the path to the shader file
		* @param[out] failed (bool&) did the shader retrieval call fail?
		*/
		D3D11Shader* GetShader(const std::string& path, bool& failed);
		
		/**
		* @brief Is the given shader loaded?
		* @param[in] path (const std::string&) the path to the shader file
		*/
		bool IsShaderLoaded(const std::string& path);

		/*************
		** TEXTURES **
		**************/

		/**
		* @brief Loads a texture into the contentmanager
		* @param[in] path (const std::string&) the path to the texture file
		*/
		void LoadTexture(const std::string& path);

		/**
		* @brief Retrieves a texture
		* @param[in] path (const std::string&) the path to the texture file
		*/
		D3D11Texture* GetTexture(const std::string& path);

		/**
		* @brief Retrieves a texture
		* @param[in] path (const std::string&) the path to the texture file
		* @param[out] failed (bool&) did the texture retrieval call fail?
		*/
		D3D11Texture* GetTexture(const std::string& path, bool& failed);

		/**
		* @brief Is the given texture loaded?
		* @param[in] path (const std::string&) the path to the texture file
		*/
		bool IsTextureLoaded(const std::string& path);

		/*************
		**    LUA   **
		**************/

		/**
		* @brief Loads a shader from lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaLoadShader(lua_State* L);

		/**
		* @brief Loads a texture from lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaLoadTexture(lua_State* L);

		CLASSNAME("ContentManager");
	private:
		std::map<std::string, SharedPtr<D3D11Texture>> textures_;
		std::map<std::string, SharedPtr<D3D11Shader>> shaders_;
	};
}