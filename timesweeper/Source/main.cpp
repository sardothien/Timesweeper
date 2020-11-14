#include "Headers/TimesweeperMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimesweeperMainWindow w;
    w.show();
    return a.exec();
}
