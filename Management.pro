#-------------------------------------------------
#
# Project created by QtCreator 2017-06-15T11:43:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Management
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    add_student.cpp \
    addstaff.cpp \
    cao_panel.cpp \
    changepassword.cpp \
    firstconfigure.cpp \
    admin_login.cpp \
    setfirstpassword.cpp \
    staffpanel.cpp \
    staff_login.cpp \
    viewstdrecord.cpp \
    viewstfrecord.cpp \
    viewstdtable.cpp \
    viewstftable.cpp \
    modifystaff.cpp \
    deletestaff.cpp \
    modifystudent.cpp \
    deletestudent.cpp \
    academicreport.cpp \
    about.cpp \
    viewresult.cpp

HEADERS += \
        mainwindow.h \
    add_student.h \
    addstaff.h \
    cao_panel.h \
    changepassword.h \
    firstconfigure.h \
    admin_login.h \
    setfirstpassword.h \
    staffpanel.h \
    staff_login.h \
    viewstdrecord.h \
    viewstfrecord.h \
    viewstdtable.h \
    viewstftable.h \
    modifystaff.h \
    deletestaff.h \
    modifystudent.h \
    deletestudent.h \
    academicreport.h \
    about.h \
    viewresult.h

FORMS += \
        mainwindow.ui \
    add_student.ui \
    addstaff.ui \
    cao_panel.ui \
    changepassword.ui \
    firstconfigure.ui \
    admin_login.ui \
    setfirstpassword.ui \
    staff_login.ui \
    viewstdrecord.ui \
    viewstfrecord.ui \
    viewstdtable.ui \
    viewstftable.ui \
    modifystaff.ui \
    deletestaff.ui \
    modifystudent.ui \
    deletestudent.ui \
    academicreport.ui \
    about.ui \
    viewresult.ui \
    staffpanel.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
