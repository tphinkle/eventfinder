#include "mainwindow.h"
#include "columnselect_dialogue.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication Qapp(argc, argv);

    MainWindow w;

    w.show();

    return Qapp.exec();

}
