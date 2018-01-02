#include "academicreport.h"
#include "ui_academicreport.h"
#include<QRegExpValidator>
#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
#include "add_student.h"

QString registration_num;
AcademicReport::AcademicReport(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AcademicReport)
{
    ui->setupUi(this);
    //QString registration_num;
   // qDebug() << "This is vale of reg in academic" << registration_num;
    //Database Connection

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    query = QSqlQuery(db);
    query.exec("SELECT * FROM Report_I");

    if (query.isActive()){
        qDebug()<<"Co//nnection Successful";
        query.first();
        FillForm();
    }else{
        qDebug()<< "Database connection:Error";
    }


}


void AcademicReport::FillForm()
{
    //Name And Address Of the Institution as saved in databse
    if(!query.exec("SELECT institution_name, institution_address  FROM users WHERE access = 1")) qDebug() << "Error while Extracting name and address";
    query.first();
    ui->inst_name->setText(query.value(0).toString());
    ui->inst_address->setText(query.value(1).toString());


    query.exec("SELECT RegistrationNumber, StudentName, Grade FROM Report_I WHERE RegistrationNumber = '"+registration_num+"'");
    query.first();

    //Genaral Information

    ui->Grade->setText(query.value(2).toString());
    ui->Redgno->setText(query.value(0).toString());
    ui->StudentName->setText(query.value(1).toString());

    query.exec("SELECT * FROM Report_I WHERE RegistrationNumber = '"+registration_num+"'");
    query.first();

}

AcademicReport::~AcademicReport()
{
    delete ui;
    db.close();
}



