#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class changepassword;
}

class changepassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit changepassword(QWidget *parent = 0);
    ~changepassword();

private slots:
    void on_ChangePassword_clicked();

private:
    Ui::changepassword *ui;
    QSqlDatabase db;
    QSqlQuery query;
    QString encrypt(QString);
    QString decrypt(QString);
};

#endif // CHANGEPASSWORD_H
