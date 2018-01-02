#include "viewstdrecord.h"
#include "ui_viewstdrecord.h"
#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
#include "viewstdtable.h"
#include "staffpanel.h"
//QString filename;
int database_id;
viewstdrecord::viewstdrecord(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewstdrecord)
{
    ui->setupUi(this);
    //Database Connection

   // qDebug() << "Arko wala:" << database_id;


    QString sid = QString::number(database_id); //converting int to string
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    if(database_id != 0)
    {
        query = QSqlQuery(db);
        query.exec("SELECT * FROM Student WHERE Id = '"+sid+"'");

        if (query.isActive()){
            qDebug()<<"Connection Successful";
            query.first();
            FillForm();
        }else{
            qDebug()<< "Database connection:Error";
        }

        newrecord =false;
    }
    else
    {
        query = QSqlQuery(db);
        query.exec("SELECT * FROM Student");

        if (query.isActive()){
            qDebug()<<"Connection Successful";
            query.first();
            FillForm();
        }else{
            qDebug()<< "Database connection:Error";
        }

        newrecord =false;
    }
}

QString viewstdrecord::decrypt(QString encrypted)
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

void viewstdrecord::FillForm()
{
    //Student General Information

    ui->student_frstname->setText(decrypt(query.value(1).toString()));
    ui->student_frstname->setEnabled(false);
    ui->Student_midname->setText(decrypt(query.value(2).toString()));
    ui->Student_midname->setEnabled(false);
    ui->Student_lastname->setText(decrypt(query.value(3).toString()));
    ui->Student_lastname->setEnabled(false);
    ui->Student_Course->setText(decrypt(query.value(7).toString()));
    ui->Student_Course->setEnabled(false);
    ui->Student_Description->setText(decrypt(query.value(8).toString()));
    ui->Student_Description->setEnabled(false);
    ui->Student_email->setText(decrypt(query.value(6).toString()));
    ui->Student_email->setEnabled(false);
    ui->Student_enrolledeyear->setText(decrypt(query.value(9).toString()));
    ui->Student_enrolledeyear->setEnabled(false);
    ui->Student_phone->setText(decrypt(query.value(19).toString()));
    ui->Student_phone->setEnabled(false);
    ui->registration->setText(decrypt(query.value(22).toString()));
    ui -> registration -> setEnabled(false);

    //To check Sex
    int sex = query.value(21).toInt(); //sex column is in 21
    switch(sex) // 1 is for male,2 for female and 3 for others
    {
    case 1:
        //male
        //qDebug() << "MAle";
        ui->Stu_male->setChecked(true);
        break;
    case 2:
        //female
        //qDebug() << "female";
        ui->Stu_female->setChecked(true);
        break;
    case 3:
        //Others
        qDebug() << "Others";
        ui->Stu_others->setChecked(true);
        break;
    default:
        qDebug() << "Not in DB";
    }








    //Family BackGround
    //Father's Information

    ui->Student_fathername->setText(decrypt(query.value(10).toString()));
    ui->Student_fathername->setEnabled(false);
    ui->Student_fatherphone->setText(decrypt(query.value(11).toString()));
    ui->Student_fatherphone->setEnabled(false);
    ui->Student_FatherOccupation->setText(decrypt(query.value(12).toString()));
    ui->Student_FatherOccupation->setEnabled(false);
    //Guardian's Information

    ui->Student_GuardianName->setText(decrypt(query.value(16).toString()));
    ui->Student_GuardianName->setEnabled(false);
    ui->Student_guardianphone->setText(decrypt(query.value(17).toString()));
    ui->Student_guardianphone->setEnabled(false);
    ui->Student_guardianoccupation->setText(decrypt(query.value(18).toString()));
    ui->Student_guardianoccupation->setEnabled(false);
    //Mother's Information

    ui->Student_Mothername->setText(decrypt(query.value(13).toString()));
    ui->Student_Mothername->setEnabled(false);
    ui->Student_MotherPhone->setText(decrypt(query.value(14).toString()));
    ui->Student_MotherPhone->setEnabled(false);
    ui->Student_motheroccupation->setText(decrypt(query.value(15).toString()));
    ui->Student_motheroccupation->setEnabled(false);
    //Student's Address

    ui->Student_permanentAdd->setText(decrypt(query.value(4).toString()));
    ui->Student_permanentAdd->setEnabled(false);
    ui->Student_TemporaryAdd->setText(decrypt(query.value(5).toString()));
    ui->Student_TemporaryAdd->setEnabled(false);

    //Loading image of student
    QString filename = query.value(20).toString(); ///Path of the image
    //  qDebug() << filename;
    QImage photo;
    bool valid = photo.load(filename);
    if(valid)
    {

        photo = photo.scaledToWidth(ui->Student_photo->width(), Qt::SmoothTransformation);
        ui->Student_photo->setPixmap(QPixmap::fromImage(photo));

    }
    v_registration_num =decrypt(query.value(22).toString());
}
viewstdrecord::~viewstdrecord()
{
    delete ui;
    db.close();
}


