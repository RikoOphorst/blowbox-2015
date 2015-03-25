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
	Game::Game() :
		delta_time_(0),
		time_elapsed_(0)
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

		cb_fixed_update_ = new LuaCallback(std::vector<LuaValue>({
			LuaValue(LUA_TYPE::LUA_TYPE_TABLE, LUA_LOCATION::LUA_LOCATION_GLOBAL, "Game"),
			LuaValue(LUA_TYPE::LUA_TYPE_FUNCTION, LUA_LOCATION::LUA_LOCATION_FIELD, "FixedUpdate")
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

		if (LuaWrapper::Instance()->CompileFromFile(LuaState::Instance()->Get(), "main.lua"))
		{	
			window->Create(std::string("blowbox"), 640, 480);
			window->SetStarted(true);

			renderDevice_->Initialize(window);
			
			cb_init_->Call<>(LuaState::Instance()->Get());

			last_time_ = high_resolution_clock::now();
			current_time_ = high_resolution_clock::now();
			
			while (window->GetStarted())
			{
				Update();
				FixedUpdate();
				Draw();
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Game::Update()
	{	
		current_time_ = high_resolution_clock::now();
		delta_time_ = duration_cast<duration<double, std::milli>>(current_time_ - last_time_).count() * 1e-3f;
		last_time_ = current_time_;
		
		FileWatch::Instance()->Update();

		window_->ProcessMessages();
		mouse_->Update();
		keyboard_->Update();

		cb_update_->Call<double>(LuaState::Instance()->Get(), delta_time_);

		lua_gc(LuaState::Instance()->Get(), LUA_GCCOLLECT, 0);

		qApp->processEvents();
	}

	//------------------------------------------------------------------------------------------------------
	void Game::FixedUpdate()
	{
		time_elapsed_ += delta_time_ * 1000;

		double fixed_delta = 1000.0f / 60;

		time_elapsed_ = min(time_elapsed_, static_cast<double>(fixed_delta * 2));

		while (time_elapsed_ > fixed_delta)
		{
			cb_fixed_update_->Call<>(LuaState::Instance()->Get());

			time_elapsed_ -= fixed_delta;
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	void Game::Draw()
	{
		cb_draw_->Call<>(LuaState::Instance()->Get());
	}

	//------------------------------------------------------------------------------------------------------
	const double& Game::GetDeltaTime()
	{
		return delta_time_;
	}
	
	//------------------------------------------------------------------------------------------------------
	Window* Game::GetWindow()
	{
		return window_.get();
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
		D3D11RenderDevice::Instance()->Draw(LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1), LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 2));
		return 0;
	}
}