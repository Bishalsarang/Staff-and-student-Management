#include "changepassword.h"
#include "ui_changepassword.h"
#include <QRegExpValidator>
#include <QString>
#include <QMessageBox>
#include "staffpanel.h"
#include "cao_panel.h"
#define OLDPASSWORD_RX "^((?=.*\\d)(?=.*[a-zA-Z])[a-zA-Z0-9!@#$%&*]{6,20})$"
#define NEWPASSWORD_RX "^((?=.*\\d)(?=.*[a-zA-Z])[a-zA-Z0-9!@#$%&*]{6,20})$"
#define CONFIRMPASSWORD_RX "^((?=.*\\d)(?=.*[a-zA-Z])[a-zA-Z0-9!@#$%&*]{6,20})$"



changepassword::changepassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::changepassword)
{
    ui->setupUi(this);
}

changepassword::~changepassword()
{
    delete ui;
}

void changepassword::on_ChangePassword_clicked()
{
    QString old_pass = ui->oldpassword->text();
    QString new_pass = ui ->newpassword -> text();
    QString confirm_pass = ui ->confirmpassword -> text();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    QSqlQuery query;
    query.exec("SELECT * FROM users");


    int user[2];
    QString inst[2]; //array to store accesibility of users
    int i = 0;
    while(query.next())
    {
        QString   test = query.value(1).toString();
        user[i] = query.value(2).toInt();
        inst[i] = query.value(3).toString();
        qDebug() << test;
        i++;
    }
    qDebug() << user[0] << user[1];
    int CAO = user[0];
    int staff = user[1];
    QMessageBox msgBox;
    if(CAO == 0 && staff == 1) //If current configuration is Staff
    {
        qDebug() << "Staff here";
        query.exec("SELECT * FROM Stafflogin ");
        query.first();
        QString password = query.value(2).toString();
        if(decrypt(password) == old_pass) //Check if password in database and user typed password are same
        {
            if(new_pass == confirm_pass)
            {
                new_pass = encrypt(new_pass);
                query.exec("UPDATE Stafflogin SET Password = '"+new_pass+"'");
                query.first();
                msgBox.setText("Password Updated Successfully");
                msgBox.exec();
                hide();
                QWidget *panel = new StaffPanel;
                panel -> show();

            }
            else
            {
                msgBox.setText("Password Not Matched. Retype the password");
                msgBox.exec();
            }

        }
        else
        {
            msgBox.setText("OLd Password Incorrect");
            msgBox.exec();
        }


    }
    if(CAO == 1 && staff == 0)
    {
        qDebug() << "Staff here";
        query.exec("SELECT * FROM AdminLogin ");
        query.first();
        QString password = query.value(2).toString();
        if(decrypt(password) == old_pass) //Check if password in database and user typed password are same
        {
            if(new_pass == confirm_pass)
            {
                new_pass = encrypt(new_pass);
                query.exec("UPDATE AdminLogin SET Password = '"+new_pass+"'");
                query.first();
                msgBox.setText("Password Updated Successfully");
                msgBox.exec();
                hide();


            }
            else
            {
                msgBox.setText("Password Not Matched. Retype the password");
                msgBox.exec();
            }

        }
        else
        {
            msgBox.setText("OLd Password Incorrect");
            msgBox.exec();
        }





    }
}
QString changepassword::decrypt(QString encrypted)
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
QString changepassword::encrypt(QString input)
{

    QString encrypted = input;

    int size_original = input.size();
    int i = 0;
    while(size_original--)
    {

        //   QChar a = input[0] + 'a';
        //qDebug() << encrypted[i];
        //qDebug() << input.replace(i,1,"a");

        encrypted[i] =  input[i].unicode() + size_original + 1;


        i++;
    }
    std::reverse(encrypted.begin(),encrypted.end());
    return  encrypted;

}
