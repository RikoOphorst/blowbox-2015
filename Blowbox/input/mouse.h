#pragma once

#include <queue>
#include <Windows.h>
#include <xnamath.h>

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	/**
	* @struct blowbox::MouseMoveEvent
	* @brief A mouse move event
	*/
	struct MouseMoveEvent
	{
		float x;
		float y;
	};

	/**
	* @enum blowbox::MouseButtonType
	* @brief The type of mouse button event type
	*/
	enum MouseButtonEvent
	{
		MouseDownEvent,
		MouseUpEvent,
		MouseDblEvent
	};

	/**
	* @enum blowbox::MouseButton
	* @brief The type of mouse buttons
	*/
	enum MouseButton
	{
		MouseLeft,
		MouseMiddle,
		MouseRight
	};

	/**
	* @struct blowbox::MouseState
	* @brief The state of a mouse button
	*/
	struct MouseState
	{
		bool down;
		bool pressed;
		bool dbl;
	};

	/**
	* @struct blowbox::MouseButtonData
	* @brief The data of a mouse button event
	*/
	struct MouseButtonData
	{
		MouseButtonEvent type;
		MouseButton button;
	};

	/**
	* @class blowbox::Mouse
	* @brief Manages the mouse
	* @author Riko Ophorst
	*/
	class Mouse: public LuaClass
	{
	public:
		/**
		* @brief Default Mouse constructor
		*/
		Mouse();

		/**
		* @brief Lua Mouse constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Mouse(lua_State* L);

		/**
		* @brief Default Mouse destructors
		*/
		~Mouse();

		/**
		* @brief Retrieves a pointer to the Mouse instance
		* @return Mouse* A pointer to the Msouse
		*/
		static Mouse*					Instance();

		/**
		* @brief Retrieves the position of the mouse
		* @return XMFLOAT2 the position of the mouse
		*/
		XMFLOAT2&						GetPosition();

		/**
		* @brief Retrieves if a given button is down
		* @param[in] btn (MouseButton) the mouse button to be checked
		* @return bool& Is the button down?
		*/
		bool&							IsDown(MouseButton btn);

		/**
		* @brief Retrieves if a given button is pressed
		* @param[in] btn (MouseButton) the mouse button to be checked
		* @return bool& Is the button pressed?
		*/
		bool&							IsPressed(MouseButton btn);

		/**
		* @brief Retrieves if a given button is double clicked
		* @param[in] btn (MouseButton) the mouse button to be checked
		* @return bool& Is the button double clicked?
		*/
		bool&							IsDbl(MouseButton btn);

		/**
		* @brief Resets the states of all buttons
		*/
		void							ResetStates();

		/**
		* @brief Updates the mouse
		*/
		void							Update();

		/**
		* @brief Receive a mouse move event
		* @param[in] moveEvent (MouseMoveEvent) Event data of the mouse move event
		*/
		void							ReceiveEvent(MouseMoveEvent moveEvent);

		/**
		* @brief Receive a mouse button event
		* @param[in] buttonData (MouseButtonData) Event data of the mouse button event
		*/
		void							ReceiveEvent(MouseButtonData buttonData);

		/**
		* @brief Turns a string into a button
		* @param[in] string (const char*) the string
		* @return MouseButton The corresponding mouse button
		*/
		static MouseButton				StringToButton(const char* string);

		/**
		* @brief Turns a button into a string
		* @param[in] button (MouseButton) the button
		* @return std::string The corresponding string
		*/
		static std::string				ButtonToString(MouseButton button);

		/**
		* @brief Registers this object's functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		/**
		* @brief Gets the mouse position via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetPosition(lua_State* L);

		/**
		* @brief Gets the mouse down via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaIsDown(lua_State* L);

		/**
		* @brief Gets the mouse pressed via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaIsPressed(lua_State* L);

		/**
		* @brief Gets the mouse dbl via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaIsDbl(lua_State* L);

		CLASSNAME("Mouse");
	private:
		XMFLOAT2						pos_;
		std::queue<MouseMoveEvent>		moveQueue_;
		std::queue<MouseButtonData>		clickQueue_;
		MouseState						mouseStates_[3];
	};
}