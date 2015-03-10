#include "../../blowbox/console/console.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Console::Console()
	{
		
		
		main_window_ = new QMainWindow();
		window_ = new Ui::MainWindow();
		window_->setupUi(main_window_);

		window_->input->installEventFilter(this);

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

		palette.setColor(QPalette::Highlight, QColor(0, 0, 0));
		palette.setColor(QPalette::HighlightedText, Qt::black);

		QFont font;
		font.setFamily("Impact");
		font.setStyleHint(QFont::Monospace);
		font.setFixedPitch(true);
		font.setPointSize(10);
		font.setBold(false);

		qApp->setApplicationDisplayName("blowbox console");
		qApp->setApplicationName("blowbox console");
		qApp->setPalette(palette);

		window_->input->setFont(font);
		window_->terminal->setFont(font);
		window_->header->setFont(font);
		window_->enter->setFont(font);

		window_->terminal->setStyleSheet(QString::fromUtf8("QScrollBar {               "
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

		main_window_->activateWindow();
		main_window_->show();
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
	bool Console::eventFilter(QObject* obj, QEvent* evt)
	{
		return true;
	}
}