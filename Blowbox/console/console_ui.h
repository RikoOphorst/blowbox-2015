/********************************************************************************
** Form generated from reading UI file 'console_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *terminal;
    QLabel *header;
    QPushButton *enter;
    QPlainTextEdit *input;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        terminal = new QTextEdit(centralwidget);
        terminal->setObjectName(QStringLiteral("terminal"));
        terminal->setGeometry(QRect(10, 50, 781, 431));
        terminal->setFrameShape(QFrame::StyledPanel);
        terminal->setFrameShadow(QFrame::Sunken);
        terminal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        terminal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        terminal->setDocumentTitle(QStringLiteral(""));
        terminal->setUndoRedoEnabled(false);
        terminal->setReadOnly(true);
        terminal->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));
        terminal->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse|Qt::TextBrowserInteraction|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        header = new QLabel(centralwidget);
        header->setObjectName(QStringLiteral("header"));
        header->setGeometry(QRect(10, 10, 781, 31));
        header->setAlignment(Qt::AlignCenter);
        header->setWordWrap(false);
        header->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        enter = new QPushButton(centralwidget);
        enter->setObjectName(QStringLiteral("enter"));
        enter->setGeometry(QRect(680, 490, 111, 81));
        input = new QPlainTextEdit(centralwidget);
        input->setObjectName(QStringLiteral("input"));
        input->setGeometry(QRect(10, 490, 661, 81));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        header->setText(QApplication::translate("MainWindow", "blowbox - console window", 0));
        enter->setText(QApplication::translate("MainWindow", "Enter", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONSOLE_UI_H
