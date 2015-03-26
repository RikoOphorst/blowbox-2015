#pragma once

#include <queue>
#include "../../blowbox/input/key.h"
#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	/**
	* @enum blowbox::KeyEvent
	* @brief A type of key event
	*/
	enum KeyEvent
	{
		Pressed,
		Down,
		Released
	};

	/**
	* @struct blowbox::KeyData
	* @brief Holds data about a key and its event
	*/
	struct KeyData
	{
		Key key;
		KeyEvent type;
	};

	/**
	* @struct blowbox::KeyState
	* @brief Keeps the state for any key
	*/
	struct KeyState
	{
		bool pressed;
		bool down;
		bool released;
	};

	/**
	* @class blowbox::Keyboard
	* @brief Manages the keyboard
	* @author Riko Ophorst
	*/
	class Keyboard: public LuaClass
	{
	public:
		/**
		* @brief Default constructor
		*/
		Keyboard();

		/**
		* @brief Lua Keyboard constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Keyboard(lua_State* L);

		/**
		* @brief Default destructor
		*/
		~Keyboard();

		/**
		* @brief Retrieves a pointer to the Keyboard instance
		* @return A pointer to the Keyboard's instance
		*/
		static Keyboard*		Instance();

		/**
		* @brief Retrieves whether given Key is down
		* @return bool Is the Key down?
		*/
		bool&					IsDown(Key key);

		/**
		* @brief Retrieves whether given Key is pressed
		* @return bool Is the Key pressed?
		*/
		bool&					IsPressed(Key key);

		/**
		* @brief Retrieves whether given Key is released
		* @return bool Is the Key released?
		*/
		bool&					IsReleased(Key key);

		/**
		* @brief Retrieves the last key that was pressed
		* @return Key The key that was last pressed
		*/
		Key						LastKey();

		/**
		* @brief Receive an event
		* @param[in] evt (KeyData) The data of the event
		*/
		void					ReceiveEvent(KeyData evt);

		/**
		* @brief Reset all the states
		*/
		void					ResetStates();

		/**
		* @brief Update the keyboard
		*/
		void					Update();

		/**
		* @brief Registers this objects functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		/**
		* @brief Is the key pressed?
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaIsPressed(lua_State* L);

		/**
		* @brief Is the key released?
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaIsReleased(lua_State* L);

		/**
		* @brief Is the key down?
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaIsDown(lua_State* L);

		/**
		* @brief Gets the last key
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaLastKey(lua_State* L);

		CLASSNAME("Keyboard");
	private:
		KeyState				keyStates_[255];
		Key						lastKey_;
		std::queue<KeyData>		queue_;
	};
}