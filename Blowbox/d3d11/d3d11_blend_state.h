#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	/**
	* @class blowbox::D3D11BlendState
	* @brief Handles blend states
	* @author Riko Ophorst
	*/
	class D3D11BlendState
	{
	public:
		/**
		* @brief Default D3D11BlendState constructor
		*/
		D3D11BlendState();

		/**
		* @brief Default D3D11BlendState destructor
		*/
		~D3D11BlendState();

		/**
		* @brief Sets the context
		* @param[in] context (ID3D11DeviceContext*) the context
		*/
		void Set(ID3D11DeviceContext* context);
	private:
		ID3D11BlendState* state_;
	};
}