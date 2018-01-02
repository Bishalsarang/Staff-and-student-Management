#include "firstconfigure.h"
#include "ui_firstconfigure.h"
#include<QRegExpValidator>
#include <QString>
#include <QFile>
#include <QtDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QMessageBox>



firstconfigure::firstconfigure(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::firstconfigure)
{
    ui->setupUi(this);


    //write to database()
    //Database Connection

    configdb = QSqlDatabase::addDatabase("QSQLITE");
    configdb.setDatabaseName("data.sqlite3");
    configdb.open();

    // set a "cursor"
    query = QSqlQuery(configdb);
    query.exec("SELECT * FROM users");

    if (query.isActive()){
        qDebug()<<"Connection Successful";


    }else{
        qDebug()<< "Database connection:Error";
    }
}

firstconfigure::~firstconfigure()
{
    delete ui;
    configdb.close();
}

void firstconfigure::on_pushButton_clicked()
{

    QSqlQuery updateQuery = QSqlQuery(configdb);
    QString insName = ui->institutionname->text();
    QString insAddress = ui ->institutionaddress->text();
if(insName.size() != 0 && insAddress != 0 )

  {  if(ui->CAO->isChecked())
        //When CAO is choosen writes access = true for CAO
        //Everytime the Sofware runs then it opens up as CAO
    {

        updateQuery.exec("UPDATE users SET  access = 1,institution_name = '" + insName + "', institution_address ='"+insAddress+"' WHERE user = 'CAO'");
        //qDebug() << "CAO";
    }
    else if(ui->Staff->isChecked())
        //When CAO is choosen writes access = true for staff
        //Everytime the Sofware runs then it opens up as staff
    {
        updateQuery.exec("UPDATE users SET  access = 1,institution_name = '" + insName + "', institution_address ='"+insAddress+"' WHERE user = 'staff'");
        // qDebug() << " OPen Staff";
    }



    if(!updateQuery.exec())
        qDebug() << updateQuery.lastError().text();
    else
        qDebug() << "Updated config file";
    hide();
    setfirst = new Setfirstpassword;
    setfirst -> show();

}
else
{

    QMessageBox msgBox;





        msgBox.setText("Please fill up the information");
        msgBox.exec();

}





}
