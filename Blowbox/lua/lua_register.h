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

		// Keeps the index to the class table
		int methods = lua_gettop(L);

		// Create the meta table the class table is going to use
		luaL_newmetatable(L, T::GetName());

		// Keeps the index to the meta table index
		int mt = lua_gettop(L);

		// Copy the class table
		lua_pushvalue(L, methods);

		// Set the class on the global table by its class name - note: pops the class table copy off the table
		lua_setfield(L, LUA_GLOBALSINDEX, T::GetName());

		// Make a copy of the class table
		lua_pushvalue(L, methods);
		lua_pushvalue(L, methods);

		// On the metatable we just set the field __index to last class table copy we just made
		lua_setfield(L, mt, "__index");

		// Set the garbage collection function
		LuaRegister::Instance()->RegisterFunction(L, T::LuaDestructor<T>, "__gc", mt);

		// Register the "new" function on the class table
		LuaRegister::Instance()->RegisterFunction(L, T::LuaConstructor<T>, "new", methods);

		// Register the "__call" function on the mt
		LuaRegister::Instance()->RegisterFunction(L, T::LuaConstructor<T>, "__call", mt);
		
		// Register the "__index" function on the mt
		LuaRegister::Instance()->RegisterFunction(L, T::LuaIndex<T>, "__index", mt);

		// Register the "__tostring" function on the mt
		LuaRegister::Instance()->RegisterFunction(L, T::LuaToString<T>, "__tostring", mt);

		// Set the metatable on the base class
		lua_setmetatable(L, methods);

		// Copy the base class to prepare for function registration
		lua_pushvalue(L, methods);

		// Register the actual functions this object has
		T::LuaRegisterFunctions<T>(L);

		// Clear the stack
		lua_pop(L, 3);
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	void LuaRegister::RegisterSingleton(lua_State* L)
	{
		// Create the singletonal class
		lua_createtable(L, 0, 0);

		// Register the class' functions
		T::LuaRegisterFunctions(L);

		// Register the table as a global
		lua_setfield(L, LUA_GLOBALSINDEX, T::GetName());
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
			T::LuaRegisterFunctions();

			// Register the table as a member on given index
			lua_setfield(L, index, T::class_name());
		}
	}
}