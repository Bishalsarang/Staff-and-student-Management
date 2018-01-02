#include "staff_login.h"
#include "ui_staff_login.h"
#include"QRegExpValidator"
#include <QSplashScreen>
#include <QMessageBox>

/*#define STAFF_USERNAME_RX "/^[a-zA-Z0-9]+([a-zA-Z0-9](_|-| )[a-zA-Z0-9])*[a-zA-Z0-9]+$/"
#define STAFF_PASSWORD_RX "^((?=.*\\d)(?=.*[a-zA-Z])[a-zA-Z0-9!@#$%&*]{6,20})$"
*/
staff_login::staff_login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::staff_login)
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
    query.exec("SELECT * FROM Stafflogin");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();

    }else{
        qDebug()<< "Database connection:Error";
    }
    /*QRegExp rxstaff_username(STAFF_USERNAME_RX);
    //QRegExp rxstaff_password(STAFF_PASSWORD_RX);
   // QRegExpValidator *valiSusername = new QRegExpValidator(rxstaff_username,this);
        ui->staff_username->setValidator(valiSusername);
        QRegExpValidator *valiSuserpass = new QRegExpValidator(rxstaff_password,this);
            ui->staff_password->setValidator(valiSuserpass);
            */
}
QString staff_login::encrypt(QString input)
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
QString staff_login::decrypt(QString encrypted)
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

staff_login::~staff_login()
{
    delete ui;
}

void staff_login::on_loginStaff_clicked()
{

    query.exec("SELECT * FROM Stafflogin");
    query.first();
    //query.bindValue(":Id",query.value(0));

    //qDebug() <<" ID is :" << query.value(0).toInt() << query.value(1).toString();
    QString password = query.value(2).toString();
    QString username = query.value(1).toString();
    QString user = ui->staff_username->text();
    QString pass = ui ->staff_password ->text();
    int num_rows;
    if(!query.exec("SELECT count(Id) as num_rows FROM Stafflogin")) qDebug() << query.lastError().text();
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
        if(user == decrypt(username) && pass == decrypt(password))
        {
            //qDebug() << "test";
            hide();
            spanel = new StaffPanel;
            spanel -> showMaximized();
        }
        else
        {
            QMessageBox msgBox;
            QString text= "Error!! Password Incorrect!!!" ;

            msgBox.setText(text);
            msgBox.exec();


        }
    }
}





