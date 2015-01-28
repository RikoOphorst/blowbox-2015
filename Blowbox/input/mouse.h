#pragma once

#include "../memory/shared_ptr.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"
#include <xnamath.h>
#include <queue>

namespace blowbox
{
	struct MouseMoveEvent
	{
		float x;
		float y;
	};

	enum MouseButtonType
	{
		MouseDownEvent,
		MouseUpEvent,
		MouseDblEvent
	};

	enum MouseButton
	{
		MouseLeft,
		MouseMiddle,
		MouseRight
	};

	struct MouseState
	{
		bool down;
		bool pressed;
		bool dbl;
	};

	struct MouseButtonEvent
	{
		MouseButtonType type;
		MouseButton button;
	};

	class Mouse : public LuaClass
	{
	public:
		Mouse();
		Mouse(lua_State* state);
		~Mouse();

		static Mouse*					Instance();

		static int						RegisterFunctions(lua_State* state);
		
		static int						LuaGetPosition(lua_State* state);
		static int						LuaIsDown(lua_State* state);
		static int						LuaIsPressed(lua_State* state);
		static int						LuaIsDbl(lua_State* state);

		XMFLOAT2&						GetPosition();
		bool&							IsDown(MouseButton btn);
		bool&							IsPressed(MouseButton btn);
		bool&							IsDbl(MouseButton btn);

		void							ResetStates();
		void							Update();

		void							ReceiveEvent(MouseMoveEvent moveEvent);
		void							ReceiveEvent(MouseButtonEvent buttonEvent);

		static MouseButton				StringToButton(const char* string);
		static std::string				ButtonToString(MouseButton button);
		
		LM_NAME("Mouse");
	private:
		XMFLOAT2						pos_;
		std::queue<MouseMoveEvent>		moveQueue_;
		std::queue<MouseButtonEvent>	clickQueue_;
		MouseState						mouseStates_[3];
	};
}