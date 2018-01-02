#ifndef DELETESTUDENT_H
#define DELETESTUDENT_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class deleteStudent;
}

class deleteStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit deleteStudent(QWidget *parent = 0);
    ~deleteStudent();

private slots:
    void on_delete_2_clicked();

    void on_Previous_clicked();

    void on_Next_clicked();

    void on_Back_clicked();

    void on_Search_clicked();

private:
    Ui::deleteStudent *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();
    QString keyword;
    QString sortValue;
    QString encrypt(QString);
    QString decrypt(QString);
};

#endif // DELETESTUDENT_H
