#ifndef ADD_STUDENT_H
#define ADD_STUDENT_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>
#include "academicreport.h"
#include <QString>
namespace Ui {
class add_Student;
}

class add_Student : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_Student(QWidget *parent = 0);
    ~add_Student();

private slots:
    void on_Student_submit_clicked();

    void on_chooseImage_clicked();



    void on_addmore_clicked();


    void on_panel_clicked();

private:
    Ui::add_Student *ui;
     QSqlDatabase db;
     QSqlQuery query;
     void FillForm();
     QString encrypt(QString);
     QString decrypt(QString);
     AcademicReport *areport;
};
extern QString registration_num;
//extern int database_id;
#endif // ADD_STUDENT_H
