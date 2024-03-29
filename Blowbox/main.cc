#include "../blowbox/game.h"
#include "../blowbox/elements/quad.h"
#include "../blowbox/elements/cube.h"
#include "../blowbox/elements/polygon.h"
#include "../blowbox/elements/widget.h"
#include "../blowbox/elements/line.h"
#include "../blowbox/input/keyboard.h"
#include "../blowbox/input/mouse.h"
#include "../blowbox/utility/lua_enum.h"
#include "../blowbox/d3d11/d3d11_render_target.h"
#include "../blowbox/d3d11/d3d11_render_queue.h"
#include "../blowbox/d3d11/d3d11_camera.h"
#include "../blowbox/d3d11/d3d11_settings.h"
#include "../blowbox/content/content_manager.h"
#include "../blowbox/utility/lua_require.h"

#include "../blowbox/lua/lua_register.h"

#include "../blowbox/console/console.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	AllocatedMemory& memory = AllocatedMemory::Instance();

	LuaRegister::Instance()->RegisterSingleton<Game>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<Console>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<ContentManager>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<D3D11Settings>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<Keyboard>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<Mouse>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<Line>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<Quad>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<Cube>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<Widget>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<blowbox::Polygon>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<LuaEnum>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<D3D11RenderTarget>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<D3D11RenderQueue>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<D3D11Camera>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterFunction(LuaState::Instance()->Get(), LuaRequire::Require, "require");

	QApplication QApp(argc, argv);
	Console::Instance();

	Game::Instance()->Run();

	if (Console::Instance()->IsVisible())
	{
		return QApp.exec();
	}

	return EXIT_SUCCESS;
}