#ifndef DELETESTAFF_H
#define DELETESTAFF_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>

namespace Ui {
class deleteStaff;
}

class deleteStaff : public QMainWindow
{
    Q_OBJECT

public:
    explicit deleteStaff(QWidget *parent = 0);
    ~deleteStaff();

private slots:
    void on_Search_clicked();

    void on_deleteStaff_2_clicked();

    void on_Previous_clicked();

    void on_Next_clicked();

    void on_Back_clicked();

private:
    Ui::deleteStaff *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();

    QString keyword;
    QString sortValue;
    QString encrypt(QString);
    QString decrypt(QString);
};

#endif // DELETESTAFF_H
