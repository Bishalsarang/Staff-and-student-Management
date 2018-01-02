#ifndef VIEWSTDRECORD_H
#define VIEWSTDRECORD_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>
#include "viewresult.h"


namespace Ui {
class viewstdrecord;
}

class viewstdrecord : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewstdrecord(QWidget *parent = 0);
    ~viewstdrecord();

private slots:


    void on_Next_clicked();

    void on_Previous_clicked();

    void on_Back_clicked();



    void on_Search_clicked();

    void on_showresult_clicked();

private:
    Ui::viewstdrecord *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();
    bool newrecord;
    QString encrypt(QString);
    QString decrypt(QString);
    viewresult *view;
};
extern QString v_registration_num;

#endif // VIEWSTDRECORD_H
