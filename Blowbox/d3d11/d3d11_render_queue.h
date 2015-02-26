#pragma once

#include <vector>

#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	class D3D11RenderElement;
	
	/**
	* @class blowbox::D3D11RenderQueue
	* @brief Handles render queues of render elements
	*/
	class D3D11RenderQueue
	{
	public:
		/**
		* @brief Default D3D11RenderQueue constructor
		*/
		D3D11RenderQueue();

		/**
		* @brief Default D3D11RenderQueue destructor
		*/
		~D3D11RenderQueue();

		/**
		* @brief Draws all the elements
		* @param[in] context (ID3D11DeviceContext*) the device context
		*/
		void Draw(ID3D11DeviceContext* context);

		/**
		* @brief Adds an element to the queue
		*/
		void Add(D3D11RenderElement* element);

		/**
		* @brief Draws a specific element
		* @param[in] context (ID3D11DeviceContext*) the device context
		* @param[in] element (D3D11RenderElement*) the element to be rendered
		*/
		void DrawElement(ID3D11DeviceContext* context, D3D11RenderElement* element);
	private:
		std::vector<D3D11RenderElement*> queue_;
	};
}