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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Console
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QLineEdit *lineEdit;
    QWidget *tab_2;
    QTreeView *treeView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Console)
    {
        if (Console->objectName().isEmpty())
            Console->setObjectName(QStringLiteral("Console"));
        Console->resize(722, 525);
        Console->setMinimumSize(QSize(722, 525));
        Console->setMaximumSize(QSize(722, 525));
        Console->setWindowOpacity(1);
        Console->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(Console);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 701, 501));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        widget = new QWidget(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 702, 458));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(widget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setMinimumSize(QSize(400, 430));
        plainTextEdit->setMaximumSize(QSize(675, 460));

        verticalLayout->addWidget(plainTextEdit);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(675, 16777215));

        verticalLayout->addWidget(lineEdit);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        treeView = new QTreeView(tab_2);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 10, 675, 450));
        treeView->setMaximumSize(QSize(675, 450));
        tabWidget->addTab(tab_2, QString());
        Console->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Console);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Console->setStatusBar(statusbar);

        retranslateUi(Console);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Console);
    } // setupUi

    void retranslateUi(QMainWindow *Console)
    {
        Console->setWindowTitle(QApplication::translate("Console", "Blowbox - Console", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Console", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Console", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class Console: public Ui_Console {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONSOLE_UI_H
