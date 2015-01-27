#pragma once

#include <chrono>
#include <iostream>
#include <math.h>

#include "memory/shared_ptr.h"

#include "lua/lua_callback.h"

#include "win32/window.h"

using namespace std::chrono;

namespace blowbox
{
	class D3D11DisplayDevice;
	class Keyboard;
	class Mouse;
	class FileWatch;
	class LuaManager;

	class Game
	{
	public:
		Game();
		~Game();

		static Game*		Instance();

		void				CreateWin32(std::string name, int width, int height);
		void				CreateDisplayDevice();

		void				Run();

		void				Update();
		void				Draw();

		double&				GetDeltaTime();
	private:
		D3D11DisplayDevice* displayDevice_;
		Keyboard*			keyboard_;
		Mouse*				mouse_;
		FileWatch*			fileWatch_;
		LuaManager*			luaManager_;
		SharedPtr<Window>	window_;
		LuaCallback<>		LuaInit_;
		LuaCallback<double>	LuaUpdate_;
		LuaCallback<double>	LuaRender_;

		void								InitDeltaTime();
		void								UpdateDeltaTime();
		double								deltaTime_;
		high_resolution_clock::time_point	lastTime_;
		high_resolution_clock::time_point	currentTime_;
	};
}