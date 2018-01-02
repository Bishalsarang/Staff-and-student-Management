#include "modifystudent.h"
#include "ui_modifystudent.h"
#include "staffpanel.h"
#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
QString std_filename;
modifyStudent::modifyStudent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modifyStudent)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"


    query = QSqlQuery(db);
    query.exec("SELECT * FROM Student");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();
        FillForm();
    }else{
        qDebug()<< "Database connection:Error";
    }


}
QString modifyStudent::decrypt(QString encrypted)
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
QString modifyStudent::encrypt(QString input)
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

void modifyStudent::FillForm()
{
    //Student General Information

    ui->student_frstname->setText(decrypt(query.value(1).toString()));
    ui->registration->setText(decrypt(query.value(22).toString()));

    ui->Student_midname->setText(decrypt(query.value(2).toString()));

    ui->Student_lastname->setText(decrypt(query.value(3).toString()));

    ui->Student_Course->setText(decrypt(query.value(7).toString()));

    ui->Student_Description->setText(decrypt(query.value(8).toString()));

    ui->Student_email->setText(decrypt(query.value(6).toString()));

    ui->Student_enrolledeyear->setText(decrypt(query.value(9).toString()));

    ui->Student_phone->setText(decrypt(query.value(19).toString()));


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

    ui->Student_fatherphone->setText(decrypt(query.value(11).toString()));

    ui->Student_FatherOccupation->setText(decrypt(query.value(12).toString()));

    //Guardian's Information

    ui->Student_GuardianName->setText(decrypt(query.value(16).toString()));

    ui->Student_guardianphone->setText(decrypt(query.value(17).toString()));

    ui->Student_guardianoccupation->setText(decrypt(query.value(18).toString()));

    //Mother's Information

    ui->Student_Mothername->setText(decrypt(query.value(13).toString()));

    ui->Student_MotherPhone->setText(decrypt(query.value(14).toString()));

    ui->Student_motheroccupation->setText(decrypt(query.value(15).toString()));

    //Student's Address

    ui->Student_permanentAdd->setText(decrypt(query.value(4).toString()));

    ui->Student_TemporaryAdd->setText(decrypt(query.value(5).toString()));


    //Loading image of student
    QString std_filename = query.value(20).toString(); ///Path of the image
    //  qDebug() << std_filename;
    QImage photo;
    bool valid = photo.load(std_filename);
    if(valid)
    {

        photo = photo.scaledToWidth(ui->Student_photo->width(), Qt::SmoothTransformation);
        ui->Student_photo->setPixmap(QPixmap::fromImage(photo));

    }
}
modifyStudent::~modifyStudent()
{
    delete ui;
    db.close();
}

