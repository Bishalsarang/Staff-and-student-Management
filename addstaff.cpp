#include "addstaff.h"
#include "ui_addstaff.h"
#include<QRegExpValidator>
#include "cao_panel.h"


#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>

QString staff_filename;

addStaff::addStaff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addStaff)
{
    ui->setupUi(this);


    /*Validator::Ayush Malla

    QRegExp rxSfrstname(SFRSTNAME_RX);
    QRegExp rxSmidname(SMIDNAME_RX);
    QRegExp rxSlastname(SLASTNAME_RX);
    QRegExp rxSpaddress(SPADDRESS_RX);
    QRegExp rxStaddress(STADDRESS_RX);
    QRegExp rxSphone(SPHONE_RX);
    QRegExp rxSemail(SEMAIL_RX);
    QRegExp rxSsalary(SSALARY_RX);
    QRegExp rxSpostion(SPOSTION_RX);

    QRegExp rxQualification1(QUALIFICATION1_RX);
    QRegExp rxQualification2(QUALIFICATION2_RX);
    QRegExp rxQualification3(QUALIFICATION3_RX);
    QRegExp rxQualification4(QUALIFICATION4_RX);
    QRegExp rxQualification5(QUALIFICATION5_RX);
    QRegExpValidator *Vsfn = new QRegExpValidator(rxSfrstname,this);
        ui->Sfrstname->setValidator(Vsfn);
    QRegExpValidator *Vsmn=new QRegExpValidator(rxSmidname,this);
        ui->Smidname->setValidator(Vsmn);
    QRegExpValidator *Vsln=new QRegExpValidator(rxSlastname,this);
        ui->Slastname->setValidator(Vsln);
    QRegExpValidator *Vspa=new QRegExpValidator(rxSpaddress);
        ui->Spaddress->setValidator(Vspa);
    QRegExpValidator *Vsta =new QRegExpValidator(rxStaddress);
        ui->Staddress->setValidator(Vsta);
    QRegExpValidator *Vsp=new QRegExpValidator(rxSphone);
        ui->Sphone->setValidator(Vsp);
    QRegExpValidator *Vse=new QRegExpValidator(rxSemail);
        ui->Semail->setValidator(Vse);
    QRegExpValidator *Vss=new QRegExpValidator(rxSsalary);
        ui->Ssalary->setValidator(Vss);
    QRegExpValidator *Vspo=new QRegExpValidator(rxSpostion);
        ui->Sposition->setValidator(Vspo);

    QRegExpValidator *Vq1=new QRegExpValidator(rxQualification1);
        ui->Qualification1->setValidator(Vq1);
    QRegExpValidator *Vq2=new QRegExpValidator(rxQualification2);
        ui->Qualification2->setValidator(Vq2);
    QRegExpValidator *Vq3=new QRegExpValidator(rxQualification3);
        ui->Qualification3->setValidator(Vq3);
    QRegExpValidator *Vq4=new QRegExpValidator(rxQualification4);
        ui->Qualification4->setValidator(Vq4);
    QRegExpValidator *Vq5=new QRegExpValidator(rxQualification5);
        ui->Qualification5->setValidator(Vq5);


        */



    staff_filename =":/img/na.jpg";

    //Database Connection

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    query = QSqlQuery(db);
    query.exec("SELECT * FROM Staff");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();

    }else{
        qDebug()<< "Database connection:Error";
    }






}



QString addStaff::encrypt(QString input)
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



addStaff::~addStaff()
{
    delete ui;
    db.close();
}


