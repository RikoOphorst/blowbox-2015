#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	/**
	* @class blowbox::D3D11RasterizerState
	* @brief Handles rasterizer states
	* @author Riko Ophorst
	*/
	class D3D11RasterizerState
	{
	public:
		/**
		* @brief Default D3D11RasterizerState constructor
		*/
		D3D11RasterizerState();

		/**
		* @brief Default D3D11RasterizerState constructor
		* @param[in] fill (const D3D11_FILL_MODE&) the fill mode
		* @param[in] cull (const D3D11_CULL_MODE&) the cull mode
		*/
		D3D11RasterizerState(const D3D11_FILL_MODE& fill, const D3D11_CULL_MODE& cull);

		/**
		* @brief Default D3D11RasterizerState destructor
		*/
		~D3D11RasterizerState();

		/**
		* @brief Sets the rasterizer state
		* @param[in] context (ID3D11DeviceContext*) the context
		*/
		void Set(ID3D11DeviceContext* context);

		/**
		* @brief Sets the fill mode
		* @param[in] fill (const D3D11_FILL_MODE&) the fill mode
		*/
		void SetFillMode(const D3D11_FILL_MODE& fill);

		/**
		* @brief Sets the cull mode
		* @param[in] cull (const D3D11_CULL_MODE&) the cull mode
		*/
		void SetCullMode(const D3D11_CULL_MODE& cull);

		/**
		* @brief Retrieves the fill mode
		*/
		const D3D11_FILL_MODE& GetFillMode() const;

		/**
		* @brief Retrieves the cull mode
		*/
		const D3D11_CULL_MODE& GetCullMode() const;
	private:
		D3D11_FILL_MODE fill_mode_;
		D3D11_CULL_MODE cull_mode_;
		ID3D11RasterizerState* state_;
	};
}