void AcademicReport::on_pushButton_clicked()
{

    QSqlQuery updateQuery = QSqlQuery(db);

    if(!updateQuery.exec("SELECT * FROM Report_I WHERE RegistrationNumber = '"+registration_num+"'")) qDebug() << "Vakai Xaina";
    updateQuery.first();
    updateQuery.prepare("UPDATE Report_I SET RollNo = :RollNo,"
                        " PresentDays = :PresentDays,"
                        " TotalDays = :TotalDays,"

                        " MathCredit = :MathCredit, MathGrade = :MathGrade, MathGradeII = :MathGradeII, MathGradeIII = :MathGradeIII, MathRemarks = :MathRemarks,"

                        " PhysicsCredit = :PhysicsCredit, PhysicsGrade = :PhysicsGrade, PhysicsGradeII = :PhysicsGradeII, PhysicsGradeIII = :PhysicsGradeIII, PhysicsRemarks = :PhysicsRemarks,"
                        " ChemistryCredit = :ChemistryCredit, ChemistryGrade = :ChemistryGrade, ChemistryGradeII = :ChemistryGradeII, ChemistryGradeIII = :ChemistryGradeIII, ChemistryRemarks = :ChemistryRemarks,"
                        " BiologyCredit = :BiologyCredit, BiologyGrade = :BiologyGrade, BiologyGradeII = :BiologyGradeII, BiologyGradeIII = :BiologyGradeIII, BiologyRemarks = :BiologyRemarks,"
                        " EnglishCredit = :EnglishCredit, EnglishGrade = :EnglishGrade, EnglishGradeII = :EnglishGradeII, EnglishGradeIII = :EnglishGradeIII, EnglishRemarks = :EnglishRemarks,"
                        "GPA = :GPA,"
                        "IssueDate = :IssueDate,"
                        "TotalCredit = :TotalCredit,"
                        "TotalGradePoint = :TotalGradePoint,"

                        "AssignmentRegularity = :AssignmentRegularity,"
                        "ReadingSpeaking = :ReadingSpeaking,"
                        "Attentiveness = :Attentiveness,"

                        "StationaryMaintenance = :StationaryMaintenance,"
                        "Discipline = :Discipline,"
                        "Elocution = :Elocution,"
                        "ECA = :ECA,"
                        "Initiative = :Initiative,"
                        "Neatness = :Neatness,"
                        "Creativity = :Creativity,"
                        "Remarks = :Remarks,"
                        "Grade = :Grade,"
                        "ClassroomParticipation = :ClassroomParticipation,"
                        " ComputerCredit = :ComputerCredit, ComputerGrade = :ComputerGrade, ComputerGradeII = :ComputerGradeII, ComputerGradeIII = :ComputerGradeIII, ComputerRemarks = :ComputerRemarks,"
                        " AbsentDays = :AbsentDays, Id = :Id"

                        " WHERE RegistrationNumber = '"+registration_num+"'");

    //Updating  Information on Academic Report
    //Bind Values
    updateQuery.bindValue(":Id", query.value(0));




    updateQuery.bindValue(":RollNo", ui->RollNo->text());


    updateQuery.bindValue(":AbsentDays", ui->AbsentDays->text());
    updateQuery.bindValue(":PresentDays", ui->PresentDays->text());
    updateQuery.bindValue(":TotalDays", ui->Totaldays->text());

    updateQuery.bindValue(":MathCredit", ui->MathCredit->text());
    updateQuery.bindValue(":MathGrade", ui->MathGrade->text());
    updateQuery.bindValue(":MathGradeII", ui->MathGradeII->text());
    updateQuery.bindValue(":MathGradeIII", ui->MathGradeIII->text());
    updateQuery.bindValue(":MathRemarks", ui->MathRemarks->text());

    updateQuery.bindValue(":PhysicsCredit", ui->PhysicsCredit->text());
    updateQuery.bindValue(":PhysicsGrade", ui->PhysicsGrade->text());
    updateQuery.bindValue(":PhysicsGradeII", ui->PhysicsGradeII->text());
    updateQuery.bindValue(":PhysicsGradeIII", ui->PhysicsGradeIII->text());
    updateQuery.bindValue(":PhysicsRemarks", ui->PhysicsRemarks->text());


    updateQuery.bindValue(":ChemistryCredit", ui->ChemistryCredit->text());
    updateQuery.bindValue(":ChemistryGrade", ui->ChemistryGrade->text());
    updateQuery.bindValue(":ChemistryGradeII", ui->ChemistryGradeII->text());
    updateQuery.bindValue(":ChemistryGradeIII", ui->ChemistryGradeIII->text());
    updateQuery.bindValue(":ChemistryRemarks", ui->ChemistryRemarks->text());

    updateQuery.bindValue(":BiologyCredit", ui->BiologyCredit->text());
    updateQuery.bindValue(":BiologyGrade", ui->BiologyGrade->text());
    updateQuery.bindValue(":BiologyGradeII", ui->BiologyGradeII->text());
    updateQuery.bindValue(":BiologyGradeIII", ui->BiologyGradeIII->text());
    updateQuery.bindValue(":BiologyRemarks", ui->BiologyRemarks->text());

    updateQuery.bindValue(":EnglishCredit", ui->EnglishCredit->text());
    updateQuery.bindValue(":EnglishGrade", ui->EnglishGrade->text());
    updateQuery.bindValue(":EnglishGradeII", ui->EnglishGradeII->text());
    updateQuery.bindValue(":EnglishGradeIII", ui->EnglishGradeIII->text());
    updateQuery.bindValue(":EnglishRemarks", ui->EnglishRemarks->text());

    updateQuery.bindValue(":ComputerCredit", ui->ComputerCredit->text());
    updateQuery.bindValue(":ComputerGrade", ui->ComputerGrade->text());
    updateQuery.bindValue(":ComputerGradeII", ui->ComputerGradeII->text());
    updateQuery.bindValue(":ComputerGradeIII", ui->ComputerGradeIII->text());
    updateQuery.bindValue(":ComputerRemarks", ui->ComputerRemarks->text());

    updateQuery.bindValue(":GPA", ui->GPA->text());
    updateQuery.bindValue(":IssueDate", ui->IssueDate->text());
    updateQuery.bindValue(":TotalCredit", ui->TotalCredit->text());
    updateQuery.bindValue(":TotalGradePoint", ui->TotalGradePoint->text());

    updateQuery.bindValue(":AssignmentRegularity", ui->AssignmentRegularity->text());
    updateQuery.bindValue(":ReadingSpeaking", ui->ReadingSpeaking->text());
    updateQuery.bindValue(":Attentiveness", ui->Attentiveness->text());
    updateQuery.bindValue(":StationaryMaintenance", ui->StationaryMaintenance->text());




    updateQuery.bindValue(":Discipline", ui->Discipline->text());
    updateQuery.bindValue(":Elocution", ui->Elocution->text());
    updateQuery.bindValue(":ECA", ui->ECA->text());
    updateQuery.bindValue(":Initiative", ui->Initiative->text());
    updateQuery.bindValue(":Neatness", ui->Neatness->text());
    updateQuery.bindValue(":Creativity", ui->Creativity->text());

    updateQuery.bindValue(":Remarks", ui->Remarks->toPlainText());

    updateQuery.bindValue(":Grade", ui->Grade->text());

    updateQuery.bindValue(":ClassroomParticipation", ui->ClassroomParticipation->text());









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



}
