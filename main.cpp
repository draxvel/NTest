#include "mainwindow.h"
#include "login.h"
#include "finish.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login l;
    MainWindow w;
    l.show();

    QObject::connect(&l, SIGNAL(loginDone()), &w, SLOT(show()));
    QObject::connect(&l, SIGNAL(passNameSurname(QString)), &w, SLOT(getNameSurname(QString)));

    return a.exec();
}