void viewstdrecord::on_Next_clicked()
{

    if(!query.next())
        query.first();
    FillForm();
}

void viewstdrecord::on_Previous_clicked()
{
    if (!query.previous())
        query.last();
    FillForm();
}

void viewstdrecord::on_Back_clicked()
{

    hide();
    QWidget *panel = new StaffPanel;
    panel-> show();

}
QString viewstdrecord::encrypt(QString input)
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


void viewstdrecord::on_Search_clicked()
{
    //Take keyword from search box and value from sort by
    //searchbox = "something"
    //firstname, lastname, GPA, email
    //if(sortBy==firstname)--> Call sortbyFirstName
    //if(if(sortBy==lastname)--> Call sortbyLastName
    //searchBox,sortBy
    QString keyword = ui->searchBox->text();
    qDebug() << keyword;
    QString sortValue =  ui->sortBy->currentText();
    qDebug() << sortValue;
    //keyword = QString::toupper(keyword);
    keyword =keyword.toUpper();
    keyword = encrypt(keyword);
    query = QSqlQuery(db);
    if(keyword.size() == 0)
    {
        if(!query.exec("SELECT * FROM Student ORDER BY Id")) qDebug() << query.lastError().text();
        query.first();
        FillForm();
    }
    else
    {
        if (sortValue == "firstname" )
        {

            int num_rows;


            //get the number of rows
            if(!query.exec("SELECT count(Id) as num_rows FROM Student WHERE upper(Firstname) = '"+keyword+"'")) qDebug() << query.lastError().text();
            //query.first();
            query.first();
            num_rows = query.value(0).toInt();


            QMessageBox msgBox;
            QString text= "Number of records found is:" + QString::number(num_rows);

            msgBox.setText(text);
            msgBox.exec();

            if(!query.exec("SELECT * FROM Student WHERE upper(Firstname) = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
            query.first();
            FillForm();


        }
        else if(sortValue == "course")
        {
            int num_rows;


            //get the number of rows
            if(!query.exec("SELECT count(Id) as num_rows FROM Student WHERE upper(Course) = '"+keyword+"'")) qDebug() << query.lastError().text();
            //query.first();
            query.first();
            num_rows = query.value(0).toInt();


            QMessageBox msgBox;
            QString text= "Number of records found is:" + QString::number(num_rows);

            msgBox.setText(text);
            msgBox.exec();


            if(!query.exec("SELECT * FROM Student WHERE upper(Course) = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
            query.first();
            FillForm();
        }
        else if(sortValue == "registration_number")
        {
            int num_rows;


            //get the number of rows
            if(!query.exec("SELECT count(Id) as num_rows FROM Student WHERE Registration = '"+keyword+"'")) qDebug() << query.lastError().text();
            //query.first();
            query.first();
            num_rows = query.value(0).toInt();


            QMessageBox msgBox;
            QString text= "Number of records found is:" + QString::number(num_rows);

            msgBox.setText(text);
            msgBox.exec();


            if(!query.exec("SELECT * FROM Student WHERE Registration = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
            query.first();
            FillForm();
        }
        else if(sortValue == "enrolledYear")
        {
            int num_rows;


            //get the number of rows
            if(!query.exec("SELECT count(Id) as num_rows FROM Student WHERE upper(EnrolledYear) = '"+keyword+"'")) qDebug() << query.lastError().text();
            //query.first();
            query.first();
            num_rows = query.value(0).toInt();


            QMessageBox msgBox;
            QString text= "Number of records found is:" + QString::number(num_rows);

            msgBox.setText(text);
            msgBox.exec();


            if(!query.exec("SELECT * FROM Student WHERE upper(EnrolledYear) = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
            query.first();
            FillForm();
        }
        else if(sortValue == "email")
        {
            int num_rows;


            //get the number of rows
            if(!query.exec("SELECT count(Id) as num_rows FROM Student WHERE upper(Email) = '"+keyword+"'")) qDebug() << query.lastError().text();
            //query.first();
            query.first();
            num_rows = query.value(0).toInt();


            QMessageBox msgBox;
            QString text= "Number of records found is:" + QString::number(num_rows);

            msgBox.setText(text);
            msgBox.exec();

            if(!query.exec("SELECT * FROM Student WHERE upper(Email) = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
            query.first();
            FillForm();
        }
        else if(sortValue == "GPA")
        {


        }



    }
}




void viewstdrecord::on_showresult_clicked()
{

    view = new  viewresult;
    view -> show();
}
