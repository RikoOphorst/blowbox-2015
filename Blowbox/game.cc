#include "game.h"

#include "../blowbox/win32/window.h"
#include "../blowbox/win32/file_watch.h"
#include "../blowbox/input/mouse.h"
#include "../blowbox/input/keyboard.h"
#include "../blowbox/d3d11/d3d11_render_device.h"
#include "../blowbox/d3d11/d3d11_render_target.h"
#include "../blowbox/d3d11/d3d11_render_queue.h"
#include "../blowbox/elements/quad.h"
#include "../blowbox/lua/lua_state.h"
#include "../blowbox/lua/lua_register.h"
#include "../blowbox/console/console.h"

#include <vector>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Game::Game()
	{
		window_ = new Window();
		mouse_ = Mouse::Instance();
		keyboard_ = Keyboard::Instance();
		renderDevice_ = D3D11RenderDevice::Instance();

		cb_init_ = new LuaCallback(std::vector<LuaValue>({
			LuaValue(LUA_TYPE::LUA_TYPE_TABLE, LUA_LOCATION::LUA_LOCATION_GLOBAL, "Game"),
			LuaValue(LUA_TYPE::LUA_TYPE_FUNCTION, LUA_LOCATION::LUA_LOCATION_FIELD, "Initialise")
		}));

		cb_update_ = new LuaCallback(std::vector<LuaValue>({
			LuaValue(LUA_TYPE::LUA_TYPE_TABLE, LUA_LOCATION::LUA_LOCATION_GLOBAL, "Game"),
			LuaValue(LUA_TYPE::LUA_TYPE_FUNCTION, LUA_LOCATION::LUA_LOCATION_FIELD, "Update")
		}));
		
		cb_draw_ = new LuaCallback(std::vector<LuaValue>({
			LuaValue(LUA_TYPE::LUA_TYPE_TABLE, LUA_LOCATION::LUA_LOCATION_GLOBAL, "Game"),
			LuaValue(LUA_TYPE::LUA_TYPE_FUNCTION, LUA_LOCATION::LUA_LOCATION_FIELD, "Draw")
		}));
	}

	//------------------------------------------------------------------------------------------------------
	Game::~Game()
	{

	}

	//------------------------------------------------------------------------------------------------------
	Game* Game::Instance()
	{
		static SharedPtr<Game> ptr(new Game());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void Game::Run()
	{
		Window* window = window_.get();

		window->Create(std::string("blowbox"), 640, 480);
		window->SetStarted(true);
		
		renderDevice_->Initialize(window);

		if (LuaWrapper::Instance()->CompileFromFile(LuaState::Instance()->Get(), "main.lua"))
		{	
			cb_init_->Call<>(LuaState::Instance()->Get());
			
			while (window->GetStarted())
			{
				Update();
				Draw();
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Game::Update()
	{
		FileWatch::Instance()->Update();

		window_->ProcessMessages();
		mouse_->Update();
		keyboard_->Update();

		cb_update_->Call<double>(LuaState::Instance()->Get(), 0.0);

		qApp->processEvents();
	}
	
	//------------------------------------------------------------------------------------------------------
	void Game::Draw()
	{
		cb_draw_->Call<>(LuaState::Instance()->Get());
	}

	//------------------------------------------------------------------------------------------------------
	void Game::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "Update", LuaUpdate },
			{ "Draw", LuaDraw },
			{ "Render", LuaRender },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int Game::LuaUpdate(lua_State* L)
	{
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Game::LuaDraw(lua_State* L)
	{
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Game::LuaRender(lua_State* L)
	{
		D3D11RenderDevice::Instance()->Draw(LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, -1));
		return 0;
	}
}