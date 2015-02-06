#pragma once

#include "../memory/shared_ptr.h"

#include "console_ui.h"
#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\qapplication.h>

namespace blowbox
{
	class Console
	{
	public:
		Console();
		~Console();

		static Console* Instance();

		void Log(const char* string);

		void Show();
	private:
		QMainWindow* window_;
		Ui::Console* console_;
		QLineEdit* lineEdit_;
		QPlainTextEdit* textEdit_;
	};
}