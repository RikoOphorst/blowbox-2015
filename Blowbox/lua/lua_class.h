#pragma once

#include "../../blowbox/lua/lua_wrapper.h"
#include "../../blowbox/lua/lua_register.h"

#define CLASSNAME(name) static const char* GetName() { return ##name; }

namespace blowbox
{
	/**
	* @class blowbox::LuaClass
	* @brief Handles LuaClass functionality (mostly for polymorphism though)
	* @author Riko Ophorst
	*/
	class LuaClass
	{
	public:
		/**
		* @brief Default LuaClass constructor
		*/
		LuaClass();

		/**
		* @brief LuaClass' lua constructor
		*/
		LuaClass(lua_State* L);

		/**
		* @brief Default LuaClass destructor
		*/
		~LuaClass();

		/**
		* @brief The LuaConstructor used by any userdata which is "new"-able
		* @param[in] L (lua_State*) the lua state
		*/
		template<typename T>
		static int LuaConstructor(lua_State* L);

		/**
		* @brief The LuaDestructor used by any userdata which is "new"-able and also needs to be garbage collected
		* @param[in] L (lua_State*) the lua state
		*/
		template <typename T>
		static int LuaDestructor(lua_State* L);

		/**
		* @brief The LuaToString function that is set in the metatables of generated objects
		* @param[in] L (lua_State*) the lua state
		*/
		template <typename T>
		static int LuaToString(lua_State* L);

		/**
		* @brief The LuaIndex metamethod
		* @param[in] L (lua_State*) the lua state
		*/
		template <typename T>
		static int LuaIndex(lua_State* L);

		/**
		* @brief Registers functions of this class
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);
	};

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline int LuaClass::LuaConstructor(lua_State* L)
	{
		// Create the instance of T via its lua constructor T(L)
		T* ptr = new T(L);
		typedef struct { T* ptr; } UserdataContainer;

		// Open the table's metatable from the lua lib register
		luaL_getmetatable(L, T::GetName());

		// Keep a variable which is an index on the stack of where the gotten metatable is on the stack
		int mt = lua_gettop(L);

		// Push a string we will use to access the userdata
		lua_pushstring(L, "userdata");

		// Get the weak userdata table
		lua_gettable(L, mt);

		// If the table had never had a weak table created for it, we create it
		if (lua_isnil(L, -1))
		{
			// Pop the nil value from the stack, we will replace it with a new weak table
			lua_pop(L, 1);

			// Create a new weak table and push it onto the stack
			LuaWrapper::Instance()->CreateWeakTable(L);

			// Push the string "userdata"
			lua_pushstring(L, "userdata");

			// Make a copy of the weak table
			lua_pushvalue(L, -2);

			// Set the main table's userdata to be the newly created weaktable: mt[userdata] = -2
			lua_settable(L, mt);
		}

		// Push the pointer onto the stack
		lua_pushlightuserdata(L, ptr);

		// Retrieve from the top most table its userdata
		lua_gettable(L, -2);

		// Is the table's userdata nil?
		if (lua_isnil(L, -1))
		{
			// Pop the nil value
			lua_pop(L, 1);

			// Create a new userdata which holds our pointer
			LuaWrapper::Instance()->CreateUserdataContainer<T>(L, ptr);

			// Copy the main metatable
			lua_pushvalue(L, mt);

			// Set the copied value's metatable to the userdata we just made (which contains the lightuserdata)
			lua_setmetatable(L, -2);
		}

		// Replace the metatable with the userdata
		lua_replace(L, mt);

		// Clear the stack, so the only the userdata remains
		lua_settop(L, mt);
		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline int LuaClass::LuaDestructor(lua_State* L)
	{
		T* ptr = LuaWrapper::Instance()->ParseUserdata<T>(L, 1);

		delete ptr;
		ptr = nullptr;

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline int LuaClass::LuaToString(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, T::GetName());
	}
}