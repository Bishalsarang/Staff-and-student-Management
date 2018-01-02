/********************************************************************************
** Form generated from reading UI file 'initial_admin.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIAL_ADMIN_H
#define UI_INITIAL_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Initial_admin
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Initial_admin)
    {
        if (Initial_admin->objectName().isEmpty())
            Initial_admin->setObjectName(QStringLiteral("Initial_admin"));
        Initial_admin->resize(1111, 828);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/images/icons/logoicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Initial_admin->setWindowIcon(icon);
        Initial_admin->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Images/1 (1).jpg);"));
        centralwidget = new QWidget(Initial_admin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 260, 831, 61));
        label->setStyleSheet(QLatin1String("color:#aaff00;\n"
"background-image: url(:/new/images/Images/cao_bg.jpeg);\n"
"font: 20pt \"Comic Sans MS\";"));
        Initial_admin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Initial_admin);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1111, 26));
        Initial_admin->setMenuBar(menubar);
        statusbar = new QStatusBar(Initial_admin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Initial_admin->setStatusBar(statusbar);

        retranslateUi(Initial_admin);

        QMetaObject::connectSlotsByName(Initial_admin);
    } // setupUi

    void retranslateUi(QMainWindow *Initial_admin)
    {
        Initial_admin->setWindowTitle(QApplication::translate("Initial_admin", "Welcoming as Admin", Q_NULLPTR));
        label->setText(QApplication::translate("Initial_admin", "Initializing as Admin,Wait for few Seconds.....", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Initial_admin: public Ui_Initial_admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIAL_ADMIN_H
