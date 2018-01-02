#include "staffpanel.h"
#include "ui_staffpanel.h"

StaffPanel::StaffPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StaffPanel)
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
    ui->inst_address->setText(query.value(1).toString());


    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();

    }else{
        qDebug()<< "Database connection:Error";
    }
}

StaffPanel::~StaffPanel()
{
    delete ui;
    db.close();
}

void StaffPanel::on_addStudent_clicked() //When Add Stuent Option is Choosen
{
    hide();
    addstd = new add_Student;
    addstd -> showMaximized();
}

void StaffPanel::on_viewStudent_clicked()
{
    hide();
    viewrec = new viewstdrecord;
    viewrec -> showMaximized();

}



void StaffPanel::on_viewTable_clicked()
{
    hide();
    viewstudenttab = new viewstdtable;
    viewstudenttab  -> showMaximized();
}

void StaffPanel::on_modifyStudent_clicked()
{
    hide();
    modstd = new modifyStudent;
    modstd -> showMaximized();
}

void StaffPanel::on_exitStaff_clicked()
{
    close();
}

void StaffPanel::on_deleteStudent_clicked()
{
    hide();
    delstd = new deleteStudent ;
    delstd -> showMaximized();
}

void StaffPanel::on_changeStaffPass_clicked()
{

    change_pass = new changepassword;
    change_pass -> show();
}

void StaffPanel::on_about_clicked()
{
  abt = new    About;
  abt -> show();
}
