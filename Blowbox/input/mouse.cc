#include "mouse.h"

namespace blowbox
{
	Mouse::Mouse()
		: pos_(0.0f, 0.0f)
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			mouseStates_[i].down = false;
			mouseStates_[i].pressed = false;
			mouseStates_[i].dbl = false;
		}
	}

	Mouse::Mouse(lua_State* state)
	{

	}

	Mouse* Mouse::Instance()
	{
		static SharedPtr<Mouse> ptr(new Mouse());
		return ptr.get();
	}

	XMFLOAT2& Mouse::GetPosition()
	{
		return pos_;
	}

	bool& Mouse::IsDown(MouseButton btn)
	{
		return mouseStates_[btn].down;
	}

	bool& Mouse::IsPressed(MouseButton btn)
	{
		return mouseStates_[btn].pressed;
	}

	bool& Mouse::IsDbl(MouseButton btn)
	{
		return mouseStates_[btn].dbl;
	}

	void Mouse::ResetStates()
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			mouseStates_[i].pressed = false;
			mouseStates_[i].dbl = false;
		}
	}

	void Mouse::ReceiveEvent(MouseMoveEvent evt)
	{
		moveQueue_.push(evt);
	}

	void Mouse::ReceiveEvent(MouseButtonEvent button)
	{
		clickQueue_.push(button);
	}

	void Mouse::Update()
	{
		ResetStates();

		while (!moveQueue_.empty())
		{
			const MouseMoveEvent& evt = moveQueue_.front();

			pos_.x = evt.x;
			pos_.y = evt.y;

			moveQueue_.pop();
		}

		while (!clickQueue_.empty())
		{
			const MouseButtonEvent& evt = clickQueue_.front();

			switch (evt.type)
			{
			case MouseDownEvent:
				mouseStates_[evt.button].pressed = true;
				mouseStates_[evt.button].down = true;
				break;
			case MouseUpEvent:
				mouseStates_[evt.button].down = false;
				break;
			case MouseDblEvent:
				mouseStates_[evt.button].dbl = true;
				break;
			}

			clickQueue_.pop();
		}
	}

	MouseButton Mouse::StringToButton(const char* name)
	{
		if (strcmp(name, "L") == 0 || strcmp(name, "l") == 0 || strcmp(name, "Left") == 0 || strcmp(name, "left") == 0)		return MouseButton::MouseLeft;
		if (strcmp(name, "M") == 0 || strcmp(name, "m") == 0 || strcmp(name, "Middle") == 0 || strcmp(name, "middle") == 0)	return MouseButton::MouseMiddle;
		if (strcmp(name, "R") == 0 || strcmp(name, "r") == 0 || strcmp(name, "Right") == 0 || strcmp(name, "right") == 0)	return MouseButton::MouseRight;

		//BLOW_BREAK("Error while attempting to convert string to button in Mouse class, given parameter:" + name);

		return MouseButton::MouseLeft;
	}

	std::string Mouse::ButtonToString(MouseButton button)
	{
		switch (button)
		{
		case MouseButton::MouseLeft:	return "Left";
		case MouseButton::MouseMiddle:	return "Middle";
		case MouseButton::MouseRight:	return "Right";
		default: return "Left";
		}
	}

	Mouse::~Mouse()
	{

	}

	int Mouse::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "getPosition", LuaGetPosition },
			{ "isDown", LuaIsDown },
			{ "isPressed", LuaIsPressed },
			{ "isDbl", LuaIsDbl },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

		return 1;
	}

	int Mouse::LuaGetPosition(lua_State* state)
	{
		XMFLOAT2 pos = Mouse::Instance()->GetPosition();
		LuaManager::PushValue(pos.x);
		LuaManager::PushValue(pos.y);
		return 2;
	}

	int Mouse::LuaIsDown(lua_State* state)
	{
		LuaManager::PushValue(Mouse::Instance()->IsDown(Mouse::StringToButton(LuaManager::GetValue<const char*>(0))));
		return 1;
	}

	int Mouse::LuaIsPressed(lua_State* state)
	{
		LuaManager::PushValue(Mouse::Instance()->IsPressed(Mouse::StringToButton(LuaManager::GetValue<const char*>(0))));
		return 1;
	}

	int Mouse::LuaIsDbl(lua_State* state)
	{
		LuaManager::PushValue(Mouse::Instance()->IsDbl(Mouse::StringToButton(LuaManager::GetValue<const char*>(0))));
		return 1;
	}
}