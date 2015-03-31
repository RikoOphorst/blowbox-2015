#include "../../blowbox/console/console.h"

#include <time.h>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Console::Console()
	{
		shift_pressed_ = false;

		main_window_ = new QMainWindow();
		window_ = new Ui::MainWindow();
		window_->setupUi(main_window_);

		QPalette palette;
		palette.setColor(QPalette::Window, QColor(8, 38, 36));
		palette.setColor(QPalette::WindowText, QColor(166, 207, 207));
		palette.setColor(QPalette::Base, QColor(23, 24, 26));
		palette.setColor(QPalette::AlternateBase, QColor(23, 24, 26));
		palette.setColor(QPalette::ToolTipBase, Qt::white);
		palette.setColor(QPalette::ToolTipText, Qt::white);
		palette.setColor(QPalette::Text, QColor(166, 207, 207));
		palette.setColor(QPalette::Button, QColor(23, 24, 26));
		palette.setColor(QPalette::ButtonText, Qt::white);
		palette.setColor(QPalette::BrightText, Qt::red);
		palette.setColor(QPalette::Link, QColor(159, 164, 98));

		palette.setColor(QPalette::Highlight, QColor(100, 106, 120));
		palette.setColor(QPalette::HighlightedText, Qt::black);

		QFont textFont;
		textFont.setFamily("Consolas");
		textFont.setStyleHint(QFont::Monospace);
		textFont.setFixedPitch(true);
		textFont.setPointSize(10);
		textFont.setBold(false);

		QFont headerFont;
		headerFont.setFamily("Impact");
		headerFont.setStyleHint(QFont::Monospace);
		headerFont.setFixedPitch(true);
		headerFont.setPointSize(10);
		headerFont.setBold(false);

		qApp->setApplicationDisplayName("blowbox console");
		qApp->setApplicationName("blowbox console");
		qApp->setPalette(palette);

		window_->input->setFont(textFont);
		window_->terminal->setFont(textFont);
		window_->header->setFont(headerFont);
		window_->enter->setFont(headerFont);

		window_->terminal->setStyleSheet(QString::fromUtf8(""
			"QTextEdit {"
			"	border: 1px solid #0b3633"
			"}"
			"QScrollBar {               "
			"    border: 1px solid #999999;"
			"    background:white;"
			"    width:10px;    "
			"    margin: 0px 0px 0px 0px;"
			"}"
			"QScrollBar::handle {"
			"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
			"    stop: 0  rgb(11, 54, 51), stop: 0.5 rgb(11, 54, 51),  stop:1 rgb(11, 54, 51));"
			"    min-height: 0px;"
			""
			"}"
			"QScrollBar::add-line {"
			"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
			"    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
			"    height: px;"
			"    subcontrol-position: bottom;"
			"    subcontrol-origin: margin;"
			"}"
			"QScrollBar::sub-line {"
			"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
			"    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
			"    height: 0px;"
			"    subcontrol-position: top;"
			"    subcontrol-origin: margin;"
			"}"
			""));

		window_->enter->setStyleSheet(QString::fromUtf8(""
			"QPushButton {"
			"	background: #072220"
			"}"
			""));

		window_->input->setStyleSheet(QString::fromUtf8(""
			"QPlainTextEdit {"
			"	background: #17181a;"
			"	border: 1px solid #0b3633"
			"}"
			""));

		main_window_->activateWindow();
		main_window_->show();

		window_->input->installEventFilter(this);
		window_->enter->installEventFilter(this);
	}

	//------------------------------------------------------------------------------------------------------
	Console::Console(lua_State* L)
	{

	}

	//------------------------------------------------------------------------------------------------------
	Console::~Console()
	{

	}

	//------------------------------------------------------------------------------------------------------
	Console* Console::Instance()
	{
		static SharedPtr<Console> ptr(new Console());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	bool Console::IsVisible()
	{
		return main_window_->isVisible();
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(std::string string)
	{
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);
		QString hour = QString::number(now.tm_hour);

		if (hour.size() < 2)
		{
			hour = "0" + hour;
		}

		QString min = QString::number(now.tm_min);
		if (min.size() < 2)
		{
			min = "0" + min;
		}

		QString sec = QString::number(now.tm_sec);
		if (sec.size() < 2)
		{
			sec = "0" + sec;
		}
		QString timeStamp = hour + ":" + min + ":" + sec + " ";
		
		QTextCursor cursor = window_->terminal->textCursor();
		cursor.movePosition(QTextCursor::End);

		string = ReplaceString(string, "\n", timeStamp.toStdString());

		string += "\n";

		QTextCharFormat format;
		format.setForeground(QBrush(QColor(166, 207, 207)));
		format.setFontPointSize(10);
		cursor.setCharFormat(format);

		cursor.insertText(timeStamp + string.c_str());
		cursor.movePosition(QTextCursor::End);

		window_->terminal->setTextCursor(cursor);
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(std::string string, const int& fr, const int& fg, const int& fb, const int& br, const int& bg, const int& bb)
	{
		
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);
		QString hour = QString::number(now.tm_hour);

		if (hour.size() < 2)
		{
			hour = "0" + hour;
		}

		QString min = QString::number(now.tm_min);
		if (min.size() < 2)
		{
			min = "0" + min;
		}

		QString sec = QString::number(now.tm_sec);
		if (sec.size() < 2)
		{
			sec = "0" + sec;
		}
		QString timeStamp = hour + ":" + min + ":" + sec + " ";

		QTextCursor cursor = window_->terminal->textCursor();
		cursor.movePosition(QTextCursor::End);

		string = ReplaceString(string, "\n", "\n" + timeStamp.toStdString());
		string += "\n";
		
		QTextCharFormat format;
		format.setForeground(QBrush(QColor(fr, fg, fb)));
		format.setBackground(QBrush(QColor(br, bg, bb)));
		format.setFontPointSize(10);
		cursor.setCharFormat(format);

		cursor.insertText(timeStamp + string.c_str());
		cursor.movePosition(QTextCursor::End);

		window_->terminal->setTextCursor(cursor);
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(std::string string, const LOG_COLOR_TYPES& type)
	{
		const LOG_COLOR_STRUCT& colors = ConvertToStruct(type);

		Log(string, colors.fr, colors.fg, colors.fb, colors.br, colors.bg, colors.bb);
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(std::string string, const LOG_COLOR_STRUCT& colors)
	{
		Log(string, colors.fr, colors.fg, colors.fb, colors.br, colors.bg, colors.bb);
	}

	//------------------------------------------------------------------------------------------------------
	std::string Console::ReplaceString(std::string subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	//------------------------------------------------------------------------------------------------------
	LOG_COLOR_STRUCT Console::ConvertToStruct(const LOG_COLOR_TYPES& type)
	{
		LOG_COLOR_STRUCT colors;
		
		switch (type)
		{
		case LOG_COLOR_TYPES::LOG_COLOR_ERROR:
			colors.fr = 255;
			colors.fg = 255;
			colors.fb = 255;
			colors.br = 153;
			colors.bg = 0;
			colors.bb = 0;
			break;
		case LOG_COLOR_TYPES::LOG_COLOR_WARNING:
			colors.fr = 50;
			colors.fg = 50;
			colors.fb = 34;
			colors.br = 200;
			colors.bg = 150;
			colors.bb = 0;
			break;
		case LOG_COLOR_TYPES::LOG_COLOR_NOTICE:
			colors.fr = 7;
			colors.fg = 56;
			colors.fb = 61;
			colors.br = 18;
			colors.bg = 142;
			colors.bb = 153;
			break;
		default:
			colors.fr = 255;
			colors.fg = 255;
			colors.fb = 255;
			colors.br = 0;
			colors.bg = 0;
			colors.bb = 0;
			break;
		}

		return colors;
	}

	//------------------------------------------------------------------------------------------------------
	bool Console::eventFilter(QObject* obj, QEvent* evt)
	{
		if (obj == window_->input)
		{
			if (evt->type() == QEvent::KeyPress || evt->type() == QEvent::KeyRelease)
			{
				QKeyEvent* keyEvent = static_cast<QKeyEvent*>(evt);

				if (evt->type() == QEvent::KeyPress)
				{
					if (keyEvent->key() == Qt::Key::Key_Shift)
					{
						shift_pressed_ = true;
					}

					if (keyEvent->key() == Qt::Key::Key_Up && !shift_pressed_)
					{
						if (history_index_ > 0)
						{
							QString string = history_.at(--history_index_).c_str();
							window_->input->setPlainText(string);
							return true;
						}
					}

					if (keyEvent->key() == Qt::Key::Key_Down && !shift_pressed_)
					{
						if (history_index_ < static_cast<int>(history_.size()))
						{
							QString string = history_.at(history_index_++).c_str();
							window_->input->setPlainText(string);
							return true;
						}
						else
						{
							window_->input->setPlainText("");
						}
					}

					if (keyEvent->key() == Qt::Key::Key_Return && !shift_pressed_)
					{
						QString string = window_->input->toPlainText();

						if (string.length() > 0)
						{
							Log("[INPUT] " + string.toStdString());
							
							LuaWrapper::Instance()->CompileFromString(LuaState::Instance()->Get(), string.toStdString(), "debug");

							history_.push_back(string.toStdString());
							history_index_ = static_cast<int>(history_.size());

							window_->input->clear();
						}

						return true;
					}
				}

				if (evt->type() == QEvent::KeyRelease)
				{
					if (keyEvent->key() == Qt::Key::Key_Shift)
					{
						shift_pressed_ = false;
					}
				}
			}
		}
		else if (obj == window_->enter)
		{
			if (evt->type() == QEvent::Type::MouseButtonRelease)
			{
				QString string = window_->input->toPlainText();

				if (string.length() > 0)
				{
					Log("[INPUT] " + string.toStdString());
					
					LuaWrapper::Instance()->CompileFromString(LuaState::Instance()->Get(), string.toStdString(), "debug");

					history_.push_back(string.toStdString());
					history_index_ = static_cast<int>(history_.size());

					window_->input->clear();
				}
			}
		}

		return false;
	}

	//------------------------------------------------------------------------------------------------------
	void Console::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "log", LuaLog },
			{ "error", LuaError },
			{ "warning", LuaWarning },
			{ "notice", LuaNotice },
			{ "rgb", LuaRGB },
			{ "stacktrace", LuaStackTrace },
			{ "trace", LuaStackTrace },
			{ "stack", LuaStackTrace },
			{ "backtrace", LuaStackTrace },
			{ "tracestack", LuaStackTrace },
			{ "traceback", LuaStackTrace },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);

		LuaRegister::Instance()->RegisterFunction(L, LuaLog, "print");
	}

	//------------------------------------------------------------------------------------------------------
	int Console::LuaLog(lua_State* L)
	{
		Console::Instance()->Log(LuaWrapper::Instance()->Get<std::string>(L, 1));
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Console::LuaError(lua_State* L)
	{
		Console::Instance()->Log(LuaWrapper::Instance()->Get<std::string>(L, 1), LOG_COLOR_TYPES::LOG_COLOR_ERROR);
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Console::LuaWarning(lua_State* L)
	{
		Console::Instance()->Log(LuaWrapper::Instance()->Get<std::string>(L, 1), LOG_COLOR_TYPES::LOG_COLOR_WARNING);
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Console::LuaNotice(lua_State* L)
	{
		Console::Instance()->Log(LuaWrapper::Instance()->Get<std::string>(L, 1), LOG_COLOR_TYPES::LOG_COLOR_NOTICE);
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Console::LuaRGB(lua_State* L)
	{
		Console::Instance()->Log(
			LuaWrapper::Instance()->Get<std::string>(L, 1),
			LuaWrapper::Instance()->Get<double>(L, 2),
			LuaWrapper::Instance()->Get<double>(L, 3),
			LuaWrapper::Instance()->Get<double>(L, 4),
			LuaWrapper::Instance()->Get<double>(L, 5),
			LuaWrapper::Instance()->Get<double>(L, 6),
			LuaWrapper::Instance()->Get<double>(L, 7)
			);
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Console::LuaStackTrace(lua_State* L)
	{
		LuaWrapper::Instance()->StackTrace(L);
		return 0;
	}
}