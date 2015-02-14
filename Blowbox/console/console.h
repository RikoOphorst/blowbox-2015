#pragma once

#include "../lua/lua_include.h"
#include "console_ui.h"
#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qstylefactory.h>

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
		void TraverseTable(lua_State* state, int idx, QTreeWidgetItem* parent);

		static int RegisterFunctions(lua_State* state);
		static int LuaLog(lua_State* state);
		static int LuaError(lua_State* state);
		static int LuaWatch(lua_State* state);

		static bool DEBUG;

		void Show();

		static const char* class_name(){ return "Console"; }
	private:
		QMainWindow* window_;
		Ui::Console* console_;
		QLineEdit* lineEdit_;
		QPlainTextEdit* textEdit_;
		QTreeWidget* treeView_;
		std::vector<std::string> history_;
		int historyIndex_;
	};
}