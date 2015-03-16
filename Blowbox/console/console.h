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
	enum LOG_COLOR_TYPES
	{
		LOG_COLOR_ERROR,
		LOG_COLOR_WARNING,
		LOG_COLOR_NOTICE
	};

	struct LOG_COLOR_STRUCT
	{
		float fr, fg, fb, br, bg, bb;
	};
	
	class Console : public QObject, public LuaClass
	{
	public:
		Console();

		Console(lua_State* L);

		~Console();

		static Console* Instance();

		void Log(std::string string);

		void Log(std::string string, const int& fr, const int& fg, const int& fb, const int& br, const int& bg, const int& bb);

		void Log(std::string string, const LOG_COLOR_TYPES& type);

		void Log(std::string string, const LOG_COLOR_STRUCT& colors);

		std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);

		LOG_COLOR_STRUCT ConvertToStruct(const LOG_COLOR_TYPES& type);

		bool eventFilter(QObject* obj, QEvent* evt);

		static void LuaRegisterFunctions(lua_State* L);

		static int LuaLog(lua_State* L);
		static int LuaError(lua_State* L);
		static int LuaWarning(lua_State* L);
		static int LuaNotice(lua_State* L);
		static int LuaRGB(lua_State* L);
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