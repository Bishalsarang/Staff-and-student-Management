#include "viewstdtable.h"
#include "ui_viewstdtable.h"
#include "staffpanel.h"
#include <QString>

viewstdtable::viewstdtable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewstdtable)
{
    ui->setupUi(this);
    database_id = 0;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.sqlite3");

    if(!db.open()){
        qDebug() << db.lastError().text();
    }

    // ui->tableWidget->hideColumn(0);
    FillTable();
}

viewstdtable::~viewstdtable()
{
    delete ui;
    db.close();
}
QString viewstdtable::decrypt(QString encrypted)
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


void viewstdtable::FillTable(){



    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Student")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Registration, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, EnrolledYear, StudentPhone, Email, Fathername, Mothername, Guardianname FROM Student ORDER BY Id")) qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 16; ++c){
            for(c = 0; c < 15; ++c){
                //qDebug() << query.value(c) << " " << c << endl;
                if ( c == 7) { //We have used 1,2,3 for sex So
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
                    ui->tableWidget->setItem(r,c, new QTableWidgetItem(decrypt(q.value(c).toString())));//value is decrypted and shown using decrypt function
            }
        }
    }
    //Making Text Field in Table read Only
    ui -> tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );






}







void viewstdtable::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        database_id = index.data().toInt();
        qDebug() << database_id;
    }
    viewstd = new viewstdrecord;
    viewstd-> show();

}

void viewstdtable::on_Search_clicked()
{

    //searchBox,sortBy
    QString keyword = ui->searchBox->text();
    qDebug() << keyword;
    QString sortValue =  ui->sortBy->currentText();
    qDebug() << sortValue;
    //keyword = QString::toupper(keyword);
    keyword =keyword.toUpper();
    keyword = encrypt(keyword); //encrypt the find keyword and compare to databse
    if (sortValue == "firstname" )
    {
        //Call sortByfirstname(keyword)
        qDebug() << "TEst first name"<< sortValue;
        sortByfirstname(keyword);

    }
    else if(sortValue == "course")
    {
        searchBycourse(keyword);
    }
    else if(sortValue == "enrolledYear")
    {
        searchByyear(keyword);
    }
    else if(sortValue == "email")
    {
        searchByemail(keyword);
    }
    else if(sortValue == "registration_number")
    {
        searchByReg(keyword);

    }
    else if(sortValue == "GPA")
    {


    }
    // query.exec("SELECT * FROM Student WHERE ")
}

QString viewstdtable::encrypt(QString input)
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

void viewstdtable::sortByfirstname(QString find)
{
    //qDebug() <<"By fname:" << find;

    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Student WHERE upper(Firstname) = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Registration, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, EnrolledYear, Course, StudentPhone, Email, Fathername, Mothername, Guardianname FROM Student WHERE upper(Firstname) = '"+find+"' ORDER BY Id")) qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 16; ++c){
            for(c = 0; c < 15; ++c){
                //qDebug() << query.value(c) << " " << c << endl;
                if ( c == 7) { //We have used 1,2,3 for sex So
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

void viewstdtable::searchByReg(QString find)
{
    qDebug() << find;

    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Student WHERE Registration = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Registration, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, EnrolledYear, Course, StudentPhone, Email, Fathername, Mothername, Guardianname FROM Student WHERE Registration = '"+find+"') ORDER BY Id")) qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 16; ++c){
            for(c = 0; c < 15; ++c){
                //qDebug() << query.value(c) << " " << c << endl;
                if ( c == 7) { //We have used 1,2,3 for sex So
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

void viewstdtable::searchByemail(QString find)
{
    qDebug() << find;

    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Student WHERE upper(Email) = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Registration, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, EnrolledYear, Course, StudentPhone, Email, Fathername, Mothername, Guardianname FROM Student WHERE upper(Email) = '"+find+"') ORDER BY Id")) qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            for(c = 0; c < 15; ++c){
                //qDebug() << query.value(c) << " " << c << endl;
                if ( c == 7) { //We have used 1,2,3 for sex So
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
void viewstdtable::searchBycourse(QString find)
{
    qDebug() <<"By course:" << find;

    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Student WHERE upper(Course) = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id, Registration, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, EnrolledYear, Course, StudentPhone, Email, Fathername, Mothername, Guardianname FROM Student WHERE upper(Course) = '"+find+"' ORDER BY Id")) qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            for(c = 0; c < 15; ++c){
                //qDebug() << query.value(c) << " " << c << endl;
                if ( c == 7) { //We have used 1,2,3 for sex So
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

void viewstdtable::searchByyear(QString find)
{

    int num_rows, r, c;
    QSqlQuery q(db);

    //get the number of rows
    if(!q.exec("SELECT count(Id) as num_rows FROM Student WHERE EnrolledYear = '"+find+"'")) qDebug() << q.lastError().text();
    q.first();
    num_rows = q.value(0).toInt();

    ui->tableWidget->setRowCount(num_rows);

    if(!q.exec("SELECT Id,Registration, Firstname, Middlename, Lastname, PermanentAdd, TemporaryAdd, sex, EnrolledYear, Course, StudentPhone, Email, Fathername, Mothername, Guardianname FROM Student WHERE EnrolledYear = '"+find+"' ORDER BY Id")) qDebug() << q.lastError().text();
    for(r = 0, q.first(); q.isValid(); q.next(), ++r){
        for(c = 0; c < 15; ++c){
            //qDebug() << query.value(c) << " " << c << endl;
            if ( c == 7) { //We have used 1,2,3 for sex So
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

void viewstdtable::on_Back_clicked()
{
    hide();
    QWidget *panel = new StaffPanel;
    panel-> showMaximized();
}

