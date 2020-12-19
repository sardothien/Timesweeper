#include "Headers/Help.h"
#include "Headers/Menu.h"
#include "ui_Help.h"

Help::Help(QWidget *parent) : QMainWindow(parent), ui(new Ui::Help)
{
    ui->setupUi(this);
    setFixedSize(800,500);
    setWindowTitle("timesweeper");
}

Help::~Help()
{
    delete ui;
}

void Help::on_backButton_clicked()
{
    Menu *menu = new Menu();
    menu->show();
    this->hide();
}
