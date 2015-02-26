#pragma once

#include "../../blowbox/logging.h"
#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/d3d11/d3d11.h"

#include <map>

namespace blowbox
{
	class Window;
	class D3D11SwapChain;
	class D3D11RenderTarget;
	class D3D11Viewport;
	class D3D11VertexBuffer;
	enum BUFFER_TYPE;
	
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
		* @brief Starts drawing all the render targets
		*/
		void Draw();

		/**
		* @brief Draws a specific render target
		* @param[in] render_target (D3D11RenderTarget*) the render target to be rendered
		*/
		void DrawRenderTarget(D3D11RenderTarget* render_target);

		/**
		* @brief Add a render target
		*/
		void AddRenderTarget(const std::string& name, D3D11RenderTarget* render_target);

		/**
		* @return The corresponding render target
		* @param[in] name (const std::string&) the name of the render target
		*/
		D3D11RenderTarget* GetRenderTarget(const std::string& name);

		/**
		* @return ID3D11Device* The Display Device from the Swap Chain
		*/
		ID3D11Device* GetDevice() const;

		/**
		* @return IDXGISwapChain* The swap chain from the Swap Chain instance
		*/
		IDXGISwapChain* GetSwapChain() const;

		/**
		* @return ID3D11DeviceContext* The context from the Swap Chain instance
		*/
		ID3D11DeviceContext* GetContext() const;

		/**
		* @return D3D11Viewport* The viewport of the device
		*/
		D3D11Viewport* GetViewport() const;

		/**
		* @return const BUFFER_TYPES& The last set buffer type
		*/
		const BUFFER_TYPE& GetBufferType() const;

		/**
		* @brief Sets the buffer type
		* @param[in] buffer_type (const BUFFER_TYPE&) The buffer type to be set
		*/
		void SetBufferType(const BUFFER_TYPE& buffer_type);

		/**
		* @return Gets the back buffer
		*/
		D3D11RenderTarget* GetBackBuffer() const;
	private:
		SharedPtr<D3D11SwapChain> swap_chain_manager_;
		IDXGISwapChain* swap_chain_;
		ID3D11DeviceContext* context_;
		ID3D11Device* device_;

		SharedPtr<D3D11RenderTarget> back_buffer_;
		SharedPtr<D3D11Viewport> viewport_;

		SharedPtr<D3D11VertexBuffer> screen_quad_;

		SharedPtr<D3D11RenderTarget> target_;

		std::map<std::string, D3D11RenderTarget*> render_targets_;

		BUFFER_TYPE buffer_type_;
	};
}