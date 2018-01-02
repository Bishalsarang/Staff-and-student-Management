#ifndef MODIFYSTUDENT_H
#define MODIFYSTUDENT_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>

namespace Ui {
class modifyStudent;
}

class modifyStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit modifyStudent(QWidget *parent = 0);
    ~modifyStudent();

private slots:
    void on_modify_clicked();

    void on_choose_clicked();

    void on_Next_clicked();

    void on_Previous_clicked();

    void on_Search_clicked();

    void on_Back_clicked();

private:
    Ui::modifyStudent *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();
    bool newrecord;
    //QString filename;
    QString sortValue;
    QString keyword;
    QString encrypt(QString);
    QString decrypt(QString);
};

#endif // MODIFYSTUDENT_H
