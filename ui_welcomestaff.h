/********************************************************************************
** Form generated from reading UI file 'welcomestaff.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMESTAFF_H
#define UI_WELCOMESTAFF_H

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

class Ui_WelcomeStaff
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WelcomeStaff)
    {
        if (WelcomeStaff->objectName().isEmpty())
            WelcomeStaff->setObjectName(QStringLiteral("WelcomeStaff"));
        WelcomeStaff->resize(1024, 821);
        WelcomeStaff->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Images/green_minimalistic_background_by_77matt77.jpg);"));
        centralwidget = new QWidget(WelcomeStaff);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(260, 540, 751, 151));
        label->setStyleSheet(QStringLiteral("font: 24pt \"ISOCTEUR\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 40, 1031, 221));
        label_2->setStyleSheet(QStringLiteral("font: 24pt \"ISOCTEUR\";"));
        WelcomeStaff->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(WelcomeStaff);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        WelcomeStaff->setStatusBar(statusbar);

        retranslateUi(WelcomeStaff);

        QMetaObject::connectSlotsByName(WelcomeStaff);
    } // setupUi

    void retranslateUi(QMainWindow *WelcomeStaff)
    {
        WelcomeStaff->setWindowTitle(QApplication::translate("WelcomeStaff", "Welcoming you as Staff", Q_NULLPTR));
        label->setText(QApplication::translate("WelcomeStaff", "Welcoming You as Staff", Q_NULLPTR));
        label_2->setText(QApplication::translate("WelcomeStaff", "<html><head/><body><p align=\"center\">Staff and Student Management Software</p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WelcomeStaff: public Ui_WelcomeStaff {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMESTAFF_H
