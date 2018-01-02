#ifndef VIEWSTFRECORD_H
#define VIEWSTFRECORD_H

#include <QMainWindow>
#include <QtSql>
#include <QRadioButton>
#include<QCoreApplication>
#include <QSqlTableModel>

namespace Ui {
class viewstfrecord;
}

class viewstfrecord : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewstfrecord(QWidget *parent = 0);
    ~viewstfrecord();

private slots:
    void on_Next_clicked();

    void on_Previous_clicked();

    void on_Back_clicked();

    void on_Search_clicked();

private:
    Ui::viewstfrecord *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();
    bool newrecord;
    QString encrypt(QString);
    QString decrypt(QString);
};

#endif // VIEWSTFRECORD_H
