#include <QApplication>
#include "Headers/Game.h"
#include "Headers/Menu.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Menu m;
    m.show();

    return a.exec();
}
