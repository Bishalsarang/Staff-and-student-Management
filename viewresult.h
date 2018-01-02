#ifndef VIEWRESULT_H
#define VIEWRESULT_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class viewresult;
}

class viewresult : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewresult(QWidget *parent = 0);
    ~viewresult();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewresult *ui;
    QSqlDatabase db;
    QSqlQuery query;
    void FillForm();
    bool newrecord;
    QString encrypt(QString);
    QString decrypt(QString);
};

#endif // VIEWRESULT_H
