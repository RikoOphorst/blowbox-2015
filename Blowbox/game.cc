#include "game.h"

#include "../blowbox/input/mouse.h"
#include "../blowbox/input/keyboard.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Game::Game()
	{
		window_ = SharedPtr<Window>(new Window());
		mouse_ = Mouse::Instance();
		keyboard_ = Keyboard::Instance();
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

		while (window->GetStarted())
		{
			Update();
			Draw();
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Game::Update()
	{
		window_.get()->ProcessMessages();
		mouse_->Update();
		keyboard_->Update();
	}
	
	//------------------------------------------------------------------------------------------------------
	void Game::Draw()
	{

	}
}