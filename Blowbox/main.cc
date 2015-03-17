#include "../blowbox/game.h"
#include "../blowbox/elements/quad.h"
#include "../blowbox/utility/lua_enum.h"
#include "../blowbox/d3d11/d3d11_render_target.h"
#include "../blowbox/d3d11/d3d11_render_queue.h"
#include "../blowbox/d3d11/d3d11_camera.h"
#include "../blowbox/content/content_manager.h"

#include "../blowbox/lua/lua_register.h"

#include "../blowbox/console/console.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	AllocatedMemory& memory = AllocatedMemory::Instance();

	LuaRegister::Instance()->RegisterSingleton<Game>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<Console>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<ContentManager>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<Quad>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<LuaEnum>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<D3D11RenderTarget>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<D3D11RenderQueue>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<D3D11Camera>(LuaState::Instance()->Get());

	QApplication QApp(argc, argv);
	Console::Instance();

	Game::Instance()->Run();

	if (Console::Instance()->IsVisible())
	{
		return QApp.exec();
	}

	return EXIT_SUCCESS;
}