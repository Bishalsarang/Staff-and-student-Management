#ifndef FIRSTCONFIGURE_H
#define FIRSTCONFIGURE_H

#include <QMainWindow>
#include "setfirstpassword.h"
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>
namespace Ui {
class firstconfigure;
}

class firstconfigure : public QMainWindow
{
    Q_OBJECT

public:
    explicit firstconfigure(QWidget *parent = 0);
    ~firstconfigure();

private slots:
    void on_pushButton_clicked();

private:
    Ui::firstconfigure *ui;
    Setfirstpassword *setfirst;

    firstconfigure *first;
    QSqlDatabase configdb;
    QSqlQuery query;

    bool newrecord;
};

#endif // FIRSTCONFIGURE_H
