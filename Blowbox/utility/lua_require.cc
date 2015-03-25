#include "../../blowbox/utility/lua_require.h"

#include "../../blowbox/console/console.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	LuaRequire::LuaRequire()
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaRequire::LuaRequire(lua_State* L)
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaRequire::~LuaRequire()
	{

	}

	//------------------------------------------------------------------------------------------------------
	int LuaRequire::Require(lua_State* L)
	{
		LuaWrapper::Instance()->CompileFromFile(L, LuaWrapper::Instance()->Get<std::string>(L, 1));

		return 0;
	}
}