#pragma once

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/memory/shared_ptr.h"
#include <map>
#include <queue>

namespace blowbox
{
	class D3D11RenderElement;

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
		*/
		void Create();
	private:
		ID3D11Texture2D*						target_;
		ID3D11RenderTargetView*					view_;
		ID3D11ShaderResourceView*				resource_;
		std::queue<D3D11RenderElement*>			queue_;
		std::vector<D3D11RenderElement*>		render_elements_;
		std::vector<D3D11RenderElement*>		opaque_elements_;
		std::vector<D3D11RenderElement*>		ui_elements_;
	};
}