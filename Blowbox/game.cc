#include "game.h"

#include "input/keyboard.h"
#include "input/mouse.h"

#include "geom/quad.h"
#include "geom/cube.h"

#include "d3d11/d3d11_display_device.h"
#include "d3d11/d3d11_camera.h"
#include "d3d11/d3d11_render_element.h"

#include "win32/window.h"
#include "win32/file_watch.h"

namespace blowbox
{
	Game::Game() :
		displayDevice_(D3D11DisplayDevice::Instance()),
		keyboard_(Keyboard::Instance()),
		mouse_(Mouse::Instance()),
		fileWatch_(FileWatch::Instance()),
		luaManager_(LuaManager::Instance())
	{
		window_ = new Window();
		LuaInit_ = LuaCallback<>("Game", "Init");
		LuaUpdate_ = LuaCallback<double>("Game", "Update");
		LuaRender_ = LuaCallback<double>("Game", "Render");
	}

	Game::~Game()
	{

	}

	Game* Game::Instance()
	{
		static SharedPtr<Game> game(new Game());
		return game.get();
	}

	void Game::CreateWin32(std::string name, int width, int height)
	{
		window_->Make(name, width, height);
	}

	void Game::CreateDisplayDevice()
	{
		displayDevice_->Create(window_->getHandle());
	}

	void Game::Run()
	{
		displayDevice_->InitScene();

		SharedPtr<D3D11Camera> camera(new D3D11Camera(CAM_ORTHOGRAPHIC));
		displayDevice_->SetCamera(camera.get());
		
		InitDeltaTime();
		
		LuaManager::Instance()->LoadScript("main.lua");
		LuaInit_.Call();

		while (window_->started())
		{	
			UpdateDeltaTime();
			Update();
			Draw();
		}

		displayDevice_->Release();
	}

	void Game::Update()
	{
		window_->ProcessMessages();

		fileWatch_->Update();

		keyboard_->Update();
		mouse_->Update();

		LuaUpdate_.Call(deltaTime_);

		lua_gc(LM_STATE, LUA_GCSTEP, 0);
	}

	void Game::Draw()
	{
		LuaRender_.Call(deltaTime_);
		displayDevice_->BeginDraw();
		displayDevice_->Draw();
		displayDevice_->EndDraw();
	}

	double& Game::GetDeltaTime()
	{
		return deltaTime_;
	}

	void Game::InitDeltaTime()
	{
		lastTime_ = high_resolution_clock::now();
		currentTime_ = high_resolution_clock::now();
	}

	void Game::UpdateDeltaTime()
	{
		currentTime_ = high_resolution_clock::now();
		deltaTime_ = duration_cast<duration<double, std::milli>>(currentTime_ - lastTime_).count() * 1e-3f;
		lastTime_ = currentTime_;
	}
}