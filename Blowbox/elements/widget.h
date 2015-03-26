#pragma once

#include "../../blowbox/d3d11/d3d11_render_element.h"

namespace blowbox
{
	/**
	* @class blowbox::Widget
	* @brief A simple UI widget
	* @author Riko Ophorst
	*/
	class Widget : public D3D11RenderElement
	{
	public:
		/**
		* @brief Default Widget constructor
		*/
		Widget();

		/**
		* @brief Lua Widget constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Widget(lua_State* L);

		/**
		* @brief Default Widget destructor
		*/
		~Widget();

		/**
		* @brief Creates the vertex buffer
		*/
		void Create();

		CLASSNAME("Widget");
	private:
	};
}