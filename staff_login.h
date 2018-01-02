#ifndef STAFF_LOGIN_H
#define STAFF_LOGIN_H

#include <QMainWindow>
#include "staffpanel.h"
#include <QString>
#include <QtSql>
namespace Ui {
class staff_login;
}

class staff_login : public QMainWindow
{
    Q_OBJECT

public:
    explicit staff_login(QWidget *parent = 0);
    ~staff_login();

private slots:
    void on_loginStaff_clicked();

private:
    Ui::staff_login *ui;
    StaffPanel *spanel;
    QString encrypt(QString);
    QString decrypt(QString);
     QSqlDatabase db;
     QSqlQuery query;
};

#endif // STAFF_LOGIN_H
