#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <firstconfigure.h>
#include "admin_login.h"
#include "staff_login.h"
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_start_clicked();

private:
    Ui::MainWindow *ui;//Main user interface
    firstconfigure *first;
    staff_login *slogin;
    Admin_Login *alogin;
    QSqlDatabase db;
    QSqlQuery query;

    bool newrecord;
};

#endif // MAINWINDOW_H
