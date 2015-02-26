#pragma once

#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	/**
	* @class blowbox::D3D11Viewport
	* @brief Handles viewports
	* @author Riko Ophorst
	*/
	class D3D11Viewport
	{
	public:
		/**
		* @brief Default D3D11Viewport constructor
		*/
		D3D11Viewport();

		/**
		* @brief Default D3D11Viewport constructor
		* @param[in] minDepth (float) the minimal depth of the viewport
		* @param[in] maxDepth (float) the maximal depth of the viewport
		*/
		D3D11Viewport(float minDepth, float mexDepth);

		/**
		* @brief Default D3D11Viewport constructor
		* @param[in] x (float) the top left x coordinate
		* @param[in] y (float) the top left y coordinate
		* @param[in] width (float) the width of the viewport
		* @param[in] height (float) the height of the viewport
		* @param[in] minDepth (float) the minimal depth of the viewport
		* @param[in] maxDepth (float) the maximal depth of the viewport
		*/
		D3D11Viewport(float x, float y, float width, float height, float minDepth, float maxDepth);

		/**
		* @brief Default D3D11Viewport destructor
		*/
		~D3D11Viewport();

		/**
		* @brief Sets the viewport to the device context
		*/
		void Set();
	private:
		D3D11_VIEWPORT viewport_;
	};
}