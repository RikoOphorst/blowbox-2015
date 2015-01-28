#pragma once

#include <queue>
#include "../input/key.h"
#include "../memory/shared_ptr.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

namespace blowbox
{
	enum KeyEvent
	{
		kePressed,
		keDown,
		keReleased
	};

	struct KeyData
	{
		Key key;
		KeyEvent type;
	};

	struct KeyState
	{
		bool pressed;
		bool down;
		bool released;
	};

	class Keyboard : public LuaClass
	{
	public:
		Keyboard();
		Keyboard(lua_State* state);
		~Keyboard();

		static Keyboard*		Instance();

		static int RegisterFunctions(lua_State* state);

		bool&					IsDown(Key key);
		bool&					IsPressed(Key key);
		bool&					IsReleased(Key key);
		Key						LastKey();

		void					ReceiveEvent(KeyData evt);

		void					ResetStates();

		void					Update();

		static int				LuaIsDown(lua_State* state);
		static int				LuaIsPressed(lua_State* state);
		static int				LuaIsReleased(lua_State* state);

		LM_NAME("Keyboard");
	private:
		KeyState				keyStates_[255];
		Key						lastKey_;
		std::queue<KeyData>		queue_;
	};
}