void modifyStudent::on_modify_clicked()
{
    if (ui->student_frstname->text().trimmed() == ""){
        ui->statusbar->showMessage("Student Name is Compulsory!");
    }else{

        QSqlQuery updateQuery = QSqlQuery(db);
        updateQuery.prepare("UPDATE Student SET Firstname = :Firstname, Middlename = :Middlename, Lastname = :Lastname, PermanentAdd = :PermanentAdd,"
                            " TemporaryAdd = :TemporaryAdd, Email = :Email, Course = :Course,"
                            " Description = :Description, EnrolledYear = :EnrolledYear,"
                            " Fathername = :Fathername, FatherPhone = :FatherPhone, FatherOccu = :FatherOccu,"
                            " Mothername = :Mothername, MotherPhone = :MotherPhone, MotherOccu = :MotherOccu,"
                            " Guardianname = :Guardianname, GuardianPhone = :GuardianPhone, GuardianOccu = :GuardianOccu,"
                            " StudentPhone = :StudentPhone, sex = :sex, image = :image, Registration = :Registration "
                            " WHERE Id = :Id");

        updateQuery.bindValue(":Id", query.value(0));
        updateQuery.bindValue(":Firstname", encrypt(ui->student_frstname->text()));
        updateQuery.bindValue(":Middlename", encrypt(ui->Student_midname->text()));
        updateQuery.bindValue(":Lastname", encrypt(ui->Student_lastname->text()));
        updateQuery.bindValue(":PermanentAdd", encrypt(ui->Student_permanentAdd->text()));
        updateQuery.bindValue(":TemporaryAdd", encrypt(ui->Student_TemporaryAdd->text()));
        updateQuery.bindValue(":Email", encrypt(encrypt(ui->Student_email->text())));
        updateQuery.bindValue(":Course", encrypt(encrypt(ui->Student_Course->text())));
        updateQuery.bindValue(":Description", encrypt(ui->Student_Description->toPlainText()));
        updateQuery.bindValue(":EnrolledYear", encrypt(ui->Student_enrolledeyear->text()));
        updateQuery.bindValue(":Fathername", encrypt(ui->Student_fathername->text()));
        updateQuery.bindValue(":FatherPhone", encrypt(ui->Student_fatherphone->text()));
        updateQuery.bindValue(":FatherOccu",encrypt(ui->Student_FatherOccupation->text()));
        updateQuery.bindValue(":Mothername", encrypt(ui->Student_Mothername->text()));
        updateQuery.bindValue(":MotherPhone", encrypt(ui->Student_MotherPhone->text()));
        updateQuery.bindValue(":MotherOccu", encrypt(ui->Student_motheroccupation->text()));
        updateQuery.bindValue(":Guardianname", encrypt(ui->Student_GuardianName->text()));
        // updateQuery.bindValue(":Guardianname",std_filename);
        updateQuery.bindValue(":GuardianPhone", encrypt(ui->Student_guardianphone->text()));
        updateQuery.bindValue(":GuardianOccu", encrypt(ui->Student_guardianoccupation->text()));
        updateQuery.bindValue(":StudentPhone", encrypt(ui->Student_phone->text()));
        updateQuery.bindValue(":Registration", encrypt(ui->registration->text()));
        updateQuery.bindValue(":image",std_filename);

        if (ui->Stu_female->isChecked())
        {
            updateQuery.bindValue(":sex",2);
        }
        else if(ui->Stu_male->isChecked())
        {
            updateQuery.bindValue(":sex",1);

        }
        else
        {
            updateQuery.bindValue(":sex",3);
        }

        //qDebug() << std_filename;

        if(!updateQuery.exec())
            ui->statusbar->showMessage(QString("Error while Updating[Please Try again later]") + updateQuery.lastError().text());
        else
            ui->statusbar->showMessage("Successfully Updated");

        if(sortValue == "firstname" )
        {
            if(!query.exec("SELECT * FROM Student WHERE upper(Firstname) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();

        }
        else if (sortValue == "lastname")
        {
            if(!query.exec("SELECT * FROM Student WHERE upper(Course) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();
        }
        else if(sortValue == "email")
        {
            if(!query.exec("SELECT * FROM Student WHERE upper(Email) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();
        }

        else if(sortValue == "enrolledYear")
        {
            if(!query.exec("SELECT * FROM Student WHERE upper(EnrolledYear) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();
        }

        query.first();
        // while (query.value(0).toInt() != currentPid) query.next();
        FillForm();

    }
}

void modifyStudent::on_choose_clicked()
{
    QFileDialog::getOpenFileName(this,tr("CHoose"),"",tr("Images(*.png *.jpg *.jpeg)"));
    if (QString::compare(std_filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(std_filename);
        if(valid)
        {
            image = image.scaledToWidth(ui->Student_photo->width(), Qt::SmoothTransformation);
            ui->Student_photo->setPixmap(QPixmap::fromImage(image));

        }

    }
}

void modifyStudent::on_Next_clicked()
{
    if(!query.next())
        query.first();
    FillForm();
}

void modifyStudent::on_Previous_clicked()
{
    if (!query.previous())
        query.last();
    FillForm();
}

void modifyStudent::on_Search_clicked()
{
    //Take keyword from search box and value from sort by
    //searchbox = "something"
    //firstname, lastname, GPA, email
    //if(sortBy==firstname)--> Call sortbyFirstName
    //if(if(sortBy==lastname)--> Call sortbyLastName
    //searchBox,sortBy
    keyword = ui->searchBox->text(); //content of srach linr edit
    qDebug() << keyword;
    sortValue =  ui->sortBy->currentText(); //combo box bata linxa
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
        else if(sortValue == "GPA")
        {


        }
    }
}

void modifyStudent::on_Back_clicked()
{

    hide();
    QWidget *panel = new StaffPanel;
    panel -> show();
}
