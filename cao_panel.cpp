#include "cao_panel.h"
#include "ui_cao_panel.h"

Cao_panel::Cao_panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cao_panel)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    query = QSqlQuery(db);
    //Name And Address Of the Institution as saved in databse
    if(!query.exec("SELECT institution_name, institution_address  FROM users WHERE access = 1")) qDebug() << "Error while Extracting name and address";
    query.first();
    ui->inst_name->setText(query.value(0).toString());



}

Cao_panel::~Cao_panel()
{
    delete ui;
}

void Cao_panel::on_pushButton_addstaff_clicked()
{
    hide();
    astaff = new addStaff;
    astaff -> showMaximized();
}

void Cao_panel::on_pushButton_modifystaff_clicked()
{
    hide();
    modStaff = new modifyStaff;
    modStaff -> showMaximized();
}

void Cao_panel::on_pushButton_viewstaff_clicked()
{
    hide();
    viewstaff = new viewstfrecord;
    viewstaff -> showMaximized();

}



void Cao_panel::on_pushButton_deletestaff_clicked()
{
    hide();
    delStaff = new  deleteStaff;
    delStaff -> show();
}

void Cao_panel::on_pushButton_exitstaff_clicked()
{
    close();
}

void Cao_panel::on_pushButton_changepasswordstaff_clicked()
{

    change_pass = new changepassword;
    change_pass -> showMaximized();
}

void Cao_panel::on_pushButton_clicked()
{
    abt_us = new About;
    abt_us -> show();
}

void Cao_panel::on_viewstafftable_clicked()
{
    hide();
    vstafftable = new viewstftable;
    vstafftable -> showMaximized();
}

void Cao_panel::on_pushButton_19_clicked()
{

   abt = new About ;
   abt -> show();
}
