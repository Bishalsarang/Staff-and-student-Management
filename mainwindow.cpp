#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    delete ui;
    db.close();


}


void MainWindow::on_start_clicked()// when get started button is clicked
{
    //Database Connection

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3"); //Ptah+ file
    db.open();

    // set a "cursor"
    QSqlQuery query;
    query.exec("SELECT * FROM users");


    int user[2];
    QString inst[2]; //array to store accesibility of users
    int i = 0;
    while(query.next())
    { QString   test = query.value(1).toString();
        user[i] = query.value(2).toInt();
        inst[i] = query.value(3).toString();
        qDebug() << test;
        i++;
    }
   // qDebug() << user[0] << user[1];
    int CAO = user[0];
    int staff = user[1];
    if(CAO && staff)
    {
        //Error
        //Both can't be 1 at same time
        qDebug() << "Error";
        db.close();
        //db.removeDatabase(QSqlDatabase::defaultConnection);
    }
    else if(CAO == 0 && staff == 0) //Program is running for the first Time

    {
        //Open First Configure


                hide();
        first = new firstconfigure;
        first -> showMaximized();

    }


    else if(!CAO && staff)//When staff is selected
    {
        //open staff
        // Qstring name_of_inst =


        hide();
        slogin = new staff_login;
        slogin -> showMaximized();
    }
    else if(CAO && !staff)//When CAO is selected
    {
        //open admin



        hide();
        alogin = new Admin_Login;
        alogin -> showMaximized();


    }



    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();
    }
    else{
        qDebug()<< "Database connection:Error";
    }




}
