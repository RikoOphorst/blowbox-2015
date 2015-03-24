#include "mouse.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Mouse::Mouse() : 
		pos_(0.0f, 0.0f)
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			mouseStates_[i].down = false;
			mouseStates_[i].pressed = false;
			mouseStates_[i].dbl = false;
		}
	}

	//------------------------------------------------------------------------------------------------------
	Mouse::Mouse(lua_State* L) :
		LuaClass(L),
		pos_(0.0f, 0.0f)
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			mouseStates_[i].down = false;
			mouseStates_[i].pressed = false;
			mouseStates_[i].dbl = false;
		}
	}

	//------------------------------------------------------------------------------------------------------
	Mouse::~Mouse()
	{

	}

	//------------------------------------------------------------------------------------------------------
	Mouse* Mouse::Instance()
	{
		static SharedPtr<Mouse> ptr(new Mouse());
		return ptr.get();
	}

	XMFLOAT2& Mouse::GetPosition()
	{
		return pos_;
	}

	//------------------------------------------------------------------------------------------------------
	bool& Mouse::IsDown(MouseButton btn)
	{
		return mouseStates_[btn].down;
	}

	//------------------------------------------------------------------------------------------------------
	bool& Mouse::IsPressed(MouseButton btn)
	{
		return mouseStates_[btn].pressed;
	}

	//------------------------------------------------------------------------------------------------------
	bool& Mouse::IsDbl(MouseButton btn)
	{
		return mouseStates_[btn].dbl;
	}

	//------------------------------------------------------------------------------------------------------
	void Mouse::ResetStates()
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			mouseStates_[i].pressed = false;
			mouseStates_[i].dbl = false;
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Mouse::ReceiveEvent(MouseMoveEvent evt)
	{
		moveQueue_.push(evt);
	}

	//------------------------------------------------------------------------------------------------------
	void Mouse::ReceiveEvent(MouseButtonData button)
	{
		clickQueue_.push(button);
	}

	//------------------------------------------------------------------------------------------------------
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
			const MouseButtonData& evt = clickQueue_.front();

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

	//------------------------------------------------------------------------------------------------------
	MouseButton Mouse::StringToButton(const char* name)
	{
		if (strcmp(name, "L") == 0 || strcmp(name, "l") == 0 || strcmp(name, "Left") == 0 || strcmp(name, "left") == 0)		return MouseButton::MouseLeft;
		if (strcmp(name, "M") == 0 || strcmp(name, "m") == 0 || strcmp(name, "Middle") == 0 || strcmp(name, "middle") == 0)	return MouseButton::MouseMiddle;
		if (strcmp(name, "R") == 0 || strcmp(name, "r") == 0 || strcmp(name, "Right") == 0 || strcmp(name, "right") == 0)	return MouseButton::MouseRight;

		//BLOW_BREAK("Error while attempting to convert string to button in Mouse class, given parameter:" + name);

		return MouseButton::MouseLeft;
	}

	//------------------------------------------------------------------------------------------------------
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

	//------------------------------------------------------------------------------------------------------
	void Mouse::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "getPosition", LuaGetPosition },
			{ "isDown", LuaIsDown },
			{ "isPressed", LuaIsPressed },
			{ "isDbl", LuaIsDbl },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int Mouse::LuaGetPosition(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, Mouse::Instance()->GetPosition().x, Mouse::Instance()->GetPosition().y);
	}

	//------------------------------------------------------------------------------------------------------
	int Mouse::LuaIsDown(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, Mouse::Instance()->IsDown(Mouse::Instance()->StringToButton(LuaWrapper::Instance()->Get<std::string>(L, -1, 1).c_str())));
	}

	//------------------------------------------------------------------------------------------------------
	int Mouse::LuaIsPressed(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, Mouse::Instance()->IsPressed(Mouse::Instance()->StringToButton(LuaWrapper::Instance()->Get<std::string>(L, -1, 1).c_str())));
	}

	//------------------------------------------------------------------------------------------------------
	int Mouse::LuaIsDbl(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, Mouse::Instance()->IsDbl(Mouse::Instance()->StringToButton(LuaWrapper::Instance()->Get<std::string>(L, -1, 1).c_str())));
	}
}