#include "modifystaff.h"
#include "ui_modifystaff.h"
#include "cao_panel.h"
#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
QString staff_image;
modifyStaff::modifyStaff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modifyStaff)
{
    ui->setupUi(this);
    //QString sid = QString::number(staff_id); //converting int to string
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");
    db.open();

    // set a "cursor"


    query = QSqlQuery(db);
    query.exec("SELECT * FROM Staff");

    if (query.isActive()){
        qDebug()<<"Connection Successful";
        query.first();
        FillForm();
    }else{
        qDebug()<< "Database connection:Error";
    }

}

QString modifyStaff::decrypt(QString encrypted)
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
QString modifyStaff::encrypt(QString input)
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
void modifyStaff::FillForm()
{
    //Staff General Information

    ui->Sfrstname->setText(decrypt(query.value(1).toString()));
    ui->Smidname->setText(decrypt(query.value(2).toString()));
    ui->Slastname->setText(decrypt(query.value(3).toString()));
    ui->Sposition->setText(decrypt(query.value(9).toString()));
    ui->StaffDescription->setText(decrypt(query.value(8).toString()));
    ui->Semail->setText(decrypt(query.value(6).toString()));
    ui->Ssalary->setText(decrypt(query.value(10).toString()));
    ui->Sphone->setText(decrypt(query.value(11).toString()));


    int sex = query.value(17).toInt(); //sex column is in 21
    switch(sex) // 1 is for male,2 for female and 3 for others
    {
    case 1:
        //male
        //qDebug() << "MAle";
        ui->sMale->setChecked(true);
        break;
    case 2:
        //female
        //qDebug() << "female";
        ui->sFemale->setChecked(true);
        break;
    case 3:
        //Others
        qDebug() << "Others";
        ui->sothers->setChecked(true);
        break;
    default:
        qDebug() << "Not in DB";
    }

    //Staff Qualification

    ui->Qualification1->setText(decrypt(query.value(7).toString()));
    ui->Qualification2->setText(decrypt(query.value(12).toString()));
    ui->Qualification3->setText(decrypt(query.value(13).toString()));
    ui->Qualification4->setText(decrypt(query.value(14).toString()));
    ui->Qualification5->setText(decrypt(query.value(15).toString()));


    //Staff's Address

    ui->Spaddress->setText(decrypt(query.value(4).toString()));
    ui->Staddress->setText(decrypt(query.value(5).toString()));
    //Loading image of student
    QString staff_image = query.value(16).toString(); ///Path of the image
    //  qDebug() << staff_image;
    QImage photo;
    bool valid = photo.load(staff_image);
    if(valid)
    {
        photo = photo.scaledToWidth(ui->pic->width(), Qt::SmoothTransformation);
        ui->pic->setPixmap(QPixmap::fromImage(photo));

    }
}

modifyStaff::~modifyStaff()
{
    delete ui;
    db.close();
}

void modifyStaff::on_Next_clicked()
{
    if(!query.next())
        query.first();
    FillForm();
}

