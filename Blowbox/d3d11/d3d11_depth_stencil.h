#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	/**
	* @class blowbox::D3D11DepthStencil
	* @brief Handles depth stenciling
	* @author Riko Ophorst
	*/
	class D3D11DepthStencil
	{
	public:
		/**
		* @brief Default D3D11DepthStencil constructor
		*/
		D3D11DepthStencil();

		/**
		* @brief Default D3D11DepthStencil destructor
		*/
		~D3D11DepthStencil();

		/**
		* @brief Retrieves the depth stencil view
		*/
		ID3D11DepthStencilView* GetView();

		/**
		* @brief Retrieves the depth stencil state
		*/
		ID3D11DepthStencilState* GetState();

		/**
		* @brief Retrieves the depth stencil buffer
		*/
		ID3D11Texture2D* GetBuffer();

		/**
		* @brief Sets the depth stencil state to the context
		* @param[in] context (ID3D11DeviceContext*) the context
		*/
		void Set(ID3D11DeviceContext* context);

		/**
		* @brief Creates the depth stencil
		*/
		void Create();

		/**
		* @brief Releases COM objects
		*/
		void Release();
	private:
		ID3D11DepthStencilState* state_;
		ID3D11DepthStencilView* view_;
		ID3D11Texture2D* buffer_;
	};
}