#include "setfirstpassword.h"
#include "ui_setfirstpassword.h"
#include<QRegExpValidator>
#include <QMessageBox>
QString adminUser,adminPass;

Setfirstpassword::Setfirstpassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setfirstpassword)
{
    ui->setupUi(this);

    //Database Connection

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    query = QSqlQuery(db);
    query.exec("SELECT * FROM AdminLogin");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();

    }else{
        qDebug()<< "Database connection:Error";
    }
    newrecord = false;
    adminUser = ui->username->text();
    adminPass = ui->password->text();

}



Setfirstpassword::~Setfirstpassword()
{
    delete ui;
    db.close();
}
QString Setfirstpassword::encrypt(QString input)
{

    QString encrypted = input;

    int size_original = input.size();
    int i = 0;
    while(size_original--)
    {
        encrypted[i] =  input[i].unicode() + size_original + 1;
        i++;
    }
    std::reverse(encrypted.begin(),encrypted.end());
    return  encrypted;

}

void Setfirstpassword::on_loginButon_clicked()
{

    if (ui->username->text().trimmed() == ""){
        ui->statusbar->showMessage("Username is Compulsory!");
    }else{





        //Inserting Login Information
        adminUser = ui->username->text();
        adminPass = ui->password->text();
        QString adminre = ui ->reenterPassword->text();
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
        qDebug() << user[0] << user[1];
        int CAO = user[0];
        int staff = user[1];




        if(!CAO && staff)
        {

            qDebug() << "Open Staff";
            QMessageBox msgBox;
            if(adminPass == adminre) //Check if password in database and user typed password are same
            {
                QSqlQuery updateQuery = QSqlQuery(db);
                updateQuery.prepare("INSERT INTO Stafflogin (Username,"

                                    "Password) "

                                    "VALUES (:Username,"

                                    ":Password) " );
                // QString encrypted_pass = encrypt(adminPass);
                updateQuery.bindValue(":Id", query.value(0));
                updateQuery.bindValue(":Username", encrypt(ui->username->text()));
                updateQuery.bindValue(":Password", encrypt(adminPass));




                if(!updateQuery.exec())
                    ui->statusbar->showMessage(QString("Error While Inserting[Please Try again] ") + updateQuery.lastError().text());
                else
                {
                    ui->statusbar->showMessage("Successfully Inserted");
                    hide();
                   slogin = new  staff_login ;
                   slogin ->show();
                }
            }
            else
            {
                msgBox.setText("Password Not Matched. Retype the password");
                msgBox.exec();
            }

        }
        else if(CAO && !staff)
        {
            //OPen admin
            QMessageBox msgBox;
            if(adminPass == adminre) //Check if password in database and user typed password are same
            {
                QSqlQuery updateQuery = QSqlQuery(db);
                updateQuery.prepare("INSERT INTO AdminLogin (Username,"

                                    "Password) "

                                    "VALUES (:Username,"

                                    ":Password) " );
                //QString encrypted_pass = encrypt(adminPass);
                updateQuery.bindValue(":Id", query.value(0));
                updateQuery.bindValue(":Username", encrypt(ui->username->text()));
                updateQuery.bindValue(":Password", encrypt(adminPass));




                if(!updateQuery.exec())
                    ui->statusbar->showMessage(QString("Error While Inserting[Please Try again] ") + updateQuery.lastError().text());
                else
                {
                    ui->statusbar->showMessage("Successfully Inserted");
                    hide();
            alogin = new    Admin_Login ;
            alogin -> show();
                }
            }
            else
            {
                msgBox.setText("Password Not Matched. Retype the password");
                msgBox.exec();
            }
        }



    }







}







