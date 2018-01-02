#ifndef VIEWSTFTABLE_H
#define VIEWSTFTABLE_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>
#include "viewstfrecord.h"
namespace Ui {
class viewstftable;
}

class viewstftable : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewstftable(QWidget *parent = 0);
    ~viewstftable();

private slots:


    void on_Back_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_Search_clicked();

private:
    Ui::viewstftable *ui;
    QSqlDatabase db;
   viewstfrecord *vstaff;

    QSqlQuery query;

    bool loading;

    void FillTable();
    QString encrypt(QString);
    QString decrypt(QString);
    void searchbyFirstName(QString);
    void searchbyLastName(QString);
    void searchbyEmail(QString);
    void searchbyPhone(QString);
    void searchByPosition(QString);


};

extern int staff_id; //database id is made global type so that it can be accesed in viewstfrecord file


#endif // VIEWSTFTABLE_H
