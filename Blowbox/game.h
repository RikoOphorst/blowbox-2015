#pragma once

#include <chrono>
#include <iostream>
#include <math.h>

#include "../blowbox/memory/shared_ptr.h"
#include "../blowbox/lua/lua_callback.h"
#include "../blowbox/lua/lua_class.h"

namespace blowbox
{
	class Window;
	class Keyboard;
	class Mouse;
	class D3D11RenderDevice;
	class Quad;
	
	/**
	* @class blowbox::Game
	* @brief Manages the Game
	* @author Riko Ophorst
	*/
	class Game : public LuaClass
	{
	public:
		/**
		* @brief Default constructor
		*/
		Game();
		/**
		* @brief Default destructor
		*/
		~Game();

		/**
		* @brief Retrieves a pointer to the Game instance
		* @return A pointer to the Game's instance
		*/
		static Game* Instance();

		/**
		* @brief Runs the game
		*/
		void Run();

		/**
		* @brief Updates the game
		*/
		void Update();

		/**
		* @brief Draws the game
		*/
		void Draw();

		/**
		* @brief Gets the window
		*/
		Window* GetWindow();

		/**
		* @brief Registers this objects functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		/**
		* @brief A placeholder update function
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaUpdate(lua_State* L);

		/**
		* @brief A placeholder draw function
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaDraw(lua_State* L);

		/**
		* @brief Renders all rendertargets with given camera
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaRender(lua_State* L);

		CLASSNAME("Game");
	private:
		SharedPtr<Window> window_;
		Mouse* mouse_;
		Keyboard* keyboard_;
		D3D11RenderDevice* renderDevice_;
		SharedPtr<LuaCallback> cb_init_;
		SharedPtr<LuaCallback> cb_update_;
		SharedPtr<LuaCallback> cb_draw_;
	};
}