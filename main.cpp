#include "mcalib.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include<QPainter>
#include <QPrinter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *Mlogo=new QSplashScreen;
    Mlogo->setPixmap(QPixmap(":/new/logo/mcalib.png"));
    Mlogo->show();

    MCALIB w;

    QTimer::singleShot(2500,Mlogo,SLOT(close()));
    QTimer::singleShot(2500,&w ,SLOT(show()));


   // w.show();

    return a.exec();
}
