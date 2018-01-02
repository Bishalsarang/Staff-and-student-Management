#ifndef ADDSTAFF_H
#define ADDSTAFF_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>

namespace Ui {
class addStaff;
}

class addStaff : public QMainWindow
{
    Q_OBJECT

public:
    explicit addStaff(QWidget *parent = 0);
    ~addStaff();

private slots:
    void on_sFormSubmit_clicked();

    void on_chooseImage_clicked();

    void on_addmore_clicked();

    void on_back_clicked();

private:
    Ui::addStaff *ui;

    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();

    QString encrypt(QString);
    QString decrypt(QString);
};

#endif // ADDSTAFF_H
