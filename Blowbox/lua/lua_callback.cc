#include "../../blowbox/lua/lua_callback.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	LuaCallback::LuaCallback(std::vector<LuaValue> tree) :
		tree_(tree)
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	LuaCallback::~LuaCallback()
	{

	}

	//------------------------------------------------------------------------------------------------------
	std::string LuaCallback::TreeToString()
	{
		std::string string = "";

		for (unsigned int i = 0; i < tree_.size(); ++i)
		{
			string += tree_[i].identifier;

			if (i < tree_.size() - 1)
			{
				for (unsigned int j = 0; j <= i; ++j)
				{
					string += ".";
				}
			}
		}
		
		string += "();";

		return string;
	}
}