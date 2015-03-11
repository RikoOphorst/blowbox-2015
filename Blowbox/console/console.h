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
	class Console : public QObject, public LuaClass
	{
	public:
		Console();

		Console(lua_State* L);

		~Console();

		static Console* Instance();

		void Log(std::string string);

		void Log(std::string string, const int& fr, const int& fg, const int& fb, const int& br, const int& bg, const int& bb);

		bool eventFilter(QObject* obj, QEvent* evt);

		CLASSNAME("console");
	private:
		QMainWindow* main_window_;
		Ui::MainWindow* window_;
		std::vector<std::string> history_;
		int history_index_;
		bool shift_pressed_;
	};
}