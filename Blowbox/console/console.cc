#include "console.h"

#include "../game.h"
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
		treeView_ = console_->treeWidget;

		historyIndex_ = 0;

		textEdit_->setReadOnly(true);

		lineEdit_->installEventFilter(this);

		qApp->setApplicationName("Blowbox Console");
		qApp->setStyle(QStyleFactory::create("Fusion"));

		QPalette steamPalette;
		steamPalette.setColor(QPalette::Window, QColor(32, 32, 34));
		steamPalette.setColor(QPalette::WindowText, QColor(166, 207, 207));
		steamPalette.setColor(QPalette::Base, QColor(23, 24, 26));
		steamPalette.setColor(QPalette::AlternateBase, QColor(23, 24, 26));
		steamPalette.setColor(QPalette::ToolTipBase, Qt::white);
		steamPalette.setColor(QPalette::ToolTipText, Qt::white);
		steamPalette.setColor(QPalette::Text, QColor(166, 207, 207));
		steamPalette.setColor(QPalette::Button, QColor(23, 24, 26));
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

		LuaRegister<Console>::Register(LM_STATE);
	}

	Console::Console(lua_State* state)
	{

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
		if (DEBUG == true)
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
							std::string string = str.toStdString();
							LuaManager::ExecuteString(string.c_str(), "@Console");

							history_.push_back(string);
							historyIndex_ = static_cast<int>(history_.size());
							lineEdit_->clear();
							return true;
						}
						break;
					}
					case Qt::Key_Up:
					{
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
		}

		return false;
	}

	void Console::Show()
	{
		window_->activateWindow();
	}

	void Console::Log(const char* msg)
	{
		if (DEBUG == true)
		{
			std::string str = static_cast<std::string>(msg);

			textEdit_->appendPlainText(msg);
		}
	}

	void Console::Watch(const char* name)
	{

	}

	void Console::Activate()
	{
		window_->show();

		Console::DEBUG = true;
	}

	int Console::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "Log", LuaLog },
			{ "Error", LuaError },
			{ "Watch", LuaWatch },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

		return 0;
	}

	int Console::LuaLog(lua_State* state)
	{
		BLOW_CONSOLE_LOG(LuaManager::GetValue<const char*>(0));
		return 0;
	}

	int Console::LuaError(lua_State* state)
	{
		BLOW_CONSOLE_ERROR(LuaManager::GetValue<const char*>(0));
		return 0;
	}

	int Console::LuaWatch(lua_State* state)
	{
		Console* console = Console::Instance();

		QTreeWidgetItem* item = new QTreeWidgetItem();

		item->setText(0, LuaManager::GetValue<const char*>(0));

		//console->TraverseTable(state, 2, item);

		console->treeView_->addTopLevelItem(item);

		return 0;
	}

	void Console::TraverseTable(lua_State* state, int idx, QTreeWidgetItem* parent)
	{
		lua_pushvalue(state, idx);

		lua_pushnil(state);

		while (lua_next(state, -2))
		{
			QTreeWidgetItem* item = new QTreeWidgetItem(parent);
			
			lua_pushvalue(state, -2);

			const char* key = lua_tostring(state, -1);
			const char* valuetype = lua_typename(state, lua_type(state, -2));
			const char* value = lua_tostring(state, -2);

			item->setText(0, key);

			if (strcmp(valuetype, "table") == 0)
			{
				item->setText(1, "[table]");
				lua_pop(state, 2);
				TraverseTable(state, 0, item);
			}
			else
			{
				std::string str = "[";

				str += valuetype;

				str += "] ";

				str += value;

				item->setText(1, QString(str.c_str()));
				lua_pop(state, 2);
			}
		}
		lua_pop(state, 1);
	}

	bool Console::DEBUG = false;
}