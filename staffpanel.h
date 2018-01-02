#ifndef STAFFPANEL_H
#define STAFFPANEL_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include "add_student.h"
#include "viewstdrecord.h"
#include "viewstdtable.h"
#include "modifystudent.h"
#include "deletestudent.h"
#include "changepassword.h"
#include "about.h"
namespace Ui {
class StaffPanel;
}

class StaffPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit StaffPanel(QWidget *parent = 0);
    ~StaffPanel();

private slots:
    void on_addStudent_clicked();

    void on_viewStudent_clicked();



    void on_viewTable_clicked();

    void on_modifyStudent_clicked();

    void on_exitStaff_clicked();

    void on_deleteStudent_clicked();

    void on_changeStaffPass_clicked();

    void on_about_clicked();

private:
    Ui::StaffPanel *ui;
    add_Student *addstd;
    viewstdrecord *viewrec;
    viewstdtable *viewstudenttab;
    modifyStudent *modstd;
    deleteStudent *delstd;
    changepassword *change_pass;
    About *abt;
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // STAFFPANEL_H
