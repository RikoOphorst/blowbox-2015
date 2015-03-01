#pragma once

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/memory/shared_ptr.h"
#include <map>
#include <queue>

namespace blowbox
{
	class D3D11RenderElement;
	class D3D11RenderQueue;

	/**
	* @enum blowbox::RENDER_TARGET_TYPE
	* @brief Describes a type of render target
	*/
	enum RENDER_TARGET_TYPE
	{
		RENDER_TARGET_TYPE_BACKBUFFER,
		RENDER_TARGET_TYPE_RENDER_TARGET
	};

	/**
	* @class blowbox::D3D11RenderTarget
	* @brief A RenderTarget handler
	* @author Riko Ophorst
	*/
	class D3D11RenderTarget
	{
	public:
		/**
		* @brief Default D3D11RenderTarget constructor
		*/
		D3D11RenderTarget();

		/**
		* @brief Default D3D11RenderTarget constructor
		*/
		~D3D11RenderTarget();

		/**
		* @brief Creates the render target
		* @param[in] type (RENDER_TARGET_TYPE) the type of render target
		* @param[in] swap_chain (IDXGISwapChain*) the swap chain
		* @param[in] device (ID3D11Device*) the device
		*/
		void Create(RENDER_TARGET_TYPE type, IDXGISwapChain* swap_chain, ID3D11Device* device);

		/**
		* @brief Sets this render target
		* @param[in] context (ID3D11DeviceContext*) the device context
		*/
		void Set(ID3D11DeviceContext* context);

		/**
		* @brief Draws this render target
		* @param[in] context (ID3D11DeviceContext*) the device context
		*/
		void Draw(ID3D11DeviceContext* context);

		/**
		* @brief Clear this render target
		* @param[in] context (ID3D11DeviceContext*) the device context
		*/
		void Clear(ID3D11DeviceContext* context);

		/**
		* @return ID3D11RenderTargetView* The render target
		*/
		ID3D11Texture2D* GetTarget() const;

		/**
		* @return ID3D11RenderTargetView* The render target view
		*/
		ID3D11RenderTargetView* GetView() const;

		/**
		* @return ID3D11RenderTargetView* The render target resource
		*/
		ID3D11ShaderResourceView* GetResource() const;

		/**
		* @return D3D11RenderQueue* The render queue of this render target
		*/
		D3D11RenderQueue* GetQueue();
	private:
		RENDER_TARGET_TYPE						type_;
		ID3D11Texture2D*						target_;
		ID3D11RenderTargetView*					view_;
		ID3D11ShaderResourceView*				resource_;
		SharedPtr<D3D11RenderQueue>				queue_;
		std::vector<D3D11RenderElement*>		render_elements_;
		std::vector<D3D11RenderElement*>		ui_elements_;
	};
}