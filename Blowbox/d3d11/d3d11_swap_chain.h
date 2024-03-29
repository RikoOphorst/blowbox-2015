#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/d3d11/d3d11_settings.h"

namespace blowbox
{
	class Window;
	
	/**
	* @class blowbox::D3D11SwapChain
	* @brief Handles the swapchain
	* @
	*/
	class D3D11SwapChain
	{
	public:
		/**
		* @brief Default D3D11SwapChain constructor
		* @param[in] window (Window*) The window to which the swap chain should bind
		*/
		D3D11SwapChain(Window* window);

		/**
		* @brief Default D3D11SwapChain destructor
		*/
		~D3D11SwapChain();

		/**
		* @brief Initializes the swap chain
		* @param[in] window (Window*) The window to which the swap chain should bind
		*/
		void Initialize(Window* window);

		/**
		* @brief Creates the swap chain
		* @param[in] window (Window*) The window to which the swap chain should bind
		*/
		void Create(Window* window);

		/**
		* @return IXGISwapChain* The swap chain
		*/
		IDXGISwapChain* GetSwapChain();

		/**
		* @return ID3D11Device* The device
		*/
		ID3D11Device* GetDevice();

		/**
		* @return ID3D11DeviceContext* The context
		*/
		ID3D11DeviceContext* GetContext();

		/**
		* @brief Sets the width & height
		* @param[in] width (const float&) the width
		* @param[in] height (const float&) the height
		*/
		void SetResolution(const float& width, const float& height);

		/**
		* @brief Gets the width & height
		*/
		const Resolution& GetResolution();
	private:
		IDXGISwapChain*						swap_chain_;
		ID3D11Device*						device_;
		ID3D11DeviceContext*				context_;
		Resolution							resolution_;
	};
}