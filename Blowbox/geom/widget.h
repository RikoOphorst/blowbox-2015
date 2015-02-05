#pragma once

#include "../d3d11/d3d11_display_device.h"
#include "../d3d11/d3d11_render_element.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

namespace blowbox
{
	class Widget : public D3D11RenderElement
	{
	public:
		Widget();
		Widget(lua_State* state);

		void CreateBuffers();
		void Draw();

		virtual XMMATRIX& GetWorld();

		Widget* GetParent();
		void SetParent(Widget* parent);

		void AddChild(Widget* widget);
		void RemoveChild(Widget* widget);

		static int RegisterFunctions(lua_State* state);
		virtual ~Widget();

		LM_NAME("Widget");
	private:
		Widget* parent_;
		std::vector<Widget*> children_;
		ID3D11Buffer* vertexBuffer_;
		ID3D11Buffer* indexBuffer_;
	};
}