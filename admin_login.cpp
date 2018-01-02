#include "admin_login.h"
#include "ui_admin_login.h"
#include<QRegExpValidator>
#include <QString>
#include <QSplashScreen>
#include <QThread>
#include <QMessageBox>



Admin_Login::Admin_Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin_Login)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    query = QSqlQuery(db);
    if(!query.exec("SELECT institution_name, institution_address  FROM users WHERE access = 1")) qDebug() << "Error while Extracting name and address";
    query.first();
    ui->inst_name->setText(query.value(0).toString());
    ui->inst_address->setText(query.value(1).toString());
    query.exec("SELECT * FROM AdminLogin");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();

    }else{
        qDebug()<< "Database connection:Error";
    }

}

Admin_Login::~Admin_Login()
{
    delete ui;
    db.close();
}

void Admin_Login::on_loginCao_clicked()

{
    query.exec("SELECT * FROM AdminLogin");
    query.first();
    //query.bindValue(":Id",query.value(0));

    //qDebug() <<" ID is :" << query.value(0).toInt() << query.value(1).toString();
    QString password = query.value(2).toString();
    QString username = query.value(1).toString();
    QString user = ui->cao_username->text();
    QString pass = ui ->cao_password ->text();
    int num_rows;
    if(!query.exec("SELECT count(Id) as num_rows FROM AdminLogin")) qDebug() << query.lastError().text();
    query.first();
    num_rows = query.value(0).toInt();
    qDebug() <<"number: " << num_rows;
    QMessageBox msgBox;
    QString error= "Error!! Password Incorrect!!!" ;
    if(num_rows != 1) //If number of users in datbase is greater than 1 then error
    {
        msgBox.setText("Some files are corrupted .Please Try reinstalling the software");
        msgBox.exec();
    }
    else
    {
        if(user == decrypt(username) && pass == decrypt(password)) //Validate if user and pass are correct
        {
            //qDebug() << "test";
            hide();
            cp = new Cao_panel;
            cp -> showMaximized();
        }
        else
        {


            msgBox.setText(error);
            msgBox.exec();


        }
    }
}

QString Admin_Login::decrypt(QString encrypted)
{
    //Decryption
    std::reverse(encrypted.begin(),encrypted.end());

    QString decrypted = encrypted;

    int size_original = encrypted.size();
    int i = 0;
    while(size_original--)
    {



        decrypted[i] =  encrypted[i].unicode() - size_original - 1;


        i++;

    }
    return decrypted;

}
