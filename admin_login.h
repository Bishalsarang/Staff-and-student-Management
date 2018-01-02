#ifndef ADMIN_LOGIN_H
#define ADMIN_LOGIN_H

#include <QMainWindow>
#include "cao_panel.h"
#include <QString>
#include <QtSql>
namespace Ui {
class Admin_Login;
}

class Admin_Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin_Login(QWidget *parent = 0);
    ~Admin_Login();

private slots:
    void on_loginCao_clicked();

private:
    Ui::Admin_Login *ui;
    Cao_panel *cp;
    QString encrypt(QString);
    QString decrypt(QString);
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // ADMIN_LOGIN_H
