#include "viewresult.h"
#include "ui_viewresult.h"
QString v_registration_num;
viewresult::viewresult(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewresult)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"
    query = QSqlQuery(db);
    query.exec("SELECT * FROM Report_I WHERE REgistrationNumber = '"+v_registration_num+"' ");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();
        FillForm();
    }else{
        qDebug()<< "Database connection:Error";
    }
}

viewresult::~viewresult()
{
    delete ui;
    db.close();
}

void viewresult::FillForm()
{
 ui->RollNo->setText(query.value(3).toString());


     ui->AbsentDays->setText(query.value(4).toString());
    ui->PresentDays->setText(query.value(5).toString());
    ui->Totaldays->setText(query.value(6).toString());

   ui->MathCredit->setText(query.value(7).toString());
 ui->MathGrade->setText(query.value(8).toString());
    ui->MathGradeII->setText(query.value(9).toString());
    ui->MathGradeIII->setText(query.value(10).toString());
    ui->MathRemarks->setText(query.value(11).toString());

 ui->PhysicsCredit->setText(query.value(12).toString());
 ui->PhysicsGrade->setText(query.value(13).toString());
 ui->PhysicsGradeII->setText(query.value(14).toString());
 ui->PhysicsGradeIII->setText(query.value(15).toString());
ui->PhysicsRemarks->setText(query.value(16).toString());


   ui->ChemistryCredit->setText(query.value(17).toString());
ui->ChemistryGrade->setText(query.value(18).toString());
 ui->ChemistryGradeII->setText(query.value(19).toString());
 ui->ChemistryGradeIII->setText(query.value(20).toString());
ui->ChemistryRemarks->setText(query.value(21).toString());

ui->BiologyCredit->setText(query.value(22).toString());
 ui->BiologyGrade->setText(query.value(23).toString());
ui->BiologyGradeII->setText(query.value(24).toString());
 ui->BiologyGradeIII->setText(query.value(25).toString());
ui->BiologyRemarks->setText(query.value(26).toString());

   ui->EnglishCredit->setText(query.value(27).toString());
 ui->EnglishGrade->setText(query.value(28).toString());
ui->EnglishGradeII->setText(query.value(29).toString());
 ui->EnglishGradeIII->setText(query.value(30).toString());
ui->EnglishRemarks->setText(query.value(31).toString());

     ui->ComputerCredit->setText(query.value(32).toString());
 ui->ComputerGrade->setText(query.value(32).toString());
     ui->ComputerGradeII->setText(query.value(34).toString());
ui->ComputerGradeIII->setText(query.value(35).toString());
  ui->ComputerRemarks->setText(query.value(36).toString());

    ui->GPA->setText(query.value(37).toString());
  ui->IssueDate->setText(query.value(38).toString());
     ui->TotalCredit->setText(query.value(39).toString());
 ui->TotalGradePoint->setText(query.value(40).toString());

    ui->AssignmentRegularity->setText(query.value(42).toString());
 ui->ReadingSpeaking->setText(query.value(43).toString());
     ui->Attentiveness->setText(query.value(44).toString());
 ui->StationaryMaintenance->setText(query.value(45).toString());




ui->Discipline->setText(query.value(46).toString());
     ui->Elocution->setText(query.value(47).toString());
  ui->ECA->setText(query.value(48).toString());
   ui->Initiative->setText(query.value(49).toString());
   ui->Neatness->setText(query.value(50).toString());
     ui->Creativity->setText(query.value(51).toString());

     ui->Remarks->setText(query.value(52).toString());

ui->Grade->setText(query.value(53).toString());
 ui->ClassroomParticipation->setText(query.value(41).toString());



 qDebug() << "Registration num for viewing" << v_registration_num;

}

void viewresult::on_pushButton_clicked()//modify
{
    QSqlQuery updateQuery = QSqlQuery(db);
qDebug() << "Registration num for modifying" << v_registration_num;
    if(!updateQuery.exec("SELECT * FROM Report_I WHERE RegistrationNumber = '"+v_registration_num+"'")) qDebug() << "Vakai Xaina";
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

                        " WHERE RegistrationNumber = '"+v_registration_num+"'");

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




FillForm();





}
