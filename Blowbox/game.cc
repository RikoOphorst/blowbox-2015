#include "game.h"

namespace blowbox
{
	Game::Game()
	{
		
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
		
		InitDeltaTime();
		
		LuaManager::Instance()->LoadScript("main.lua");
		LuaInit_.Call();

		SharedPtr<D3D11Camera> camera(new D3D11Camera(CAM_ORTHOGRAPHIC));
		displayDevice_->SetCamera(camera.get());

		SharedPtr<Quad> myQuad(new Quad());
		myQuad->SetTexture("tex1.png");
		myQuad->SetShader("shaders/anotherFile.fx");
		myQuad->SetPosition(-50.0f, 0, 0);

		SharedPtr<Quad> myQuad2(new Quad());
		myQuad2->SetTexture("tex2.png");
		myQuad2->SetShader("shaders/effects.fx");
		myQuad2->SetPosition(50.0f, 0, 0);

		displayDevice_->AddElement(myQuad.get());
		displayDevice_->AddElement(myQuad2.get());

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