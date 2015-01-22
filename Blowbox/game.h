#pragma once

#include <chrono>
#include <iostream>
#include <math.h>

#include "d3d11/d3d11_display_device.h"
#include "d3d11/d3d11_camera.h"
#include "d3d11/d3d11_render_element.h"

#include "win32/window.h"
#include "win32/file_watch.h"

#include "memory/shared_ptr.h"

#include "input/keyboard.h"
#include "input/mouse.h"

#include "geom/quad.h"
#include "geom/cube.h"

#include "lua/lua_manager.h"

using namespace std::chrono;

namespace blowbox
{
	class D3D11DisplayDevice;

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
		D3D11DisplayDevice* displayDevice_	= D3D11DisplayDevice::Instance();
		Keyboard*			keyboard_		= Keyboard::Instance();
		Mouse*				mouse_			= Mouse::Instance();
		FileWatch*			fileWatch_		= FileWatch::Instance();
		LuaManager*			luaManager_		= LuaManager::Instance();
		SharedPtr<Window>	window_			= new Window();

		void								InitDeltaTime();
		void								UpdateDeltaTime();
		double								deltaTime_;
		high_resolution_clock::time_point	lastTime_;
		high_resolution_clock::time_point	currentTime_;
	};
}