void addStaff::on_sFormSubmit_clicked()
{
    //Inserting,Updating and Deleting Records of the Staffs


    if (ui->Sfrstname->text().trimmed() == ""){
        ui->statusbar->showMessage("Staff Name is Compulsory!");
    }else{

        QSqlQuery updateQuery = QSqlQuery(db);
        updateQuery.prepare("INSERT INTO Staff (Firstname, Middlename, Lastname,"
                            "PermanentAdd,TemporaryAdd,"
                            "Email,Position,Salary,Description,"
                            "StaffPhone,"
                            "Qualification1,Qualification2,Qualification3,Qualification4,Qualification5,image,sex) "

                            "VALUES (:Firstname, :Middlename, :Lastname,"
                            ":PermanentAdd,:TemporaryAdd,"
                            ":Email,:Position,:Salary,:Description,"
                            ":StaffPhone,"
                            ":Qualification1,:Qualification2,:Qualification3,:Qualification4,:Qualification5,:image,:sex) ");




        //Updating Staff Information after entering it manually
        //Inserting Staff Information


        updateQuery.bindValue(":Id", query.value(0));
        updateQuery.bindValue(":Firstname", encrypt(ui->Sfrstname->text()));
        updateQuery.bindValue(":Middlename", encrypt(ui->Smidname->text()));
        updateQuery.bindValue(":Lastname", encrypt(ui->Slastname->text()));
        updateQuery.bindValue(":PermanentAdd", encrypt(ui->Spaddress->text()));
        updateQuery.bindValue(":TemporaryAdd",encrypt(ui->Staddress->text()));
        updateQuery.bindValue(":Email", encrypt(ui->Semail->text()));
        updateQuery.bindValue(":Position", encrypt(ui->Sposition->text()));
        updateQuery.bindValue(":Description", encrypt(ui->StaffDescription->toPlainText()));
        updateQuery.bindValue(":Salary", encrypt(ui->Ssalary->text()));
        updateQuery.bindValue(":StaffPhone", encrypt(ui->Sphone->text()));
        updateQuery.bindValue(":image", staff_filename);

        updateQuery.bindValue(":Qualification1", encrypt(ui->Qualification1->text()));
        updateQuery.bindValue(":Qualification2", encrypt(ui->Qualification2->text()));
        updateQuery.bindValue(":Qualification3", encrypt(ui->Qualification3->text()));
        updateQuery.bindValue(":Qualification4", encrypt(ui->Qualification4->text()));
        updateQuery.bindValue(":Qualification5", encrypt(ui->Qualification5->text()));

        if (ui->sFemale->isChecked())
        {
            updateQuery.bindValue(":sex",2);
        }
        else if(ui->sMale->isChecked())
        {
            updateQuery.bindValue(":sex",1);

        }
        else
        {
            updateQuery.bindValue(":sex",3);
        }




        //Error Message
        QMessageBox msgBox;
        if(!updateQuery.exec())
        {
            msgBox.setText("Failed to Add.Please Try Again!!!");
            msgBox.exec();
        }
        else
        {
            msgBox.setText("Successfully Added");
            msgBox.exec();
        }

        query.exec("SELECT * FROM Staff");
        query.next();
        query.last();


    }
}


void addStaff::on_chooseImage_clicked()
{
    // qDebug() << filename;
    staff_filename = QFileDialog::getOpenFileName(this,tr("Choose Image"),"",tr("Images(*.png *.jpg *.jpeg)"));
    if (QString::compare(staff_filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(staff_filename);
        if(valid)
        {
            image = image.scaledToWidth(ui->pic->width(), Qt::SmoothTransformation);
            ui->pic->setPixmap(QPixmap::fromImage(image));

        }

    }
}

void addStaff::on_addmore_clicked()
{
    ui->Qualification1->clear();
    ui->Qualification2->clear();
    ui->Qualification3->clear();
    ui->Qualification4->clear();
    ui->Qualification5->clear();
    ui->Semail->clear();
    ui->Sfrstname->clear();
    ui->Slastname->clear();
    ui->Smidname->clear();
    ui->Spaddress->clear();
    ui->Sphone->clear();
    ui->Sposition->clear();
    ui->Ssalary->clear();
    ui->Staddress->clear();
    ui->StaffDescription->clear();
    staff_filename = ":/img/na.jpg";
    ui->pic->setPixmap(QPixmap(":/img/na.jpg") );
}

void addStaff::on_back_clicked()
{
    hide();
    QWidget *backToCao = new Cao_panel;
    backToCao-> showMaximized();
}
