#pragma once

#include "../../blowbox/logging.h"
#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	/**
	* @enum blowbox::TEXTURE_FILTERING_TYPE
	* @brief All the texture filtering type
	*/
	enum TEXTURE_FILTERING_TYPE
	{
		TEXTURE_POINT,
		TEXTURE_BILINEAR,
		TEXTURE_TRILINEAR,
		TEXTURE_ANISOTROPIC
	};

	/**
	* @class blowbox::D3D11SamplerState
	* @brief Handles sampler states
	* @author Riko Ophorst
	*/
	class D3D11SamplerState
	{
	public:
		/**
		* @brief Default D3D11SamplerState constructor
		* @param[in] type (const TEXTURE_FILTERING_TYPE&) the type of texture filtering
		*/
		D3D11SamplerState(const TEXTURE_FILTERING_TYPE& type);

		/**
		* @brief Default D3D11SamplerState destructor
		*/
		~D3D11SamplerState();

		/**
		* @brief Sets the sampler state to the context
		* @param[in] context (ID3D11DeviceContext* context);
		*/
		void Set(ID3D11DeviceContext* context);

		/**
		* @brief Retrieves sampler state types
		* @param[in] type (const TEXTURE_FILTERING_TYPE&) the type of texture filtering
		*/
		static D3D11SamplerState* GetSamplerState(const TEXTURE_FILTERING_TYPE& type);
	private:
		ID3D11SamplerState* state_;
	};
}