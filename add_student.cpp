#include "add_student.h"
#include "ui_add_student.h"
#include<QRegExpValidator>
#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include "staffpanel.h"
#include <QMessageBox>
QString filename;


add_Student::add_Student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::add_Student)
{
    ui->setupUi(this);
    QString registration_num;

    registration_num = "hwllo";
    qDebug() << registration_num ;

    filename =":/img/na.jpg";

    //Database Connection

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    query = QSqlQuery(db);
    query.exec("SELECT * FROM Student");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();

    }else{
        qDebug()<< "Database connection:Error";
    }
}

QString add_Student::encrypt(QString input)
{

    QString encrypted = input;

    int size_original = input.size();
    int i = 0;
    while(size_original--)
    {


        encrypted[i] =  input[i].unicode() + size_original + 1;


        i++;
    }
    std::reverse(encrypted.begin(),encrypted.end());//function standard
    return  encrypted;

}


add_Student::~add_Student()
{
    delete ui;
    db.close();
}


void add_Student::on_Student_submit_clicked()
{
    //Inserting Records of the students
    if (ui->student_frstname->text().size() == 0|| (ui->registrationNumber->text()).size() == 0){
        ui->statusbar->showMessage("Student Name and Registration are Compulsory");
    }
    else{
        QSqlQuery updateQuery = QSqlQuery(db);
        updateQuery.prepare("INSERT INTO Student (Firstname, Middlename, Lastname,"
                            "PermanentAdd,TemporaryAdd,"
                            "Email,Course,Description,EnrolledYear,"
                            "Fathername,FatherPhone,FatherOccu,"
                            "Mothername,MotherPhone,MotherOccu,"
                            "Guardianname,GuardianPhone,GuardianOccu,"
                            "StudentPhone,"
                            "sex,Registration,"
                            "image) "

                            "VALUES (:Firstname, :Middlename, :Lastname,"
                            ":PermanentAdd,:TemporaryAdd,"
                            ":Email,:Course,:Description,:EnrolledYear,"
                            ":Fathername,:FatherPhone,:FatherOccu,"
                            ":Mothername,:MotherPhone,:MotherOccu,"
                            ":Guardianname,:GuardianPhone,:GuardianOccu,"
                            ":StudentPhone,"
                            ":sex,:Registration,"
                            ":image) ");

        //Inserting Student Information

        updateQuery.bindValue(":Id", query.value(0));
        updateQuery.bindValue(":Firstname", encrypt(ui->student_frstname->text()));
        updateQuery.bindValue(":Middlename", encrypt(ui->Student_midname->text()));
        updateQuery.bindValue(":Lastname", encrypt(ui->Student_lastname->text()));
        updateQuery.bindValue(":PermanentAdd",encrypt( ui->Student_permanentAdd->text()));
        updateQuery.bindValue(":TemporaryAdd", encrypt(ui->Student_TemporaryAdd->text()));
        updateQuery.bindValue(":Email", encrypt(ui->Student_email->text()));
        updateQuery.bindValue(":Course", encrypt(ui->Student_Course->text()));
        updateQuery.bindValue(":Description", encrypt(ui->Student_Description->toPlainText()));
        updateQuery.bindValue(":EnrolledYear", encrypt(ui->Student_enrolledeyear->text()));
        updateQuery.bindValue(":Fathername", encrypt(ui->Student_fathername->text()));
        updateQuery.bindValue(":FatherPhone", encrypt(ui->Student_fatherphone->text()));
        updateQuery.bindValue(":FatherOccu", encrypt(ui->Student_FatherOccupation->text()));
        updateQuery.bindValue(":Mothername", encrypt(ui->Student_Mothername->text()));
        updateQuery.bindValue(":MotherPhone", encrypt(ui->Student_MotherPhone->text()));
        updateQuery.bindValue(":MotherOccu", encrypt(ui->Student_motheroccupation->text()));
        updateQuery.bindValue(":Guardianname", encrypt(ui->Student_GuardianName->text()));
        updateQuery.bindValue(":GuardianPhone", encrypt(ui->Student_guardianphone->text()));
        updateQuery.bindValue(":GuardianOccu", encrypt(ui->Student_guardianoccupation->text()));
        updateQuery.bindValue(":StudentPhone", encrypt(ui->Student_phone->text()));
        updateQuery.bindValue(":Registration", encrypt(ui->registrationNumber->text()));
        updateQuery.bindValue(":image",filename);
        // int student_reg = ui->registrationNumber->text();


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

        //qDebug() << filename;

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
        query.exec("SELECT * FROM Report_I");
        query.first();
        registration_num = ui->registrationNumber->text(); //registration number to write on report card which is extern variable
        QString firstName = ui->student_frstname->text();
        QString lastName = ui ->Student_midname->text();
        QString midName = ui ->Student_midname ->text();
        QString fullName = firstName + " " + midName + " " + lastName; //Student full name concatenated to write to databse of result
        QString course = ui->Student_Course->text();
        query.exec("INSERT INTO Report_I (RegistrationNumber, StudentName, Grade) VALUES('"+registration_num+"', '"+fullName+"', '"+course+"') ");
        //Insert into registration_num to set result according to registration
        // query.exec("")

        areport = new AcademicReport;
        areport -> showMaximized();


    }
}


void add_Student::on_chooseImage_clicked()
{
    filename = QFileDialog::getOpenFileName(this,tr("Choose Image"),"",tr("Images(*.png *.jpg *.jpeg)"));//store tha path of image that has been browsed
    if (QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            image = image.scaledToWidth(ui->Student_photo->width(), Qt::SmoothTransformation);
            ui->Student_photo->setPixmap(QPixmap::fromImage(image));

        }

    }
}







void add_Student::on_addmore_clicked()
{
    ui->Student_Course->clear();
    ui->Student_Description->clear();
    ui->Student_FatherOccupation->clear();
    ui->Student_GuardianName->clear();
    ui->Student_MotherPhone->clear();
    ui->Student_Mothername->clear();
    ui->Student_TemporaryAdd->clear();
    ui->Student_email->clear();
    ui->Student_enrolledeyear->clear();
    ui->Student_fathername->clear();
    ui->Student_fatherphone->clear();
    ui->Student_guardianoccupation->clear();
    ui->Student_guardianphone->clear();
    ui->Student_lastname->clear();
    ui->Student_midname->clear();
    ui->Student_motheroccupation->clear();
    ui->Student_permanentAdd->clear();
    ui->Student_phone->clear();
    ui->registrationNumber->clear();
    ui->Student_photo->setPixmap(QPixmap(":/img/na.jpg") );

}

void add_Student::on_panel_clicked() //When Back is Clicked
{
    hide();
    QWidget *test = new StaffPanel;
    test-> showMaximized();
}
