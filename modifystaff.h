#ifndef MODIFYSTAFF_H
#define MODIFYSTAFF_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>
namespace Ui {
class modifyStaff;
}

class modifyStaff : public QMainWindow
{
    Q_OBJECT

public:
    explicit modifyStaff(QWidget *parent = 0);
    ~modifyStaff();

private slots:
    void on_Next_clicked();

    void on_Search_clicked();

    void on_Previous_clicked();

    void on_Back_clicked();

    void on_modify_clicked();

    void on_pushButton_clicked();

private:
    Ui::modifyStaff *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();
    QString sortValue;
    QString keyword;
    QString encrypt(QString);
    QString decrypt(QString);

};

#endif // MODIFYSTAFF_H
