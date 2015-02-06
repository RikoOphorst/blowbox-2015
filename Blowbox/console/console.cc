#include "console.h"

namespace blowbox
{
	Console::Console()
	{
		window_ = new QMainWindow();
		console_ = new Ui::Console();
		console_->setupUi(window_);

		lineEdit_ = console_->lineEdit;
		textEdit_ = console_->plainTextEdit;

		textEdit_->setReadOnly(true);

		connect(SOCKET(lineEdit_), lineEdit_->returnPressed(), 

		Log("Hallo ik ben een bericht en ik wil graag verschijnen in de console is dat okay nou mooi dan wat gebeurt er nudat ik dit heb gedaan ik weet het niet help help help");
	}

	Console::~Console()
	{

	}

	Console* Console::Instance()
	{
		static SharedPtr<Console> ptr(new Console());
		return ptr.get();
	}

	void Console::Show()
	{
		window_->show();
	}

	void Console::Log(const char* msg)
	{
		std::string str = static_cast<std::string>(msg);
		
		textEdit_->appendPlainText(msg);
	}
}