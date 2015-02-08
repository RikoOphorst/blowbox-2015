#pragma once

#include "../memory/shared_ptr.h"

#include "console_ui.h"
#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qstylefactory.h>
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

#define BLOW_CONSOLE_LOG(msg) if (Console::DEBUG == true) { std::string m = "[LOG]\t"; std::string m2 = ##msg; Console::Instance()->Log(std::string(m + m2).c_str()); }
#define BLOW_CONSOLE_INPUT(msg) if (Console::DEBUG == true) { std::string m = "[INPUT]\t"; std::string m2 = ##msg; Console::Instance()->Log(std::string(m + m2).c_str()); }
#define BLOW_CONSOLE_ERROR(msg) if (Console::DEBUG == true) { std::string m = "[ERROR]\t"; std::string m2 = ##msg; Console::Instance()->Log(std::string(m + m2).c_str()); }

namespace blowbox
{
	class Console : public QObject
	{
		
	public:
		Console();
		Console(lua_State* state);
		~Console();

		static Console* Instance();

		bool eventFilter(QObject* obj, QEvent* evt);

		void Log(const char* string);
		void Watch(const char* string);
		void Activate();

		static int RegisterFunctions(lua_State* state);
		static int LuaLog(lua_State* state);
		static int LuaError(lua_State* state);
		static int LuaWatch(lua_State* state);

		static bool DEBUG;

		void Show();

		LM_NAME("Console");
	private:
		QMainWindow* window_;
		Ui::Console* console_;
		QLineEdit* lineEdit_;
		QPlainTextEdit* textEdit_;
		QTreeView* treeView_;
		std::vector<std::string> history_;
		int historyIndex_;
	};
}