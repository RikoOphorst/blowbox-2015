#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/lua/lua_state.h"

namespace blowbox
{
	/**
	* @class blowbox::LuaWrapper
	* @brief Wraps the Lua interface because it's ugly as shit
	* @author Riko Ophorst
	*/
	class LuaWrapper
	{
	public:
		/**
		* @brief Default LuaWrapper constructor
		*/
		LuaWrapper();
		
		/**
		* @brief Default LuaWrapper destructor
		*/
		~LuaWrapper();

		/**
		* @brief Retrieves the lua wrapper instance
		*/
		static LuaWrapper* Instance();

		/**
		* @brief Parses userdata to given object type
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the index on the lua stack that should be parsed
		*/
		template<typename T>
		T* ParseUserdata(lua_State* L, const int& index);

		/**
		* @brief Dumps the stack in the subsystem's console window
		* @param[in] L (lua_State*) the lua state
		* @param[in] brief (lua_State*) brief description of what the dump should be headed by
		* @todo make it dump in the actual subsystem
		*/
		void Dump(lua_State* L, const std::string& brief);

		/**
		* @brief Compiles and runs a file
		* @param[in] L (lua_State*) the lua state
		* @param[in] path (const std::string&) the path to the file
		*/
		void CompileFromFile(lua_State* L, const std::string& path);

		/**
		* @brief Compiles and runs a string of lua code
		* @param[in] L (lua_State*) the lua state
		* @param[in] code (const std::string&) the code to be compiled
		* @param[in] source (const std::string&) the source to be displayed while debugging
		*/
		void CompileFromString(lua_State* L, const std::string& code, const std::string& source);

		/**
		* @brief Retrieves a value from the stack
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the index on the stack to be retrieved
		* @param[in] check (const bool&) should the value be checked?
		*/
		template<typename T>
		T Get(lua_State* L, const int& index, const bool& check = true);

		/**
		* @brief Pushes values onto the stack
		* @param[in] L (lua_State*) the lua state
		* @param[in] anything (Args...) anything
		*/
		template<typename T, typename...Args>
		int Push(lua_State* L, T first, Args ... others);

		/**
		* @brief Pushes values onto the stack
		* @param[in] L (lua_State*) the lua state
		* @param[in] anything (Args...) anything
		*/
		template<typename T>
		int Push(lua_State* L, T first);

		/**
		* @brief Fakes a push onto the stack
		* @param[in] L (lua_State*) the lua state
		*/
		int Push(lua_State* L);

		/**
		* @brief Pushes a value on the stack
		*/
		template<typename T>
		int PushValue(lua_State* L, T value);
	private:
	};

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline T* LuaWrapper::ParseUserdata(lua_State* L, const int& index)
	{
		if (!lua_isuserdata(L, index))
		{
			BLOW_BREAK("Error while parsing user data to an object, maybe you used a dot/period instead of a colon to access the object?");
		}
		else
		{
			struct userDataType { T* ptr; } *userdata;

			userdata = (userDataType*)(lua_touserdata(L, index)); 
			
			return userdata->ptr;
		}

		return nullptr;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline double LuaWrapper::Get<double>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			return luaL_checknumber(L, index);
		}
		return lua_tonumber(L, index);
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline const char* LuaWrapper::Get<const char*>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			return luaL_checkstring(L, index);
		}
		return lua_tostring(L, index + 1);
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline std::string LuaWrapper::Get<std::string>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			return luaL_checkstring(L, index);
		}
		return lua_tostring(L, index);
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline bool LuaWrapper::Get<bool>(lua_State* L, const int& index, const bool& check)
	{
		return lua_toboolean(L, index) != 1;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline void* LuaWrapper::Get<void*>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			return luaL_checkudata(L, index, NULL);
		}
		return lua_touserdata(L, index);
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T, typename...Args>
	inline int LuaWrapper::Push(lua_State* L, T first, Args ... others)
	{
		return PushValue(first) + Push(others...);
	}
	
	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline int LuaWrapper::Push(lua_State* L, T value)
	{
		return PushValue(value);
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline int LuaWrapper::PushValue<int>(lua_State* L, int first)
	{
		lua_pushnumber(L, static_cast<double>(first));
		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline int LuaWrapper::PushValue<double>(lua_State* L, double first)
	{
		lua_pushnumber(L, first);
		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline int LuaWrapper::PushValue<const char*>(lua_State* L, const char* first)
	{
		lua_pushstring(L, first);
		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline int LuaWrapper::PushValue<std::string>(lua_State* L, std::string first)
	{
		lua_pushstring(L, first.c_str());
		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline int LuaWrapper::PushValue<bool>(lua_State* L, bool first)
	{
		lua_pushboolean(L, first);
		return 1;
	}
}