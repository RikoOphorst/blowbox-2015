#include "console.h"

#include "../lua/lua_manager.h"

namespace blowbox
{
	Console::Console()
	{
		window_ = new QMainWindow();
		console_ = new Ui::Console();
		console_->setupUi(window_);

		lineEdit_ = console_->lineEdit;
		textEdit_ = console_->plainTextEdit;

		historyIndex_ = 0;

		textEdit_->setReadOnly(true);

		lineEdit_->installEventFilter(this);

		qApp->setApplicationName("Snuffbox Console");
		qApp->setStyle(QStyleFactory::create("Fusion"));

		QPalette steamPalette;
		steamPalette.setColor(QPalette::Window, QColor(32, 32, 34));
		steamPalette.setColor(QPalette::WindowText, QColor(166, 207, 207));
		steamPalette.setColor(QPalette::Base, QColor(23, 24, 26));
		steamPalette.setColor(QPalette::AlternateBase, QColor(23, 24, 26));
		steamPalette.setColor(QPalette::ToolTipBase, Qt::white);
		steamPalette.setColor(QPalette::ToolTipText, Qt::white);
		steamPalette.setColor(QPalette::Text, QColor(166, 207, 207));
		steamPalette.setColor(QPalette::Button, QColor(88, 106, 80));
		steamPalette.setColor(QPalette::ButtonText, Qt::white);
		steamPalette.setColor(QPalette::BrightText, Qt::red);
		steamPalette.setColor(QPalette::Link, QColor(159, 164, 98));

		steamPalette.setColor(QPalette::Highlight, QColor(159, 164, 98));
		steamPalette.setColor(QPalette::HighlightedText, Qt::black);

		qApp->setPalette(steamPalette);

		QFont courier;
		courier.setFamily("Courier New");
		courier.setStyleHint(QFont::Monospace);
		courier.setFixedPitch(true);
		courier.setPointSize(10);
		courier.setBold(false);

		textEdit_->setFont(courier);
		lineEdit_->setFont(courier);
	}

	Console::~Console()
	{

	}

	Console* Console::Instance()
	{
		static SharedPtr<Console> ptr(new Console());
		return ptr.get();
	}

	bool Console::eventFilter(QObject* obj, QEvent* evt)
	{
		if (obj == lineEdit_)
		{
			switch (evt->type()) 
			{
				case QEvent::KeyPress:
					QKeyEvent* keyEvent = static_cast<QKeyEvent*>(evt);
					switch (keyEvent->key())
					{
						case Qt::Key_Return:
						{
							QString str = lineEdit_->text();

							if (str.length() != 0)
							{
								std::string string = "";

								for (int i = 0; i < str.length(); ++i)
								{
									string += str.at(i).toLatin1();
								}

								LuaManager::ExecuteString(string.c_str(), "HALLO");

								history_.push_back(string);
								historyIndex_ = static_cast<int>(history_.size());
								lineEdit_->clear();
								return true;
							}
							break;
						}
						case Qt::Key_Up:
						{
							int size = history_.size();
							if (historyIndex_ > 0)
							{
								QString string = history_.at(--historyIndex_).c_str();
								lineEdit_->setText(string);
								return true;
							}
							break;
						}
						case Qt::Key_Down:
						{
							if (historyIndex_ < static_cast<int>(history_.size()))
							{
								QString string = history_.at(historyIndex_++).c_str();
								lineEdit_->setText(string);
								return true;
							}
							else
							{
								lineEdit_->setText("");
							}
							break;
						}
					}
				break;
			}

		}

		return false;
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