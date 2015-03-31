#pragma once

#include <map>

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/lua/lua_state.h"

namespace blowbox
{
	/**
	* @enum blowbox::LUA_TYPE
	* @brief Defines the type of a lua value
	*/
	enum LUA_TYPE
	{
		LUA_TYPE_TABLE,
		LUA_TYPE_FUNCTION,
		LUA_TYPE_NUMBER,
		LUA_TYPE_NIL,
		LUA_TYPE_NONE,
		LUA_TYPE_STRING,
		LUA_TYPE_USERDATA,
		LUA_TYPE_LIGHTUSERDATA,
		LUA_TYPE_BOOLEAN,
		LUA_TYPE_UNKNOWN
	};

	/**
	* @enum blowbox::LUA_LOCATION
	* @brief The location of where the lua value is stored
	*/
	enum LUA_LOCATION
	{
		LUA_LOCATION_GLOBAL,
		LUA_LOCATION_FIELD,
		LUA_LOCATION_LOCAL,
		LUA_LOCATION_UNKNOWN,
	};

	/**
	* @struct blowbox::LuaValue
	* @brief Defines a lua value
	*/
	struct LuaValue
	{
		LuaValue() :
			type(LUA_TYPE::LUA_TYPE_NONE),
			location(LUA_LOCATION::LUA_LOCATION_UNKNOWN),
			identifier(""),
			value("")
		{

		}
		
		LuaValue(LUA_TYPE type_, LUA_LOCATION location_, std::string identifier_, std::string value_) :
			type(type_),
			location(location_),
			identifier(identifier_),
			value(value_)
		{};
		
		LuaValue(LUA_TYPE type_, LUA_LOCATION location_, std::string identifier_) : 
			type(type_), 
			location(location_),
			identifier(identifier_),
			value("") 
		{};
		
		LUA_TYPE type;
		LUA_LOCATION location;
		std::string identifier;
		std::string value;
		std::map<std::string, LuaValue> fields;
	};
	
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
		*/
		void Dump(lua_State* L, const std::string& brief);

		/**
		* @brief Creates a weak table and pushes it onto the stack
		* @param[in] L (lua_State*) the lua state
		*/
		void CreateWeakTable(lua_State* L);

		/**
		* @brief Create a lightuserdata container on the stack
		*/
		template<typename T>
		void CreateUserdataContainer(lua_State* L, T* ptr);

		/**
		* @brief Compiles and runs a file
		* @param[in] L (lua_State*) the lua state
		* @param[in] path (const std::string&) the path to the file
		* @param[in] reloading (bool) is the file reloading?
		*/
		bool CompileFromFile(lua_State* L, const std::string& path, bool reloading = false);

		/**
		* @brief Compiles and runs a string of lua code
		* @param[in] L (lua_State*) the lua state
		* @param[in] code (const std::string&) the code to be compiled
		* @param[in] source (const std::string&) the source to be displayed while debugging
		*/
		bool CompileFromString(lua_State* L, const std::string& code, const std::string& source);

		/**
		* @brief To relative index
		* @param[in] L (lua_State*) the lua state
		* @param[in] absolute (const int&) the absolute index
		*/
		int ToRelative(lua_State* L, const int& absolute);

		/**
		* @brief To absolute index
		* @param[in] L (lua_State*) the lua state
		* @param[in] relative (const int&) the relative index
		*/
		int ToAbsolute(lua_State* L, const int& relative);

		/**
		* @brief To argument index
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the relative/absolute index
		*/
		int ToArgument(lua_State* L, const int& index);

		/**
		* @brief Convert stack element to string
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the index
		*/
		std::string ToString(lua_State* L, const int& index);

		/**
		* @brief Convert stack element to a std::map<std::string key, std::string value>
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the index
		*/
		std::map<std::string, LuaValue> ToTable(lua_State* L, const int& index);

		/**
		* @brief Convert stack element to a typename-string
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the index
		*/
		LUA_TYPE Typename(lua_State* L, const int& index);

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
		* @param[in] value (T) the value to be pushed
		*/
		template<typename T>
		int PushValue(lua_State* L, T value);

