#pragma once

#include <string>

#include "../../blowbox/d3d11/d3d11.h"

#define BLOW_BASE_TEXTURE "base_texture.png"

namespace blowbox
{
	/**
	* @class blowbox::D3D11Texture
	* @brief Creates a shader
	* @author Riko Ophorst
	*/
	class D3D11Texture
	{
	public:
		/**
		* @brief Default D3D11Texture constructor
		* @param[in] path (const std::string&) the path to the texture file
		*/
		D3D11Texture(const std::string& path);

		/**
		* @brief Default D3D11Texture destructor
		*/
		~D3D11Texture();

		/**
		* @brief Reloads this texture
		*/
		bool Reload();

		/**
		* @brief Gets the actual resource
		*/
		ID3D11ShaderResourceView* GetResource();

		/**
		* @brief Sets the resources
		* @param[in] context (ID3D11DeviceContext*) the context
		* @param[in] slot (const int&) the slot at which the texture should be placed
		*/
		void Set(ID3D11DeviceContext* context, const int& slot = 0);
	private:
		ID3D11ShaderResourceView* resource_;
		std::string path_;
	};
}