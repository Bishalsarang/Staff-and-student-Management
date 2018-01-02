#ifndef ACADEMICREPORT_H
#define ACADEMICREPORT_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>

namespace Ui {
class AcademicReport;
}

class AcademicReport : public QMainWindow
{
    Q_OBJECT

public:
    explicit AcademicReport(QWidget *parent = 0);
    ~AcademicReport();

private slots:
    void on_pushButton_clicked();


private:
    Ui::AcademicReport *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();

};

#endif // ACADEMICREPORT_H
