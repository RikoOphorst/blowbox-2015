#pragma once

#include <functional>
#include "../../blowbox/lua/lua_state.h"
#include "../../blowbox/lua/lua_wrapper.h"

#undef RegisterClass

namespace blowbox
{
	/**
	* @class blowbox::LuaRegister
	* @brief Handles registering of all globals in the lua state
	* @author Riko Ophorst
	*/
	class LuaRegister
	{
	public:
		/**
		* @brief Default LuaRegister constructor
		*/
		LuaRegister();

		/**
		* @brief Default LuaRegister destructor
		*/
		~LuaRegister();

		/**
		* @brief Retrieves the instance of the LuaRegister
		*/
		static LuaRegister* Instance();

		/**
		* @brief Registers a function
		* @param[in] L (lua_State*) the lua state
		* @param[in] function (lua_CFunction) the function
		* @param[in] name (const std::string&) the name of the function in lua
		*/
		void RegisterFunction(lua_State* L, lua_CFunction function, const std::string& name);

		/**
		* @brief Registers a function
		* @param[in] L (lua_State*) the lua state
		* @param[in] function (lua_CFunction) the function
		* @param[in] name (const std::string&) the name of the function in lua
		* @param[in] index (const int&) the index on the stack of where the function should be registered (should be a table)
		*/
		void RegisterFunction(lua_State* L, lua_CFunction function, const std::string& name, const int& index);

		/**
		* @brief Register a class
		* @param[in] L (lua_State*) the lua state
		*/
		template<typename T>
		void RegisterClass(lua_State* L);

		/**
		* @brief Registers a singleton
		* @param[in] L (lua_State*) the lua state
		*/
		template<typename T>
		void RegisterSingleton(lua_State* L);

		/**
		* @brief Registers a singleton
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the index on the stack of where the function should be registered (should be a table)
		*/
		template<typename T>
		void RegisterSingleton(lua_State* L, const int& index);
	private:
	};

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	void LuaRegister::RegisterClass(lua_State* L)
	{
		// Create the class table
		lua_createtable(L, 0, 0);
		LuaWrapper::Instance()->Dump(L, "\nCreated the class table..");

		// Keeps the index to the class table
		int methods = lua_gettop(L);
		printf("methods: %i\n", methods);

		// Create the meta table the class table is going to use
		luaL_newmetatable(L, "hurdur");
		LuaWrapper::Instance()->Dump(L, "\nJust made the meta table..");

		// Keeps the index to the meta table index
		int mt = lua_gettop(L);
		printf("mt: %i\n", mt);

		// Copy the class table
		lua_pushvalue(L, methods);
		LuaWrapper::Instance()->Dump(L, "\nPushed (copied) value on methods index, so the class table");

		// Set the class on the global table by its class name - note: pops the class table copy off the table
		lua_setfield(L, LUA_GLOBALSINDEX, "hurdur");
		LuaWrapper::Instance()->Dump(L, "\nSet field on the global table");

		// Make two copies of the class table
		lua_pushvalue(L, methods);
		lua_pushvalue(L, methods);
		LuaWrapper::Instance()->Dump(L, "\nCopied the class table twice");

		// On the metatable we just set the field __index to last class table copy we just made
		lua_setfield(state, mt, "__index");
		LuaWrapper::Instance()->Dump(L, "\nOn the metatable we just set the field __index to last class table copy we just made");

		// Set the garbage collection function
		LuaRegister::Instance()->RegisterFunction(L, LuaRegister<T>::LuaGC, "__gc", mt);

		// Not really sure what this table is for
		lua_newtable(L);

		// Register the "new" function on the class table
		LuaRegister::Instance()->RegisterFunction(L, LuaRegister<T>::LuaNew, "new", methods);

		// Register the "__call" function on the 
		/*LuaRegister::Instance()->RegisterFunction(L, LuaRegister<T>::LuaNew, "__call", -3);
		/*lua_setmetatable(state, methods);

		lua_pushvalue(state, methods);

		T::RegisterFunctions(state);

		lua_pop(state, 3);*/
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	void LuaRegister::RegisterSingleton(lua_State* L)
	{
		// Create the singletonal class
		lua_createtable(L, 0, 0);

		// Register the class' functions
		T::RegisterFunctions();

		// Register the table as a global
		lua_setfield(L, GLOBALSINDEX, T::class_name());
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	void LuaRegister::RegisterSingleton(lua_State* L, const int& index)
	{
		if (!lua_istable(L, index))
		{
			BLOW_BREAK("Given index on the stack is not a table, could not register the singleton");
		}
		else
		{
			// Create the singletonal class
			lua_createtable(L, 0, 0);

			// Register the class' functions
			T::RegisterFunctions();

			// Register the table as a member on given index
			lua_setfield(L, index, T::class_name());
		}
	}
}