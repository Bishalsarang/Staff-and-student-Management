#include "viewstftable.h"
#include "ui_viewstftable.h"
#include "cao_panel.h"

viewstftable::viewstftable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewstftable)
{
    ui->setupUi(this);
    staff_id = 0;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");

    if(!db.open()){
        qDebug() << db.lastError().text();
    }

    // ui->tableWidget->hideColumn(0);
    FillTable();
}

void viewstftable::FillTable(){



    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Staff")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, Email, StaffPhone, Position, Salary, Qualification1, Qualification2, Qualification3, Qualification4, Qualification5, Description FROM Staff ORDER BY Id"))
        qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 17; ++c){
            if ( c == 6) { //We have used 1,2,3 for sex So
                switch(q.value(c).toInt())
                {
                case 1:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Male"));
                    break;
                case 2:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Female"));
                    break;
                case 3:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));
                    break;
                default:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));

                }
            }
            else
                ui->tableWidget->setItem(r,c, new QTableWidgetItem(decrypt(q.value(c).toString())));
        }
    }
    //Making Text Field in Table read Only
    ui -> tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );






}
QString viewstftable::encrypt(QString input)
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
QString viewstftable::decrypt(QString encrypted)
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
viewstftable::~viewstftable()
{
    delete ui;
    db.close();
}



void viewstftable::on_Back_clicked()
{
    hide();
    QWidget *cpanel = new Cao_panel;
    cpanel-> showMaximized();
}

void viewstftable::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        staff_id = index.data().toInt();
        qDebug() << staff_id;
    }
    vstaff = new viewstfrecord;
    vstaff-> show();
}

void viewstftable::on_Search_clicked()
{
    //searchBox,sortBy
    QString keyword = ui->searchBox->text();
    qDebug() << keyword;
    QString sortValue =  ui->sortBy->currentText();
    qDebug() << sortValue;
    //keyword = QString::toupper(keyword);
    keyword =keyword.toUpper();
    keyword = encrypt(keyword);
    if (sortValue == "firstname" )
    {
        searchbyFirstName(keyword);

    }
    else if(sortValue == "lastname")
    {
        searchbyLastName(keyword);
    }
    else if(sortValue == "position")
    {
        searchByPosition(keyword);
    }
    else if(sortValue == "email")
    {
        searchbyEmail(keyword);
    }
    else if(sortValue == "phone")
    {
        searchbyPhone(keyword);

    }
}


void viewstftable::searchbyFirstName(QString find)
{

    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Firstname) = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, Email, StaffPhone, Position, Salary, Qualification1, Qualification2, Qualification3, Qualification4, Qualification5, Description FROM Staff WHERE upper(Firstname) = '"+find+"' ORDER BY Id")) qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            if ( c == 6) { //We have used 1,2,3 for sex So
                switch(q.value(c).toInt())
                {
                case 1:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Male"));
                    break;
                case 2:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Female"));
                    break;
                case 3:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));
                    break;
                default:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));

                }
            }
            else
                ui->tableWidget->setItem(r,c, new QTableWidgetItem(decrypt(q.value(c).toString())));
        }
    }
    //Making Text Field in Table read Only
    ui -> tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
}
void viewstftable::searchbyLastName(QString find)
{
    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Lastname) = '"+find+"'"))
        qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, Email, StaffPhone, Position, Salary, Qualification1, Qualification2, Qualification3, Qualification4, Qualification5, Description FROM Staff WHERE upper(Lastname) = '"+find+"' ORDER BY Id"))
        qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            if ( c == 6) { //We have used 1,2,3 for sex So
                switch(q.value(c).toInt())
                {
                case 1:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Male"));
                    break;
                case 2:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Female"));
                    break;
                case 3:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));
                    break;
                default:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));

                }
            }
            else
                ui->tableWidget->setItem(r,c, new QTableWidgetItem(decrypt(q.value(c).toString())));
        }
    }
    //Making Text Field in Table read Only
    ui -> tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );

}

void viewstftable::searchbyEmail(QString find)
{
    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Email) = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, Email, StaffPhone, Position, Salary, Qualification1, Qualification2, Qualification3, Qualification4, Qualification5, Description FROM Staff WHERE upper(Email) = '"+find+"' ORDER BY Id"))
        qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            if ( c == 6) { //We have used 1,2,3 for sex So
                switch(q.value(c).toInt())
                {
                case 1:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Male"));
                    break;
                case 2:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Female"));
                    break;
                case 3:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));
                    break;
                default:
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));

                }
            }
            else
                ui->tableWidget->setItem(r,c, new QTableWidgetItem(decrypt(q.value(c).toString())));
        }
    }
    //Making Text Field in Table read Only
    ui -> tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
}

void viewstftable::searchbyPhone(QString find)
{
    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(StaffPhone) = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, Email, StaffPhone, Position, Salary, Qualification1, Qualification2, Qualification3, Qualification4, Qualification5, Description FROM Staff WHERE upper(StaffPhone) = '"+find+"' ORDER BY Id"))
        qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            for(c = 0; c < 15; ++c){
                //qDebug() << query.value(c) << " " << c << endl;
                if ( c == 6) { //We have used 1,2,3 for sex So
                    switch(q.value(c).toInt())
                    {
                    case 1:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Male"));
                        break;
                    case 2:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Female"));
                        break;
                    case 3:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));
                        break;
                    default:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));

                    }
                }
                else
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem(decrypt(q.value(c).toString())));
            }
        }
    }
    //Making Text Field in Table read Only
    ui -> tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
}

void viewstftable::searchByPosition(QString find)
{
    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Staff WHERE upper(Position) = '"+find+"'"))
        qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, Email, StaffPhone, Position, Salary, Qualification1, Qualification2, Qualification3, Qualification4, Qualification5, Description FROM Staff WHERE upper(Position) = '"+find+"' ORDER BY Id"))
        qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            for(c = 0; c < 15; ++c){
                //qDebug() << query.value(c) << " " << c << endl;
                if ( c == 6) { //We have used 1,2,3 for sex So
                    switch(q.value(c).toInt())
                    {
                    case 1:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Male"));
                        break;
                    case 2:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Female"));
                        break;
                    case 3:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));
                        break;
                    default:
                        ui->tableWidget->setItem(r,c, new QTableWidgetItem("Others"));

                    }
                }
                else
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem(decrypt(q.value(c).toString())));
            }

        }
    }
    //Making Text Field in Table read Only
    ui -> tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
}