		/**
		* @brief Performs a stack trace
		* @param[in] L (lua_State*) the lua state
		*/
		int StackTrace(lua_State*);

		/**
		* @brief Tries to invoke a stacktrace
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaStackTrace(lua_State* L);
	};

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline T* LuaWrapper::ParseUserdata(lua_State* L, const int& index)
	{
		if (!lua_isuserdata(L, index))
		{
			luaL_typerror(L, index, "userdata");
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
	template<typename T>
	inline void LuaWrapper::CreateUserdataContainer(lua_State* L, T* ptr)
	{
		// The userdata container which contains the lightuserdata (a T*)
		typedef struct { T* ptr; } UserdataContainer;

		// Make sure the stack is big enough
		lua_checkstack(L, 3);

		// Make a new userdata with the size of UserdataContainer
		UserdataContainer* udata = (UserdataContainer*)lua_newuserdata(L, sizeof(UserdataContainer*));

		// Push the light userdata
		lua_pushlightuserdata(L, ptr);

		// Copy the value at -2
		lua_pushvalue(L, -2);

		// Set the lightuserdata (the pointer) to the newly created user data
		lua_settable(L, -4);

		// Set the userdata's pointer to the pointer class's instance
		udata->ptr = ptr;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline double LuaWrapper::Get<double>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			if (Typename(L, index) != LUA_TYPE::LUA_TYPE_NUMBER)
			{
				luaL_typerror(L, index, "number");
				return 0;
			}

			return luaL_checknumber(L, index);
		}
		return lua_tonumber(L, index);
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline float LuaWrapper::Get<float>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			if (Typename(L, index) != LUA_TYPE::LUA_TYPE_NUMBER)
			{
				luaL_typerror(L, index, "number");
				return 0;
			}

			return static_cast<float>(luaL_checknumber(L, index));
		}
		return static_cast<float>(lua_tonumber(L, index));
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline int LuaWrapper::Get<int>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			if (Typename(L, index) != LUA_TYPE::LUA_TYPE_NUMBER)
			{
				luaL_typerror(L, index, "number");
				return 0;
			}

			return static_cast<int>(luaL_checknumber(L, index));
		}
		return static_cast<int>(lua_tonumber(L, index));
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline const char* LuaWrapper::Get<const char*>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			if (Typename(L, index) != LUA_TYPE::LUA_TYPE_STRING)
			{
				luaL_typerror(L, index, "string");
				return "";
			}
			
			return LuaWrapper::Instance()->ToString(L, index).c_str();
		}
		return lua_tostring(L, index + 1);
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline std::string LuaWrapper::Get<std::string>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			if (Typename(L, index) != LUA_TYPE::LUA_TYPE_STRING)
			{
				luaL_typerror(L, index, "string");
				return "";
			}

			return LuaWrapper::Instance()->ToString(L, index);
		}
		return lua_tostring(L, index);
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline bool LuaWrapper::Get<bool>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			if (!lua_isboolean(L, index))
			{
				luaL_typerror(L, index, "bool");
				return false;
			}
		}

		return lua_toboolean(L, index) != 0;
	}

	//------------------------------------------------------------------------------------------------------
	template<>
	inline void* LuaWrapper::Get<void*>(lua_State* L, const int& index, const bool& check)
	{
		if (check == true)
		{
			if (!lua_isuserdata(L, index))
			{
				luaL_typerror(L, index, "userdata");
				return nullptr;
			}
			
			return luaL_checkudata(L, index, NULL);
		}
		return lua_touserdata(L, index);
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T, typename...Args>
	inline int LuaWrapper::Push(lua_State* L, T first, Args ... others)
	{
		return PushValue(L, first) + Push(L, others...);
	}
	
	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline int LuaWrapper::Push(lua_State* L, T value)
	{
		return PushValue(L, value);
	}

	//------------------------------------------------------------------------------------------------------
	inline int LuaWrapper::Push(lua_State* L)
	{
		return 0;
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
	inline int LuaWrapper::PushValue<float>(lua_State* L, float first)
	{
		lua_pushnumber(L, static_cast<double>(first));
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