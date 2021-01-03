#include <QApplication>
#include "Headers/Game.h"
#include "Headers/Menu.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Other/Resources/Other/icon.png"));

    Menu m;
    m.show();

    return a.exec();
}
