#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen> //to use splash
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/new/images/Images/welcome.jpg")); // splash picture

    splash->show();

    MainWindow w;
   w.showMaximized();
     QTimer::singleShot(3000, splash,SLOT(close())); // Timer


     return a.exec();
}
