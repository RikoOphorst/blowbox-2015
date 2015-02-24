#pragma once

#include "../../blowbox/logging.h"
#include "../../blowbox/memory/shared_ptr.h"

namespace blowbox
{
	class Window;
	class D3D11SwapChain;
	
	/**
	* @class blowbox::D3D11RenderDevice
	* @brief Handles all D3D11 rendering
	* @author Riko Ophorst
	*/
	class D3D11RenderDevice
	{
	public:
		/**
		* @brief Default D3D11RenderDevice constructor
		*/
		D3D11RenderDevice();

		/**
		* @brief Default D3D11RenderDevice destructor
		*/
		~D3D11RenderDevice();

		/**
		* @brief Retrieves a pointer to the D3D11RenderDevice instance
		* @return D3D11RenderDevice* A pointer to the D3D11RenderDevice instance
		*/
		static D3D11RenderDevice* Instance();

		/**
		* @brief Initialize DirectX
		* @param[in] window (Window*) The window in which DirectX should run
		*/
		void Initialize(Window* window);

		/**
		* @brief Starts the draw sequence
		*/
		void BeginDraw();

		/**
		* @brief Performs the draw for all render targets
		*/
		void Draw();

		/**
		* @brief Ends the draw sequence
		*/
		void EndDraw();

		/**
		* @brief Creates the backbuffer
		*/
		void CreateBackBuffer();

		/**
		* @return ID3D11Device* The Display Device from the Swap Chain
		*/
		ID3D11Device* GetDevice() const;
	private:
		SharedPtr<D3D11SwapChain> swap_chain_;
		ID3D11RenderTargetView* back_buffer_view_;
		ID3D11Texture2D* back_buffer_;
	};
}