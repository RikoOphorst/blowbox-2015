#pragma once

#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qstylefactory.h>
#include <QtGui\qevent.h>

#include "../../blowbox/console/console_ui.h"

#include "../../blowbox/lua/lua_wrapper.h"
#include "../../blowbox/lua/lua_class.h"
#include "../../blowbox/memory/shared_ptr.h"

namespace blowbox
{
	/**
	* @enum blowbox::LOG_COLOR_TYPES
	* @brief Color types for logs
	*/
	enum LOG_COLOR_TYPES
	{
		LOG_COLOR_ERROR,
		LOG_COLOR_WARNING,
		LOG_COLOR_NOTICE
	};

	/**
	* @struct blowbox::LOG_COLOR_STRUCT
	* @brief Color struct for logs
	*/
	struct LOG_COLOR_STRUCT
	{
		float fr, fg, fb, br, bg, bb;
	};
	
	/**
	* @class blowbox::Console
	* @brief The console widget
	*/
	class Console : public QObject, public LuaClass
	{
	public:
		/**
		* @brief Default Console constructor
		*/
		Console();

		/**
		* @brief Lua Console constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Console(lua_State* L);

		/**
		* @brief Default Console constructor
		*/
		~Console();

		/**
		* @brief Retrieves the Console instance
		*/
		static Console* Instance();

		/**
		* @brief Is the console visible
		*/
		bool IsVisible();

		/**
		* @brief Logs a string in the console
		* @param[in] string (std::string) the string to be logged
		*/
		void Log(std::string string);

		/**
		* @brief Logs a string in the console
		* @param[in] string (std::string) the string to be logged
		* @param[in] fr (const int&) foreground red value
		* @param[in] fg (const int&) foreground green value
		* @param[in] fb (const int&) foreground blue value
		* @param[in] br (const int&) background red value
		* @param[in] bg (const int&) background green value
		* @param[in] bb (const int&) background blue value
		*/
		void Log(std::string string, const int& fr, const int& fg, const int& fb, const int& br, const int& bg, const int& bb);

		/**
		* @brief Logs a string in the console
		* @param[in] string (std::string) the string to be logged
		* @param[in] type (const LOG_COLOR_TYPES&) the type of log that is to be used colorwise
		*/
		void Log(std::string string, const LOG_COLOR_TYPES& type);

		/**
		* @brief Logs a string in the console
		* @param[in] string (std::string) the string to be logged
		* @param[in] colors (const LOG_COLOR_STRUCT&) the type of log that is to be used colorwise
		*/
		void Log(std::string string, const LOG_COLOR_STRUCT& colors);

		/**
		* @brief Replaces a part of a string
		* @param[in] subject (std::string) the string to be changed
		* @param[in] search (const std::string&) the string to be searched for and replaced
		* @param[in] replace (const std::string&) the string the search should be replaced by
		*/
		std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);

		/**
		* @brief Converts a color type to a color struct
		* @param[in] type (const LOG_COLOR_TYPE&) the type to be converted
		*/
		LOG_COLOR_STRUCT ConvertToStruct(const LOG_COLOR_TYPES& type);

		/**
		* @brief The event filter used on the input box and the enter button
		* @param[in] obj (QObject*) the object
		* @param[in] evt (QEvent*) the event
		*/
		bool eventFilter(QObject* obj, QEvent* evt);

		/**
		* @brief Logs a string
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaLog(lua_State* L);

		/**
		* @brief Logs an error string
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaError(lua_State* L);

		/**
		* @brief Logs a warning string
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaWarning(lua_State* L);

		/**
		* @brief Logs a notice string
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaNotice(lua_State* L);

		/**
		* @brief Logs an rgb string
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaRGB(lua_State* L);

		/**
		* @brief Logs a stacktrace
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaStackTrace(lua_State* L);

		CLASSNAME("Console");
	private:
		QMainWindow* main_window_;
		Ui::MainWindow* window_;
		std::vector<std::string> history_;
		int history_index_;
		bool shift_pressed_;
	};
}