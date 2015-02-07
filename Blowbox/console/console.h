#pragma once

#include "../memory/shared_ptr.h"

#include "console_ui.h"
#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qstylefactory.h>

#define BLOW_CONSOLE_LOG(msg) { std::string m = "[LOG]\t"; std::string m2 = ##msg; Console::Instance()->Log(std::string(m + m2).c_str()); }
#define BLOW_CONSOLE_INPUT(msg) { std::string m = "[INPUT]\t"; std::string m2 = ##msg; Console::Instance()->Log(std::string(m + m2).c_str()); }
#define BLOW_CONSOLE_ERROR(msg) { std::string m = "[ERROR]\t"; std::string m2 = ##msg; Console::Instance()->Log(std::string(m + m2).c_str()); }

namespace blowbox
{
	class Console : public QObject
	{
		
	public:
		Console();
		~Console();

		static Console* Instance();

		bool eventFilter(QObject* obj, QEvent* evt);

		void Log(const char* string);

		void Show();
	private:
		QMainWindow* window_;
		Ui::Console* console_;
		QLineEdit* lineEdit_;
		QPlainTextEdit* textEdit_;
		std::vector<std::string> history_;
		int historyIndex_;
	};
}