void modifyStaff::on_Search_clicked()
{
    QString keyword = ui->searchBox->text();
    qDebug() << keyword;
    QString sortValue =  ui->sortBy->currentText();
    qDebug() << sortValue;
    //keyword = QString::toupper(keyword);
    keyword =keyword.toUpper();
    keyword = encrypt(keyword);

    query = QSqlQuery(db);
    if (sortValue == "firstname" )
    {

        int num_rows;


        //get the number of rows
        if(!query.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Firstname) = '"+keyword+"'")) qDebug() << query.lastError().text();
        //query.first();
        query.first();
        num_rows = query.value(0).toInt();


        QMessageBox msgBox;
        QString text= "Number of records found is:" + QString::number(num_rows);

        msgBox.setText(text);
        msgBox.exec();

        if(!query.exec("SELECT * FROM Staff WHERE upper(Firstname) = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
        query.first();
        FillForm();


    }
    else if(sortValue == "email")
    {
        int num_rows;


        //get the number of rows
        if(!query.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Email) = '"+keyword+"'")) qDebug() << query.lastError().text();
        //query.first();
        query.first();
        num_rows = query.value(0).toInt();


        QMessageBox msgBox;
        QString text= "Number of records found is:" + QString::number(num_rows);

        msgBox.setText(text);
        msgBox.exec();

        if(!query.exec("SELECT * FROM Staff WHERE upper(Email) = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
        query.first();
        FillForm();
    }
    else if(sortValue == "phone")
    {
        int num_rows;


        //get the number of rows
        if(!query.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(StaffPhone) = '"+keyword+"'")) qDebug() << query.lastError().text();
        //query.first();
        query.first();
        num_rows = query.value(0).toInt();


        QMessageBox msgBox;
        QString text= "Number of records found is:" + QString::number(num_rows);

        msgBox.setText(text);
        msgBox.exec();

        if(!query.exec("SELECT * FROM Staff WHERE upper(StaffPhone) = '"+keyword+"' ORDER BY Id")) qDebug() << query.lastError().text();
        query.first();
        FillForm();
    }
    else if(sortValue == "position")
    {
        int num_rows;


        //get the number of rows
        if(!query.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Position) = '"+keyword+"'"))
            qDebug() << query.lastError().text();
        //query.first();
        query.first();
        num_rows = query.value(0).toInt();


        QMessageBox msgBox;
        QString text= "Number of records found is:" + QString::number(num_rows);

        msgBox.setText(text);
        msgBox.exec();

        if(!query.exec("SELECT * FROM Staff WHERE upper(Position) = '"+keyword+"' ORDER BY Id"))
            qDebug() << query.lastError().text();
        query.first();
        FillForm();
    }
    else if(sortValue == "lastname")
    {
        int num_rows;


        //get the number of rows
        if(!query.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Lastname) = '"+keyword+"'"))
            qDebug() << query.lastError().text();
        //query.first();
        query.first();
        num_rows = query.value(0).toInt();


        QMessageBox msgBox;
        QString text= "Number of records found is:" + QString::number(num_rows);

        msgBox.setText(text);
        msgBox.exec();

        if(!query.exec("SELECT * FROM Staff WHERE upper(Lastname) = '"+keyword+"' ORDER BY Id"))
            qDebug() << query.lastError().text();
        query.first();
        FillForm();

    }
}



void modifyStaff::on_Previous_clicked()
{
    if (!query.previous())
        query.last();
    FillForm();
}

void modifyStaff::on_Back_clicked()
{
    hide();
    QWidget *panel = new Cao_panel;
    panel-> show();
}

void modifyStaff::on_modify_clicked()
{
    // Updating Records of the Staffs
    if (ui->Sfrstname->text().trimmed() == ""){
        ui->statusbar->showMessage("Staff Name is Compulsory!");
    }else{

        QSqlQuery updateQuery = QSqlQuery(db);

        updateQuery.prepare("UPDATE Staff SET Firstname = :Firstname, Middlename = :Middlename, Lastname = :Lastname, PermanentAdd = :PermanentAdd,"
                            " Email = :Email, Position = :Position,"
                            " Salary = :Salary, Description = :Description, StaffPhone = :StaffPhone,"
                            " Qualification1 = :Qualification1, Qualification2 = :Qualification2, Qualification3 = :Qualification3,"
                            " Qualification4 = :Qualification4, Qualification5 = :Qualification5, image = :image, sex = :sex"
                            " WHERE Id = :Id");




        //Updating Staff Information
        //Bind Values

        updateQuery.bindValue(":Id", query.value(0).toInt());
        updateQuery.bindValue(":Firstname", encrypt(ui->Sfrstname->text()));
        updateQuery.bindValue(":Middlename", encrypt(ui->Smidname->text()));
        updateQuery.bindValue(":Lastname", encrypt(ui->Slastname->text()));
        updateQuery.bindValue(":PermanentAdd", encrypt(ui->Spaddress->text()));
        updateQuery.bindValue(":TemporaryAdd", encrypt(ui->Staddress->text()));
        updateQuery.bindValue(":Email", encrypt(ui->Semail->text()));
        updateQuery.bindValue(":Position", encrypt(ui->Sposition->text()));
        updateQuery.bindValue(":Description", encrypt(ui->StaffDescription->toPlainText()));
        updateQuery.bindValue(":Salary", encrypt(ui->Ssalary->text()));
        updateQuery.bindValue(":StaffPhone", encrypt(ui->Sphone->text()));
        updateQuery.bindValue(":image", staff_image);
        // updateQuery.bindValue(":sex", staff_image);
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



        if(!updateQuery.exec())
            ui->statusbar->showMessage(QString("Error while Updating[Please Try again later]") + updateQuery.lastError().text());
        else
            ui->statusbar->showMessage("Successfully Updated");

        if(sortValue == "firstname" )
        {
            if(!query.exec("SELECT * FROM Staff WHERE upper(Firstname) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();

        }
        else if (sortValue == "lastname")
        {
            if(!query.exec("SELECT * FROM Staff WHERE upper(Lastname) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();
        }
        else if(sortValue == "email")
        {
            if(!query.exec("SELECT * FROM Staff WHERE upper(Email) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();
        }

        else if(sortValue == "phone")
        {
            if(!query.exec("SELECT * FROM Student WHERE upper(StaffPhone) = '"+keyword+"' ORDER BY Id"))
                qDebug() << query.lastError().text();
        }

        query.first();

        FillForm();
    }
}

void modifyStaff::on_pushButton_clicked()
{
    // qDebug() << filename;
    staff_image = QFileDialog::getOpenFileName(this,tr("Choose Image"),"",tr("Images(*.png *.jpg *.jpeg)"));
    if (QString::compare(staff_image, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(staff_image);
        if(valid)
        {
            image = image.scaledToWidth(ui->pic->width(), Qt::SmoothTransformation);
            ui->pic->setPixmap(QPixmap::fromImage(image));

        }

    }
}
