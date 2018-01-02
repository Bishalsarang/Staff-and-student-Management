#ifndef VIEWSTDTABLE_H
#define VIEWSTDTABLE_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>
#include "viewstdrecord.h"

namespace Ui {
class viewstdtable;
}

class viewstdtable : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewstdtable(QWidget *parent = 0);
    ~viewstdtable();
private slots:





    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_Search_clicked();
    void on_Back_clicked();



public:

private:
    Ui::viewstdtable *ui;
    QSqlDatabase db;
    viewstdrecord *viewstd;

    QSqlQuery query;
    QString encrypt(QString);
    QString decrypt(QString);


    void FillTable();
    void sortByfirstname(QString);
     void searchByemail(QString);
     void searchBycourse(QString);
     void searchByyear(QString);
     void searchByReg(QString);

};
extern int database_id; //database id is made global type so that it can be accesed in viewstdrecord file

#endif // VIEWSTDTABLE_H
