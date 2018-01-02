#ifndef SETFIRSTPASSWORD_H
#define SETFIRSTPASSWORD_H

#include <QMainWindow>
#include <QtSql>
#include "admin_login.h"
#include "staff_login.h"
namespace Ui {
class Setfirstpassword;
}

class Setfirstpassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit Setfirstpassword(QWidget *parent = 0);

    ~Setfirstpassword();

private slots:
    void on_loginButon_clicked();

private:
    Ui::Setfirstpassword *ui;


    QSqlDatabase db;
    QSqlQuery query;
    QString encrypt(QString);
    QString decrypt(QString);
    Admin_Login *alogin;
    staff_login *slogin;
    bool newrecord;
};

#endif // SETFIRSTPASSWORD_H
