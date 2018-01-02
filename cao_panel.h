#ifndef CAO_PANEL_H
#define CAO_PANEL_H

#include <QMainWindow>
#include "addstaff.h"
#include "viewstfrecord.h"
#include "viewstftable.h"
#include "modifystaff.h"
#include "deletestaff.h"
#include "changepassword.h"
#include "about.h"
#include "about.h"
namespace Ui {
class Cao_panel;
}

class Cao_panel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cao_panel(QWidget *parent = 0);
    ~Cao_panel();

private slots:
    void on_pushButton_addstaff_clicked();

    void on_pushButton_modifystaff_clicked();

    void on_pushButton_viewstaff_clicked();



    void on_pushButton_deletestaff_clicked();

    void on_pushButton_exitstaff_clicked();

    void on_pushButton_changepasswordstaff_clicked();

    void on_pushButton_clicked();

    void on_viewstafftable_clicked();


    void on_pushButton_19_clicked();

private:
    Ui::Cao_panel *ui;
    addStaff *astaff;
    viewstfrecord *viewstaff;
    viewstftable *vstafftable;
    modifyStaff *modStaff;
    deleteStaff *delStaff;
    changepassword *change_pass;
      About *abt;
    QSqlQuery query;
       QSqlDatabase db;
    About *abt_us;
};

#endif // CAO_PANEL_H
