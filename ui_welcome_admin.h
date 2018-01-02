/********************************************************************************
** Form generated from reading UI file 'welcome_admin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_ADMIN_H
#define UI_WELCOME_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Welcome_admin
{
public:
    QWidget *centralwidget;
    QLabel *label_insname;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Welcome_admin)
    {
        if (Welcome_admin->objectName().isEmpty())
            Welcome_admin->setObjectName(QStringLiteral("Welcome_admin"));
        Welcome_admin->resize(1024, 744);
        Welcome_admin->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Images/1730959.jpg);"));
        centralwidget = new QWidget(Welcome_admin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_insname = new QLabel(centralwidget);
        label_insname->setObjectName(QStringLiteral("label_insname"));
        label_insname->setGeometry(QRect(140, 210, 741, 81));
        label_insname->setStyleSheet(QLatin1String("color:#ffff00;\n"
"font: 28pt \"ISOCPEUR\";\n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 380, 751, 61));
        label->setStyleSheet(QLatin1String("background-color:#55aaff;\n"
"font: 28pt \"ISOCTEUR\";\n"
"color:#ffff00;"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 310, 441, 61));
        label_2->setStyleSheet(QLatin1String("font: 28pt \"ISOCTEUR\";\n"
"color:#ffff00;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(490, 510, 751, 61));
        label_3->setStyleSheet(QLatin1String("background-color:#55aaff;\n"
"font: 28pt \"ISOCTEUR\";\n"
"color:#ffff00;"));
        Welcome_admin->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Welcome_admin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Welcome_admin->setStatusBar(statusbar);

        retranslateUi(Welcome_admin);

        QMetaObject::connectSlotsByName(Welcome_admin);
    } // setupUi

    void retranslateUi(QMainWindow *Welcome_admin)
    {
        Welcome_admin->setWindowTitle(QApplication::translate("Welcome_admin", "Welcoming you as Admin", Q_NULLPTR));
        label_insname->setText(QApplication::translate("Welcome_admin", "Staff and Student Management ", Q_NULLPTR));
        label->setText(QApplication::translate("Welcome_admin", "Welcoming you as Admin", Q_NULLPTR));
        label_2->setText(QApplication::translate("Welcome_admin", "Admin Section", Q_NULLPTR));
        label_3->setText(QApplication::translate("Welcome_admin", "Please Wait......", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Welcome_admin: public Ui_Welcome_admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_ADMIN_H
